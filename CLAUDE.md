# CLAUDE.md — `school-21` working agreement

This file captures the durable rules and standards for this repository so that any future Claude session (or contributor) walks in with the right context. Updated whenever the user establishes a new rule.

> Last updated: 2026-05-10 — initial founding session.

## 1. Repository purpose

`school-21` is the user's **major pinned GitHub project**: an open-source example portfolio collecting all School 21 work (analogue of School 42), kept alive after graduation as a flagship technical showcase.

## 2. Audience (priority order)

1. **Technical specialists** — evaluate code depth and quality.
2. **Open-source community** — fork, reuse, learn from interesting projects.
3. **School 21 students** — find solutions and approaches.
4. **HR** — treated as "boilerplate" audience; do not optimize design at the expense of points 1–3.

When designs conflict (e.g., short marketing-style README vs. long technical README), choose technical depth.

## 3. Visitor outcomes (priority order)

| Priority | Outcome                                          | Scope                                                        |
| -------- | ------------------------------------------------ | ------------------------------------------------------------ |
| 1        | **Evaluate** the user's level by reading         | All subprojects                                              |
| 2        | **Clone and run** locally in ≤5 min              | All subprojects                                              |
| 3        | **Use as a dependency** with releases/versioning | Flagship subprojects only (decided per-project, not upfront) |
| —        | Contribute (PRs, issues)                         | **OUT OF SCOPE** — no community-contribution infrastructure  |

## 4. Definition of Done — per subproject

A subproject is considered **production-ready** only when **all eight** items below are satisfied:

- **A.** README in repo-wide template (purpose / build / run / demo).
- **B.** Unit tests + coverage % visible in README.
- **C.** GitHub Actions CI (build + test) with badge in README.
- **D.** Linter/formatter configured and applied (clang-format / ruff / sqlfluff / …).
- **E.** Reproducible build (Dockerfile or Makefile, "one command builds it").
- **F.** `LICENSE` file present.
- **G.** Demo (gif / screenshot / asciinema) — required for GUI and CLI projects.
- **H.** Doxygen / Sphinx API docs (beyond README).

DoD is the universal acceptance criteria. If a pragmatic exception is needed for a specific subproject, surface it explicitly — do not silently relax it.

## 5. Working agreements (for AI sessions)

- Ask **one sub-question at a time** during brainstorming.
- Prefer dialogue over rigid multi-choice for broad/strategic questions.
- Allowed: parallel work on low-blast-radius foundational items (CLAUDE.md, memory, formatting configs) while a design discussion is ongoing.
- Not allowed without confirmation: structural rewrites, mass renames, force-pushes, history rewrites, deletions of unfamiliar state.
- Do not invent file paths, package names, or APIs. Verify with `Glob`/`Grep` before referencing in plans.

### Autonomy mode: **cruise control**

- Work in **autonomous batches** (e.g., "add CI to all C subprojects", "regenerate README from template for all Python subprojects").
- Commit directly to `main` (no per-task PR overhead).
- Stop and check in **only at language-folder boundaries** (all of `c/`, all of `cpp/`, etc.) or at any newly-discovered blocker.
- Each batch must (a) move `STATUS.md` forward and (b) be a single coherent commit (or small commit chain) with conventional-commit messages.
- Even in cruise mode, the "Not allowed without confirmation" list above stands — destructive/risky ops always pause.

## 6. Repo conventions (to be filled in as decided)

- **Tracking mechanism:**
  - **Primary:** `STATUS.md` at repo root — single source of truth. Markdown table, rows = subprojects, columns = DoD letters A–H, cells ∈ {✓, ✗, ◐ partial, n/a}.
  - **Secondary view:** GitHub Projects board (kanban/table) — read-mostly mirror of `STATUS.md`.
  - **Secondary view:** GitHub Issues + milestones — one issue per non-trivial gap, milestones group by subproject. Generated from `STATUS.md`, not edited by hand.
  - **Rule:** never edit secondary views as a primary write path. If the board or an issue diverges from `STATUS.md`, regenerate the secondary view.
- **License — dual structure:**
  - Repo-root `LICENSE` = **MIT** (governs the repo as an open-source whole, makes GitHub recognise the licence, allows reuse).
  - Per-subproject `LICENSE` = **keep the existing "School 21 License" placeholder** as educational attribution / historical artefact. Do not delete or replace.
  - Each subproject README must say: "This project was developed as part of the School 21 curriculum. The repository as a whole is MIT-licensed (see root `LICENSE`)."
- **README template path:** `content/templates/SUBPROJECT_README.md` (created 2026-05-11).
- **README structure rule:** every subproject README has a *production fold* on top (`# Title` → badges → tagline → `## Quick start` → `## Demo` → `## Documentation` → `## Tests` → `## License & attribution` → `---`) followed by `## Original task (School 21)` and the *original School 21 task description* preserved verbatim. The "Original task" heading is `## H2`, not `# H1`, to satisfy markdownlint MD025 (only one H1 per file). No existing School 21 narrative content (preamble, Chapter I/II/III, story sections) may be removed.
- **CI strategy — per-language workflows with path filters:**
  - `.github/workflows/c.yml`, `cpp.yml`, `python.yml`, `sql.yml`, `bash.yml`, `docker.yml` — each triggered only when files in its language folder change (`on.push.paths` / `on.pull_request.paths`).
  - `.github/workflows/lint.yml` — runs on every push/PR; covers `markdownlint`, link-check, and any cross-language lint (yaml, gitleaks, etc.).
  - Each per-language workflow uses an internal matrix over the subprojects of that language.
  - Each workflow ends with publishing a status badge (added to the corresponding language-folder README and to root `STATUS.md`).
  - Reusable callable workflows are introduced **only** when duplication becomes painful (3+ near-identical workflows). Don't pre-optimise.
- **Docker base images per language:** *to be decided per workflow during implementation (default: official `gcc`, `python:3.12-slim`, etc.).*

## 7. Naming convention for subprojects

The repo already follows an implicit two-track naming convention. Make it explicit and respect it for any new or renamed subproject:

| Kind | Style | Examples | Rationale |
| ---- | ----- | -------- | --------- |
| Library / module (produces a header + static/shared lib) | `snake_case`, often prefixed with `s21_` | `c/s21_math`, `c/s21_decimal`, `c/s21_matrix`, `c/s21_string+`, `cpp/s21_containers`, `cpp/s21_matrix+` | Folder name matches the `#include "s21_math.h"` literal — easy mental mapping, lowercase friendly across all FS. |
| Application / Tool / Viewer (built into an executable, GUI or CLI) | `PascalCase` + `_v<MAJOR>.<MINOR>` | `c/SmartCalc_v1.0`, `c/3DViewer_v1.0`, `c/SimpleBashUtils`, `cpp/SmartCalc_v2.0`, `cpp/3DViewer_v2.0`, `cpp/CPP5_3DViewer_v2.1`, `cpp/CPP6_3DViewer_v2.2` | Matches public product naming (visible in window titles, About dialogs, releases). Version suffix lets multiple revisions of the same product coexist. |
| Bootcamp day / iterative material | `snake_case` with `day_NN` / `team_NN` / `ct_NN` | `python/bootcamp/old/day_00`, `data_science/bootcamp/day_03`, `career_track/ct_05` | Sequence-ordered, sortable, week/cohort grouping. |

**Hard rules:**

- Never mix styles within a track (no `Smart_Calc_v1.0`, no `s21Math`).
- Filesystem case must match git index case — verify with `git ls-files <path>` after any rename. Set `git config core.ignorecase false` for the duration of any cross-case rename, then restore.
- A library promoted to an application gets renamed; both tracks have version suffix only when versioning is meaningful.

## 8. Known global issues (to be resolved early)

- **SmartCalc index/disk drift:** git index canonical = `c/SmartCalc_v1.0/` (PascalCase, 175 files); disk = `c/smart_calculator/` (lowercase). Recent commits silently routed back to PascalCase via `core.ignorecase=true`. **Decision: PascalCase is canonical**; rename disk back, restore or consciously discard the few actually-deleted files (Qt translations `qt_*.qm`, two background `.jpg`s, `.DS_Store`).
- **Committed virtualenv:** `data_science/bootcamp/day_03/src/charisel/Lib/...` — 3477 vendor pip files in the index. Resolve via root `.gitignore` + `git rm -r --cached`. History-level cleanup (`git filter-repo`) is a separate, destructive op requiring explicit approval.
- **Missing root `.gitignore`:** repo has none. Add one covering OS noise (`.DS_Store`, `Thumbs.db`), language artefacts (Python `__pycache__/`, `*.pyc`, virtualenvs; C/C++ `*.o`, `*.a`, `*.exe`, `build/`), editor scratch (`.vscode/`, `.idea/`).
- **`README2.md` at repo root** contains Python Bootcamp content — move to `python/bootcamp/README.md` (and merge with whatever is currently there).

## 9. Per-subproject "flagship" decision

The decision whether a subproject is a "flagship" (and therefore in scope for outcome-priority **3 = use as a dependency**) is made **per-subproject during its individual review**, not upfront from a list. By default a subproject is **not** a flagship — it gets DoD treatment for outcomes 1+2 only. Flagship status must be explicitly declared in `STATUS.md` (extra column / tag).

## 10. Commit and branch conventions

- **Conventional Commits** are mandatory. Format: `type(scope): subject`.
- Allowed `type`s: `feat`, `fix`, `refactor`, `perf`, `style`, `docs`, `test`, `build`, `ci`, `chore`, `revert`.
- `scope` = subproject directory name (e.g., `s21_math`, `smart_calculator`, `SmartCalc_v2.0`). For changes spanning a whole language folder, scope = the folder name (`c`, `cpp`, `python`, …). For repo-wide infrastructure, scope is omitted (e.g., `chore: bump CI runner image`).
- Subject ≤ 72 chars, imperative mood ("add", "fix", "remove"), no trailing period.
- Body (optional) explains WHY, references related items in `STATUS.md` if applicable.
- **Branching:** direct commits to `main` (cruise control mode). Use a short-lived `wip/<topic>` branch ONLY for history-affecting operations (`git filter-repo`, mass-renames, large case-sensitivity fixes) — merge with `--no-ff` and a one-line summary.
- Never force-push to `main`. Never amend an already-pushed commit.

## 11. House rules for changes inside subprojects

- Do not mass-rewrite an existing subproject's code style on first touch — apply the agreed linter/formatter once, in a dedicated commit.
- New code in a subproject must respect that subproject's chosen language/style (e.g., C uses S21 naming convention).
- Tests live next to source unless the subproject's existing structure dictates otherwise.
