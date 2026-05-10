# `devops/linux_monitoring_v1.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`devops/linux_monitoring_v1.0`](../../../devops/linux_monitoring_v1.0/)
- **Kind:** script-collection
- **Language:** Bash
- **Build system:** n/a
- **Tests on disk:** n/a
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** No bats test coverage yet — bash scripts are tested manually by running each `0x/main.sh`
- [~] **C.** Covered by `devops.yml` (shellcheck across the 5 task `0x/main.sh` chains)
- [~] **D.** shellcheck via `devops.yml`
- [x] **E.** `bash 0x/main.sh ...` reproducible on any POSIX shell (Ubuntu 20.04 Server LTS canonical)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — `02/main.sh` system snapshot or `05/main.sh` filesystem report
- [ ] **H.** Sphinx HTML — n/a (script-collection subproject)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add `bats` (Bash Automated Testing System) coverage for `02/main.sh` (interactive Y/N branch) and `05/main.sh` (filesystem stats).
- [ ] Address shellcheck warnings before flipping `continue-on-error` to false on `devops.yml`.
- [ ] Consider a tiny Dockerfile that bundles the scripts for one-line `docker run`.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved; `devops.yml` workflow (shellcheck + hadolint) added (this commit).
