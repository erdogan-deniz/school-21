# `school-21` production-grade overhaul — design

> **Status:** approved (2026-05-11)
> **Owner:** Deniz Erdogan
> **Implementation lead:** Claude Code (cruise-control mode)
> **Authoritative companion:** [`CLAUDE.md`](../../CLAUDE.md) (rules), [`STATUS.md`](../../STATUS.md) (live dashboard)

## Context

The `school-21` repo is a collection of all of the user's School 21 work
(analogue of School 42). After graduation (Final Exam passed), the repo
is being repositioned as the user's **major pinned GitHub project** —
an open-source example portfolio that the user keeps extending.

The repo today has ~37 subprojects across 6+ language tracks (C, C++,
Python, SQL, Bash, Docker), most of which build, but the quality is
uneven: README structure varies, no CI, no unified linting, no central
visibility on what's done versus pending. There are also accumulated
hygiene debts (committed virtualenv with 3477 vendor files, an
in-flight Windows case-sensitivity rename of `SmartCalc_v1.0`,
misplaced `README2.md`, no root `LICENSE` or `.gitignore`).

The goal of this overhaul is to bring **every** subproject up to a
single Definition of Done (eight items: README, tests, CI, linter,
reproducible build, licence, demo, API docs) and make progress
visible via a single dashboard, without touching what already works
inside subprojects beyond what the DoD requires.

## Audience and outcomes

(Full text in `CLAUDE.md` §2 and §3. Summary here.)

Audience priority: tech specialists > OSS community > School 21
students > HR. Outcomes priority: visitor can **evaluate** > visitor
can **clone and run** > visitor can **use as dependency** (flagships
only). Community contribution infrastructure is out of scope.

## Definition of Done (per subproject)

A — README in repo template · B — unit tests + coverage · C — GitHub
Actions CI with badge · D — linter/formatter applied · E —
reproducible build (Docker or Make) · F — `LICENSE` file · G — demo
(gif/screenshot/asciinema) · H — Doxygen/Sphinx API docs.

All eight are **required** (user is a maximalist on this). Pragmatic
exceptions surface explicitly per subproject.

## Phased approach

### Phase 0 — Foundations

Goal: minimal production scaffolding without which no later phase
can land.

Already in place: `CLAUDE.md`, `content/templates/SUBPROJECT_README.md`,
memory store.

Remaining deliverables:

- Root `LICENSE` (MIT, © 2022–2026 Deniz Erdogan).
- Root `.gitignore` (OS noise, Python venvs, C/C++ build artefacts,
  editor scratch, coverage outputs, doc builds).
- Root `STATUS.md` (skeleton: matrix of subprojects × DoD letters
  A–H, legend, flagship column).
- `.github/workflows/lint.yml` (markdownlint + link-check on every
  push/PR).

One commit per artefact. ETA: one session.

### Phase 1 — Tactical cleanup

Goal: clear known debts that obstruct further work.

| Op  | Description                                                                                                  | Reversibility | Approval needed beyond this doc?     |
| --- | ------------------------------------------------------------------------------------------------------------ | ------------- | ------------------------------------ |
| 1.1 | SmartCalc rename: align disk `c/smart_calculator/` to canonical index path `c/SmartCalc_v1.0/` (PascalCase). | reversible    | no                                   |
| 1.2 | Decide actually-deleted Qt translations / images: restore from history or accept deletion.                   | reversible    | yes (per-file, surfaced in commit)   |
| 1.3 | Virtualenv eviction from current HEAD: `git rm -r --cached data_science/.../charisel/` (history untouched).  | reversible    | no                                   |
| 1.4 | History-level virtualenv purge (`git filter-repo`).                                                          | destructive   | **yes — explicit user opt-in later** |
| 1.5 | `git mv README2.md python/bootcamp/README.md` and merge with existing.                                       | reversible    | no                                   |

ETA: one session, three to four commits.

### Phase 2 — Per-language production passes

Goal: walk through each language folder and close DoD A–H for every
subproject in it.

Order (most-recently-active first, then by toolchain affinity):

`c/` → `cpp/` → `python/` → `data_science/` → `sql/` → `algorithms/python/`
→ `devops/` → `qa/` → `machine_learning/` → `internship/` → `career_track/`
→ `survival_camp/`.

Per-language template of work (each is its own commit chain, scoped
with conventional-commits):

1. Add language workflow `.github/workflows/<lang>.yml` (matrix over
   the language's subprojects) — `ci(<lang>): scaffold workflow`.
2. Land or unify linter/formatter config — `style(<lang>): apply
   <linter> across all subprojects`.
3. README pass per subproject (template applied, original task
   preserved verbatim) — one commit per subproject:
   `docs(<subproject>): adopt repo README template`.
4. Tests pass per subproject (existing tests wired into CI; missing
   coverage added where reasonable) — `test(<subproject>): wire CI
   coverage`.
5. Doxygen/Sphinx pass per subproject — `docs(<subproject>): add API
   docs`.
6. Demo pass per subproject (gif/screenshot/asciinema) —
   `docs(<subproject>): add demo`.
7. STATUS.md update inline at every step.

Stop point: end of language folder. User spot-checks, says continue,
next language begins.

ETA: weeks, paced by user availability.

### Phase 3 — Flagship promotions

Goal: 2–3 subprojects (decided per-subproject during their Phase 2
review) get C-tier treatment — release pipelines, semver tags,
GitHub Releases artefacts, optional package publication
(PyPI/Conan/...).

Triggered explicitly by marking `★` in `STATUS.md`. Not a Phase 0/1/2
prerequisite.

## Tracking

Single source of truth: `STATUS.md` at repo root. Markdown table,
rows = subprojects, columns = DoD letters A–H + flagship flag,
cells ∈ {✓, ✗, ◐ partial, n/a}.

Secondary views (read-only mirrors, NOT edited by hand):

- GitHub Projects board (kanban / table) — generated from STATUS.md.
- GitHub Issues + milestones — one issue per non-trivial gap,
  generated from STATUS.md.

## Working agreements

- Direct commits to `main` (cruise control). Short-lived branches
  only for history-affecting operations.
- Conventional Commits, scope = subproject directory or language
  folder.
- Pause points: end of language folder, any newly-discovered
  blocker, any destructive operation.
- Markdownlint per `.markdownlint.json` (asterisk emphasis, padded
  tables).

## Verification

End-to-end checks for the overall overhaul (re-run after every
language pass):

- `git status` clean (no orphan untracked, no case-drift).
- `gh workflow list` shows all per-language workflows + lint
  workflow, all green for at least one push.
- `STATUS.md` rendered: visual count of ✓ matches actual artefacts
  on disk for a sample subproject.
- Root `README.md` "Quick start for the visitor" section links to
  `STATUS.md`, `LICENSE`, and a representative subproject in each
  language.
- A fresh clone + `make` (or `docker build`) on each subproject
  succeeds inside its own CI matrix entry.

## Out of scope

- Community-contribution infrastructure (CONTRIBUTING.md, issue
  templates, PR templates).
- Cross-subproject refactoring not driven by DoD.
- Translating subproject content; user-facing language stays as it
  is in the original task (mostly English with occasional Russian).
- Replacing or modifying the per-subproject `# School 21 License`
  placeholders.
