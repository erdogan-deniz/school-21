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

### Pushed (2026-05-11)

All commits up to and including the flagship-designation commit
were pushed to `origin/main` (`14daa67a` initial push, then
`040c50af` for flagships, plus the URL-rename fix in `14daa67a`).
8 GitHub Actions workflows now run on every push/PR; GitHub Pages
deploys to `erdogan-deniz.github.io/school-21` on changes to source
files referenced in `pages.yml`.

### Continuation batches (post first-push, still 2026-05-11)

After the initial push to `origin/main` (the dashboard read **38 %**),
a series of cruise-control follow-ups raised the figure to **54 %**
honest production-readiness. Grouped by theme:

**Doxygen rollout — all C/C++ subprojects.** File preambles + class
@briefs + grouped public-API blocks on every header. After this pass
the H column (Doxygen / Sphinx API docs) is **✓ across all 13 c/ and
cpp/ subprojects** — the first DoD column to be fully closed across
two complete tracks. Libraries: `c/{s21_math,s21_decimal,s21_matrix,
s21_string+,SimpleBashUtils}`, `cpp/{s21_containers,s21_matrix+}`.
Applications: `c/{3DViewer_v1.0,SmartCalc_v1.0}`,
`cpp/{3DViewer_v2.0,CPP5_3DViewer_v2.1,CPP6_3DViewer_v2.2,
SmartCalc_v2.0}`. The `cpp/s21_containers` flagship received per-class
Doxygen too — all 8 containers (vector / list / map / set / multiset
/ queue / stack / array) with STL-parallel notes and backing-data-
structure trade-offs documented. (`d7960ba6`, `9def2070`, `0e1f1128`,
`69da2920`)

**Bats coverage for `devops/linux_monitoring_v1.0`.** 47 bats tests
across all five parts plus smoke — input-validation rules (Part 1),
config-info Y/N save path (Part 2), visual-design colour params
(Part 3), `colors.cfg`-driven coloured output with ANSI envelope
asserts (Part 4), filesystem report with mktemp fixture (Part 5).
B column ◐ → ✓. (`ff0e0416`, `0b0d36eb`)

**Sphinx skeleton for `python/bootcamp/new/day_01`.** Mirrored
day_07's canonical setup — autodoc + napoleon + viewcode under furo
theme; wired into `python.yml` sphinx matrix and `pages.yml` unified
site. (`a72fda28`)

**`AGENTS.md` + `docs/BRANCH_PROTECTION.md`.** Public counterpart of
private `CLAUDE.md` covering AI-coding-agent contract; recipe for
maintainer to apply classic branch protection on `main` once CI
stabilises (required-status-check list + tag-protection patterns +
local pre-commit mirror). (`9352310d`, `24cd9ea6`, `9bffe24e`
recipe updates)

**Reproducible-build setups.** Real `make install / run / clear`
workflows or docker-compose stacks for the three lowest-scoring
subprojects:

- `sql/bootcamp` — `docker-compose.yml` (Postgres 16 service +
  healthcheck + tree bind-mount) + `Makefile`
  (`make up / seed DAY=NN / psql / test-all / down`) with auto-located
  per-day `model.sql` under either `materials/` or `resources/`.
  CI gains a `bootcamp-schema-load` job iterating all 10 numbered
  days against a real Postgres service container. (`baef03bb`)
- `machine_learning/project_01` — cross-platform `Makefile` venv
  workflow + pinned `requirements.txt` (semver `>=A.B,<C` bounds on
  numpy / scipy / pandas / xgboost / matplotlib / scikit-learn);
  obsolete `commands.txt` evicted. (`71e06fd1`)
- `data_science/bootcamp` — per-day isolated `.venv` workflow
  (`make install / jupyter / clear DAY=NN`); 4 previously bare
  requirements.txt files pinned. (`adb000ab`)

**STATUS.md honesty pass.** n/a audit for text-only / report-driven
subprojects (career_track ×9, internship, qa ×2, devops/linux,
devops/linux_network, survival_camp) — 13 rows where B / C / D / E
/ G / H were marked ✗ but had no actual code to test/lint/build now
read n/a. Roll-up arithmetic clarified in the legend ("n/a excluded
from the denominator"). Same pass recounted every track's numerator
from current cell values; the prior 138/296 figure had drifted
~25 cells over incremental updates. Honest final: **111/206 = 54 %**.
(`87ca19f8`, `8c98f9be`)

**Reproducibility fixes.** Four broken `requirements.txt` files
that would have prevented `pip install -r` from working at all:
`data_science/bootcamp/day_09` (UTF-16 LE encoding + CRLF — fixed
to UTF-8 LF), `python/bootcamp/old/day_05` (stdlib `atexit` listed
as PyPI package — removed), `python/bootcamp/old/day_06`
(`psycopg2 binary` with a space → `psycopg2-binary`; `postgresql`
which is the DB server — removed), `python/bootcamp/old/day_08`
(stdlib `asyncio` + `uuid` listed as PyPI packages — removed).
(`cb5655c5`)

**Security incidents + permanent guards.** Two hardcoded-credential
finds during the security sweep:

- **HIGH**: Telegram bot token + chat ID hardcoded in
  `devops/ci_cd/src/notify.sh`. Refactored to env vars
  (`TELEGRAM_BOT_TOKEN`, `TELEGRAM_CHAT_ID`); added `set -euo pipefail`
  and `${VAR:?}` bail-out. Token must be rotated upstream by the
  maintainer in @BotFather. (`8c98f9be`)
- **LOW**: Local-Postgres password (`1969`) in
  `python/bootcamp/old/day_06/src/arguments.py` and `alembic.ini`.
  Refactored to `os.environ.get("DB_PASSWORD", "1969")` with
  alembic's `sqlalchemy.url` now built dynamically in
  `env.py:config.set_main_option(...)`. (`e8428293`)

To stop the next leak before it reaches `git log`, three-layer
defence-in-depth:

- `gitleaks` pre-commit hook (`v8.18.4`) — catches new leaks at
  `git commit` time.
- `.github/workflows/secrets.yml` — `gitleaks-action@v2` with
  `fetch-depth: 0` (full history scan) on every push/PR.
- `.gitleaks.toml` — minimal allow-list scoped to *rotated* values
  and bootcamp env-var fall-back defaults only; never allow-list a
  live secret.
- `bandit==1.7.10` job in `python.yml` for Python SAST
  (medium/medium severity+confidence); `.bandit` config with curated
  skip list for educational patterns (B101 assert, B311 non-crypto
  random, B324 md5 in hashing exercises, B404/B603 subprocess,
  B608 templated SQL).
- `pip-audit==2.7.3` matrix job (14 entries) scanning every
  `requirements.txt` against PyPI's CVE / advisory database.

AGENTS.md gained hard rules #7 (never commit secrets — rotate first,
then refactor, then allow-list rotated values) and #8 (security
scanners are signal, not noise). (`24cd9ea6`, `9bffe24e`)

**`devops/simple_docker` smoke + Dockerfile bug fix.** 12 occurrences
of `chown 755 /bin/...` corrected to `chmod 755` (the sister
`nginx_server/Dockerfile` already used `chmod` — the root one was a
silent-failing typo). Added `simple-docker-smoke` job to `devops.yml`
that does `docker compose up -d --build`, polls
`http://localhost:80` for up to 30 s, asserts `Hello World` in the
response body, then `docker compose down -v --remove-orphans`.
End-to-end proof the multi-service stack still works. B column
✗ → ◐. (`2819e2e4`)

**Per-subproject plans synced with STATUS.** After several batches
landed without their plan files moving in lock-step, a sync pass
brought 11 plans (`docs/plans/c/*`, `docs/plans/cpp/*`,
`docs/plans/devops/linux_monitoring_v1.0.md`) up to date — DoD ticks
flipped, history entries appended with commit hashes. The
working-agreement rule "Both layers move together" is now enforced
per batch, not retrofitted. (`7b446971`, plus plan entries within
each subsequent feature commit)

### Flagships designated (2026-05-11)

Three subprojects flagged **★** in STATUS.md, targeting DoD-C
("use as a dependency"):

- `cpp/s21_containers` — header-only STL replica (Conan/vcpkg candidate).
- `c/s21_math` — standalone `math.h` replacement (simplest first
  release pipeline).
- `cpp/SmartCalc_v2.0` — packaged desktop app (GitHub Releases
  artefact — AppImage/dmg/exe).

Per-flagship release pipelines, semver tags, and packaging are queued
as a follow-up batch.

### Hygiene findings (deferred)

- **History-level virtualenv purge** (`git filter-repo`): the eviction
  in `554dc46a` removed `charisel/` from HEAD, but the 3502 files
  still inflate clone size when traversing history. A `git filter-repo`
  pass is technically prepared (`backup-pre-filter-repo` branch
  exists, `git-filter-repo` installed locally) but the Claude Code
  agent harness blocks force-push + history-rewrite operations even
  with verbal user consent — they require either a `Bash(git
  filter-repo:*)` permission rule in `~/.claude/settings.json` or
  manual execution via shell. Concrete recipe is documented in the
  history-rewrite follow-up message; queued as Phase 1 op 1.4.
- **Demo gif/asciinema**: per-subproject demos require local
  execution of subprojects, not autonomously schedulable.
- **Build/test gates**: `c.yml`, `cpp.yml`, `python.yml` build/test
  jobs are still `continue-on-error: true`. Hardening pending stable
  green runs in CI after first push (which has now happened — review
  Actions tab).
- **Demo gif/asciinema**: per-subproject demos require local execution
  of subprojects, not autonomously schedulable.
- **Build/test gates**: `c.yml`, `cpp.yml`, `python.yml` build/test jobs
  are still `continue-on-error: true`. Hardening pending stable green
  runs after first push.

## Pre-overhaul history

For the per-subproject working history before 2026-05-11, see `git log`.
The repo predates this changelog and was a record of School 21 coursework
collected as the user advanced through Wave 10.2022.
