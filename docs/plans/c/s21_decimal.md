# `c/s21_decimal` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/s21_decimal`](../../../c/s21_decimal/)
- **Kind:** library
- **Language:** C
- **Build system:** Makefile
- **Tests on disk:** yes (`src/s21_test.c`)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests + coverage % visible in README — tests exist (`s21_test.c`), coverage badge pending
- [~] **C.** GitHub Actions CI in `c.yml` matrix (informational); flip to green-gating after slice 4
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending (slice 4)
- [x] **E.** `make` target reproducible on the canonical Linux toolchain
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif / screenshot / asciinema) — overflow / bank-rounding example
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Verify `s21_div` precision against the original .NET `System.Decimal` reference vectors.
- [ ] Add Doxygen comments for `s21_decimal.h` in slice 5.
- [ ] Embed coverage badge in README from `make gcov_report`.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/Deniz211/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved ([d8b012da](https://github.com/Deniz211/school-21/commit/d8b012da)).
- 2026-05-11: Included in `c.yml` build/test matrix ([8c5bd24d](https://github.com/Deniz211/school-21/commit/8c5bd24d)).
