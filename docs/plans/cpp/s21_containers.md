# `cpp/s21_containers` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`cpp/s21_containers`](../../../cpp/s21_containers/)
- **Kind:** library (header-only STL replica)
- **Language:** C++
- **Build system:** Makefile
- **Tests on disk:** varies
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests — `tests.cc` with GoogleTest, coverage badge pending
- [~] **C.** GitHub Actions CI in `cpp.yml` matrix (informational); flip to green-gating after slice 4
- [~] **D.** Repo-wide `.clang-format` (Google) covers C++ too; `make clang` target available; deliberate format pass pending
- [x] **E.** `make` targets reproducible on the canonical Linux toolchain (g++17 + libgtest)
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo — terminal capture of typical container usage (vector, map, iterator semantics)
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add Doxygen comments per container header (`s21_list.h`, `s21_vector.h`, `s21_map.h`, `s21_set.h`, `s21_stack.h`, `s21_queue.h`, `s21_array.h`, `s21_multiset.h`).
- [ ] Verify `insert_many` Parameter Pack edge cases for each container.
- [ ] Decide flagship status — strong candidate (header-only STL replica, immediately reusable as a dependency).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: Included in `cpp.yml` build/test matrix ([cc0ebb33](https://github.com/erdogan-deniz/school-21/commit/cc0ebb33)).
- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
