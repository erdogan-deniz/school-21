# Toolchain — pinned versions

This document is the single source of truth for the **versions of every
tool** the repo's CI relies on. Bumping a version here means updating the
corresponding workflow / config; this file documents what you should see
if you scrape `.github/workflows/`.

> Last reviewed: 2026-05-11.

## Languages

| Language | Version             | Rationale                                                  |
| -------- | ------------------- | ---------------------------------------------------------- |
| C        | C11 (gcc, GNU)      | School 21 standard; pinned in every C subproject Makefile. |
| C++      | C++17 (g++, GNU)    | School 21 standard for the OOP track.                      |
| Python   | 3.12                | `.ruff.toml` `target-version`; CI `actions/setup-python@v5` argument. |
| SQL      | PostgreSQL 16-ish   | `sql.yml` sqlfluff `--dialect postgres`.                   |
| Bash     | POSIX + bash 5.x    | Ubuntu LTS shipped by GitHub Actions runners.              |
| Docker   | latest stable       | Provided by Ubuntu LTS runner image.                       |

## Linters / formatters

| Tool          | Version | Where pinned                                |
| ------------- | ------- | ------------------------------------------- |
| markdownlint-cli2 | 0.13.0 | [`.github/workflows/lint.yml`](../.github/workflows/lint.yml) |
| lychee        | latest  | `lycheeverse/lychee-action@v2`              |
| clang-format  | 18.1.8  | apt `clang-format` on Ubuntu (CI); pip `clang-format==18.1.8` locally; obeys repo-root [`.clang-format`](../.clang-format) |
| ruff          | 0.6.9   | [`.github/workflows/python.yml`](../.github/workflows/python.yml); obeys repo-root [`.ruff.toml`](../.ruff.toml) |
| sqlfluff      | 3.2.5   | [`.github/workflows/sql.yml`](../.github/workflows/sql.yml) |
| shellcheck    | apt latest | [`.github/workflows/devops.yml`](../.github/workflows/devops.yml) |
| hadolint      | hadolint-action@v3.1.0 | [`.github/workflows/devops.yml`](../.github/workflows/devops.yml) |
| EditorConfig  | (config-only) | [`.editorconfig`](../.editorconfig)        |

## Test frameworks

| Track    | Framework                     | Pinning                                     |
| -------- | ----------------------------- | ------------------------------------------- |
| C        | Check (`libcheck-dev` + `libsubunit-dev`) | apt latest in `c.yml`           |
| C++      | GoogleTest (`libgtest-dev`)   | apt latest + cmake-installed in `cpp.yml`  |
| Python   | pytest                        | per-day `requirements.txt`; `pytest` fallback in `python.yml` |
| Coverage | lcov + gcovr                  | apt latest in `c.yml` / `cpp.yml`           |
| Memcheck | valgrind                      | available but not yet wired into CI         |

## Build systems

| Track   | System        | Notes                                     |
| ------- | ------------- | ----------------------------------------- |
| c/      | Makefile      | Per-subproject `src/Makefile`.            |
| cpp/    | Makefile + qmake | qmake invoked from Makefile for Qt apps. |
| python/ | pyproject.toml (new days) / setup.py (older) | per-day, `pip install -e .` reproducible.   |

## Qt

| Aspect          | Pinning                          |
| --------------- | -------------------------------- |
| Version         | 6.5.3 desktop                    |
| Action          | `jurplel/install-qt-action@v4`   |
| arch            | `linux_gcc_64`                   |
| Runtime wrap    | `xvfb-run -a make ...` (headless display) |
| Used in         | `c.yml` `apps-qt-build`, `cpp.yml` `apps-qt-build` |

## Documentation

| Tool      | Pinning                          |
| --------- | -------------------------------- |
| Doxygen   | apt latest (`doxygen` + `graphviz`) |
| Sphinx    | pip latest + `furo` theme        |
| Used in   | `docs.yml` (Doxygen), `python.yml` `sphinx` job (Sphinx), `pages.yml` (both) |

## CI runner

| Aspect          | Pinning           |
| --------------- | ----------------- |
| OS              | `ubuntu-latest` (currently 24.04 LTS) |
| Architecture    | x86_64            |
| Concurrency     | per-workflow concurrency-grouped by `${{ github.ref }}`; `cancel-in-progress: true` (false for `pages`). |

## Bumping policy

- **Breaking bumps** (e.g. Python 3.12 → 3.13, Qt 6.5 → 6.6): one
  workflow at a time; verify all jobs green before merging the bump.
- **Patch bumps** (clang-format 18.1.8 → 18.1.9): batched via
  Dependabot weekly Monday PR (see [`.github/dependabot.yml`](../.github/dependabot.yml)).
- **Action `@vN` major bumps**: review Dependabot PR for behaviour
  changes (especially `actions/checkout`, `actions/setup-python`).
