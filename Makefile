# Repo-root Makefile for school-21.
#
# Aggregates dev-experience shortcuts at the repo level. Per-subproject
# Makefiles (e.g. c/s21_math/src/Makefile, sql/bootcamp/Makefile,
# machine_learning/project_01/Makefile) keep their own targets — this
# file does not shadow them.
#
# Usage:
#     make help               # list targets
#     make install            # install pre-commit + dev tooling
#     make precommit          # run pre-commit on staged files
#     make precommit-all      # run pre-commit on every tracked file
#     make lint               # alias for precommit-all
#     make lint-md            # markdownlint only
#     make lint-shell         # shellcheck on devops/ shell scripts
#     make lint-python        # ruff check + format-check
#     make lint-cpp           # clang-format dry-run over c/ + cpp/
#     make lint-sql           # sqlfluff on sql/
#     make lint-secrets       # gitleaks scan of the working tree
#
# Tested with GNU Make 4.x on Linux, macOS, and Windows (MSYS2).

# ----- Variables -----
SHELL          := /bin/bash
PYTHON         ?= python3
PIP            ?= $(PYTHON) -m pip

PRECOMMIT_VER  := 3.7.1
RUFF_VER       := 0.6.9
SQLFLUFF_VER   := 3.2.5
GITLEAKS_VER   := 8.18.4

# ----- Targets -----
.PHONY: help install \
        precommit precommit-all \
        lint lint-md lint-shell lint-python lint-cpp lint-sql lint-secrets \
        clean

help:                  ## Show this help.
	@awk 'BEGIN {FS = ":.*## "; printf "Targets:\n"} \
	      /^[a-zA-Z_-]+:.*## / {printf "  %-18s %s\n", $$1, $$2}' \
	      $(MAKEFILE_LIST)

install:               ## Install pre-commit + repo-level dev tooling.
	$(PIP) install --upgrade pip
	$(PIP) install \
	    pre-commit==$(PRECOMMIT_VER) \
	    ruff==$(RUFF_VER) \
	    sqlfluff==$(SQLFLUFF_VER)
	@command -v pre-commit > /dev/null && pre-commit install || \
	    echo "pre-commit install skipped — re-run 'make install' to retry"

precommit:             ## Run pre-commit on staged files (the git-hook path).
	pre-commit run

precommit-all:         ## Run every pre-commit hook over every tracked file.
	pre-commit run --all-files

lint: precommit-all    ## Alias for `precommit-all`.

lint-md:               ## markdownlint over every *.md, sans vendor folders.
	@command -v markdownlint-cli2 > /dev/null || { \
	    echo "markdownlint-cli2 not found — install via 'npm i -g markdownlint-cli2'"; exit 1; }
	markdownlint-cli2 \
	    '**/*.md' \
	    '#**/node_modules/**' \
	    '#**/charisel/**' \
	    '#**/site-packages/**'

lint-shell:            ## shellcheck over every devops/**/*.sh + *.bash.
	@command -v shellcheck > /dev/null || { \
	    echo "shellcheck not found — install via 'apt install shellcheck' or 'brew install shellcheck'"; exit 1; }
	@mapfile -t files < <(find devops/ \( -name '*.sh' -o -name '*.bash' \)); \
	  if [ "$${#files[@]}" -eq 0 ]; then echo "No shell scripts."; exit 0; fi; \
	  echo "Checking $${#files[@]} files..."; \
	  shellcheck "$${files[@]}"

lint-python:           ## ruff lint + format-check over the Python tracks.
	ruff check python/ algorithms/python/ data_science/ machine_learning/ qa/
	ruff format --check python/ algorithms/python/ data_science/ machine_learning/ qa/

lint-cpp:              ## clang-format dry-run over c/ + cpp/ (no writes).
	@command -v clang-format > /dev/null || { \
	    echo "clang-format not found — install via 'apt install clang-format' or 'brew install clang-format'"; exit 1; }
	@find c/ cpp/ \
	    \( -name '*.c' -o -name '*.h' -o -name '*.cc' -o -name '*.cpp' -o -name '*.hpp' \) \
	    -not -path '*/build*/*' \
	    -not -path '*/Qt/*' \
	    -not -path '*/QtGifImage*/*' \
	    -not -path '*/moc_*' -not -path '*/ui_*' \
	    -print0 \
	    | xargs -0 -r clang-format --dry-run --Werror

lint-sql:              ## sqlfluff over sql/ (postgres dialect).
	sqlfluff lint sql/ --dialect postgres

lint-secrets:          ## gitleaks scan of the working tree.
	@command -v gitleaks > /dev/null || { \
	    echo "gitleaks not found — install via https://github.com/gitleaks/gitleaks/releases or 'brew install gitleaks'"; exit 1; }
	gitleaks detect --source . --config .gitleaks.toml --verbose

clean:                 ## Remove cached pyc / __pycache__ / .ruff_cache.
	find . \
	    \( -name '__pycache__' -o -name '.ruff_cache' -o -name '.pytest_cache' \) \
	    -type d -prune -exec rm -rf {} + 2>/dev/null || true
	find . -name '*.pyc' -type f -delete 2>/dev/null || true
