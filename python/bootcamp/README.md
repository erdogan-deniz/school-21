# `python/bootcamp`

[![CI](https://github.com/Deniz211/school-21/actions/workflows/python.yml/badge.svg?branch=main)](https://github.com/Deniz211/school-21/actions/workflows/python.yml)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](../../LICENSE)

> *Day-by-day School 21 Python Bootcamp curriculum and team projects — 10 instructional days plus 2 team projects, modernised in `new/day_01`+ with `pyproject.toml` + `ruff`.*

## Quick start

```bash
# Lint everything (ruff respects the repo-wide .ruff.toml)
pip install ruff==0.6.9
ruff check python/ algorithms/python/

# Run a specific day with tests (e.g. day_07)
cd python/bootcamp/old/day_07
pip install -r requirements.txt pytest
pytest -v

# New-format day (day_01) is a real package
cd python/bootcamp/new/day_01
pip install -e .
```

For a fully reproducible environment, use Python 3.12 inside a Linux container —
see [`.github/workflows/python.yml`](../../.github/workflows/python.yml) for the
canonical install line.

## Demo

> **TODO** — short asciinema cast of one of the Web/async days (Day 05 Flask or Day 08 async crawler) is planned in the python/ Phase 2 demo slice.

## Documentation

- Day-by-day index below.
- Sphinx HTML for Day 07 (Voight-Kampff): planned in the docs slice.
- API references for `new/day_01`+: planned alongside Sphinx.

## Tests

- Framework: **pytest**.
- Days currently exercised in CI: `day_05`, `day_07`, `day_09`. Other days have
  no test files yet.
- Run: `pytest -v` from the day's working directory.

## License & attribution

This project was developed as part of the **School 21** curriculum (analogue of
School 42). The repository as a whole is licensed under the **MIT License** —
see the root [`LICENSE`](../../LICENSE).

The per-day `LICENSE` files (`# School 21 License`) under `old/day_*/` are
preserved as educational attribution and historical artefact; they do not
override the repo-wide MIT licence.

---

## Original task (School 21)

Project topic: Python Bootcamp.

### Day 00: Creating a Python package for working with script arguments

— Created a script for processing and parsing script arguments.
— Implemented pattern search in files using regular expressions.

### Day 01: Developing a Python package in the functional programming paradigm

— Implemented functionality modification using decorators.

### Day 02: Developing a "Prisoner's Dilemma" system

— Implemented a system of classes with player models.

### Day 03: Creating a transaction system

— Implemented functionality for transforming HTML pages with embedded JavaScript
  code.
— Configured a system with a Redis message broker.
— Integrated operation logging.
— Developed an Ansible playbook for system deployment.

### Day 04: Working with advanced Python features

— Explored working with generators, iterators, and functional programming.
— Implemented a game simulation using dynamic class creation.
— Conducted functional code testing.

### Day 05: Web development with Python

— Implemented a REST API on a WSGI server for processing HTTP requests.
— Developed a web application for managing audio files using Flask.
— Implemented a solution to the "Dining Philosophers" problem.
— Conducted API testing.

### Day 06: Developing a web knowledge base

— Implemented a client-server system on gRPC with strict protobuf typing and
  data validation via Pydantic.
— Integrated a PostgreSQL database for information storage.
— Configured database schema migrations using Alembic.
— Covered system functionality with unit and integration tests.

### Day 07: Implementation of the Voight-Kampff test

— Created project documentation using Sphinx.
— Conducted functional testing of the test implementation.

### Day 08: Neo's Fight

— Implemented an asynchronous fight system.
— Developed an asynchronous client-server web crawler for data collection.
— Integrated data caching via Redis and metric calculation.

### Day 09: Python code optimization

— Implemented a Python module in the C language.
— Wrote a clock using the ctypes library.
— Accelerated code execution by compiling via Cython.

### Team 00: Wikipedia analyzer

— Implemented a script for loading and analyzing data via API.
— Developed an algorithm for finding the shortest path between articles.
— Visualized the graph of connections between articles.

### Team 01: Developing an MMO RPG in Telegram with turn-based mechanics
