"""Tests for QLearningAgent — Q-table, action selection,
training, and path extraction."""

# python3 -m pytest tests/test_maze_agent.py -v

from unittest.mock import patch

import pytest

from core.maze import Maze
from core.maze_agent import QLearningAgent

# ---------------------------------------------------------------------------
# Fixtures
# ---------------------------------------------------------------------------


@pytest.fixture
def corridor() -> Maze:
    """Horizontal corridor 1×3: (0,0)→(0,1)→(0,2)."""
    return Maze(
        rows=1,
        cols=3,
        rights=[[0, 0, 1]],  # no walls between cells, right boundary = 1
        bottoms=[[1, 1, 1]],  # single row — cannot go down
    )


@pytest.fixture
def vcorridor() -> Maze:
    """Vertical corridor 3×1: (0,0)→(1,0)→(2,0)."""
    return Maze(
        rows=3,
        cols=1,
        rights=[[1], [1], [1]],
        bottoms=[[0], [0], [1]],
    )


@pytest.fixture
def walled() -> Maze:
    """Fully walled 2×2: no passage in any direction."""
    return Maze(
        rows=2,
        cols=2,
        rights=[[1, 1], [1, 1]],
        bottoms=[[1, 1], [1, 1]],
    )


@pytest.fixture
def open2x2() -> Maze:
    """Fully open 2×2: all internal walls removed."""
    return Maze(
        rows=2,
        cols=2,
        rights=[[0, 1], [0, 1]],
        bottoms=[[0, 0], [1, 1]],
    )


@pytest.fixture
def agent() -> QLearningAgent:
    """Default QLearningAgent with an empty Q-table."""
    return QLearningAgent()


# ---------------------------------------------------------------------------
# __init__
# ---------------------------------------------------------------------------


class TestInit:
    """Tests for QLearningAgent.__init__ (hyperparameter defaults/overrides)."""

    def test_default_hyperparams(self) -> None:
        """Default constructor sets the expected hyperparameter values."""
        a = QLearningAgent()
        assert a.lr == 0.2
        assert a.gamma == 0.95
        assert a.epsilon == 1.0
        assert a.epsilon_decay == 0.995
        assert a.epsilon_min == 0.01
        assert a.q_table == {}

    def test_custom_hyperparams(self) -> None:
        """Custom constructor arguments are stored correctly."""
        a = QLearningAgent(
            learning_rate=0.5,
            discount=0.9,
            epsilon=0.5,
            epsilon_decay=0.99,
            epsilon_min=0.05,
        )
        assert a.lr == 0.5
        assert a.gamma == 0.9
        assert a.epsilon == 0.5
        assert a.epsilon_decay == 0.99
        assert a.epsilon_min == 0.05


# ---------------------------------------------------------------------------
# _q
# ---------------------------------------------------------------------------


class TestQ:
    """Tests for QLearningAgent._q (Q-value lookup)."""

    def test_unknown_state_returns_zero(self, agent: QLearningAgent) -> None:
        """Returns 0.0 for a (state, action) pair not yet in the Q-table."""
        assert agent._q((0, 0), 0) == 0.0

    def test_returns_stored_value(self, agent: QLearningAgent) -> None:
        """Returns the value previously stored in the Q-table."""
        agent.q_table[((1, 2), 3)] = 42.0
        assert agent._q((1, 2), 3) == 42.0


# ---------------------------------------------------------------------------
# _valid_actions
# ---------------------------------------------------------------------------


class TestValidActions:
    """Tests for QLearningAgent._valid_actions — wall-aware reachability."""

    def test_corridor_start_only_right(
        self, agent: QLearningAgent, corridor: Maze
    ) -> None:
        """From the left end of a corridor only action 0 (right) is valid."""
        assert agent._valid_actions(corridor, (0, 0)) == [0]

    def test_corridor_middle_right_and_left(
        self, agent: QLearningAgent, corridor: Maze
    ) -> None:
        """From the middle of a corridor both right (0) and left (1)
        are valid."""
        assert agent._valid_actions(corridor, (0, 1)) == [0, 1]

    def test_corridor_end_only_left(
        self, agent: QLearningAgent, corridor: Maze
    ) -> None:
        """From the right end of a corridor only action 1 (left) is valid."""
        assert agent._valid_actions(corridor, (0, 2)) == [1]

    def test_vcorridor_top_only_down(
        self, agent: QLearningAgent, vcorridor: Maze
    ) -> None:
        """From the top of a vertical corridor only action 2 (down) is valid."""
        assert agent._valid_actions(vcorridor, (0, 0)) == [2]

    def test_vcorridor_middle_up_and_down(
        self, agent: QLearningAgent, vcorridor: Maze
    ) -> None:
        """From the middle of a vertical corridor both down (2) and up (3)
        are valid."""
        assert agent._valid_actions(vcorridor, (1, 0)) == [2, 3]

    def test_vcorridor_bottom_only_up(
        self, agent: QLearningAgent, vcorridor: Maze
    ) -> None:
        """From the bottom of a vertical corridor only action 3 (up)
        is valid."""
        assert agent._valid_actions(vcorridor, (2, 0)) == [3]

    def test_walled_no_actions(
        self, agent: QLearningAgent, walled: Maze
    ) -> None:
        """In a fully walled maze no actions are valid from any cell."""
        assert agent._valid_actions(walled, (0, 0)) == []
        assert agent._valid_actions(walled, (1, 1)) == []

    def test_open2x2_corner_right_and_down(
        self, agent: QLearningAgent, open2x2: Maze
    ) -> None:
        """From (0,0) in an open 2×2 maze right (0) and down (2) are valid."""
        valid = agent._valid_actions(open2x2, (0, 0))
        assert 0 in valid  # right
        assert 2 in valid  # down

    def test_open2x2_bottom_right_left_and_up(
        self, agent: QLearningAgent, open2x2: Maze
    ) -> None:
        """From (1,1) in an open 2×2 maze left (1) and up (3) are valid."""
        valid = agent._valid_actions(open2x2, (1, 1))
        assert 1 in valid  # left
        assert 3 in valid  # up


# ---------------------------------------------------------------------------
# _choose_action
# ---------------------------------------------------------------------------


class TestChooseAction:
    """Tests for QLearningAgent._choose_action (ε-greedy policy)."""

    def test_greedy_picks_max_q(self, agent: QLearningAgent) -> None:
        """With ε=0 the action with the highest Q-value is chosen."""
        agent.epsilon = 0.0
        agent.q_table[((0, 0), 0)] = 10.0
        agent.q_table[((0, 0), 1)] = 5.0
        assert agent._choose_action((0, 0), [0, 1]) == 0

    def test_greedy_picks_among_valid_only(self, agent: QLearningAgent) -> None:
        """With ε=0 only actions in the valid list are considered."""
        agent.epsilon = 0.0
        # action 2 has highest Q but is not in valid list
        agent.q_table[((0, 0), 2)] = 99.0
        agent.q_table[((0, 0), 0)] = 3.0
        assert agent._choose_action((0, 0), [0, 1]) == 0

    def test_random_when_epsilon_one(self, agent: QLearningAgent) -> None:
        """With ε=1 a random action is chosen via random.choice."""
        agent.epsilon = 1.0
        with (
            patch("core.maze_agent.random.random", return_value=0.5),
            patch(
                "core.maze_agent.random.choice", return_value=1
            ) as mock_choice,
        ):
            result = agent._choose_action((0, 0), [0, 1])
        mock_choice.assert_called_once_with([0, 1])
        assert result == 1


# ---------------------------------------------------------------------------
# _update
# ---------------------------------------------------------------------------


class TestUpdate:
    """Tests for QLearningAgent._update (Bellman equation Q-update)."""

    def test_update_with_lr1_gamma0_equals_reward(
        self, agent: QLearningAgent, corridor: Maze
    ) -> None:
        """With lr=1 and γ=0 the formula reduces to Q(s,a) = reward."""
        a = QLearningAgent(learning_rate=1.0, discount=0.0)
        a._update((0, 0), 0, 100.0, (0, 1), corridor)
        assert a._q((0, 0), 0) == pytest.approx(100.0)

    def test_update_negative_reward_decreases_q(
        self, agent: QLearningAgent, corridor: Maze
    ) -> None:
        """A negative step reward correctly decreases the Q-value."""
        a = QLearningAgent(learning_rate=1.0, discount=0.0)
        a._update((0, 1), 0, -1.0, (0, 2), corridor)
        assert a._q((0, 1), 0) == pytest.approx(-1.0)

    def test_update_terminal_state_no_next_actions(
        self, agent: QLearningAgent, walled: Maze
    ) -> None:
        """From a fully walled cell max_next=0."""
        a = QLearningAgent(learning_rate=1.0, discount=1.0)
        a._update((0, 0), 0, 50.0, (0, 1), walled)
        # max_next=0 (no valid actions from (0,1) in walled maze)
        assert a._q((0, 0), 0) == pytest.approx(50.0)

    def test_update_accumulates_with_partial_lr(self, corridor: Maze) -> None:
        """Repeated updates converge the Q-value towards the reward."""
        a = QLearningAgent(learning_rate=0.5, discount=0.0)
        # First update: Q = 0 + 0.5*(10 - 0) = 5.0
        a._update((0, 0), 0, 10.0, (0, 1), corridor)
        assert a._q((0, 0), 0) == pytest.approx(5.0)
        # Second update: Q = 5 + 0.5*(10 - 5) = 7.5
        a._update((0, 0), 0, 10.0, (0, 1), corridor)
        assert a._q((0, 0), 0) == pytest.approx(7.5)


# ---------------------------------------------------------------------------
# train
# ---------------------------------------------------------------------------


class TestTrain:
    """Tests for QLearningAgent.train — episode loop and Q-table population."""

    def test_train_populates_q_table(self, corridor: Maze) -> None:
        """After training the Q-table contains at least one entry."""
        a = QLearningAgent()
        a.train(corridor, (0, 0), (0, 2), episodes=50)
        assert len(a.q_table) > 0

    def test_train_decays_epsilon(self, corridor: Maze) -> None:
        """Epsilon decreases below 1.0 after training."""
        a = QLearningAgent()
        a.train(corridor, (0, 0), (0, 2), episodes=10)
        assert a.epsilon < 1.0

    def test_train_respects_epsilon_min(self, corridor: Maze) -> None:
        """Epsilon never falls below epsilon_min."""
        a = QLearningAgent(epsilon_decay=0.0001, epsilon_min=0.05)
        a.train(corridor, (0, 0), (0, 2), episodes=1000)
        assert a.epsilon >= 0.05

    def test_train_resets_epsilon_on_retrain(self, corridor: Maze) -> None:
        """Calling train again resets epsilon to 1.0 before starting."""
        a = QLearningAgent()
        a.epsilon = 0.001
        # train with 0 episodes: epsilon is reset to 1.0, loop does not run
        a.train(corridor, (0, 0), (0, 2), episodes=0)
        assert a.epsilon == 1.0

    def test_train_clears_q_table_on_retrain(self, corridor: Maze) -> None:
        """Calling train again clears the Q-table before starting."""
        a = QLearningAgent()
        a.q_table[((0, 0), 0)] = 999.0
        a.train(corridor, (0, 0), (0, 2), episodes=0)
        assert a.q_table == {}

    def test_train_single_episode_no_crash(self, corridor: Maze) -> None:
        """Training for a single episode does not raise."""
        a = QLearningAgent()
        a.train(corridor, (0, 0), (0, 2), episodes=1)

    def test_train_walled_maze_no_crash(self, walled: Maze) -> None:
        """Agent must not crash when no actions are available."""
        a = QLearningAgent()
        a.train(walled, (0, 0), (1, 1), episodes=10)


# ---------------------------------------------------------------------------
# get_path
# ---------------------------------------------------------------------------


class TestGetPath:
    """Tests for QLearningAgent.get_path — greedy policy path extraction."""

    def test_start_equals_end_returns_singleton(
        self, corridor: Maze, agent: QLearningAgent
    ) -> None:
        """When start == end the path contains only that cell."""
        agent.train(corridor, (0, 0), (0, 0), episodes=1)
        path = agent.get_path(corridor, (0, 0), (0, 0))
        assert path == [(0, 0)]

    def test_path_found_in_corridor(self, corridor: Maze) -> None:
        """After sufficient training the agent finds a valid path
        in a corridor."""
        a = QLearningAgent(learning_rate=0.5, discount=0.9, epsilon_decay=0.99)
        a.train(corridor, (0, 0), (0, 2), episodes=200)
        path = a.get_path(corridor, (0, 0), (0, 2))
        assert path is not None
        assert path[0] == (0, 0)
        assert path[-1] == (0, 2)

    def test_path_found_in_vcorridor(self, vcorridor: Maze) -> None:
        """After sufficient training the agent finds a valid path
        in a vertical corridor."""
        a = QLearningAgent(learning_rate=0.5, discount=0.9, epsilon_decay=0.99)
        a.train(vcorridor, (0, 0), (2, 0), episodes=200)
        path = a.get_path(vcorridor, (0, 0), (2, 0))
        assert path is not None
        assert path[0] == (0, 0)
        assert path[-1] == (2, 0)

    def test_no_valid_actions_returns_none(
        self, walled: Maze, agent: QLearningAgent
    ) -> None:
        """Returns None when the starting cell has no valid actions."""
        path = agent.get_path(walled, (0, 0), (1, 1))
        assert path is None

    def test_cycle_returns_none(
        self, open2x2: Maze, agent: QLearningAgent
    ) -> None:
        """Untrained agent on an open maze will loop → None."""
        # Q-table is empty → all actions are equal → first is chosen → cycle
        path = agent.get_path(open2x2, (0, 0), (1, 1))
        assert path is None

    def test_path_length_matches_corridor(self, corridor: Maze) -> None:
        """The path in a 1×3 corridor has exactly 3 cells."""
        a = QLearningAgent(learning_rate=0.5, discount=0.9, epsilon_decay=0.99)
        a.train(corridor, (0, 0), (0, 2), episodes=200)
        path = a.get_path(corridor, (0, 0), (0, 2))
        # Shortest path in a 1×3 corridor: 3 cells
        assert path is not None
        assert len(path) == 3

    def test_get_path_returns_none_when_max_steps_exhausted(self) -> None:
        """When max_steps=0 (empty mock maze), get_path exhausts
        the loop and returns None."""

        class _EmptyMaze:
            def get_rows(self) -> int:
                return 0

            def get_cols(self) -> int:
                return 0

        a = QLearningAgent()
        # rows*cols*2 = 0 → loop does not execute → line 124 return None
        result = a.get_path(_EmptyMaze(), (0, 0), (1, 1))
        assert result is None
