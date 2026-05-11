# `machine_learning/project_01` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- Filled in during the README adoption pass — see the project's own README header for path / kind / language / build details.
- **Flagship:** no.

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests + coverage — notebook-only; pending extraction of a helper module under `src/` plus a pytest harness
- [~] **C.** `python.yml` ruff + path-trigger covers the subproject; no per-project test job (no tests yet)
- [x] **D.** `ruff` (repo-wide `.ruff.toml`) applied via `python.yml`
- [x] **E.** `Makefile` venv workflow — `make install / notebook / check / clear`; pinned `requirements.txt` (numpy / scipy / pandas / xgboost / matplotlib / scikit-learn) with semver upper bounds
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — Jupyter notebook walk-through, or a static screenshot of the MAE / RMSE result tables
- [ ] **H.** Doxygen / Sphinx API docs — n/a until functions move out of the notebook

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Extract feature-engineering helpers (`polynomial_features`,
      `evaluate_mae_rmse`, `decode_interest_level`) from `notebooks/workflow.ipynb`
      into `src/ml/utils.py` so pytest can exercise them outside the notebook.
- [ ] Add `tests/test_utils.py` with smoke + property checks on the
      extracted helpers; wire into `python.yml` `pytest` matrix.
- [ ] Decide whether to host a rendered HTML of the notebook (`nbconvert
      --to html`) under the unified GitHub Pages site.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved.
- 2026-05-11: `Makefile` venv workflow + pinned `requirements.txt`; obsolete `commands.txt` evicted; README quick-start rewritten around `make install / notebook / clear`. STATUS ML row E ✗→✓ (this commit).
