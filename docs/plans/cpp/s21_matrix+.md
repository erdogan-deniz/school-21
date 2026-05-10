# `cpp/s21_matrix+` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`cpp/s21_matrix+`](../../../cpp/s21_matrix+/)
- **Kind:** library
- **Language:** C++
- **Build system:** Makefile
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — GoogleTest in `src/`, coverage badge pending
- [~] **C.** GitHub Actions CI in `cpp.yml` matrix (informational); flip to green-gating after slice 4
- [~] **D.** Repo-wide `.clang-format` (Google) covers C++ too; deliberate format pass pending (slice 4)
- [x] **E.** `make` targets reproducible on the canonical Linux toolchain (g++17 + libgtest)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo — terminal capture of `S21Matrix` operator usage (`+`, `*`, inverse)
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add Doxygen comments for `S21Matrix` class and overloaded operators.
- [ ] Embed coverage % in README from `make gcov_report` (if Makefile supports it; otherwise add target).
- [ ] Decide whether to package as a header-only fallback (currently `.a` static library).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: Included in `cpp.yml` build/test matrix ([cc0ebb33](https://github.com/Deniz211/school-21/commit/cc0ebb33)).
- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
