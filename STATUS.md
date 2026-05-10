# `school-21` — production-readiness dashboard

Single source of truth for the production-grade overhaul of every
subproject. Updated on every batch commit. Secondary views (GitHub
Projects board, GitHub Issues + milestones) are derived from this
file — never edited by hand.

## Legend

| Symbol | Meaning                           |
| ------ | --------------------------------- |
| ✓      | Done                              |
| ◐      | Partially done / in progress      |
| ✗      | Not done                          |
| n/a    | Not applicable for this subproject |
| ★      | Flagship — also targets DoD-C (use as dependency) |
| ⚠      | Known broken / blocked by a tactical issue |

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
| `3DViewer_v1.0`    | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `SimpleBashUtils`  | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `s21_decimal`      | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `s21_math`         | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `s21_matrix`       | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `s21_string+`      | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present                                    |
| `SmartCalc_v1.0`   | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present; rename resolved (commit a6744d9d) |

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

| Subproject              | A | B | C | D | E | F | G | H | Flagship | Notes |
| ----------------------- | - | - | - | - | - | - | - | - | -------- | ----- |
| `3DViewer_v2.0`         | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |
| `CPP5_3DViewer_v2.1`    | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |
| `CPP6_3DViewer_v2.2`    | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |
| `SmartCalc_v2.0`        | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |
| `s21_containers`        | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |
| `s21_matrix+`           | ◐ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | School 21 README present |

### `data_science/`

| Subproject   | A | B | C | D | E | F | G | H | Flagship | Notes |
| ------------ | - | - | - | - | - | - | - | - | -------- | ----- |
| `bootcamp`   | ✗ | ✗ | ✗ | ✗ | ✗ | ◐ | ✗ | ✗ |          | committed venv — Phase 1 op 1.3 |
| `project_01` | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ | ✗ |          |       |

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

| Track          | Subprojects | DoD cells filled | % done |
| -------------- | ----------- | ---------------- | ------ |
| `algorithms/`  | 1           | 0 / 8            | 0 %    |
| `c/`           | 7           | 14 / 56          | 25 %   |
| `career_track/`| 9           | 9 / 72           | 13 %   |
| `cpp/`         | 6           | 12 / 48          | 25 %   |
| `data_science/`| 2           | 1 / 16           | 6 %    |
| `devops/`      | 5           | 5 / 40           | 13 %   |
| `internship/`  | 1           | 1 / 8            | 13 %   |
| `machine_learning/` | 1      | 0 / 8            | 0 %    |
| `python/`      | 1           | 1 / 8            | 13 %   |
| `qa/`          | 2           | 0 / 16           | 0 %    |
| `sql/`         | 1           | 1 / 8            | 13 %   |
| `survival_camp/` | 1         | 0 / 8            | 0 %    |
| **Total**      | **37**      | **44 / 296**     | **15 %** |

> "DoD cells filled" counts ✓ as 1 and ◐ as 0.5. The "School 21
> License" placeholders count ◐ for the F column — they are
> historical attribution but not sufficient on their own; the root
> MIT `LICENSE` (Phase 0) closes the gap repo-wide.
