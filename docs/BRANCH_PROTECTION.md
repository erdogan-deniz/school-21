# Branch protection — recipe

> Reference recipe for the maintainer to apply to `main` once the CI
> matrix stabilises (most `continue-on-error: true` shims are dropped
> and the workflows run green on every push).
>
> This is **not** currently active — the repo runs in cruise control
> mode (direct commits to `main`). The recipe is captured here so that
> when the bar moves up it can be applied in one step.

## When to enable

Apply branch protection on `main` once **all** of the following are
true:

- The 9-workflow CI matrix is green for two consecutive weeks of
  active development.
- Every `continue-on-error: true` gate has been audited and either
  flipped to `false` or replaced by an explicit allow-list (see
  the entries in [`STATUS.md`](../STATUS.md) "Notes" column).
- The three flagship release pipelines (`release-s21_math.yml`,
  `release-s21_containers.yml`, `release-SmartCalc_v2.0.yml`) have
  produced at least one successful tagged release each.

Until then, branch protection would slow the polish pass without
adding genuine safety — local pre-commit hooks already mirror the
remote checks.

## Recipe — minimal set

GitHub → **Settings → Branches → Add classic branch protection rule**
for `main`:

| Setting                                                 | Value                                                                        |
| ------------------------------------------------------- | ---------------------------------------------------------------------------- |
| Branch name pattern                                     | `main`                                                                       |
| Require a pull request before merging                   | **on** — applies to maintainer too, but admins can bypass when needed       |
| Require approvals                                       | **off** (solo-maintained repo)                                              |
| Dismiss stale pull request approvals when new commits are pushed | n/a — no approvers required                                                  |
| Require status checks to pass before merging            | **on**                                                                       |
| Require branches to be up to date before merging        | **on**                                                                       |
| Required status checks                                  | see [below](#required-status-checks)                                         |
| Require conversation resolution before merging          | **on**                                                                      |
| Require signed commits                                  | **off** initially; enable once `git config user.signingkey` is on every host |
| Require linear history                                  | **on** — keeps `git log --oneline` legible                                  |
| Require deployments to succeed before merging           | **off** (no production environment in this repo)                            |
| Lock branch                                             | **off**                                                                      |
| Do not allow bypassing the above settings               | **off** — maintainer must be able to land tactical fixes quickly            |
| Restrict who can push to matching branches              | **off**                                                                      |
| Allow force pushes                                      | **off** (the default)                                                       |
| Allow deletions                                         | **off** (the default)                                                       |

## Required status checks

The workflows live under [`.github/workflows/`](../.github/workflows/).
Once they run green consistently, mark the following job IDs as
required (use the **exact** job name shown in a recent workflow run
URL — GitHub will surface the live list once at least one run has
completed for each):

| Workflow file  | Required job(s)                                          |
| -------------- | -------------------------------------------------------- |
| `c.yml`        | `clang-format-check`, `libs-build`, `apps-c-tests`, `apps-qt-build` |
| `cpp.yml`      | `clang-format-check`, `libs-build`, `apps-cpp-tests`, `apps-qt-build` |
| `python.yml`   | `ruff` (gating format check), `pytest (...)`, `sphinx (...)` |
| `sql.yml`      | `sqlfluff`, `bootcamp-schema-load`                       |
| `devops.yml`   | `shellcheck`, `bats`, `hadolint`                         |
| `docs.yml`     | `doxygen`                                                |
| `secrets.yml`  | `gitleaks` — **non-negotiable**, blocks merge on any new secret leak |
| `pages.yml`    | leave **off** required list — deploy job is best-effort  |
| `actionlint.yml` | `actionlint`                                          |
| `lint.yml`    | `markdownlint`, `lychee` (link-check)                    |

`pages.yml` is excluded because Pages deployment can transiently fail
on race conditions; it shouldn't gate merges.

## Tag-protection rules

Apply alongside branch protection: GitHub → **Settings → Tags →
New rule**:

| Pattern             | Effect                                                |
| ------------------- | ----------------------------------------------------- |
| `v*-s21_math`       | Only the maintainer (or `GITHUB_TOKEN` from a workflow) can push these — release pipeline |
| `v*-s21_containers` | Same                                                  |
| `v*-SmartCalc_v2.0` | Same                                                  |

This prevents accidental tag rewrites that would re-trigger a release
workflow with stale artefacts.

## Local mirror — pre-commit

Local enforcement lives in [`.pre-commit-config.yaml`](../.pre-commit-config.yaml).
After cloning, run:

```bash
pip install pre-commit
pre-commit install
```

So every `git commit` runs `ruff`, `clang-format`, `markdownlint`,
`sqlfluff`, `shellcheck`, and `typos` before the commit hook would
otherwise be bypassed by branch protection's signal-too-late timing.

## Rollback

If branch protection blocks legitimate work for >24 h with no obvious
remediation, **disable the rule first, fix the issue, re-enable**.
Do not work around it by force-pushing or signing-off-as-admin — that
defeats the point of having it.
