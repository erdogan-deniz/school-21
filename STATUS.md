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
| `python/maze` | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | README templated; covered by python.yml ruff job |

### `c/`

| Subproject         | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ------------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `3DViewer_v1.0`    | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C tests + Qt GUI build in c.yml (xvfb)      |
| `SimpleBashUtils`  | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_decimal`      | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_math`         | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_matrix`       | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_string+`      | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `SmartCalc_v1.0`   | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C tests + Qt GUI build in c.yml (xvfb)      |

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
| `3DViewer_v2.0`         | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C++ tests + Qt GUI build in cpp.yml (xvfb)  |
| `CPP5_3DViewer_v2.1`    | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C++ tests + Qt GUI build in cpp.yml (xvfb)  |
| `CPP6_3DViewer_v2.2`    | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C++ tests + Qt GUI build in cpp.yml (xvfb)  |
| `SmartCalc_v2.0`        | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C++ tests + Qt GUI build in cpp.yml (xvfb)  |
| `s21_containers`        | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in cpp.yml matrix (informational)        |
| `s21_matrix+`           | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in cpp.yml matrix (informational)        |

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
| `linux_monitoring_v1.0` | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | bash 0x/main.sh; shellcheck via devops.yml |
| `linux_network`         | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report-driven; shellcheck via devops.yml |
| `simple_docker`         | ✓ | ✗ | ◐ | ◐ | ✓ | ◐ | ✗ | ✗ |          | docker-compose; hadolint via devops.yml  |

### `internship/`

| Subproject     | A | B | C | D | E | F | G | H | Flagship | Notes |
| -------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `internship`   | ✓ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | report subproject |

### `machine_learning/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | ✗ | ◐ | ◐ | ✗ | ✗ | ✗ | ✗ |          | covered by python.yml ruff |

### `python/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `bootcamp`  | ✓ | ◐ | ◐ | ◐ | ◐ | ◐ | ✗ | ✗ |          | README templated; ruff + per-day pytest in python.yml       |

### `qa/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report subproject; ruff via python.yml |
| `project_02` | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | report subproject; ruff via python.yml |

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
| `algorithms/`        | 1           | 3 / 8            | 38 %     |
| `c/`                 | 7           | 25.5 / 56        | 46 %     |
| `career_track/`      | 9           | 13.5 / 72        | 19 %     |
| `cpp/`               | 6           | 21 / 48          | 44 %     |
| `data_science/`      | 2           | 6 / 16           | 38 %     |
| `devops/`            | 5           | 17 / 40          | 43 %     |
| `internship/`        | 1           | 1.5 / 8          | 19 %     |
| `machine_learning/`  | 1           | 2 / 8            | 25 %     |
| `python/`            | 1           | 3.5 / 8          | 44 %     |
| `qa/`                | 2           | 5 / 16           | 31 %     |
| `sql/`               | 1           | 2.5 / 8          | 31 %     |
| `survival_camp/`     | 1           | 1 / 8            | 13 %     |
| **Total**            | **37**      | **111.5 / 296**  | **38 %** |

> "DoD cells filled" counts ✓ as 1 and ◐ as 0.5. The "School 21
> License" placeholders count ◐ for the F column — they are
> historical attribution but not sufficient on their own; the root
> MIT `LICENSE` (Phase 0) closes the gap repo-wide.
