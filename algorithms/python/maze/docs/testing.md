# Testing

## Run All Tests

```bash
make tests
```

Equivalent to `python3 -m pytest` — runs the full test suite from the project root.

## Run with Coverage

```bash
make cov
```

Produces a terminal coverage report for the entire `src/` package:

```bash
python3 -m pytest --cov=src --cov-report=term-missing
```

## Test Layout

All tests live in `tests/` at the project root, organized by layer:

```text
tests/
├── unit/
│   ├── core/           # Business-logic unit tests
│   ├── controller/     # Controller/service unit tests
│   └── app/            # PyQt5 app unit tests
└── integration/        # File I/O and web API integration tests
```

### `tests/unit/`

| File | What it covers |
| ---- | -------------- |
| `test_main.py` | `main()` return codes — 0 on success, 1 when `MazeApp` raises an exception |
| `test_paths.py` | `ProjectPaths.get_assets_dir()` — candidate path resolution and fallback |
| `conftest.py` | Shared fixtures: `maze_model` (4×4 `MazeFieldModel`) and `ctrl` (`AppController` with mocked `BusinessController`) |

### `tests/unit/core/`

| File | What it covers |
| ---- | -------------- |
| `test_maze.py` | `Maze` data model — construction, wall access, boundary conditions |
| `test_maze_generator.py` | Eller's algorithm — perfect maze properties (no islands, no loops, full connectivity) |
| `test_maze_solver.py` | BFS solver — shortest path correctness, unreachable cells, start == end |
| `test_cave.py` | Cellular automaton — birth/death rules, final generation detection, boundary cells |
| `test_maze_agent.py` | Q-learning agent — hyperparameters, Q-table updates, training convergence, `get_path` |

### `tests/unit/controller/`

| File | What it covers |
| ---- | -------------- |
| `test_controller.py` | `Controller` façade — all public methods, error paths, agent state lifecycle |
| `test_cave_service.py` | `CaveService` — generate, load, save, step operations |

### `tests/unit/app/`

| File | What it covers |
| ---- | -------------- |
| `test_app.py` | `QApplication` bootstrap |
| `test_app_controller_basic.py` | `AppController` — initialisation, basic signal wiring |
| `test_app_controller_canvas.py` | Canvas click handling and coordinate mapping |
| `test_app_controller_cave.py` | Cave-specific controller flows |
| `test_app_controller_files.py` | Load/save file dialog interactions |
| `test_app_controller_render.py` | Render update calls |
| `test_app_controller_solve.py` | Solve and agent train/use flows |
| `test_solve_manager.py` | `SolveManager` — solution state holder, click sequencing, overlay rendering |
| `test_cave_auto_play.py` | `CaveAutoPlay` QTimer wrapper |
| `test_render.py` | `MazeRender` / `CaveRender` / `MazeSolutionRender` → `QImage` |
| `test_griders.py` | `BaseGrider`, `MazeGrider`, `CaveGrider` — cell geometry |
| `test_widgets.py` | Main window and tab widget structure |
| `test_main_window_extras.py` | Additional `QMainWindow` behaviour |
| `test_base_toolbar.py` | Shared toolbar base class |
| `test_maze_toolbar_io.py` | Maze toolbar load/save controls |
| `test_cave_toolbar_io.py` | Cave toolbar load controls |
| `test_cave_toolbar_widgets.py` | Cave toolbar parameter widgets |

### `tests/integration/`

| File | What it covers |
| ---- | -------------- |
| `test_file_handler.py` | `MazeFileHandler` / `CaveFileHandler` — read, save, roundtrip, nested directory creation, invalid/empty file handling |
| `test_web_maze.py` | FastAPI endpoints via `TestClient` — generate, upload, download, solve, clear; error paths (400, 404, 422, 500) |

## Coverage Scope

Coverage is measured across the entire `src/` tree:

```bash
python3 -m pytest --cov=src --cov-report=term-missing
```

The `app/` package (PyQt5 widgets) requires a display; tests run under a headless Qt environment provided by `pytest-qt` (configured via `qt_api = "pyqt5"` in `pyproject.toml`).

## Running a Single Test File

```bash
python3 -m pytest tests/unit/core/test_maze_solver.py -v
```

## Running a Single Test

```bash
python3 -m pytest tests/unit/core/test_maze_solver.py::test_shortest_path -v
```
