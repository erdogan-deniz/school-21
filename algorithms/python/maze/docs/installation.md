# Installation

## Prerequisites

- Python 3.12 or higher
- `pip` (bundled with Python)
- `make` utility
  - **Windows:** use [Git Bash](https://git-scm.com/), MSYS2, or WSL — the `python3` alias must be available
  - **macOS/Linux:** available by default
- PyQt5 and other dependencies are installed automatically via `make install`

## Quick Start

```bash
make install
make run
```

## Install

Installs all Python dependencies and copies the source to `~/.local/maze`:

```bash
make install
```

> **Note:** `make run` always runs from the **source tree** (`src/`), not from the installed copy. The install target is useful for packaging; for day-to-day use just run `make run` directly from the project root.

## Run the GUI

```bash
make run
```

Opens the PyQt5 desktop application.

## Run the Web Interface

```bash
make web
```

Then open [http://localhost:8080](http://localhost:8080) in a browser.

## Uninstall

Removes installed files and uninstalls Python packages:

```bash
make uninstall
```

## Development Install

Installs runtime **and** development dependencies (pytest, coverage, httpx, ruff) in one step.
Use this instead of `make install` if you plan to run tests or contribute:

```bash
make install-dev
```

## Lint and Format

```bash
make lint      # Check code style with ruff
make format    # Auto-format code with ruff
```
