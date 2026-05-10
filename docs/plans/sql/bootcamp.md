# `sql/bootcamp` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`sql/bootcamp`](../../../sql/bootcamp/)
- **Kind:** bootcamp (multi-day)
- **Language:** SQL
- **Build system:** per-day .sql scripts
- **Tests on disk:** varies (per day)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + day-by-day index)
- [ ] **B.** Per-day end-to-end runs against a Postgres service container — TBD
- [~] **C.** GitHub Actions CI in `sql.yml` (sqlfluff lint, postgres dialect; `continue-on-error: true`)
- [~] **D.** sqlfluff config implicit (postgres dialect via CLI flag); explicit `.sqlfluff` config TBD
- [ ] **E.** Per-day reproducible build varies (no top-level Makefile; psql one-liners)
- [~] **F.** Root MIT `LICENSE` ✓; per-day `LICENSE` files preserved as School 21 placeholders
- [ ] **G.** Demo (asciinema) — Day 07 OLAP or Day 08 transaction-isolation walkthrough
- [ ] **H.** Sphinx HTML for the bootcamp as a whole

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add explicit `.sqlfluff` config at repo root (or `sql/.sqlfluff`) with rule excludes for the educational dialect.
- [ ] Service-container Postgres in `sql.yml` for end-to-end day script execution.
- [ ] Per-day README adoption (10 days + 2 team projects).
- [ ] Cross-link `data_science/bootcamp/day_06` (SQL) with this bootcamp.
- [ ] Day 09 (triggers / Fibonacci) is a great demo candidate.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from former empty `#` placeholder + day-by-day index; `sql.yml` workflow added ([4bc35f94](https://github.com/Deniz211/school-21/commit/4bc35f94)).
