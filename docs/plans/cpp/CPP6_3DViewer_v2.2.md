# `cpp/CPP6_3DViewer_v2.2` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`cpp/CPP6_3DViewer_v2.2`](../../../cpp/CPP6_3DViewer_v2.2/)
- **Kind:** application
- **Language:** C++ + Qt
- **Build system:** Makefile + qmake
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — coverage badge pending
- [~] **C.** C++-only test job in `cpp.yml` `apps-cpp-tests` matrix; Qt-aware GUI build job pending
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending
- [~] **E.** `make install` requires Qt6 / qmake
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif + still) — wireframe → flat → Phong → ray-traced; cornell-box style still render for the README header
- [x] **H.** Doxygen API reference — file preambles + class docs on `Controller`, `Parse` singleton, `scene`, `viewer` (mirrors CPP5; v2.2 interface is byte-identical to v2.1)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Document KD-tree intersection optimisation in README + Doxygen.
- [ ] Sample primitive scenes (sphere, cylinder, cone, cube, pyramid) in `misc/samples/`.
- [ ] Performance benchmark: render time vs. resolution for the 5-light, 5-model case.
- [ ] Add Qt-aware CI job for the GUI build.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: Included in `cpp.yml` `apps-cpp-tests` matrix ([cc0ebb33](https://github.com/erdogan-deniz/school-21/commit/cc0ebb33)).
- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Doxygen rollout — Controller / Parsing / GLWidget / Viewer headers documented ([d7960ba6](https://github.com/erdogan-deniz/school-21/commit/d7960ba6)).
