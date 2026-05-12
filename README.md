#

<!-- School 21 Logo -->
<p align="center">
    <img
    src="https://sun9-38.userapi.com/impg/KJR2NK87iyCNo7L8oZ9379FOTBF2nQJJ3mWvZw/mFRmaBUOkuk.jpg?size=480x360&quality=96&sign=8ffee636080944c3067db7ad320c8400&type=album"
    alt="School 21 Logo"
    />
</p>

## About *School 21*

**School 2️⃣1️⃣** (the analogue of the *School 4️⃣2️⃣*) — is a free digital
technology school.
It offers: free and non-profit education without: traditional teachers, lessons,
grades.
Students learn teamwork and project activities.

## Repository Description

A repository is a collection of completed *School 2️⃣1️⃣* projects.

## Production readiness

This repo is undergoing a production-grade overhaul (2026-05). Live status:

[![lint](https://github.com/erdogan-deniz/school-21/actions/workflows/lint.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/lint.yml)
[![c](https://github.com/erdogan-deniz/school-21/actions/workflows/c.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/c.yml)
[![cpp](https://github.com/erdogan-deniz/school-21/actions/workflows/cpp.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/cpp.yml)
[![python](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml)
[![sql](https://github.com/erdogan-deniz/school-21/actions/workflows/sql.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/sql.yml)
[![devops](https://github.com/erdogan-deniz/school-21/actions/workflows/devops.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/devops.yml)
[![docs](https://github.com/erdogan-deniz/school-21/actions/workflows/docs.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/docs.yml)
[![pages](https://github.com/erdogan-deniz/school-21/actions/workflows/pages.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/pages.yml)
[![secrets](https://github.com/erdogan-deniz/school-21/actions/workflows/secrets.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/secrets.yml)
[![codecov](https://codecov.io/gh/erdogan-deniz/school-21/branch/main/graph/badge.svg)](https://codecov.io/gh/erdogan-deniz/school-21)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

- **Top-level dashboard:** [`STATUS.md`](STATUS.md) — production-readiness matrix
  for all 37 subprojects across 8 Definition-of-Done items.
- **Per-subproject plans:** [`docs/plans/`](docs/plans/) — checklist + history
  per subproject.
- **Design doc:** [`docs/specs/2026-05-11-production-grade-overhaul.md`](docs/specs/2026-05-11-production-grade-overhaul.md).
- **Working agreement:** [`CLAUDE.md`](CLAUDE.md) — repo-wide rules and conventions.
- **AI-coding-agent contract:** [`AGENTS.md`](AGENTS.md) — public counterpart of CLAUDE.md, read by Copilot CLI / Cursor / Aider on session start.
- **Security policy:** [`SECURITY.md`](SECURITY.md) — how to report vulnerabilities + the three-layer leak-prevention stack (gitleaks pre-commit + secrets.yml CI + bandit + pip-audit).
- **Dev shortcuts:** [`Makefile`](Makefile) — `make install` (pre-commit + dev tooling), `make precommit-all` (run every hook), `make lint-{md,shell,python,cpp,sql,secrets}` for the per-language gates. `make help` lists every target.
- **Toolchain pins:** [`docs/TOOLCHAIN.md`](docs/TOOLCHAIN.md) — every language / linter / framework version, single source of truth.
- **Changelog:** [`CHANGELOG.md`](CHANGELOG.md) — Keep-a-Changelog record of the 2026-05-11 production-grade overhaul.
- **Generated docs site:** [erdogan-deniz.github.io/school-21](https://erdogan-deniz.github.io/school-21/) — Doxygen + Sphinx HTML, built and deployed by [`pages.yml`](.github/workflows/pages.yml).

## Repository Source File Structure

- [`algorithms/`](algorithms/), [`c/`](c/), [`career_track/`](career_track/), [`cpp/`](cpp/), [`data_science/`](data_science/), [`devops/`](devops/), [`internship/`](internship/), [`machine_learning/`](machine_learning/), [`python/`](python/), [`qa/`](qa/), [`sql/`](sql/), [`survival_camp/`](survival_camp/) — language / track folders, each with one or more subprojects.
- [`content/`](content/) — materials for the repo's design (badge images) and templates ([`content/templates/SUBPROJECT_README.md`](content/templates/SUBPROJECT_README.md)).
- [`docs/`](docs/) — design specs and per-subproject plans.
- [`.github/workflows/`](.github/workflows/) — 8 CI workflows (lint, c, cpp, python, sql, devops, docs, pages).
- [`CLAUDE.md`](CLAUDE.md), [`STATUS.md`](STATUS.md), [`LICENSE`](LICENSE), [`.clang-format`](.clang-format), [`.ruff.toml`](.ruff.toml), [`.gitignore`](.gitignore), [`.markdownlint.json`](.markdownlint.json) — repo-wide configuration and rules.
- `README.md`: the description file of the repository (you read it).

## About My Platform Account

### General Information

- Campus location: *Moscow*
- Wawe: 10.2022
- Nickname: *charisel*
- Program: *Core program*
- Level: 12
- XP: 20975
- *E-mail*: <charisel@student.21-school.ru>

### Acquired Skills

<!-- Acquired Skills Wheel Photo -->
<img
    src="content/images/account/skill_wheel.png"
    alt="Skill Wheel"
/>

| Skill Name: | Skill Points: |
|:------------:|:--------------------:|
| Math | 91 |
| *QA* | 400 |
| *C* | 1423 |
| *OOP* | 1284 |
| *C++* | 1188 |
| *SQL* | 1183 |
| DevOps | 264 |
| *Linux* | 558 |
| Backend | 153 |
| Analysis | 122 |
| Graphics | 704 |
| *Python* | 1936 |
| Team Work | 940 |
| DB & Data | 576 |
| *ML* & *AI* | 639 |
| Algorithms | 2091 |
| Leadership | 1339 |
| Web Development | 136 |
| *Shell* & *Bash* | 411 |
| Parallel Computing | 23 |
| Company Experience | 3574 |
| Information Security | 36 |
| Functional Programming | 180 |
| Structured Programming | 1551 |
| Types & Data Structures | 873 |
| Network & System Administration | 506 |

### Peers Feedback

- Nice: 4/4 😃
- Punctual: 4/4 ⏲
- Rigorous: 4/4 ⚖️
- Interested: 4/4 ❓

All peer reviews: 196

### Learning Badges

#### Education Progress

| Badge Name: | Badge Rank: | Badge Description: | Badge Image: |
|:-----------:|:-----------:|:------------------:|:------------:|
| *Real Programmer* | 5/5 | Successfully perform `50` projects. | <img src="content/images/badges/real_programmer.png" width="100" height="100" alt="Real programmer" /> |
| *Perfectionist* | 5/5 | Successfully perform `21` projects with a bonus part. | <img src="content/images/badges/perfectionist.png" width="100" height="100" alt="Perfectionist" /> |
| *Mistakes Are Not For Me* | 5/5 | Successfully perform `21` projects in a row without failur. | <img src="content/images/badges/mistakes_are_not_for_me.png" width="100" height="100" alt="Mistakes Are Not For Me" /> |
| *King Of Study* | - | Two badges for studies were obtained. | <img src="content/images/badges/king_of_study.png" width="100" height="100" alt="King Of Study" /> |
| *Welcome On Board* | - | The *Survival Camp* was completed. | <img src="content/images/badges/welcome_on_board.png" width="100" height="100" alt="Welcome On Board" /> |
| *Pollinator* | - | Successfully perform `15` group projects with `15` different partners in a team. | <img src="content/images/badges/pollinator.png" width="100" height="100" alt="Pollinator" /> |
| *3 PRP* | - | - | <img src="content/images/badges/3_prp.png" width="100" height="100" alt="3 PRP" /> |
| *Finale Exam Passed* | - | - | <img src="content/images/badges/final_exam_passed.png" width="100" height="100" alt="Finale Exam Passed" /> |

#### Academic Activities

| Badge Name: | Badge Rank: | Badge Description: | Badge Image: |
|:-----------:|:-----------:|:------------------:|:------------:|
| *Such A Listener* | 5/5 | Visit `50` lectures`. | <img src="content/images/badges/such_a_listener.png" width="100" height="100" alt="Such A Listener" /> |
| *Lead The World* | 3/5 | Be a team lead in `5` projects. | <img src="content/images/badges/lead_the_world.png" width="100" height="100" alt="Lead The World" /> |

#### Social Activities

| Badge Name: | Badge Rank: | Badge Description: | Badge Image: |
|:-----------:|:-----------:|:------------------:|:------------:|
| *Happy Halloween!* | - | BOOOO! | <img src="content/images/badges/halloween.png" width="100" height="100" alt="Such Happy Halloween!" /> |
| *Computer Security Day 2023* | - | Happy Cybersecurity Day! | <img src="content/images/badges/computer_security_day.png" width="100" height="100" alt="Computer Security Day 2023" /> |
| *Harry New Year, Moscow!* | - | *Happy New Year*, our dear, beloved peers! | <img src="content/images/badges/happy_new_year.png" width="100" height="100" alt="Harry New Year, Moscow!" /> |
| *Space Exploration Day* | - | As *Yuri Gagarin* once said: `Let's go!` | <img src="content/images/badges/space_exploration.png" width="100" height="100" alt="Space Exploration Day" /> |

#### Other

| Badge Name: | Badge Rank: | Badge Description: | Badge Image: |
|:-----------:|:-----------:|:------------------:|:------------:|
| *Billionaire* | 3/5 | Accumulate 500 coins. | <img src="content/images/badges/billionaire.png" width="100" height="100" alt="Billionaire" /> |
| *Happy Halloween!* | - | Happy Halloween! | <img src="content/images/badges/halloween_old.png" width="100" height="100" alt="Happy Halloween!" /> |
| *Happy Birthday, Moscow сampus!* | - | The *Moscow* campus of *School 21* has turned `5` years old! | <img src="content/images/badges/happy_birthday.png" width="100" height="100" alt="Happy Birthday, Moscow сampus!" /> |
| *Happy birthday, Wave `16`!* | - | With love from ADM. | <img src="content/images/badges/wawe_16.png" width="100" height="100" alt="Happy birthday, Wave 16!" /> |

#### Supporting

| Badge Name: | Badge Rank: | Badge Description: | Badge Image: |
|:-----------:|:-----------:|:------------------:|:------------:|
| *Will you be my peer?* | - | Love is *School 21*, which has become a second home! | <img src="content/images/badges/14_febrarue.png" width="100" height="100" alt="Will you be my peer?" /> |

### About Me

- Telegram: @deniz_erdogan
- E-mail: <erdogan33@mail.ru>
- Specialization: Python backend developer & Data Scientist
