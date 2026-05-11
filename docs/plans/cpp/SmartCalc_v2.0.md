# `cpp/SmartCalc_v2.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`cpp/SmartCalc_v2.0`](../../../cpp/SmartCalc_v2.0/)
- **Kind:** application
- **Language:** C++ + Qt
- **Build system:** Makefile + qmake
- **Tests on disk:** varies
- **Flagship:** **yes (★)** — designated 2026-05-11; release pipeline pending

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — `src/UnitTests/`, coverage badge pending
- [~] **C.** C++-only test job in `cpp.yml` `apps-cpp-tests` matrix; Qt-aware GUI build job pending
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending
- [~] **E.** `make install` requires Qt6 / qmake
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — RPN evaluation + `f(x)` plot in action
- [x] **H.** Doxygen API reference — file preambles + class docs on MVC layers: `Controller/{calculator,credit,deposit}controller.h` (facade pattern) and `Model/{calculator,credit,deposit}model.h` (shunting-yard / RPN + financial schedules)

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [x] Document MVC layering (Model/Controller/View) in README + Doxygen ([69da2920](https://github.com/erdogan-deniz/school-21/commit/69da2920)).
- [ ] Cross-test the calculator model against `c/SmartCalc_v1.0` reference outputs.
- [ ] Add Qt-aware CI job for the GUI build.
- [ ] Decide flagship status — strong candidate (packaged-release potential).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: Included in `cpp.yml` `apps-cpp-tests` matrix ([cc0ebb33](https://github.com/erdogan-deniz/school-21/commit/cc0ebb33)).
- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Doxygen rollout — Controller + Model headers documented (MVC + shunting-yard architecture) ([69da2920](https://github.com/erdogan-deniz/school-21/commit/69da2920)).
