# Security policy

## Reporting a vulnerability

If you've found a security issue in this repository, please report it
privately so the fix can land before the issue is publicised:

- **Preferred:** open a private security advisory via GitHub's
  [Security tab][advisory] (Settings → Security → Advisories →
  "Report a vulnerability"). This keeps the discussion confidential
  with the maintainer.
- **Alternative:** email the maintainer at the address on the GitHub
  profile ([@erdogan-deniz](https://github.com/erdogan-deniz)).
- **What to include:** the affected file path(s), how to reproduce,
  why it's a problem, and a suggested fix if you have one.

Please **do not** file a public Issue or Pull Request that describes
the vulnerability before the fix lands.

[advisory]: https://github.com/erdogan-deniz/school-21/security/advisories/new

## Scope and intent

`school-21` is an **educational portfolio** of work completed during
the School 21 curriculum (analogue of School 42). The code is not
production-deployed anywhere — it exists for inspection, learning, and
forking. That said, the repository is public and pinned, so it gets
some real-world traffic and the security posture matters:

- Forks of this repo may end up running the bootcamp code with real
  credentials substituted in.
- Workflows under [`.github/workflows/`](.github/workflows/) execute
  on every push and PR — anything insecure there directly affects
  the CI environment.
- Two real hardcoded-credential leaks have already been caught and
  rotated during the 2026-05-11 production-grade overhaul (Telegram
  bot token in `devops/ci_cd/src/notify.sh`; local-Postgres password
  in `python/bootcamp/old/day_06/src/arguments.py`). The defences
  below exist specifically to make a third one impossible without
  deliberate bypass.

## How we prevent leaks

Three independent layers, mechanical enforcement at every layer:

| Layer | Tool | Where | What it catches |
| ----- | ---- | ----- | --------------- |
| Pre-commit | [gitleaks][gl] v8.18.4 hook in [`.pre-commit-config.yaml`](.pre-commit-config.yaml) | Local `git commit` | New secrets before they enter any commit |
| CI | [`secrets.yml`](.github/workflows/secrets.yml) — `gitleaks-action@v2` with `fetch-depth: 0` | Every push / PR on `main` | Anything that slipped past pre-commit, including full history |
| CI (Python) | [`python.yml`](.github/workflows/python.yml) `bandit` job (`bandit==1.7.10`) | Every push / PR touching Python | SAST issues — weak crypto, SQL injection, dangerous deserialisation, ` shell=True ` subprocesses |
| CI (Python deps) | [`python.yml`](.github/workflows/python.yml) `pip-audit` matrix (`pip-audit==2.7.3`) | Every push / PR | Known-CVE packages in every `requirements.txt` |

[gl]: https://github.com/gitleaks/gitleaks

The full repo-wide allow-list is in [`.gitleaks.toml`](.gitleaks.toml).
Allowed entries are scoped to two cases only:

1. Rotated former secrets that no longer authenticate anything
   (kept so historical commits don't re-trigger alerts).
2. Bootcamp-local env-var fallbacks (e.g. the `1969` Postgres
   password used as a *default* in `os.environ.get("DB_PASSWORD",
   "1969")` — never a live credential).

**Never** allow-list an active secret. The protocol is documented
in [`AGENTS.md` rule #7](AGENTS.md): rotate first (upstream
revocation), refactor source to read from env, then if necessary
allow-list the rotated value.

## What's deliberately NOT addressed

- **Threat modelling for production deployment.** Bootcamp code
  shouldn't be deployed as-is to anything that touches real users.
  Where samples wire up Flask / FastAPI / nginx, the patterns are
  pedagogical, not hardened.
- **Dependency auto-update merges.** [`dependabot.yml`](.github/dependabot.yml)
  opens weekly PRs for GitHub Actions versions; nothing auto-merges.
  All Python and C/C++ pins are deliberate.
- **History-level secret scrubbing.** A `git filter-repo` pass is
  prepared (`backup-pre-filter-repo` branch exists locally), but
  history rewrites require the maintainer to run them manually —
  the Claude Code agent harness blocks force-push by design. The
  rotated Telegram bot token and the local Postgres password are
  both **valueless** in their pre-rotation forms, so the practical
  attack surface has been neutralised even before history is
  scrubbed.

## Supported versions

This is a single-branch repository (`main` only). Whatever is at
`HEAD` is what's "supported"; there is no LTS / current / release
split. The three flagship subprojects ([`STATUS.md`](STATUS.md)
"Flagships" section) carry semver tags (`v*-s21_math`,
`v*-s21_containers`, `v*-SmartCalc_v2.0`) on independent release
trains — those tags are signed and reproducible from the
corresponding `release-*.yml` workflow output.

## Acknowledgements

The two 2026-05-11 incidents were caught by maintainer-side security
sweep (`grep` audit during the production-grade overhaul). No
external reports have been received yet; this section will list
researchers as reports come in.
