# `cpp/3DViewer_v2.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`cpp/3DViewer_v2.0`](../../../cpp/3DViewer_v2.0/)
- **Kind:** application
- **Language:** C++ + Qt
- **Build system:** Makefile + qmake
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — `src/tests/`, coverage badge pending
- [~] **C.** C++-only test job in `cpp.yml` `apps-cpp-tests` matrix; Qt-aware GUI build job pending
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending
- [~] **E.** `make install` requires Qt6 / qmake; document Docker recipe
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — orbit of a 1M-vertex `.obj`, recordable via the bonus Part 3 button
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Document the chosen 3+ design patterns (e.g. facade, strategy, command) in README + Doxygen.
- [ ] Add Qt-aware CI job (jurplel/install-qt-action + xvfb-run).
- [ ] Confirm reuse of `cpp/s21_matrix+` for affine transformations is wired up correctly.
- [ ] Sample `.obj` models in `misc/samples/`.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: Included in `cpp.yml` `apps-cpp-tests` matrix ([cc0ebb33](https://github.com/erdogan-deniz/school-21/commit/cc0ebb33)).
- 2026-05-11: README adopted from repo template + Original task preserved ([80403498](https://github.com/erdogan-deniz/school-21/commit/80403498)).
