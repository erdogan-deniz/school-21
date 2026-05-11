# `school-21` — production-readiness dashboard

Single source of truth for the production-grade overhaul of every
subproject. Updated on every batch commit. Secondary views (GitHub
Projects board, GitHub Issues + milestones) are derived from this
file — never edited by hand.

For **per-subproject detail** — DoD checklist with `[x]` / `[~]` / `[ ]`
ticks, free-form tasks, and a history log — see
[`docs/plans/<track>/<subproject>.md`](docs/plans/). Each subproject
has its own plan file generated from
[`docs/plans/_TEMPLATE.md`](docs/plans/_TEMPLATE.md). The matrix below
stays high-level; the plans hold the detail.

## Flagships

Three subprojects are designated **flagship** — they target DoD-C
("use as a dependency") in addition to the universal A + B (evaluate +
clone & run) treatment:

| ★ | Subproject | Distribution shape | Why this one |
| -- | ---------- | ------------------ | ------------ |
| ★ | [`cpp/s21_containers`](cpp/s21_containers/) | Header-only C++ library — Conan / vcpkg candidate | STL replica (list, map, queue, set, stack, vector, array, multiset). Drop-in for any C++17 project; immediate reusability. |
| ★ | [`c/s21_math`](c/s21_math/)                 | Static library `s21_math.a` — drop-in `math.h` replacement | Simple, well-scoped, easiest first flagship to validate the release pipeline. |
| ★ | [`cpp/SmartCalc_v2.0`](cpp/SmartCalc_v2.0/) | Packaged desktop app — GitHub Releases `.AppImage` / `.dmg` / `.exe` | Demonstrates the full end-user distribution cycle (Qt + MVC + cross-platform installer). Different category from the two libraries above. |

Per-flagship work in scope:

- `release.yml` GitHub Actions workflow — builds artefacts, tags semver,
  publishes to GitHub Releases.
- Semantic-version git tags (`v0.1.0`, `v1.0.0`, ...).
- For libraries: a curated `package.{conan,vcpkg}.{py,json}` so the
  library can be consumed as a dependency.
- For the app: per-OS installer build (Linux AppImage, macOS dmg,
  Windows exe).

Designated 2026-05-11. Other 34 subprojects retain A + B scope only;
their READMEs say so explicitly.

## Legend

| Symbol | Meaning                                           |
| ------ | ------------------------------------------------- |
| ✓      | Done — counts as 1.0 in the roll-up                                              |
| ◐      | Partially done / in progress — counts as 0.5                                     |
| ✗      | Not done — counts as 0.0, but the cell stays in the denominator (real gap)       |
| n/a    | Not applicable — cell is **excluded from the denominator** (does not exist here) |
| ★      | Flagship — also targets DoD-C (use as dependency)                                |
| ⚠      | Known broken / blocked by a tactical issue                                       |

## Definition of Done — column key

A README · B Tests + coverage · C CI on GitHub Actions · D Linter/formatter
· E Reproducible build · F LICENSE · G Demo · H API docs (Doxygen / Sphinx)

> Full details: [`CLAUDE.md` §4](CLAUDE.md), design: [`docs/specs/2026-05-11-production-grade-overhaul.md`](docs/specs/2026-05-11-production-grade-overhaul.md).

## Subprojects

### `algorithms/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `python/maze` | ✓ | ✗ | ◐ | ✓ | ✓ | ◐ | ✗ | ✗ |          | ruff format applied; python.yml ruff job |

### `c/`

| Subproject         | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ------------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `3DViewer_v1.0`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen on 3d_viewer.h + qt_viewer headers                   |
| `SimpleBashUtils`  | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen on s21_cat.h + s21_grep.h; Codecov upload             |
| `s21_decimal`      | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; Codecov upload                              |
| `s21_math`         | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ | ★        | flagship; release-s21_math.yml; Codecov upload                |
| `s21_matrix`       | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; Codecov upload                              |
| `s21_string+`      | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; errno table preserved; Codecov upload       |
| `SmartCalc_v1.0`   | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen on core (parser/calc/transform/stack/list/etc) + Qt views |

### `career_track/`

| Subproject | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ct_00`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_01`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_02`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_03`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_04`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_05`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_06`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_07`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |
| `ct_08`    | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | text-only career project — only A + F apply |

### `cpp/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes                                                    |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | -------------------------------------------------------- |
| `3DViewer_v2.0`         | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments on Controller/Model/View headers            |
| `CPP5_3DViewer_v2.1`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments on Controller/Parsing/GLWidget/Viewer       |
| `CPP6_3DViewer_v2.2`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments on Controller/Parsing/GLWidget/Viewer       |
| `SmartCalc_v2.0`        | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ | ★        | Doxygen comments on MVC Controller + Model headers           |
| `s21_containers`        | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ | ★        | flagship; release-s21_containers.yml; Codecov upload; per-class Doxygen on all 8 containers |
| `s21_matrix+`           | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments + class; Codecov upload                     |

### `data_science/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes                                                 |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------- |
| `bootcamp`   | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | top-level Makefile (per-day .venv); pinned reqs day_03/08, team_00/01 |
| `project_01` | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | NLP "Tweets"; Makefile venv reproducible              |

### `devops/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ci_cd`                 | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | deploy.sh + notify.sh + .gitlab-ci.yml; Telegram token de-hardcoded → env vars; shellcheck via devops.yml |
| `linux`                 | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | report-driven (markdown notes + screenshots only); only A + F apply |
| `linux_monitoring_v1.0` | ✓ | ✓ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | 47 bats tests across Parts 1-5 + smoke; shellcheck + hadolint |
| `linux_network`         | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | report-driven (markdown notes + screenshots only); only A + F apply |
| `simple_docker`         | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | docker-compose; hadolint via devops.yml  |

### `internship/`

| Subproject     | A | B | C | D | E | F | G | H | Flagship | Notes |
| -------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `internship`   | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | report subproject — only A + F apply |

### `machine_learning/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | ✗ | ◐ | ✓ | ✓ | ◐ | ✗ | ✗ |          | Makefile venv (`make install/notebook/clear`); pinned reqs; ruff via python.yml |

### `python/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `bootcamp`  | ✓ | ◐ | ◐ | ✓ | ◐ | ◐ | ✗ | ◐ |          | ruff format applied + pytest + Sphinx (day_07 + new/day_01) + Pages |

### `qa/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | report subproject — no source files (manual-QA artefact is the report) |
| `project_02` | ✓ | n/a | n/a | n/a | n/a | ◐ | n/a | n/a |          | report subproject — no source files (manual-QA artefact is the report) |

### `sql/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `bootcamp`  | ✓ | ◐ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | docker-compose + Makefile + per-day schema-load CI; sqlfluff in sql.yml |

### `survival_camp/`

| Subproject       | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `survival_camp`  | ✓ | n/a | n/a | n/a | n/a | ✗ | n/a | n/a |          | historical record — only A + F apply; F gap because no LICENSE file shipped |

## Roll-up

| Track                | Subprojects | DoD cells filled | % done   |
| -------------------- | ----------- | ---------------- | -------- |
| `algorithms/`        | 1           | 4 / 8            | 50 %     |
| `c/`                 | 7           | 30.5 / 56        | 54 %     |
| `career_track/`      | 9           | 13.5 / 18        | 75 %     |
| `cpp/`               | 6           | 25 / 48          | 52 %     |
| `data_science/`      | 2           | 7 / 16           | 44 %     |
| `devops/`            | 5           | 12.5 / 28        | 45 %     |
| `internship/`        | 1           | 1.5 / 2          | 75 %     |
| `machine_learning/`  | 1           | 4 / 8            | 50 %     |
| `python/`            | 1           | 4.5 / 8          | 56 %     |
| `qa/`                | 2           | 3 / 4            | 75 %     |
| `sql/`               | 1           | 4 / 8            | 50 %     |
| `survival_camp/`     | 1           | 1 / 2            | 50 %     |
| **Total**            | **37**      | **110.5 / 206**  | **54 %** |

> Roll-up arithmetic: ✓ = 1.0, ◐ = 0.5, ✗ = 0.0 (stays in the
> denominator as a real gap), **n/a = excluded from the denominator**
> (cell does not exist for this subproject — see Legend).
>
> The "School 21 License" placeholders count ◐ for the F column —
> they are historical attribution but not sufficient on their own;
> the root MIT `LICENSE` (Phase 0) closes the gap repo-wide.
>
> Text-only / report-driven subprojects (`career_track/ct_*`,
> `internship/internship`, `qa/project_0*`, `survival_camp/`) mark
> B / C / D / E / G / H as **n/a** since there is no source code to
> test, lint, build, demo, or API-document. Only A (README) and F
> (LICENSE) are meaningful, so the denominator for those rows is 2.
> Previous roll-ups penalised these rows for "missing" work that was
> never in scope; the 2026-05-11 honesty pass corrected this.
>
> Numerator totals were also recounted from current cell values in
> the same pass (the prior 138/296 figure had drifted +25 cells over
> incremental updates).
