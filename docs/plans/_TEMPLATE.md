<!--
  Per-subproject production-readiness plan template.

  How to use:
  - Copy this file to docs/plans/<track>/<subproject>.md.
  - Fill in the "At a glance" header.
  - Tick checklist items as DoD letters land.
  - Add subproject-specific tasks below the checklist.
  - Append a one-line History entry per session, with a commit link.

  Status updates flow back to /STATUS.md (top-level dashboard).
-->

# `<subproject>` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: YYYY-MM-DD.

## At a glance

- **Path:** [`<relative path>`](../../../<relative path>/)
- **Kind:** library | application | bootcamp-day | script-collection | course-track
- **Language:** C | C++ | Python | SQL | Bash | mixed
- **Build system:** Makefile | CMake | qmake | setup.py / pyproject.toml | none
- **Tests on disk:** yes (`<path>`) | no
- **Flagship:** no | yes (target DoD-C: use as dependency / packaged release)

## Definition of Done — checklist

- [ ] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests + coverage % visible in README
- [ ] **C.** GitHub Actions CI green + badge in README
- [ ] **D.** Linter / formatter applied (clang-format / ruff / sqlfluff / shellcheck / …)
- [ ] **E.** Reproducible build (Dockerfile or Makefile — one command)
- [ ] **F.** `LICENSE` present (MIT root + School 21 placeholder kept)
- [ ] **G.** Demo (gif / screenshot / asciinema)
- [ ] **H.** Doxygen / Sphinx API docs

## Subproject-specific tasks

- [ ] (placeholder — to be filled in during per-subproject review)

## History

<!--
  Append entries chronologically as work happens.
  Format: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>))
-->

- *(no entries yet)*
