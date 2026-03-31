"""Q-learning agent for navigating the maze."""

import random

from core.maze import Maze


class QLearningAgent:
    """
    Q-learning agent for navigating the maze.

    Learns by trial and error: receives a penalty of -1 per step
    and a reward of +100 for reaching the goal. After training it builds
    a path using a greedy policy (selects the action with the highest Q-value).

    Q-update:
        Q(s,a) ← Q(s,a) + α · [r + γ · max_a' Q(s',a') - Q(s,a)]
    """

    lr: float
    gamma: float
    epsilon: float
    epsilon_decay: float
    epsilon_min: float

    # action_idx → (delta_row, delta_col)
    ACTIONS: list[tuple[int, int]] = [
        (0, 1),  # 0: right
        (0, -1),  # 1: left
        (1, 0),  # 2: down
        (-1, 0),  # 3: up
    ]

    def __init__(
        self,
        learning_rate: float = 0.2,
        discount: float = 0.95,
        epsilon: float = 1.0,
        epsilon_decay: float = 0.995,
        epsilon_min: float = 0.01,
    ) -> None:
        """Initializes the Q-learning agent with hyperparameters.

        Args:
            learning_rate: Step size α for the Q-update (0 < α ≤ 1).
            discount: Discount factor γ for future rewards (0 < γ ≤ 1).
            epsilon: Initial exploration rate (1.0 = fully random).
            epsilon_decay: Multiplicative decay applied to ε after each episode.
            epsilon_min: Lower bound for ε (prevents pure greedy policy).
        """
        self.lr = learning_rate
        self.gamma = discount
        self.epsilon = epsilon
        self.epsilon_decay = epsilon_decay
        self.epsilon_min = epsilon_min
        self.q_table: dict[tuple[tuple[int, int], int], float] = {}

    def train(
        self,
        maze: Maze,
        start: tuple[int, int],
        end: tuple[int, int],
        episodes: int = 1000,
    ) -> None:
        """Trains the agent using Q-learning.

        Each episode starts from a random cell in the maze, allowing the
        agent to learn a policy from any starting point (endpoint is fixed).
        The start parameter is not used during training — it is passed for
        backwards compatibility and is only used in get_path().

        Args:
            maze: maze to train on.
            start: starting point (not used during training, see get_path).
            end: end point (fixed throughout training).
            episodes: number of training episodes.
        """
        rows, cols = maze.get_rows(), maze.get_cols()
        max_steps = rows * cols * 4
        self.epsilon = 1.0  # reset ε on re-training
        self.q_table.clear()

        for _ in range(episodes):
            state = (random.randint(0, rows - 1), random.randint(0, cols - 1))
            for _ in range(max_steps):
                valid = self._valid_actions(maze, state)
                if not valid:
                    break

                action = self._choose_action(state, valid)
                dr, dc = self.ACTIONS[action]
                next_state = (state[0] + dr, state[1] + dc)

                reward = 100.0 if next_state == end else -1.0
                self._update(state, action, reward, next_state, maze)

                state = next_state
                if state == end:
                    break

            self.epsilon = max(
                self.epsilon_min, self.epsilon * self.epsilon_decay
            )

    def get_path(
        self,
        maze: Maze,
        start: tuple[int, int],
        end: tuple[int, int],
    ) -> list[tuple[int, int]] | None:
        """
        Extracts the path after training (greedy policy, ε=0).
        Returns None if the agent enters a cycle or reaches a dead end.
        """
        rows, cols = maze.get_rows(), maze.get_cols()
        max_steps = rows * cols * 2

        path = [start]
        state = start
        visited = {start}

        for _ in range(max_steps):
            if state == end:
                return path

            valid = self._valid_actions(maze, state)
            if not valid:
                return None

            action = max(valid, key=lambda a: self._q(state, a))
            dr, dc = self.ACTIONS[action]
            state = (state[0] + dr, state[1] + dc)

            if state in visited:
                return None  # cycle — undertrained

            visited.add(state)
            path.append(state)

        return None

    # ------------------------------------------------------------------ private

    def _q(self, state: tuple[int, int], action: int) -> float:
        """Returns the Q-value for a (state, action) pair; 0.0 if unseen."""
        return self.q_table.get((state, action), 0.0)

    def _choose_action(self, state: tuple[int, int], valid: list[int]) -> int:
        """ε-greedy action selection."""
        if random.random() < self.epsilon:
            return random.choice(valid)
        return max(valid, key=lambda a: self._q(state, a))

    def _update(
        self,
        state: tuple[int, int],
        action: int,
        reward: float,
        next_state: tuple[int, int],
        maze: Maze,
    ) -> None:
        """Updates the Q-table using the Bellman equation."""
        next_valid = self._valid_actions(maze, next_state)
        max_next = max(
            (self._q(next_state, a) for a in next_valid), default=0.0
        )
        old_q = self._q(state, action)
        self.q_table[(state, action)] = old_q + self.lr * (
            reward + self.gamma * max_next - old_q
        )

    def _valid_actions(self, maze: Maze, state: tuple[int, int]) -> list[int]:
        """Returns the list of valid actions from the given state."""
        row, col = state
        reachable = set(maze.get_neighbors(row, col))
        return [
            i
            for i, (dr, dc) in enumerate(self.ACTIONS)
            if (row + dr, col + dc) in reachable
        ]
