# `data_science/bootcamp` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`data_science/bootcamp`](../../../data_science/bootcamp/)
- **Kind:** bootcamp (multi-day)
- **Language:** Python
- **Build system:** per-day setup.py / scripts
- **Tests on disk:** varies (per day)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** Top-level `data_science/bootcamp/README.md` adopts the repo template (per-day index)
- [ ] **B.** Per-day pytest TBD (no day in this bootcamp ships test files yet)
- [~] **C.** Covered by `python.yml` ruff job (lint over `data_science/`)
- [~] **D.** Repo-wide `.ruff.toml`; deliberate format pass pending
- [ ] **E.** Per-day reproducible build varies (notebooks vs scripts vs venvs)
- [~] **F.** Root MIT `LICENSE` ✓; per-day `LICENSE` files preserved as School 21 placeholders
- [ ] **G.** Demo (asciinema) — choose a representative day (Day 06 SQL or Day 08 ML)
- [ ] **H.** Sphinx HTML for the bootcamp as a whole

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Adopt the repo README template per-day (10 days + 2 team projects).
- [ ] Backfill pytest for at least 2-3 days (most likely Day 04 NumPy or Day 05 pandas).
- [ ] Confirm `charisel/` venv eviction (commit 554dc46a) didn't leave stragglers in other days.
- [ ] Cross-link Day 06 SQL day with `sql/bootcamp` once that subproject lands.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: Committed virtualenv (`charisel/`) evicted from index ([554dc46a](https://github.com/Deniz211/school-21/commit/554dc46a)).
- 2026-05-11: Top-level README created from repo template + day-by-day index; `python.yml` extended to lint `data_science/` (this commit).
