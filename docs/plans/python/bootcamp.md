# `python/bootcamp` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`python/bootcamp`](../../../python/bootcamp/)
- **Kind:** bootcamp (multi-day + team projects)
- **Language:** Python
- **Build system:** per-day pyproject.toml / setup.py
- **Tests on disk:** varies (per day)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [~] **B.** pytest in CI for `day_05`, `day_07`, `day_09`; other days have no tests yet
- [~] **C.** GitHub Actions CI in `python.yml` (ruff + per-day pytest matrix; `continue-on-error: true`)
- [~] **D.** Repo-wide `.ruff.toml` (modest ruleset); deliberate format pass pending
- [~] **E.** `pip install -e .` reproducible only for `new/day_*` (real pyproject.toml); `old/day_*` is loose-script style
- [~] **F.** Root MIT `LICENSE` ✓; per-day `LICENSE` files preserved as School 21 placeholders
- [ ] **G.** Demo (asciinema) — Day 05 Flask REST API or Day 08 async crawler
- [ ] **H.** Sphinx HTML for Day 07 (Voight-Kampff), API references for `new/day_*`

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Backfill tests for days 00, 01, 02, 03, 04, 06, 08, team_00, team_01.
- [ ] Migrate every `old/day_*` to `new/day_*` style (`pyproject.toml`, src layout, ruff-clean).
- [ ] Sphinx for Day 07 — already part of the original task ("Created project documentation using Sphinx").
- [ ] Decide a global Python toolchain (3.12 currently) and pin in CI.
- [ ] Address the 2 untracked items in `python/bootcamp/new/day_01/` (`docs/`, `src/models/__init__.py`) — they appeared in `git status` since session start.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from former root `README2.md` ([c53e9251](https://github.com/Deniz211/school-21/commit/c53e9251)).
- 2026-05-11: Repo-wide `.ruff.toml` and `python.yml` workflow (ruff + per-day pytest matrix) added (this commit).
- 2026-05-11: README brought to repo template (production fold + day-by-day index) (this commit).
