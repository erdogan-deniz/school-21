# `algorithms/python` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`algorithms/python`](../../../algorithms/python/)
- **Kind:** script-collection
- **Language:** Python
- **Build system:** varies
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task) — applied at `algorithms/python/maze/README.md`
- [ ] **B.** Unit tests — pytest scaffold present, coverage badge pending
- [~] **C.** GitHub Actions CI in `python.yml` (ruff over `algorithms/python/`, pytest job per-day matrix in same workflow)
- [~] **D.** Repo-wide `.ruff.toml`; deliberate format pass pending
- [x] **E.** `pip install -e .` reproducible (real `pyproject.toml` at `algorithms/python/maze/`)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — Eller's-algorithm maze + Q-learning agent solving it
- [ ] **H.** Sphinx HTML — already a project requirement (see "Web-interface" task)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add a pytest matrix entry for `algorithms/python/maze` in `.github/workflows/python.yml` (currently only `python/bootcamp/old/day_{05,07,09}` are listed).
- [ ] Implement / wire up `make tests` against the existing `pytest` infra under `algorithms/python/maze/`.
- [ ] Decide whether to track `algorithms/python` or its child `maze` as the canonical subproject row in STATUS.md (currently the row is at the parent path).
- [ ] Sphinx HTML for `docs/` (already part of the original task — `Web-interface` requirement).
- [ ] Sample `.maze` and `.cave` files in a top-level `samples/` directory for reproducible demo runs.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template at `algorithms/python/maze/README.md` + Original task preserved (this commit).
- 2026-05-11: Covered by `python.yml` ruff job (no per-day pytest entry yet) ([af77283e](https://github.com/erdogan-deniz/school-21/commit/af77283e)).
