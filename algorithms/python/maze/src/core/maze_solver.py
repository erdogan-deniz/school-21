"""Maze solving using breadth-first search (BFS)."""

from collections import deque

from core.maze import Maze


class MazeSolver:
    """
    Solves the maze using breadth-first search (BFS / wave algorithm).
    Guarantees finding the shortest path.
    """

    maze: Maze
    rows: int
    cols: int

    def __init__(self, maze: Maze) -> None:
        """Initializes the solver with the maze to be solved.

        Args:
            maze: The maze object containing wall data and neighbour logic.
        """
        self.maze = maze
        self.rows = maze.get_rows()
        self.cols = maze.get_cols()

    def solve(
        self,
        start: tuple[int, int],
        end: tuple[int, int],
    ) -> list[tuple[int, int]] | None:
        """
        Finds the shortest path from start to end.

        Args:
            start: (row, col) start cell
            end:   (row, col) end cell

        Returns:
            List of cells [(row, col), ...] from start to end,
            or None if no path is found.
        """
        if start == end:
            return [start]

        # visited: cell → where we came from (for path reconstruction)
        visited: dict[tuple[int, int], tuple[int, int] | None] = {start: None}
        queue: deque[tuple[int, int]] = deque([start])

        while queue:
            current = queue.popleft()

            if current == end:
                return self._reconstruct_path(visited, end)

            for neighbor in self._get_neighbors(current):
                if neighbor not in visited:
                    visited[neighbor] = current
                    queue.append(neighbor)

        return None  # path not found

    def _get_neighbors(self, cell: tuple[int, int]) -> list[tuple[int, int]]:
        """Returns cells reachable from cell with no walls between them."""
        row, col = cell
        return self.maze.get_neighbors(row, col)

    def _reconstruct_path(
        self,
        visited: dict[tuple[int, int], tuple[int, int] | None],
        end: tuple[int, int],
    ) -> list[tuple[int, int]]:
        """Reconstructs the path by following parent links from end to start."""
        path = []
        current: tuple[int, int] | None = end
        while current is not None:
            path.append(current)
            current = visited[current]
        return list(reversed(path))
