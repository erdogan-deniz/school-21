# `python/SmartCalc_v3.0` — production-readiness plan

> Status row in [`/STATUS.md`](../../../STATUS.md). Last reviewed: 2026-09-14.

## At a glance

- **Path:** [`python/SmartCalc_v3.0`](../../../python/SmartCalc_v3.0/)
- **Kind:** application (desktop GUI)
- **Language:** Python 3.11 (PyQt6) over the C core of [`c/SmartCalc_v1.0`](../../../c/SmartCalc_v1.0/) via `ctypes`
- **Build system:** Makefile + `pyproject.toml` (setuptools); `scripts/build_lib.py` compiles the shared library (gcc / clang / MSVC)
- **Tests on disk:** yes (`tests/` — 361 pytest + hypothesis tests, 99 % model/viewmodel/utils coverage)
- **Flagship:** no

## Definition of Done — checklist

- [x] **A.** README adopts the repo template (production fold + preserved task)
- [x] **B.** Unit tests + coverage % visible in README (361 tests, 99 %; Codecov flag `python-SmartCalc_v3.0`)
- [~] **C.** Dedicated `smartcalc-v3` job in `python.yml` (Python 3.11, `make lib`, ruff, pytest); soft-gated until green runs land on origin
- [x] **D.** Own strict ruff config (line-length 80, Google docstrings, `DOC` / `ANN` / `PL` …) + mypy; `ruff format` applied 2026-09-14
- [~] **E.** `make install-dev && make lib && make test` reproducible on Linux / macOS / Windows given Python 3.11 + a C toolchain; no Dockerfile
- [~] **F.** Root MIT `LICENSE` ✓; subproject `LICENSE` is the School 21 placeholder (kept by design)
- [ ] **G.** Demo (gif) — expression + `f(x)` plot + deposit mode
- [~] **H.** Hand-written `docs/api.md`, `docs/user-guide.md`, `docs/developer-guide.md`; Sphinx HTML not yet generated

> Legend: `[x]` done · `[~]` partial / pending follow-up · `[ ]` not started.

## Subproject-specific tasks

- [ ] Triage the 14 remaining ruff findings (10× E501 in view / viewmodel / tests, 6× SLF001 in white-box viewmodel tests — candidate for the `tests/**` per-file-ignores next to `PLC2701`, 1× DOC201).
- [ ] Sphinx skeleton reusing the `python/bootcamp/new/day_01` layout; wire into the `python.yml` sphinx matrix and `pages.yml`.
- [ ] Record the demo gif (DoD-G).
- [ ] Decide whether the Windows installer (`make dist` + Inno Setup) should become a GitHub Release artefact — if yes, this is a flagship candidate next to `cpp/SmartCalc_v2.0`.
- [ ] Consider relaxing `requires-python` to `>=3.11,<3.13` once PyQt6 wheels for 3.12 are verified, so the repo-wide Python 3.12 matrix can host it.
- [x] Reuse the C core from `c/SmartCalc_v1.0/src` instead of a bundled copy (token-level diff of the two trees: identical apart from clang-format + Doxygen).

## History

<!-- Append: - YYYY-MM-DD: short description ([commit](https://github.com/erdogan-deniz/school-21/commit/<sha>)) -->

- 2026-09-14: Imported as a one-commit snapshot of the School 21 GitLab repo `APP2_SmartCalc_v3.0_Desktop_Python` (branch `develop`, 757e3db) ([25c282c](https://github.com/erdogan-deniz/school-21/commit/25c282c)).
- 2026-09-14: C core resolved from `../../c/SmartCalc_v1.0/src` in `build_lib.py` + Makefile ([193dd6a](https://github.com/erdogan-deniz/school-21/commit/193dd6a)); the C header bug that blocked the build fixed in `c/SmartCalc_v1.0` ([26b8310](https://github.com/erdogan-deniz/school-21/commit/26b8310)).
- 2026-09-14: Dedicated CI job + repo-wide ruff exclusion ([b090dcf](https://github.com/erdogan-deniz/school-21/commit/b090dcf)); ruff format pass ([1fb5bad](https://github.com/erdogan-deniz/school-21/commit/1fb5bad)).
- 2026-09-14: README brought to repo template, plan created, STATUS row added ([1491cec](https://github.com/erdogan-deniz/school-21/commit/1491cec)).
- 2026-09-14: `TestHistoryAppDir` made cross-platform — expected paths via `os.path.join`, `os.name` patch scoped to `monkeypatch.context()`; the CI job on `ubuntu-latest` crashed with `NotImplementedError: cannot instantiate 'WindowsPath'` (this commit).
