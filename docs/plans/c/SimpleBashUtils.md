# `c/SimpleBashUtils` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-05-11.

## At a glance

- **Path:** [`c/SimpleBashUtils`](../../../c/SimpleBashUtils/)
- **Kind:** library / CLI utilities (cat, grep)
- **Language:** C
- **Build system:** Makefile (per-utility under `src/cat`, `src/grep`)
- **Tests on disk:** no (integration tests against bash)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [ ] **B.** Tests — currently integration-style (compare against host `cat`/`grep`); coverage badge n/a, but a green output-diff suite would suffice
- [~] **C.** GitHub Actions CI in `c.yml` matrix (informational); CI handles both `cat/` and `grep/` per-utility Makefiles
- [~] **D.** Repo-wide `.clang-format`; deliberate format pass pending (slice 4)
- [x] **E.** `make` targets reproducible on the canonical Linux toolchain
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (asciinema) — `s21_cat -benst` and `s21_grep -in '...'`
- [x] **H.** Doxygen API reference — file preambles + flag-mask / `GrepArgs` struct docs on `s21_cat.h` and `s21_grep.h`

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Add structured integration-test diff harness so CI can publish a pass/fail count.
- [ ] Decide on `pcre` vs `regex` for `s21_grep` and document choice in README.
- [ ] Verify GNU long-flag aliases (`--number`, `--squeeze-blank`, …) on the actual `s21_cat` binary.

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-05-11: README adopted from repo template + Original task preserved (this commit).
- 2026-05-11: Included in `c.yml` build/test matrix (split-Makefile branch handles cat/ and grep/ separately) ([8c5bd24d](https://github.com/erdogan-deniz/school-21/commit/8c5bd24d)).
- 2026-05-11: Doxygen rollout — `s21_cat.h` + `s21_grep.h` documented ([9def2070](https://github.com/erdogan-deniz/school-21/commit/9def2070)).
