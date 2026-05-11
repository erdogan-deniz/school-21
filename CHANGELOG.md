# Changelog

All notable changes to this repository are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html)
where applicable. Pre-1.0 work is tracked here under dated *"production-grade
overhaul"* sections rather than versions.

## [Unreleased] — 2026-05-11 production-grade overhaul

The repo went from "ad-hoc collection of completed School 21 projects" to
**38 % production-readiness** across 37 subprojects in a single intensive
series of cruise-control sessions (commits `ce85f7a2` → `50ef3e34`,
plus follow-ups). Detail by phase:

### Foundations (Phase 0)

- Root `LICENSE` (MIT) — repo as a whole now has a real OSI-approved licence;
  per-subproject `# School 21 License` placeholders preserved as educational
  attribution. (`ce85f7a2`)
- Root `.gitignore` covering OS noise, Python venvs, C/C++ build artefacts,
  editor scratch, coverage outputs. (`0ba3aac8`)
- [`CLAUDE.md`](CLAUDE.md) — repo-wide working agreement (audience
  priority, DoD, tracking, autonomy, conventions, naming, README rule).
  (`04f2a40c`)
- [`STATUS.md`](STATUS.md) — production-readiness dashboard (37 subprojects ×
  8 DoD items). (`04f2a40c`)
- [`content/templates/SUBPROJECT_README.md`](content/templates/SUBPROJECT_README.md)
  — canonical README template (production fold + preserved School 21 task).
  (`04f2a40c`)
- [`docs/specs/2026-05-11-production-grade-overhaul.md`](docs/specs/2026-05-11-production-grade-overhaul.md)
  — design document for the overhaul. (`04f2a40c`)
- `.github/workflows/lint.yml` — markdownlint + lychee link-check on every
  push/PR. (`5ee143b6`)

### Tactical cleanup (Phase 1)

- **SmartCalc_v1.0**: resolved long-standing disk/index drift caused by
  Windows case-insensitivity. Recovered missing Qt assets from history;
  dropped dead-code .c files and 8 Qt MOC build artefacts. (`a6744d9d`)
- **Committed virtualenv eviction**: removed 3502 vendor pip files at
  `data_science/bootcamp/day_03/src/charisel/...` from the index (kept on
  disk locally, blocked by `.gitignore` going forward). (`554dc46a`)
- **README2.md → python/bootcamp/README.md**: misplaced root-level file
  moved to its rightful subproject location. (`c53e9251`)
- **OS noise eviction**: untracked 7 pre-existing `.DS_Store` and
  `.vscode/` files. (`7f13076f`)

### Per-subproject infrastructure (Phase 2)

**README adoption** — all 37 subprojects now use the repo-wide template
(production fold on top, original School 21 task preserved verbatim
below `## Original task (School 21)`). Across c/, cpp/, python/, sql/,
data_science/, devops/, qa/, machine_learning/, internship/,
survival_camp/, career_track/, algorithms/.

**Per-subproject plans** — `docs/plans/<track>/<subproject>.md` for each
of 37 subprojects, generated from
[`docs/plans/_TEMPLATE.md`](docs/plans/_TEMPLATE.md). Each plan tracks the
8-item DoD checklist with three-state ticks (`[x]` / `[~]` / `[ ]`),
subproject-specific tasks, and a chronological History log linked to
commits. (`d4cde2a2`)

**Naming convention** — observed two-track convention (`snake_case` for
libraries, `PascalCase`+version for applications, sequence-suffixed for
bootcamp days) made explicit in `CLAUDE.md` §7.

### CI workflows (Phase 2 slice 1+2)

Eight GitHub Actions workflows now cover the polyglot repo:

- `lint.yml` — markdownlint + lychee on every push/PR.
- `c.yml` — clang-format check (gating) + libs build/test matrix +
  apps C-only tests + Qt6 GUI build (`xvfb`).
- `cpp.yml` — clang-format check (gating) + libs build/test (GoogleTest) +
  apps C++-only tests + Qt6 GUI build (`xvfb`).
- `python.yml` — ruff lint (informational) + ruff format check (gating) +
  per-day pytest matrix + Sphinx (day_07). Covers `python/`,
  `algorithms/python/`, `data_science/`, `machine_learning/`, `qa/`.
- `sql.yml` — sqlfluff (postgres dialect).
- `devops.yml` — shellcheck + hadolint.
- `docs.yml` — Doxygen for 7 C/C++ libraries (autogen Doxyfile).
- `pages.yml` — unified GitHub Pages site combining Doxygen + Sphinx.

### Format passes (Phase 2 slice 4)

- **Python**: `ruff format` applied to 140 .py files (`4243c5d2`); `ruff
  check --fix` safe auto-fixes applied to 94 files (159 fixes — F541, I001,
  F401, W291) (`db3f12e4`).
- **C / C++**: `clang-format -i` applied to 68 of 336 candidate files
  (`e3590aa1`).
- **CI gates**: `format-check` jobs in `c.yml`, `cpp.yml`, `python.yml`
  promoted from `continue-on-error: true` to **hard gating** (`50ef3e34`).
  Style drift now caught at PR door.

### Infrastructure polish

- `.clang-format` (Google style) at repo root. (`3f64148d`)
- `.ruff.toml` (modest ruleset, sensible exclusions). (`af77283e`)
- `.gitattributes` for cross-platform CRLF/LF normalisation
  (eliminates the noisy warnings on every commit). (`8fea2396`)
- `.markdownlint.json` updated to disable MD036 (italic dialogue
  in preserved School 21 narratives) and MD060 (long preserved-task
  tables). (`5530f24b`, `89e5b0ca`)
- Root `README.md` gained a Production-readiness section with
  9 workflow status badges + cross-links to STATUS, plans, design doc,
  CLAUDE, and the GitHub Pages site. (`642427af`)
- `.editorconfig` for IDE consistency.
- `.github/dependabot.yml` for automated GitHub Actions version bumps.

### Hygiene findings (deferred)

- **History-level virtualenv purge** (`git filter-repo`): the eviction in
  `554dc46a` removed `charisel/` from HEAD, but the 3502 files still
  inflate clone size when traversing history. A `git filter-repo` pass
  to remove them from history is queued as Phase 1 op 1.4 — destructive,
  awaits explicit user opt-in.
- **Demo gif/asciinema**: per-subproject demos require local execution
  of subprojects, not autonomously schedulable.
- **Build/test gates**: `c.yml`, `cpp.yml`, `python.yml` build/test jobs
  are still `continue-on-error: true`. Hardening pending stable green
  runs after first push.

## Pre-overhaul history

For the per-subproject working history before 2026-05-11, see `git log`.
The repo predates this changelog and was a record of School 21 coursework
collected as the user advanced through Wave 10.2022.
