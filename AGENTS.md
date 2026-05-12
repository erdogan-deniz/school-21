# AGENTS.md — guidance for AI coding agents working on `school-21`

This file is read by AI assistants (Claude Code, GitHub Copilot CLI,
Cursor, Aider, etc.) when they are dispatched to do work in this
repository. It captures the durable expectations and constraints they
should respect.

> **For humans:** much of `school-21`'s production-grade overhaul (the
> CI matrix, the Doxygen / Sphinx rollout, the 37 per-subproject
> plans, the bats test suite) was authored by the maintainer in
> partnership with AI coding agents. This file is the public
> counterpart of the private `CLAUDE.md` — it explains the contract
> any future agent (or contributor) operates under.

## Repository purpose

A pinned open-source portfolio of School 21 (analogue of School 42)
work, kept alive after graduation as a flagship technical showcase
across 12 language folders and 37 subprojects (C, C++, Python, SQL,
Bash, Docker, …).

The audience priority is:

1. **Technical specialists** — evaluating code depth and quality.
2. **Open-source community** — forking / reusing interesting projects.
3. **School 21 students** — finding solutions and approaches.
4. **HR** — treated as a "boilerplate" audience; never optimised at
   the expense of points 1-3.

## Hard rules for agents

These are non-negotiable. Take them as if signed off by the
maintainer.

1. **No history rewrites without explicit human approval.** `git
   filter-repo`, force-push, history-affecting rebases, and rewrites
   of merge commits all require the user to authorise the specific
   operation. The "we agreed earlier" line does not transfer across
   distinct destructive ops.
2. **No `--no-verify`, `--no-gpg-sign`, `-c commit.gpgsign=false`.**
   Hooks exist for a reason. If a hook fails, fix the underlying
   cause; do not bypass it.
3. **Never delete unfamiliar state.** Lock files, branches, files in
   `git status` that you did not create — investigate first. Many of
   them represent the maintainer's in-progress work.
4. **Conventional Commits, scope = subproject.** `type(scope):
   subject ≤72 chars, imperative mood, no trailing period.` See
   [`CLAUDE.md` §10](CLAUDE.md) for the allowed types and the
   scope-resolution rule for cross-folder changes.
5. **Direct commits to `main` are the norm** (cruise control mode).
   Branches are only used for history-affecting ops, mass renames,
   and case-sensitivity remediations.
6. **Both layers move together.** Every behavioural change updates
   *both* [`STATUS.md`](STATUS.md) (the dashboard) *and* the relevant
   [`docs/plans/<track>/<subproject>.md`](docs/plans/) file. Plans
   stay in sync with code, not lagging behind.
7. **Never commit secrets.** API keys, bot tokens, DB passwords,
   private keys — read them from environment variables (or a secret
   store) at runtime. The `gitleaks` pre-commit hook + the
   [`secrets.yml`](.github/workflows/secrets.yml) CI job back this up
   with mechanical enforcement. If `gitleaks` flags real
   credentials: **rotate first** (upstream revocation), refactor the
   source to env vars, then if necessary allow-list the rotated
   value in [`.gitleaks.toml`](.gitleaks.toml). Never allow-list a
   live secret.
8. **Security scanners are signal, not noise.** [`bandit`][bandit]
   (Python SAST) and [`pip-audit`][pa] (vulnerable deps) run as
   `python.yml` jobs. When they flag something, the response order is
   the same as for `gitleaks`: triage the finding, fix the underlying
   issue (or refactor away the pattern), and *only* skip in
   [`.bandit`](.bandit) if the rule is genuinely inapplicable in
   educational context (the existing skip list covers `assert`-in-
   tests, non-crypto `random`, and bootcamp SQL string templates).

[bandit]: https://bandit.readthedocs.io/
[pa]: https://pypi.org/project/pip-audit/

## Soft rules (override only with good reason)

- **Edit existing files first.** Create new files only when the task
  genuinely requires one.
- **No documentation files (`*.md`, README) unless explicitly
  asked.** Working code beats narrative.
- **No emojis in source code, commit messages, or PR descriptions
  unless explicitly requested.**
- **Comments answer "why," not "what."** Well-named identifiers
  document themselves. Multi-paragraph docstrings are reserved for
  publishable API surface (Doxygen / Sphinx) — internal helpers do
  not need them.
- **No premature abstraction.** Three similar lines is better than
  a one-off `helper.foo()` that hides intent.

## Definition of Done — the bar to aim for

Each subproject is "production-ready" only when all **eight** items
below are satisfied:

| Letter | Item                                                     |
| ------ | -------------------------------------------------------- |
| A      | README adopts the repo template                          |
| B      | Unit tests + coverage % in README                        |
| C      | GitHub Actions CI (build + test) with badge in README    |
| D      | Linter / formatter configured and applied                |
| E      | Reproducible build (Dockerfile or Makefile one-command)  |
| F      | `LICENSE` file present                                   |
| G      | Demo (gif / screenshot / asciinema) — required for GUIs  |
| H      | Doxygen / Sphinx API docs                                |

Current per-track progress lives in [`STATUS.md`](STATUS.md). The
expectation is **maximalist**: no DoD letter is silently dropped —
exceptions are flagged in the row's "Notes" column.

## Toolchain

The repo's pinned version table is in
[`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md). Highlights:

- C/C++: `clang-format 18.1.8` (Google style), `Doxygen 1.9.x` +
  `Graphviz`.
- Python: `3.12`, `ruff 0.6.9`, `pytest` + `pytest-cov`,
  `Sphinx ≥ 7` with `furo` theme.
- Bash: `shellcheck`, `bats`, `hadolint` for Dockerfiles.
- SQL: `sqlfluff 3.2.5` with `postgres` dialect.
- Markdown: `markdownlint-cli2 0.13.0`, `lychee` for link-check.

When uncertain about a tool version, prefer the value in
`docs/TOOLCHAIN.md` over your training-data default.

## CI architecture

One workflow per language under `.github/workflows/`, each triggered
only when files in its language folder change (path filters):
`c.yml`, `cpp.yml`, `python.yml`, `sql.yml`, `devops.yml`, `docs.yml`,
`pages.yml`, plus repo-wide `lint.yml` (markdownlint + link-check)
and `actionlint.yml` (workflow lint).

Per-flagship release workflows (`release-<name>.yml`) trigger on
tags of the form `v*-<subproject>` so each flagship can semver
independently inside this monorepo.

## How to introduce a new file or pattern

1. Read the existing pattern. The chances that an analogous
   subproject already established the convention are high.
2. Update [`STATUS.md`](STATUS.md) and the plan in
   [`docs/plans/`](docs/plans/) **in the same commit** that introduces
   the change. Do not leave one of them stale.
3. Conventional Commits message with the subproject scope.

## How to introduce a new subproject

1. Pick a name that matches [`CLAUDE.md` §7 naming convention][cname]:
   `snake_case` for libraries (often `s21_` prefix), `PascalCase_vX.Y`
   for applications, `snake_case + dayNN` for bootcamps.
2. Generate a plan from [`docs/plans/_TEMPLATE.md`](docs/plans/_TEMPLATE.md).
3. Add a row to [`STATUS.md`](STATUS.md).
4. Decide flagship status only after the basic DoD is in place — see
   [`CLAUDE.md` §9][cflag]. Default is **not a flagship**.

[cname]: CLAUDE.md
[cflag]: CLAUDE.md

## Where to ask for help

- [`STATUS.md`](STATUS.md) — current production-readiness state.
- [`SECURITY.md`](SECURITY.md) — vulnerability-reporting protocol and the three-layer leak-prevention stack.
- Root [`Makefile`](Makefile) — `make install` / `make precommit-all` /
  `make lint-{md,shell,python,cpp,sql,secrets}` shortcuts. `make help`
  lists every target.
- [`docs/specs/2026-05-11-production-grade-overhaul.md`](docs/specs/2026-05-11-production-grade-overhaul.md)
  — the design doc behind the recent overhaul.
- [`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md) — pinned tool versions.
- [`CHANGELOG.md`](CHANGELOG.md) — phase-by-phase commit log.
- Per-subproject plans under [`docs/plans/`](docs/plans/) — detail-level
  checklists and history.

If something is unclear, do not invent it. Ask the maintainer.
