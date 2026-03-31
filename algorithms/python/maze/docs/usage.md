# Usage Guide

## GUI Application

Start the GUI with `make run`.

The application has two tabs: **Maze** and **Cave**.

---

### Maze Tab

#### Loading a Maze from File

1. Click **Load Maze** in the toolbar.
2. Select a `.txt` maze file (see [File Formats](#file-formats)).
3. The maze renders in the 500×500 px canvas.

Example files are located in `data/maze/`.

#### Generating a Maze

1. Set **Rows** and **Columns** (1–50 each).
2. Click **Generate**.

The maze is generated using Eller's algorithm — it is always perfect (no isolated areas, no loops).

#### Saving a Maze

Click **Save Maze** and choose a destination file.
The maze is written in the standard text format.

#### Solving the Maze (BFS)

1. **Click** any cell on the canvas — this sets the **start** point.
2. **Click** another cell — this sets the **end** point.
3. Click the **Solve** button.

The shortest path (BFS) is drawn on top of the maze.
A third click resets the selection.

#### Q-Learning Agent

1. Set start and end with two clicks (same as above).
2. Set the **Episodes** count (range 100–20000; default 1000; higher = better-trained agent, slower).
3. Click **Solve** (in the Agent section).

After training the **end point is fixed**. Every subsequent click on the canvas sets a new start — the agent builds a path from that point instantly without retraining.

---

### Cave Tab

#### Loading a Cave from File

1. Click **Load Cave**.
2. Select a `.txt` cave file (see [File Formats](#file-formats)).

Example files are located in `data/cave/`.

#### Generating a Cave

Set the parameters and click **Generate**:

| Parameter | Range | Default | Description |
| --------- | ----- | ------- | ----------- |
| Rows | 1–50 | 10 | Grid height |
| Columns | 1–50 | 10 | Grid width |
| Initialization chance | 0–100 % | 50 | Probability a cell starts alive |
| Birth limit | 0–7 | 4 | Live neighbours needed to birth a dead cell |
| Death limit | 0–7 | 3 | Minimum live neighbours to keep a cell alive |

#### Saving a Cave

Click **Save Cave** and choose a destination file.
The **Save Cave** button is enabled after a cave is loaded or generated.

#### Step-by-Step Mode

Click **Next** to advance the cellular automaton by one generation.

#### Auto-Play Mode

1. Set the delay in the **Delay** field (range 50–500 ms; default 500 ms).
2. Click **Run** to start continuous simulation. The button changes to **Stop** while running; click **Stop** to pause (becomes **Play**). Click **Play** to resume.

The simulation stops automatically when the cave reaches a stable (final) state.

---

## Web Interface

Start with `make web`, then open [http://localhost:8080](http://localhost:8080).

| Action | How |
| ------ | --- |
| Load a maze file | Click **LOAD**, select a `.txt` file |
| Generate a maze | Enter rows/cols, click **GENERATE** |
| Save current maze | Click **SAVE** |
| Solve | Click the start cell, then the end cell on the canvas, then **SOLVE** |

For full API details see [api.md](api.md).

---

## File Formats

Sample files are located in:

- **Maze files:** `data/maze/` (4x4.txt, example_1.txt – example_3.txt)
- **Cave files:** `data/cave/` (4x4.txt, example_1.txt – example_3.txt)

**Maze file format:**

```text
<rows> <cols>
<right-wall matrix>

<bottom-wall matrix>
```

Each matrix row contains space-separated `0`/`1` values. `1` = wall present, `0` = open passage.

**Cave file format:**

```text
<rows> <cols>
<cell matrix>
```

Each cell is `1` (alive/wall) or `0` (dead/open).
