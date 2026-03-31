"""REST routes for maze operations:
generation, upload, download, and solving."""

import contextlib
import os
import tempfile
from collections.abc import Generator

from fastapi import APIRouter, File, HTTPException, UploadFile
from fastapi.responses import StreamingResponse
from pydantic import BaseModel

from controller.controller import Controller
from models.field import MazeFieldModel


class MazeData(BaseModel):
    """API representation of a maze returned to the client.

    Attributes:
        rows: Number of maze rows.
        cols: Number of maze columns.
        vertical_walls: Vertical wall matrix (1 = wall present, 0 = passage).
        horizontal_walls: Horizontal wall matrix
            (1 = wall present, 0 = passage).
    """

    rows: int
    cols: int
    vertical_walls: list[list[int]]
    horizontal_walls: list[list[int]]


class GenerateRequest(BaseModel):
    """Request body for generating a new maze.

    Attributes:
        rows: Desired number of rows (1 to 50).
        cols: Desired number of columns (1 to 50).
    """

    rows: int
    cols: int


class SolveRequest(BaseModel):
    """Request body for finding a path through the maze.

    Attributes:
        start: Start cell as ``[row, col]``.
        end: End cell as ``[row, col]``.
    """

    start: tuple[int, int]
    end: tuple[int, int]


def _model_to_maze_data(model: MazeFieldModel) -> MazeData:
    """Converts the maze field model into an API response.

    Args:
        model: Internal maze model
            :class:`~models.field.MazeFieldModel`.

    Returns:
        A :class:`MazeData` instance with wall values cast to ``int``.
    """
    return MazeData(
        rows=model.rows,
        cols=model.cols,
        vertical_walls=[[int(v) for v in row] for row in model.vertical_walls],
        horizontal_walls=[
            [int(v) for v in row] for row in model.horizontal_walls
        ],
    )


def make_maze_router(controller: Controller) -> APIRouter:
    """Creates and returns an APIRouter with all maze endpoints.

    Registers the ``POST /generate``, ``POST /upload``,
    ``GET /download``, ``POST /solve``, and ``DELETE /`` routes.

    Args:
        controller: A :class:`~controller.controller.Controller` instance
            through which all maze operations are performed.

    Returns:
        A configured :class:`~fastapi.APIRouter` with the registered endpoints.
    """
    router = APIRouter()

    @router.post("/generate", response_model=MazeData)
    def generate(req: GenerateRequest) -> MazeData:
        """Generates a new maze of the requested size.

        Args:
            req: Generation parameters (rows and cols, each from 1 to 50).

        Returns:
            The generated maze as a :class:`MazeData` instance.

        Raises:
            HTTPException: 400 if dimensions are outside the allowed range;
                500 if generation failed.
        """
        if not (1 <= req.rows <= 50 and 1 <= req.cols <= 50):
            raise HTTPException(
                status_code=400, detail="Dimensions must be 1-50"
            )
        ok = controller.generate_maze(req.rows, req.cols)
        if not ok:
            raise HTTPException(status_code=500, detail="Generation failed")
        model = controller.get_current_field_model()
        if not isinstance(model, MazeFieldModel):
            raise HTTPException(status_code=500, detail="Generation failed")
        return _model_to_maze_data(model)

    @router.post("/upload", response_model=MazeData)
    async def upload(file: UploadFile = File(...)) -> MazeData:
        """Loads a maze from a text file.

        Saves the content to a temporary file, passes the path to the
        controller, and deletes the temporary file after loading.

        Args:
            file: Uploaded file in ``.txt`` format.

        Returns:
            The loaded maze as a :class:`MazeData` instance.

        Raises:
            HTTPException: 400 if the file is not a valid maze description.
        """
        content = await file.read()
        # mkstemp + manual close keeps the file unlocked on Windows before
        # load_maze_from_file opens it.
        fd, tmp_path = tempfile.mkstemp(suffix=".txt")
        try:
            os.write(fd, content)
            os.close(fd)
            ok = controller.load_maze_from_file(tmp_path)
        except Exception:
            with contextlib.suppress(OSError):
                os.close(fd)
            ok = False
        finally:
            os.unlink(tmp_path)
        if not ok:
            raise HTTPException(status_code=400, detail="Invalid maze file")
        model = controller.get_current_field_model()
        if not isinstance(model, MazeFieldModel):
            raise HTTPException(status_code=400, detail="Invalid maze file")
        return _model_to_maze_data(model)

    @router.get("/download")
    def download() -> StreamingResponse:
        """Downloads the current maze as a text file.

        Returns:
            A :class:`~fastapi.responses.StreamingResponse` with the contents
            of ``maze.txt`` and a ``Content-Disposition: attachment`` header.

        Raises:
            HTTPException: 404 if no maze is currently loaded;
                500 if saving failed.
        """
        if not isinstance(controller.get_current_field_model(), MazeFieldModel):
            raise HTTPException(status_code=404, detail="No maze loaded")
        # Use mkstemp (not NamedTemporaryFile) so the fd is closed before
        # controller.save_maze() opens the file — required on Windows.
        fd, tmp_path = tempfile.mkstemp(suffix=".txt")
        os.close(fd)
        try:
            ok = controller.save_maze(tmp_path)
            if not ok:
                raise HTTPException(status_code=500, detail="Save failed")
            with open(tmp_path) as f:
                content = f.read()
        finally:
            os.unlink(tmp_path)

        def _iter() -> Generator[str, None, None]:
            yield content

        return StreamingResponse(
            _iter(),
            media_type="text/plain",
            headers={"Content-Disposition": 'attachment; filename="maze.txt"'},
        )

    @router.post("/solve")
    def solve(req: SolveRequest) -> dict[str, list[list[int]]]:
        """Finds a path between two cells in the current maze.

        Args:
            req: Start and end cells in the format ``[row, col]``.

        Returns:
            A dict of the form ``{"path": [[r, c], ...]}``; the list is empty
            if no path was found.

        Raises:
            HTTPException: 404 if no maze is currently loaded.
            HTTPException: 400 if start or end are outside the maze bounds.
        """
        model = controller.get_current_field_model()
        if not isinstance(model, MazeFieldModel):
            raise HTTPException(status_code=404, detail="No maze loaded")
        rows, cols = model.rows, model.cols
        for name, cell in (("start", req.start), ("end", req.end)):
            r, c = cell
            if not (0 <= r < rows and 0 <= c < cols):
                raise HTTPException(
                    status_code=400,
                    detail=(
                        f"{name} {cell} is out of bounds for {rows}x{cols} maze"
                    ),
                )
        path = controller.solve_maze(req.start, req.end)
        return {"path": [list(cell) for cell in path] if path else []}

    @router.delete("", status_code=204)
    def clear() -> None:
        """Clears the current maze and resets the controller state."""
        controller.clear()

    return router
