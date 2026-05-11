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
- [~] **B.** Per-day schema-load smoke runs against a Postgres 16 service container — `make test-all` + the matching `sql.yml bootcamp-schema-load` job verify every `model.sql` parses cleanly. Per-exercise assertions still TBD.
- [~] **C.** GitHub Actions CI in `sql.yml` (sqlfluff lint, postgres dialect; `continue-on-error: true`)
- [~] **D.** sqlfluff config implicit (postgres dialect via CLI flag); explicit `.sqlfluff` config TBD
- [x] **E.** `sql/bootcamp/docker-compose.yml` + `Makefile` one-line workflow (`make up && make psql DAY=NN`) — Postgres 16 in Docker, bootcamp tree bind-mounted, healthcheck-blocked startup, `make test-all` smoke target.
- [~] **F.** Root MIT `LICENSE` ✓; per-day `LICENSE` files preserved as School 21 placeholders
- [ ] **G.** Demo (asciinema) — Day 07 OLAP or Day 08 transaction-isolation walkthrough
- [ ] **H.** Sphinx HTML for the bootcamp as a whole

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add explicit `.sqlfluff` config at repo root (or `sql/.sqlfluff`) with rule excludes for the educational dialect.
- [x] Service-container Postgres in `sql.yml` — new `bootcamp-schema-load` job iterates the 10 numbered days and asserts every `model.sql` loads against `public` (this commit).
- [ ] Per-day README adoption (10 days + 2 team projects).
- [ ] Cross-link `data_science/bootcamp/day_06` (SQL) with this bootcamp.
- [ ] Day 09 (triggers / Fibonacci) is a great demo candidate.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from former empty `#` placeholder + day-by-day index; `sql.yml` workflow added ([4bc35f94](https://github.com/erdogan-deniz/school-21/commit/4bc35f94)).
- 2026-05-11: `docker-compose.yml` + `Makefile` for one-line reproducible setup; `sql.yml` gains the `bootcamp-schema-load` job spinning up Postgres 16 service container + iterating 10 numbered days (this commit). STATUS sql/bootcamp B ✗→◐, E ✗→✓.
