# `c/s21_math` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/s21_math`](../../../c/s21_math/)
- **Kind:** library
- **Language:** C
- **Build system:** Makefile
- **Tests on disk:** yes (`src/unit_test.c`)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests + coverage % visible in README — tests exist (`unit_test.c`), coverage badge pending
- [~] **C.** GitHub Actions CI in `c.yml` matrix (build/test informational, `continue-on-error: true`); flip to green-gating after slice 4
- [~] **D.** Repo-wide `.clang-format` (Google) at root; deliberate format pass on `*.c` / `*.h` pending (slice 4)
- [x] **E.** `make` target reproducible on the canonical Linux toolchain (gcc + libcheck + lcov, see `c.yml`)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif / screenshot / asciinema) — captured terminal run of `./test`
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add `s21_math.h` Doxygen comments in slice 5.
- [ ] Capture coverage % from `make gcov_report` and embed badge in README.
- [ ] Decide flagship status (candidate due to standalone library nature).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved ([3a8752a7](https://github.com/Deniz211/school-21/commit/3a8752a7)).
- 2026-05-11: Repo-wide `.clang-format` and `c.yml` workflow with build/test matrix added ([3f64148d](https://github.com/Deniz211/school-21/commit/3f64148d), [8c5bd24d](https://github.com/Deniz211/school-21/commit/8c5bd24d)).
