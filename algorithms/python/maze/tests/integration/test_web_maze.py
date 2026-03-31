"""Integration tests for the FastAPI web maze API —
generate, solve, upload/download."""

import pytest
from fastapi.testclient import TestClient

from web.server import create_app


@pytest.fixture
def client() -> TestClient:
    return TestClient(create_app())


def test_generate_returns_maze_data(client: TestClient) -> None:
    resp = client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    assert resp.status_code == 200
    data = resp.json()
    assert data["rows"] == 4
    assert data["cols"] == 4
    assert len(data["vertical_walls"]) == 4
    assert len(data["vertical_walls"][0]) == 4
    assert len(data["horizontal_walls"]) == 4
    assert len(data["horizontal_walls"][0]) == 4


def test_generate_invalid_dimensions(client: TestClient) -> None:
    resp = client.post("/api/maze/generate", json={"rows": 0, "cols": 4})
    assert resp.status_code == 400


def test_generate_too_large(client: TestClient) -> None:
    resp = client.post("/api/maze/generate", json={"rows": 51, "cols": 4})
    assert resp.status_code == 400


def test_index_returns_html(client: TestClient) -> None:
    resp = client.get("/")
    assert resp.status_code == 200
    assert "text/html" in resp.headers.get("content-type", "")


def test_upload_valid_file(client: TestClient) -> None:
    content = (
        b"4 4\n0 0 0 1\n1 0 1 1\n0 1 0 1\n0 0 0 1\n"
        b"\n1 0 1 0\n0 0 1 0\n1 1 0 1\n1 1 1 1\n"
    )
    resp = client.post(
        "/api/maze/upload",
        files={"file": ("maze.txt", content, "text/plain")},
    )
    assert resp.status_code == 200
    data = resp.json()
    assert data["rows"] == 4
    assert data["cols"] == 4


def test_upload_invalid_content(client: TestClient) -> None:
    resp = client.post(
        "/api/maze/upload",
        files={"file": ("bad.txt", b"not a maze", "text/plain")},
    )
    assert resp.status_code == 400


def test_download_returns_text(client: TestClient) -> None:
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.get("/api/maze/download")
    assert resp.status_code == 200
    assert "attachment" in resp.headers.get("content-disposition", "")
    text = resp.text
    assert text.startswith("4 4")


def test_download_no_maze_returns_404(client: TestClient) -> None:
    resp = client.get("/api/maze/download")
    assert resp.status_code == 404


def test_solve_returns_path(client: TestClient) -> None:
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.post("/api/maze/solve", json={"start": [0, 0], "end": [3, 3]})
    assert resp.status_code == 200
    data = resp.json()
    assert "path" in data
    assert isinstance(data["path"], list)


def test_solve_no_maze_returns_404(client: TestClient) -> None:
    resp = client.post("/api/maze/solve", json={"start": [0, 0], "end": [1, 1]})
    assert resp.status_code == 404


def test_solve_invalid_cell_length_returns_422(client: TestClient) -> None:
    """start/end with wrong number of elements → 422 Unprocessable Entity."""
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.post("/api/maze/solve", json={"start": [0], "end": [3, 3]})
    assert resp.status_code == 422


def test_solve_negative_start_returns_400(client: TestClient) -> None:
    """Negative row in start → 400; guards against Python negative-index
    silent read of the last matrix row."""
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.post(
        "/api/maze/solve", json={"start": [-1, 0], "end": [0, 0]}
    )
    assert resp.status_code == 400


def test_solve_out_of_bounds_end_returns_400(client: TestClient) -> None:
    """end beyond maze dimensions → 400."""
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.post("/api/maze/solve", json={"start": [0, 0], "end": [4, 4]})
    assert resp.status_code == 400


def test_clear_returns_204(client: TestClient) -> None:
    client.post("/api/maze/generate", json={"rows": 4, "cols": 4})
    resp = client.delete("/api/maze")
    assert resp.status_code == 204


def test_generate_controller_failure_returns_500(client: TestClient) -> None:
    """Controller generation failure → 500."""
    from unittest.mock import patch

    with patch("web.router.maze.Controller") as MockCtrl:
        MockCtrl.return_value.generate_maze.return_value = False
        app = create_app()
    c = TestClient(app)
    with patch.object(
        c.app.state.__class__,
        "__getattr__",
        side_effect=AttributeError,
    ):
        pass
    # Simpler: recreate the app with a mock controller via
    # monkey-patching the router
    from unittest.mock import MagicMock

    from fastapi import FastAPI

    from web.router.maze import make_maze_router

    ctrl = MagicMock()
    ctrl.generate_maze.return_value = False
    router = make_maze_router(ctrl)
    app2 = FastAPI()
    app2.include_router(router, prefix="/api/maze")
    c2 = TestClient(app2)
    resp = c2.post("/api/maze/generate", json={"rows": 5, "cols": 5})
    assert resp.status_code == 500


def test_download_save_failure_returns_500(client: TestClient) -> None:
    """If save_maze raises → 500."""
    from unittest.mock import MagicMock

    from fastapi import FastAPI

    from models.field import MazeFieldModel
    from web.router.maze import make_maze_router

    model = MagicMock(spec=MazeFieldModel)
    ctrl = MagicMock()
    ctrl.get_current_field_model.return_value = model
    ctrl.save_maze.return_value = False

    router = make_maze_router(ctrl)
    app2 = FastAPI()
    app2.include_router(router, prefix="/api/maze")
    c2 = TestClient(app2)
    resp = c2.get("/api/maze/download")
    assert resp.status_code == 500


def test_generate_wrong_model_type_returns_500(client: TestClient) -> None:
    """generate_maze succeeds but model is not MazeFieldModel → 500."""
    from unittest.mock import MagicMock

    from fastapi import FastAPI

    from web.router.maze import make_maze_router

    ctrl = MagicMock()
    ctrl.generate_maze.return_value = True
    ctrl.get_current_field_model.return_value = object()  # not MazeFieldModel

    router = make_maze_router(ctrl)
    app2 = FastAPI()
    app2.include_router(router, prefix="/api/maze")
    c2 = TestClient(app2)
    resp = c2.post("/api/maze/generate", json={"rows": 5, "cols": 5})
    assert resp.status_code == 500


def test_upload_wrong_model_type_returns_400(client: TestClient) -> None:
    """load_maze_from_file succeeds but model is not MazeFieldModel → 400."""
    from unittest.mock import MagicMock, patch

    from fastapi import FastAPI

    from web.router.maze import make_maze_router

    ctrl = MagicMock()
    ctrl.load_maze_from_file.return_value = True
    ctrl.get_current_field_model.return_value = object()  # not MazeFieldModel

    router = make_maze_router(ctrl)
    app2 = FastAPI()
    app2.include_router(router, prefix="/api/maze")
    c2 = TestClient(app2)

    content = (
        b"4 4\n0 0 0 1\n1 0 1 1\n0 1 0 1\n0 0 0 1\n"
        b"\n1 0 1 0\n0 0 1 0\n1 1 0 1\n1 1 1 1\n"
    )
    with (
        patch("web.router.maze.os.write"),
        patch("web.router.maze.os.close"),
        patch("web.router.maze.os.unlink"),
    ):
        resp = c2.post(
            "/api/maze/upload",
            files={"file": ("maze.txt", content, "text/plain")},
        )
    assert resp.status_code == 400


def test_upload_os_write_failure_returns_400(client: TestClient) -> None:
    """Error writing to a temporary file → 400."""
    from unittest.mock import patch

    with (
        patch("web.router.maze.os.write", side_effect=OSError("disk full")),
        patch("web.router.maze.os.close"),
        patch("web.router.maze.os.unlink"),
    ):
        resp = client.post(
            "/api/maze/upload",
            files={"file": ("maze.txt", b"4 4\n0 1\n", "text/plain")},
        )
    assert resp.status_code == 400


def test_upload_write_and_close_both_fail_returns_400(
    client: TestClient,
) -> None:
    """Both os.write and os.close raise → OSError caught in fallback → 400."""
    from unittest.mock import patch

    with (
        patch("web.router.maze.os.write", side_effect=OSError("disk full")),
        patch("web.router.maze.os.close", side_effect=OSError("bad fd")),
        patch("web.router.maze.os.unlink"),
    ):
        resp = client.post(
            "/api/maze/upload",
            files={"file": ("maze.txt", b"4 4\n0 1\n", "text/plain")},
        )
    assert resp.status_code == 400
