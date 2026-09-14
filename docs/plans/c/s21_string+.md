# `c/s21_string+` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/s21_string+`](../../../c/s21_string+/)
- **Kind:** library
- **Language:** C
- **Build system:** Makefile
- **Tests on disk:** yes (`src/s21_string_test.c`)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Unit tests + coverage % visible in README — tests exist (`s21_string_test.c`), coverage badge pending
- [~] **C.** GitHub Actions CI in `c.yml` matrix (informational); flip to green-gating after slice 4
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending (slice 4)
- [x] **E.** `make` target reproducible on the canonical Linux toolchain
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif / screenshot / asciinema) — `sprintf` formatter showcase
- [ ] **H.** Doxygen API reference

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Verify `sprintf` against glibc reference for the full flag × width × precision × length matrix.
- [ ] Cross-platform `strerror` table (Linux vs macOS sys_errlist) — confirm both branches still build.
- [ ] Add Doxygen comments for `s21_string.h`.
- [ ] Embed coverage badge in README from `make gcov_report`.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Included in `c.yml` build/test matrix ([8c5bd24d](https://github.com/erdogan-deniz/school-21/commit/8c5bd24d)).
- 2026-09-14: clang-format 18.1.3 pass (the runner's version; 18.1.8 accepted the file) — `c / clang-format check` green again ([75f638e](https://github.com/erdogan-deniz/school-21/commit/75f638e)).
- 2026-09-14: Makefile links Check via `pkg-config --libs check` (bare `-lcheck` fallback), replacing the uname branch ([bcc2e1f](https://github.com/erdogan-deniz/school-21/commit/bcc2e1f)); the two `"%%"` sprintf tests pass literal formats so Ubuntu's default `-Wformat-security` + `-Werror` compiles again ([06b3f34](https://github.com/erdogan-deniz/school-21/commit/06b3f34)).
- 2026-09-14: **Known red:** `sprintf_null_ptr` fails on glibc — `%p` of NULL prints `(nil)` there, `0x0` in `s21_sprintf` (macOS parity). Pre-existing; decide between matching the host libc or making the test platform-tolerant.
- 2026-09-14: `sprintf_null_ptr` made libc-tolerant — accepts `(nil)` and `0x0`, checks the return value against the produced length; `s21_sprintf` keeps `0x0` ([6e27ec9](https://github.com/erdogan-deniz/school-21/commit/6e27ec9)). Root cause of the "green" run on `e625ee7`: the job *was* red (602 checks, 1 failure, Build step exit 2 because `all:` runs `test`), masked by the job-level `continue-on-error: true` — item C stays `[~]` until that flag is dropped.
