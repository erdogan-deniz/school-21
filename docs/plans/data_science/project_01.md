# `data_science/project_01` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`data_science/project_01`](../../../data_science/project_01/)
- **Kind:** data-science project
- **Language:** Python
- **Build system:** varies
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** No formal pytest yet — accuracy threshold (≥ 0.832) checked from notebook runs
- [~] **C.** Covered by `python.yml` ruff job (lint over `data_science/`)
- [~] **D.** Repo-wide `.ruff.toml`; deliberate format pass pending
- [x] **E.** `Makefile` + `requirements.txt` make the venv setup reproducible (cross-platform via `OS` branch)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (notebook screenshot) — top-10 cosine similarity output preview
- [ ] **H.** Sphinx HTML for the notebook utilities

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add a CI smoke job: install deps, execute `notebooks/preprocessing.ipynb` headlessly, fail if cells error.
- [ ] Pin `scipy==1.10.1` is fragile — confirm it still installs on Python 3.12 (project may need a >= bound).
- [ ] Track accuracy / similarity output as a versioned artefact (badge: model accuracy % in README).
- [ ] Decide whether NLP corpus / models go into git LFS.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
