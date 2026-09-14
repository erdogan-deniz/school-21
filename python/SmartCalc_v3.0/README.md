# `SmartCalc_v3.0`

[![CI](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml/badge.svg?branch=main)](https://github.com/erdogan-deniz/school-21/actions/workflows/python.yml)
[![Coverage](https://img.shields.io/badge/coverage-99%25-brightgreen.svg)](#tests)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](../../LICENSE)

> *PyQt6 desktop calculator on top of the [`c/SmartCalc_v1.0`](../../c/SmartCalc_v1.0/) C core (loaded via `ctypes`) — strict MVVM, expression evaluation with `x`, function plotting, loan and deposit modes, persistent history, config file and rotating logs.*

## Quick start

```bash
cd python/SmartCalc_v3.0
python3.11 -m venv .venv && source .venv/bin/activate   # Windows: .venv\Scripts\activate

# Build
make install-dev   # pip install -e ".[dev]"  (PyQt6, matplotlib, pytest, hypothesis, ruff, mypy)
make lib           # compiles ../../c/SmartCalc_v1.0/src -> src/libs/libsmartcalc.{so,dylib,dll}

# Run
make run           # PyQt6 GUI

# Test
make test          # pytest + coverage (361 tests)
```

`make lib` needs a C toolchain: `gcc` on Linux, `clang` on macOS, MSVC Build Tools on
Windows (discovered through `vswhere.exe`; run `python scripts/build_lib.py` there). The
C sources are resolved in this order: `$SMARTCALC_C_SRC`, `../../c/SmartCalc_v1.0/src`
(this repo), `smart_calculator/src/`, `c_src/`. Packaging: `make dist` (PyInstaller,
`smartcalc.spec`) and `make installer` (Inno Setup, `installer.iss`). Python is pinned to
3.11 (`requires-python = ">=3.11,<3.12"`).

## Demo

> **TODO** — short capture of evaluating an expression, plotting `f(x)` and switching to the
> deposit mode is planned in the python/ demo slice.

## Documentation

- [`docs/user-guide.md`](docs/user-guide.md) — interface walkthrough, expression syntax, config keys.
- [`docs/developer-guide.md`](docs/developer-guide.md) — MVVM layering, build of the C core, packaging, how to add a C export.
- [`docs/api.md`](docs/api.md) — model-layer API (`Calculator`, `LoanCalculator`, `DepositCalculator`, `History`, results and enums).
- Layout: `src/model/` (ctypes wrapper, finance, history) · `src/viewmodel/` (Qt-free observable state) · `src/view/` (PyQt6 widgets, zero business logic) · `src/utils/` (config, logger).
- Sphinx HTML build: planned — the docstrings already follow the Google convention (ruff rule sets `D` and `DOC`).

## Tests

- Framework: **pytest** + **hypothesis** (property-based) + **pytest-cov**; static checks: **ruff** (strict, see `pyproject.toml`) and **mypy**.
- 361 tests across `tests/model`, `tests/viewmodel`, `tests/utils`, `tests/integration`, `tests/property_based`.
- Coverage: **99 %** of `src/model`, `src/viewmodel`, `src/utils` (the `src/view` layer and `main.py` are excluded by design — see `[tool.coverage.run]`).
- CI: the `smartcalc-v3` job in [`.github/workflows/python.yml`](../../.github/workflows/python.yml) builds the C core, runs ruff and pytest on Python 3.11 and uploads coverage to Codecov (flag `python-SmartCalc_v3.0`).
- The shared library must exist before the tests run — `make lib` first.

## License & attribution

This project was developed as part of the **School 21** curriculum (analogue of
School 42). The repository as a whole is licensed under the **MIT License** —
see the root [`LICENSE`](../../LICENSE).

The `LICENSE` file inside this subproject (`# School 21 License`) is preserved
as educational attribution and historical artefact; it does not override the
repo-wide MIT licence.

---

## Original task (School 21)

![Project header](content/images/project_header.jpg)

## Story

Thomas stood outside the painfully familiar club, which now looked completely abandoned.
Seb hadn't been seen for months and this was probably why.
When Thomas received a text message with no name but a familiar address, he thought it was Sebastian and jumped on the first flight to *California*.
And even now he is still hoping that it will be Seb who shows up at the time mentioned in the message.
But those hopes began to fade.

- "I thought this was a popular place," a voice behind him brought Thomas out of his musings."

- "What?"
  "Yes, it used to be like that," Thomas replied confusedly to the stranger.

- "A guy I know used to brag about it."
  "Said his dad used to run the place and serve the best non-alcoholic mojitos in *Compton*."
  "I wish I'd had time to come here earlier when it was still open."
  "I'm John, by the way."

- "I'm Thomas."
  "So you knew Sebastian?"

- "Yeah, he and I worked in the same department."
  "Well, he was an intern there until one day he suddenly disappeared without a word."
  "And you?"

- "We grew up in the same area."
  "I haven't heard from him lately either."
  "I got a message with a familiar address, so I thought it might be from him."

- "A message, you say?"
  "With an address and time?" John raised an eyebrow.

- "And a promise of answers to all questions, yes," Thomas replied.

- "Looks like we are here for a reason."
  "And it looks like we're not the only ones," Thomas turned and noticed a girl looking around the square in front of the jazz club.

- "Let me guess, a mysterious text message promising answers to all your questions brought you here as well?" Thomas asked the girl.

- "Yes, exactly," she replied after a moment's thought.

- "Well, that makes three of us!" John exclaimed.

- "Instead of answers, we just get more questions."
  "I'm John, by the way, and this is Thomas."
  "We literally just got here and met."
  "And you are...?"

- "Eve."

- "Well, nice to meet you, Eve," John said.

- "I'm curious to hear your guesses as to why we're here and what we're expecting," he hadn't finished speaking when another taxi pulled up beside them and a young man jumped out, dropping his bag on the way.

He looked strange to John.

- "Chuck?!"
  "And you're here too?" Eve said slightly surprised.

- "Oh, hi, Eve!"
  "What a faraway place to meet."
  "How small the world is!"
  "And what do you mean, here?"
  "Did you get that weird text message too?" Chuck seemed out of breath, constantly looking around for either potential danger or something interesting.

- "I hope I'm not too late."

- "We all got that text," John interjected.

- "I'm John, this is Thomas."

- "I'm Chuck."
  "I never thought it would be such a mysterious meeting in the middle of nowhere," Chuck replied, looking around.

- "It's not exactly the middle of nowhere," Thomas replied.

- "Until a few months ago, there was a nice, lively jazz club here, owned by the father of a good friend of mine."
  "Who, it turns out, was an acquaintance of John's."
  "He was a colleague of yours, wasn't he?"
  "Except that neither John nor I had heard from him in over three months."
  "And the club..."
  "Well, you can see how it's turned out," Thomas looked sadly at the building.

- "Where did you work?" Eve asked John.

- "A local branch of *SIS*," John murmured back.
  "Managing network applications and configuring computer hardware."

- "Chuck and I are also from *SIS*."
  "Different departments and the *Eastern Division*, but still," Eve said thoughtfully.

- "Where do you work, Thomas?"

- "*Advanced Solutions Inc*."
  "Subsidiary of *SIS*, recently transferred there."
  "I had to take a leave of absence to come here, but I was seriously worried about Seb, and apparently not for nothing."
  "It turns out that we're all connected to *SIS* in one way or another."

- "And not just that, right, Eve?" Chuck said.

- "I've got some documents here that I think you might find interesting, so where are they..."

Who knows where this conversation would have gone if not for the simultaneous beeping and vibrating of the smartphones in everyone's pockets.

> Greetings to all!
I'm very pleased that you were interested and were able to arrive on time.
You are gathered here for a reason and you will indeed get all the answers.
But only after a small test.
There is one task that you like to test me on.
But now it's time to trade places.
Prove that you are ready and able to handle the tasks ahead of you and then I will answer all your questions.
A test with details is already waiting for you in your personal repositories.
Please begin immediately.
Thank you.

Thomas thoughtfully reread the text over and over again, and only Chuck's quiet whisper broke the silence:
"The Terminator..." he whispered.

## Introduction

In this project, you will implement an extended version of the calculator in the *Python* programming language.

## *MVP* pattern

The *MVP* pattern shares components with *MVC* pattern: the model, the view.
It replaces the controller with a presenter.
The presenter implements the interaction between the model and the view.
When the view notifies the presenter that the action has been done, the presenter update the model and synchronizes changes between the model and the view.
The presenter does not interact with the view, it uses an interface.
This allows components of the application to be tested individually.

![*MVP* pattern](content/images/patterns/mvp.png)

## *MVVM* pattern

*MVVM* pattern is a updated of *MVC* pattern.
The target of *MVVM* pattern is to provide a separation between the presentation and model.
*MVVM* pattern supports bi-directional data binding between view and view model components.
The view is a subscriber to property value change events the view model.
When a property has changed in the view model, the view updated property value from the view model.
When the user interacts with an *UI*, the view calls a command provided by the view model.
A view model is an abstraction of a view and a wrapper of data from the model.
It contains the model transformed into the view, as the commands that the view use to affect the model.

![*MVVM* pattern](content/images/patterns/mvvm.png)

## Implementation of the project

Implement a program:

- The program is developed in *Python* 3.11 - OK
- Stick to *Google* code style *CHECK*
- The program has the *MVVM* or *MVP* pattern:
  - there are not business logic in the view
  - there are not interface code in the model, presenter and view model

- The "core" of the calculator is a dynamic library in *C*/*C++*
- The model is a "core" with a wrapper
- The model has the functionality of the calculator
- The program code is in the `src` folder
- Integers and real numbers entered into the program, written in point or exponential form
- The calculation will be performed after the input of the expression and pressing the `=` symbol
- Calculation of bracketed expressions in infix notation
- Calculate parenthesized expressions in infix notation with substitution of the `x` number
- The user enter up to `255` characters
- The accuracy of the fractional part is `7`+ decimal places
- Plotting a function defined by an expression in infix notation with the `x`
  With: coordinate axes, scale markers and grid with adaptive step

- The definition and the value ranges of the functions are limited from `-1000000` to `1000000`
- It is necessary to specify the definition and value ranges to plot a function
- The program stores the history of operations, allow: load expressions from the history and clear the history
- The history saved between runs of the application
- Develop a desktop application
- Prepare an implementation with a graphical user interface for either Linux or Mac OS, based on any GUI library or framework
- The application should have a help section with a description of the program interface in random form
- Prepare full coverage of the methods in the model layer with unit tests
- Prepare the installer, which will install the application to the system with the standard settings (installation path, creating shortcut)

- Bracketed arithmetic expressions in infix notation shall support the following arithmetic operations and mathematical functions:
  - **Arithmetic operators**:

      | Operator name | Infix Notation | Prefix notation | Postfix notation |
      | ------------- | ------------------------ | --------------------------------- | ------------------------------------------ |
      | Parentheses | (a + b) | (+ a b) | a b + |
      | Addition | a + b | + a b | a b + |
      | Subtraction | a - b | - a b | a b - |
      | Multiplication | a * b | * a b | a b * |
      | Division | a / b | / a b | a b \ |
      | Rasing to the power | a ^ b | ^ a b | a b ^ |
      | Remainder of division | a mod b | mod a b | a b mod |
      | Unary plus | +a | +a | a+ |
      | Unary minus | -a | -a | a- |

      > Please note that the multiplication operator contains a mandatory `*` sign.
      Processing an expression with the `*` sign omitted is optional and left to the developer's discretion.

      | Function description | Function |
      | -------------------- | -------- |
      | Calculates cosine | cos(x) |
      | Calculates sine | sin(x) |
      | Calculates tangent | tan(x) |
      | Calculates arc cosine | acos(x) |
      | Calculates the arcsine | asin(x) |
      | Calculates arctangent | atan(x) |
      | Calculates square root | sqrt(x) |
      | Calculates natural logarithm | ln(x) |
      | Calculates decimal logarithm | log(x) |

## Loan calculator

Provide a mode: "loan calculator" (you can take websites like banki.ru and calcus.ru as an example):

- Input: total loan amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment for the loan, total repayment

## Deposit calculator

Provide a special mode "deposit calculator" (you can take websites like banki.ru and calcus.ru as an example):

- Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, list of additions, list of partial withdrawals
- Output: accrued interest, tax amount, amount on deposit by the end of the term

## Configuration and logging

Add settings to the app:

- Add reading of settings from configuration file when the program runs
- Include in the configuration file 3 or more parameters to choose from, such as background color, font size, etc
- Add descriptions of editable parameters to help

Add logging to the application:

- Store operation history in logs
- Save logs in the logs folder, one file per rotation period
- It should be possible to set the period of logs rotation (hour/day/month)
- Files must be named according to the following pattern: `logs_dd-MM-yy-hh-mm-ss`

## Cross-platform

Make application cross-platform:

- Add support: Linux, Mac, Windows
- The installer should be available for: Linux, Mac and Windows

## End

Thomas finished the calculator without too much trouble.
He already knew *Python*, so he quickly put together a simple desktop application.
The other guys seemed to be finishing their work as well.

As soon as everyone was done, new messages from an anonymous person appeared on their phones:

> Thank you.
I see you all did well.
That's great, even though the algorithms predicted it all along.
Please establish a secure connection to the server specified in the following message and connect to the chat room specified.
There we will be able to talk freely and calmly.
I also have some special information for Thomas and John regarding your friend Seb.
See you in the chat room!
