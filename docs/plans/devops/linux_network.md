# `devops/linux_network` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`devops/linux_network`](../../../devops/linux_network/)
- **Kind:** script-collection
- **Language:** Bash
- **Build system:** n/a
- **Tests on disk:** n/a
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Report-driven subproject — no automated tests apply
- [~] **C.** Covered by `devops.yml` (shellcheck for any helper bash, including `firewall.sh` snippets in `materials/`)
- [~] **D.** shellcheck via `devops.yml`
- [ ] **E.** Multi-VM reproducibility hard — needs Vagrant/Terraform; documented via netplan/dhcpd snippets in `materials/`
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — multi-VM static-routing demo (Part 5)
- [ ] **H.** Sphinx HTML — n/a (report-driven subproject)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Vagrantfile or `docker-compose` topology (5 nodes: 3 workstations + 2 routers) so Part 5 is reproducible.
- [ ] Cross-link with `devops/simple_docker` (NAT vs container networking).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved; `devops.yml` workflow (shellcheck + hadolint) added (this commit).
