# `c/3DViewer_v1.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/3DViewer_v1.0`](../../../c/3DViewer_v1.0/)
- **Kind:** application
- **Language:** C + Qt6
- **Build system:** Makefile + qmake
- **Tests on disk:** yes (`src/3d_viewer_test.c`)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — `3d_viewer_test.c` exists, coverage badge pending
- [~] **C.** C-only test job in `c.yml` `apps-c-tests` matrix (informational); Qt-aware GUI build job pending (slice 2 follow-up)
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending (slice 4)
- [~] **E.** `make build` reproducible **only with Qt6 / qmake on PATH**; needs `qt6-base-dev` + headless GL for CI; document Docker recipe
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — orbit of a 1M-vertex `.obj`, recordable via the bonus Part 3 button
- [x] **H.** Doxygen API reference — file preamble + struct/function docs on `3d_viewer.h` (C core: `obj_data`, `polygons_t`, `matrix_t`, parser + transform pipeline) and `qt_viewer/{mainwindow,miwidget,filesbrows}.h` (legacy fixed-function GL host)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add Qt-aware CI job (`jurplel/install-qt-action` + `xvfb-run`) to `c.yml` to actually build the GUI in CI.
- [ ] Audit `qt_viewer/` `.pro` for hard-coded Windows paths leaked from the original Qt Creator project.
- [ ] Confirm `make install` target works on Linux as well as macOS (currently uses `~/Desktop/`).
- [ ] Sample `.obj` models (cube, teapot, low-poly toy) committed to `misc/samples/` — referenced from demo.
- [x] Doxygen comments on `3d_viewer.h` ([9def2070](https://github.com/erdogan-deniz/school-21/commit/9def2070)).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Included in `c.yml` `apps-c-tests` matrix for the C-only test layer ([30441670](https://github.com/erdogan-deniz/school-21/commit/30441670)).
- 2026-05-11: Doxygen rollout — C core + Qt host headers documented ([9def2070](https://github.com/erdogan-deniz/school-21/commit/9def2070)).
