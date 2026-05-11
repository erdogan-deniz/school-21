# `devops/simple_docker` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`devops/simple_docker`](../../../devops/simple_docker/)
- **Kind:** Dockerfile + scripts
- **Language:** Docker / Bash
- **Build system:** n/a
- **Tests on disk:** n/a
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [~] **B.** `simple-docker-smoke` job in `devops.yml` — `docker compose up -d --build` + 30 s poll-loop + assert `Hello World` in `curl http://localhost:80` body + `docker compose down -v`. End-to-end proof the multi-service stack still works against current Docker. Per-component unit tests still TBD.
- [~] **C.** Covered by `devops.yml` (hadolint Dockerfile + shellcheck for any bash helpers)
- [~] **D.** hadolint via `devops.yml`
- [x] **E.** `docker build` + `docker-compose up` are one-liner reproducible
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — `docker-compose up` + browser hit on `localhost:80`
- [ ] **H.** Sphinx HTML — n/a (Dockerfile-driven subproject)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [x] Add a CI smoke job: `docker compose up -d` + `curl --fail localhost:80` + `docker compose down` (this commit).
- [ ] Run Dockle locally and address the warnings (Part 5 of the original task).
- [ ] Decide flagship status — strong candidate (publishable Docker image of the C+FastCGI mini-server).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved; `devops.yml` workflow (shellcheck + hadolint) added (this commit).
- 2026-05-11: `simple-docker-smoke` job added to `devops.yml` — full compose up + curl smoke; concurrent `chown 755` → `chmod 755` bug fix in the root Dockerfile (12 lines; the proxy Dockerfile already used `chmod`). STATUS B ✗→◐ (this commit).
