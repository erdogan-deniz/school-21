"""Application configuration constants: window, maze, and cave dimensions."""

# Window
CANVAS_WIDTH: int = 500  # pixels
CANVAS_HEIGHT: int = 500  # pixels

MAX_ROWS: int = 50
MAX_COLS: int = 50

DEFAULT_N_ROWS: int = 10
DEFAULT_N_COLS: int = 10

# Maze
WALL_THICKNESS: int = 2  # pixels
PATH_THICKNESS: int = 2  # pixels

# Cave
BIRTH_DEATH_LIMITS: tuple[int, ...] = tuple(range(0, 8))
DEFAULT_BIRTH_LIMIT: int = 4
DEFAULT_DEATH_LIMIT: int = 3
DEFAULT_INIT_CHANCE: int = 50  # Birth chance: percentage

# Colors (R, G, B)
COLOR_BACKGROUND: tuple[int, int, int] = (250, 246, 240)  # #FAF6F0
COLOR_WALL: tuple[int, int, int] = (0, 0, 0)  # black
COLOR_CAVE_CELL: tuple[int, int, int] = (0, 0, 0)  # black

# Solve overlay colors (R, G, B)
COLOR_PATH: tuple[int, int, int] = (0, 100, 220)  # BFS path — blue
COLOR_AGENT_PATH: tuple[int, int, int] = (255, 140, 0)  # Q-learning — orange
COLOR_START: tuple[int, int, int] = (0, 180, 0)  # start marker — green
COLOR_END: tuple[int, int, int] = (200, 0, 0)  # end marker — red
SOLVE_MARKER_RADIUS: int = 5
