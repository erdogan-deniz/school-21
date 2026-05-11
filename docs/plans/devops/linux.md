# `devops/linux` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`devops/linux`](../../../devops/linux/)
- **Kind:** script-collection
- **Language:** Bash
- **Build system:** n/a
- **Tests on disk:** n/a
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Report-driven subproject — no automated tests apply
- [~] **C.** Covered by `devops.yml` (shellcheck for any helper bash in `src/`)
- [~] **D.** shellcheck via `devops.yml`
- [ ] **E.** VirtualBox + Ubuntu 20.04 Server LTS image — not reproducible in CI; `materials/` documents the steps
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (screenshot collage) — htop + sudo + CRON output from the report
- [ ] **H.** Sphinx HTML — n/a (report-driven subproject)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add a Vagrantfile or cloud-init recipe so the Ubuntu Server admin tasks can be reproduced reproducibly.
- [ ] Convert the per-task screenshots in the report into asciinema casts where applicable.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved; `devops.yml` workflow (shellcheck + hadolint) added (this commit).
