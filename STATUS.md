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
| ✓      | Done                                              |
| ◐      | Partially done / in progress                      |
| ✗      | Not done                                          |
| n/a    | Not applicable for this subproject                |
| ★      | Flagship — also targets DoD-C (use as dependency) |
| ⚠      | Known broken / blocked by a tactical issue        |

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
| `3DViewer_v1.0`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | clang-format applied; C tests + Qt GUI build in c.yml (xvfb) |
| `SimpleBashUtils`  | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ◐ |          | clang-format applied; Codecov upload                          |
| `s21_decimal`      | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; Codecov upload                              |
| `s21_math`         | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ | ★        | flagship; release-s21_math.yml; Codecov upload                |
| `s21_matrix`       | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; Codecov upload                              |
| `s21_string+`      | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments; errno table preserved; Codecov upload       |
| `SmartCalc_v1.0`   | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | clang-format applied; C tests + Qt GUI build in c.yml (xvfb) |

### `career_track/`

| Subproject | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ct_00`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_01`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_02`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_03`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_04`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_05`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_06`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_07`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |
| `ct_08`    | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | text-only career project |

### `cpp/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes                                                    |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | -------------------------------------------------------- |
| `3DViewer_v2.0`         | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | clang-format applied; C++ tests + Qt GUI build (xvfb)        |
| `CPP5_3DViewer_v2.1`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | clang-format applied; C++ tests + Qt GUI build (xvfb)        |
| `CPP6_3DViewer_v2.2`    | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | clang-format applied; C++ tests + Qt GUI build (xvfb)        |
| `SmartCalc_v2.0`        | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ | ★        | clang-format applied; C++ tests + Qt GUI build (xvfb)        |
| `s21_containers`        | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ | ★        | flagship; release-s21_containers.yml; Codecov upload         |
| `s21_matrix+`           | ✓ | ◐ | ◐ | ✓ | ✗ | ◐ | ✗ | ✓ |          | Doxygen comments + class; Codecov upload                     |

### `data_science/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes                                                 |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------- |
| `bootcamp`   | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | top-level README; venv evicted (op 1.3 / 554dc46a)    |
| `project_01` | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | NLP "Tweets"; Makefile venv reproducible              |

### `devops/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ci_cd`                 | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report-driven; shellcheck via devops.yml |
| `linux`                 | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report-driven; shellcheck via devops.yml |
| `linux_monitoring_v1.0` | ✓ | ◐ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | bats suite for Part 1; shellcheck + hadolint via devops.yml |
| `linux_network`         | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report-driven; shellcheck via devops.yml |
| `simple_docker`         | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | docker-compose; hadolint via devops.yml  |

### `internship/`

| Subproject     | A | B | C | D | E | F | G | H | Flagship | Notes |
| -------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `internship`   | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | report subproject |

### `machine_learning/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | ✗ | ◐ | ✓ | ✗ | ✗ | ✗ | ✗ |          | ruff format applied via python.yml |

### `python/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `bootcamp`  | ✓ | ◐ | ◐ | ✓ | ◐ | ◐ | ✗ | ◐ |          | ruff format applied + pytest + Sphinx (day_07) + Pages     |

### `qa/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | report subproject; ruff format applied |
| `project_02` | ✓ | ✗ | ◐ | ✓ | ✗ | ◐ | ✗ | ✗ |          | report subproject; ruff format applied |

### `sql/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `bootcamp`  | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README templated; sqlfluff in sql.yml      |

### `survival_camp/`

| Subproject       | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `survival_camp`  | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          | historical record |

## Roll-up

| Track                | Subprojects | DoD cells filled | % done   |
| -------------------- | ----------- | ---------------- | -------- |
| `algorithms/`        | 1           | 3.5 / 8          | 44 %     |
| `c/`                 | 7           | 36 / 56          | 64 %     |
| `career_track/`      | 9           | 13.5 / 72        | 19 %     |
| `cpp/`               | 6           | 25 / 48          | 52 %     |
| `data_science/`      | 2           | 7 / 16           | 44 %     |
| `devops/`            | 5           | 17.5 / 40        | 44 %     |
| `internship/`        | 1           | 1.5 / 8          | 19 %     |
| `machine_learning/`  | 1           | 2.5 / 8          | 31 %     |
| `python/`            | 1           | 4.5 / 8          | 56 %     |
| `qa/`                | 2           | 6 / 16           | 38 %     |
| `sql/`               | 1           | 2.5 / 8          | 31 %     |
| `survival_camp/`     | 1           | 1 / 8            | 13 %     |
| **Total**            | **37**      | **130.5 / 296**  | **44 %** |

> "DoD cells filled" counts ✓ as 1 and ◐ as 0.5. The "School 21
> License" placeholders count ◐ for the F column — they are
> historical attribution but not sufficient on their own; the root
> MIT `LICENSE` (Phase 0) closes the gap repo-wide.
