# `devops/ci_cd` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`devops/ci_cd`](../../../devops/ci_cd/)
- **Kind:** script-collection
- **Language:** shell / yaml
- **Build system:** n/a
- **Tests on disk:** n/a
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** No formal unit tests — pipeline itself runs SimpleBashUtils integration tests as Stage 4
- [~] **C.** Covered by `devops.yml` (shellcheck for any helper bash; the actual pipeline runs in GitLab CI per the report)
- [~] **D.** shellcheck via `devops.yml`
- [ ] **E.** Pipeline is the artefact — runs only on a registered GitLab runner, not reproducible locally
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — full pipeline run + Telegram notification
- [ ] **H.** Sphinx HTML — n/a (report-driven subproject)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Mirror the GitLab `gitlab-ci.yml` into a GitHub `ci_cd-mirror.yml` workflow so the pipeline shape can be evaluated directly here.
- [ ] Cross-link with `c/SimpleBashUtils` (the project being built/tested by this pipeline).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved; `devops.yml` workflow (shellcheck + hadolint) added (this commit).
