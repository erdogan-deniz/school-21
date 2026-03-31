# Architecture

## Source Layout

```files
python_maze/
├── data/
│   ├── maze/                       # Sample maze files (4x4.txt, example_1–3.txt)
│   └── cave/                       # Sample cave files (4x4.txt, example_1–3.txt)
├── tests/                          # pytest test suite (see testing.md)
│   ├── unit/
│   │   ├── core/                   # Unit tests for core business logic
│   │   ├── controller/             # Unit tests for controller layer
│   │   └── app/                    # Unit tests for Qt app layer
│   └── integration/                # Integration tests (file I/O, web API)
└── src/
    ├── main.py                     # Entry point — launches PyQt5 app
    ├── core/                       # Pure business logic, no UI dependencies
    │   ├── base_field.py           # Shared base class for Maze and Cave
    │   ├── maze.py                 # Maze data model (vertical_walls/horizontal_walls matrices)
    │   ├── maze_generator.py       # MazeGenerator ABC + MazeGeneratorImpl (Eller's algorithm)
    │   ├── maze_solver.py          # BFS shortest-path solver
    │   ├── maze_agent.py           # Q-learning agent (train / get_path)
    │   └── cave.py                 # Cellular automaton cave model
    ├── models/
    │   └── field.py                # FieldModel / MazeFieldModel / CaveFieldModel — DTOs between layers
    ├── handlers/
    │   └── file_handler.py         # Read/write maze and cave .txt files
    ├── controller/
    │   ├── controller.py           # Business logic facade (thin wrapper over services)
    │   ├── maze_service.py         # Maze-specific operations (generate, load, save, solve, agent)
    │   └── cave_service.py         # Cave-specific operations (generate, load, save, step)
    ├── app/                        # PyQt5 desktop application
    │   ├── app.py                  # QApplication bootstrap
    │   ├── controller/
    │   │   ├── app_controller.py   # Signal/slot coordinator between widgets and controller
    │   │   ├── solve_manager.py    # Solution state holder (start/end/path/agent_trained, click logic, overlay render)
    │   │   └── cave_auto_play.py   # QTimer wrapper for cave auto-play mode
    │   ├── render/
    │   │   ├── base_grider.py      # Shared grid geometry (cell size, offsets)
    │   │   ├── maze_grider.py      # Maze grid geometry
    │   │   ├── cave_grider.py      # Cave grid geometry
    │   │   └── render.py           # BaseRender, MazeRender, CaveRender, MazeSolutionRender → QImage
    │   └── widgets/
    │       ├── main_window.py      # Top-level QMainWindow
    │       ├── content/            # Tab and canvas widgets
    │       │   ├── base_canvas.py  # Shared canvas base (click handling, pixmap display)
    │       │   ├── maze_canvas.py  # Maze canvas widget
    │       │   ├── cave_canvas.py  # Cave canvas widget
    │       │   ├── maze_tab.py     # Maze tab (canvas + layout)
    │       │   ├── cave_tab.py     # Cave tab (canvas + layout)
    │       │   └── content_container.py  # QTabWidget hosting maze and cave tabs
    │       └── toolbar/            # Toolbar widgets
    │           ├── base_toolbar.py     # Shared toolbar base
    │           ├── maze_toolbar.py     # Maze-specific toolbar controls
    │           ├── cave_toolbar.py     # Cave-specific toolbar controls
    │           └── toolbar_container.py  # Container hosting both toolbars
    ├── web/                        # FastAPI web interface
    │   ├── server.py               # App factory — mounts router and static files
    │   ├── router/
    │   │   └── maze.py             # REST endpoints: generate/upload/download/solve/clear
    │   └── static/
    │       └── index.html          # SPA frontend (HTML5 Canvas + vanilla JS)
    └── utils/
        ├── config.py               # App-wide constants (canvas 500px, max 50×50, wall 2px)
        └── paths.py                # Path helpers for data directories
```

## Module Responsibilities

| Layer | File | Responsibility |
| ----- | ---- | -------------- |
| Core | `core/maze.py` | Maze data model — exposes `get_vertical_walls()` / `get_horizontal_walls()` matrices |
| Core | `core/maze_generator.py` | `MazeGenerator` ABC + `MazeGeneratorImpl` — Eller's algorithm, guarantees perfect maze |
| Core | `core/maze_solver.py` | BFS shortest-path from start to end; returns ordered cell list |
| Core | `core/maze_agent.py` | Q-learning agent: `train(maze, start, end, episodes)` → `get_path(maze, start, end)` |
| Core | `core/cave.py` | Cellular automaton: `next_generation()` returns a new `Cave` after applying birth/death rules |
| Models | `models/field.py` | DTOs (`FieldModel`, `MazeFieldModel`, `CaveFieldModel`) wrapping core objects; consumed by `controller/`, `app/controller/`, and `web/router/` |
| Handlers | `handlers/file_handler.py` | Parses and writes the text file format for both mazes and caves |
| Controller | `controller/maze_service.py` | Maze operations: generate, load from file, save, solve (BFS), train/use agent |
| Controller | `controller/cave_service.py` | Cave operations: generate, load from file, save, advance one step |
| Controller | `controller/controller.py` | Thin façade over `MazeService` and `CaveService`; owns `current_field_model` |
| App | `app/controller/app_controller.py` | Translates Qt signals (button clicks, canvas clicks) into controller calls; owns render state |
| App | `app/controller/solve_manager.py` | Solution state holder: tracks start/end/path/agent_trained, handles sequential click logic (1st→start, 2nd→end, 3rd→new start with end cleared), renders path overlay |
| App | `app/controller/cave_auto_play.py` | `QObject` wrapping `QTimer`; emits `step_requested` signal on each tick — drives the cave cellular automaton in auto-play mode |
| App | `app/render/render.py` | `BaseRender`, `MazeRender`, `CaveRender`, `MazeSolutionRender` — render geometry from `Grider` objects into `QImage` via QPainter |
| App | `app/widgets/` | All PyQt5 UI: main window, two tabs (Maze/Cave), toolbars, canvases |
| Web | `web/server.py` | Creates FastAPI app, wires router, serves static SPA |
| Web | `web/router/maze.py` | Five REST endpoints sharing a single `Controller` instance per server session |
| Utils | `utils/config.py` | Single source of truth for canvas size, wall thickness, max dimensions, default values |
| Utils | `utils/paths.py` | Resolves absolute paths to `data/maze/`, `data/cave/`, and `assets/` |

## Dependency Flow

| Layer | Imports from |
| ----- | ------------ |
| `core/` | nothing (fully self-contained) |
| `models/` | `core/`, `utils/` |
| `handlers/` | `core/`, `utils/` |
| `controller/` | `core/`, `models/`, `handlers/`, `utils/` |
| `app/render/` | `utils/`, `app/render/` (griders) |
| `app/controller/` | `controller/`, `models/`, `app/render/`, `utils/` |
| `web/router/` | `controller/`, `models/` |
| `app/widgets/` | `app/controller/`, `app/widgets/` (submodules), `utils/` |

`core/` has no imports from `app/`, `web/`, or `controller/` — it is fully self-contained.
`models/` is a shared DTO layer used by `controller/`, `app/controller/`, and `web/router/` — it has no UI dependencies.
`app/render/` works with `Grider` geometry objects, not `FieldModel` DTOs directly.
