"""FastAPI server: application assembly, static file mounting, and routing."""

from pathlib import Path

import uvicorn
from fastapi import FastAPI
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles

from controller.controller import Controller
from web.router.maze import make_maze_router


def create_app() -> FastAPI:
    """Creates and configures a FastAPI application instance.

    Registers the maze API routes under the ``/api/maze`` prefix,
    mounts the static files directory, and adds a root route that
    returns ``index.html``.

    Returns:
        A fully configured :class:`~fastapi.FastAPI` instance.
    """
    app = FastAPI(title="Maze")
    controller = Controller()

    app.include_router(make_maze_router(controller), prefix="/api/maze")

    static_dir = Path(__file__).parent / "static"
    app.mount("/static", StaticFiles(directory=static_dir), name="static")

    @app.get("/")
    def index() -> FileResponse:
        """Serves the single-page application entry point (index.html)."""
        return FileResponse(static_dir / "index.html")

    return app


app: FastAPI = create_app()

if __name__ == "__main__":  # pragma: no cover
    uvicorn.run("web.server:app", host="0.0.0.0", port=8080, reload=True)
