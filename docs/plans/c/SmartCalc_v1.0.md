# `c/SmartCalc_v1.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/SmartCalc_v1.0`](../../../c/SmartCalc_v1.0/)
- **Kind:** application
- **Language:** C + Qt6
- **Build system:** Makefile + qmake
- **Tests on disk:** yes (`src/tests/`)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — `src/tests/` exists, coverage badge pending
- [~] **C.** C-only test job in `c.yml` `apps-c-tests` matrix (informational); Qt-aware GUI build job pending (slice 2 follow-up)
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending (slice 4)
- [~] **E.** `make test` reproducible on the canonical Linux toolchain; `make install` requires Qt6 / qmake
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — RPN evaluator + `f(x)` plot in action
- [x] **H.** Doxygen API reference — file preambles + class/function docs across core (`s21_calculator.h`, `s21_main.h`, parser/calc/transform/stack/list/additional/validation/bonus/finance) and Qt view panels (start_window, window_one/two/three)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add Qt-aware CI job (jurplel/install-qt-action + `xvfb-run`) for the GUI build.
- [ ] Audit `view/view.pro` for any leaked Windows-only paths from the original Qt Creator project.
- [ ] Clean up the recently-added `s21_finance` module: confirm Doxygen + tests cover loan and deposit.
- [ ] Confirm `make install` works under both Linux and macOS (the Makefile already branches on `uname`).
- [ ] Decide whether SmartCalc deserves flagship status (candidate due to packaged-release potential).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: SmartCalc rename to PascalCase canonical, dead-code/MOC eviction, Qt asset recovery from history ([a6744d9d](https://github.com/erdogan-deniz/school-21/commit/a6744d9d)).
- 2026-05-11: Included in `c.yml` `apps-c-tests` matrix for the C-only test layer ([30441670](https://github.com/erdogan-deniz/school-21/commit/30441670)).
- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Doxygen rollout — full module set documented ([9def2070](https://github.com/erdogan-deniz/school-21/commit/9def2070)).
