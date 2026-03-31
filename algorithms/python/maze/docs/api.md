# Web API Reference

## Base URL

```url
http://localhost:8080/api/maze
```

Start the server with `make web`.

## Interactive Documentation

Swagger UI (auto-generated): [http://localhost:8080/docs](http://localhost:8080/docs)
ReDoc: [http://localhost:8080/redoc](http://localhost:8080/redoc)

---

## Endpoints

### POST `/api/maze/generate`

Generate a new perfect maze using Eller's algorithm.

**Request body (JSON):**

```json
{ "rows": 10, "cols": 10 }
```

- `rows` — integer, 1–50
- `cols` — integer, 1–50

**Response (`200 OK`):** `MazeData` object (see [Schema](#mazedata-schema)).

**Errors:**

- `400` — dimensions outside 1–50

---

### POST `/api/maze/upload`

Upload a maze from a `.txt` file.

**Request:** `multipart/form-data`, field name `file`.

**Response (`200 OK`):** `MazeData` object.

**Errors:**

- `400` — invalid or unparseable file content

---

### GET `/api/maze/download`

Download the currently loaded maze as a `.txt` file.

**Response (`200 OK`):** `text/plain`, `Content-Disposition: attachment; filename="maze.txt"`

**Errors:**

- `404` — no maze currently loaded on the server

---

### POST `/api/maze/solve`

Find the BFS shortest path between two cells.

**Request body (JSON):**

```json
{ "start": [0, 0], "end": [9, 9] }
```

- `start` — `[row, col]` of the start cell
- `end` — `[row, col]` of the end cell

**Response (`200 OK`):**

```json
{ "path": [[0,0], [0,1], [1,1], ..., [9,9]] }
```

`path` is an ordered list of `[row, col]` cells from start to end.
`path` is `[]` if no path exists.

**Errors:**

- `400` — start or end cell is outside the maze bounds
- `404` — no maze currently loaded

---

### DELETE `/api/maze`

Clear the current maze from the server session.

**Response:** `204 No Content`

---

## MazeData Schema

```json
{
  "rows": 4,
  "cols": 4,
  "vertical_walls": [[0,0,0,1],[1,0,1,1],[0,1,0,1],[0,0,0,1]],
  "horizontal_walls": [[1,0,1,0],[0,0,1,0],[1,1,0,1],[1,1,1,1]]
}
```

| Field | Type | Description |
| ----- | ---- | ----------- |
| `rows` | int | Number of rows |
| `cols` | int | Number of columns |
| `vertical_walls` | `int[][]` | Right-wall matrix: `1` = wall to the right of cell `(i,j)` |
| `horizontal_walls` | `int[][]` | Bottom-wall matrix: `1` = wall below cell `(i,j)` |

## Error Response Format

```json
{ "detail": "human-readable error message" }
```

| Code | Meaning |
| ---- | ------- |
| `400` | Invalid request (bad dimensions, unparseable file, out-of-bounds cell coordinates) |
| `404` | No maze loaded on server |
| `500` | Internal generation or save error |
