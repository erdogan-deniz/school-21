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
| `python/`   | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |

### `c/`

| Subproject         | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ------------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `3DViewer_v1.0`    | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C tests in c.yml; Qt GUI build deferred     |
| `SimpleBashUtils`  | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_decimal`      | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_math`         | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_matrix`       | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `s21_string+`      | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; CI in c.yml matrix (informational)          |
| `SmartCalc_v1.0`   | ✓ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | README adopted; C tests in c.yml; rename in a6744d9d        |

### `career_track/`

| Subproject | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ct_00`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_01`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_02`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_03`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_04`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_05`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_06`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_07`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `ct_08`    | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |

### `cpp/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes                    |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | ------------------------ |
| `3DViewer_v2.0`         | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | C++ tests in cpp.yml; Qt GUI build deferred to follow-up |
| `CPP5_3DViewer_v2.1`    | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | C++ tests in cpp.yml; Qt GUI build deferred to follow-up |
| `CPP6_3DViewer_v2.2`    | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | C++ tests in cpp.yml; Qt GUI build deferred to follow-up |
| `SmartCalc_v2.0`        | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | C++ tests in cpp.yml; Qt GUI build deferred to follow-up |
| `s21_containers`        | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | CI in cpp.yml matrix (build/test informational)          |
| `s21_matrix+`           | ◐ | ✗ | ◐ | ◐ | ✗ | ◐ | ✗ | ✗ |          | CI in cpp.yml matrix (build/test informational)          |

### `data_science/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes                                                 |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------- |
| `bootcamp`   | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | committed venv evicted from index (op 1.3 / 554dc46a) |
| `project_01` | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |                                                       |

### `devops/`

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `ci_cd`                 | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `linux`                 | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `linux_monitoring_v1.0` | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `linux_network`         | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |
| `simple_docker`         | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |

### `internship/`

| Subproject     | A | B | C | D | E | F | G | H | Flagship | Notes |
| -------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `internship`   | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |

### `machine_learning/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |

### `python/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes                                                       |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----------------------------------------------------------- |
| `bootcamp`  | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | README adopted from former root README2.md (op 1.5)         |

### `qa/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `project_01` | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |
| `project_02` | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |

### `sql/`

| Subproject  | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `bootcamp`  | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          |       |

### `survival_camp/`

| Subproject       | A | B | C | D | E | F | G | H | Flagship | Notes |
| ---------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `survival_camp`  | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |

## Roll-up

| Track                | Subprojects | DoD cells filled | % done   |
| -------------------- | ----------- | ---------------- | -------- |
| `algorithms/`        | 1           | 0 / 8            | 0 %      |
| `c/`                 | 7           | 25.5 / 56        | 46 %     |
| `career_track/`      | 9           | 9 / 72           | 13 %     |
| `cpp/`               | 6           | 18 / 48          | 38 %     |
| `data_science/`      | 2           | 1 / 16           | 6 %      |
| `devops/`            | 5           | 5 / 40           | 13 %     |
| `internship/`        | 1           | 1 / 8            | 13 %     |
| `machine_learning/`  | 1           | 0 / 8            | 0 %      |
| `python/`            | 1           | 1 / 8            | 13 %     |
| `qa/`                | 2           | 0 / 16           | 0 %      |
| `sql/`               | 1           | 1 / 8            | 13 %     |
| `survival_camp/`     | 1           | 0 / 8            | 0 %      |
| **Total**            | **37**      | **61.5 / 296**   | **21 %** |

> "DoD cells filled" counts ✓ as 1 and ◐ as 0.5. The "School 21
> License" placeholders count ◐ for the F column — they are
> historical attribution but not sufficient on their own; the root
> MIT `LICENSE` (Phase 0) closes the gap repo-wide.
