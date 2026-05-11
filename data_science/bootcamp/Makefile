# Reproducible setup for data_science/bootcamp.
#
# Each day's environment is isolated: `make install DAY=NN` creates
# `day_NN/.venv` (or `team_NN/.venv`) and installs the local
# requirements.txt into it. This avoids cross-day version conflicts
# (e.g. numpy 1.x vs 2.x between teams).
#
# Usage:
#     make install DAY=08          # day_08/.venv
#     make install DAY=team_00     # team_00/.venv
#     make jupyter DAY=07          # launch Jupyter Lab in day_07/
#     make clear DAY=08            # drop day_08/.venv
#     make help
#
# Days 00-04 are shell-based (bash + curl + jq) — no Python venv
# needed; run their `src/setup.sh` directly.
#
# Tested with Python 3.12 on Linux, macOS, Windows.

DAY ?= 05

# Resolve the day folder: prefer `day_$(DAY)`, fall back to literal $(DAY)
# (so `make install DAY=team_00` works).
ifneq ($(wildcard day_$(DAY)),)
DAY_DIR = day_$(DAY)
else
DAY_DIR = $(DAY)
endif

VENV = $(DAY_DIR)/.venv

# Cross-platform venv path resolution.
ifeq ($(OS), Windows_NT)
	PIP=$(VENV)/Scripts/pip.exe
	PYTHON=$(VENV)/Scripts/python.exe
else
	PIP=$(VENV)/bin/pip
	PYTHON=$(VENV)/bin/python
endif

# Locate the day's requirements.txt — some live at the day root,
# some under day/src.
REQS = $(shell \
         if [ -f $(DAY_DIR)/requirements.txt ]; then echo $(DAY_DIR)/requirements.txt; \
         elif [ -f $(DAY_DIR)/src/requirements.txt ]; then echo $(DAY_DIR)/src/requirements.txt; \
         fi)

.PHONY: help install jupyter clear list

help:
	@echo "Targets:"
	@echo "  install DAY=NN    create $(DAY_DIR)/.venv + pip install -r requirements.txt"
	@echo "  jupyter DAY=NN    install + launch Jupyter Lab on the day folder"
	@echo "  clear   DAY=NN    drop $(DAY_DIR)/.venv"
	@echo "  list              print every day's requirements.txt path"
	@echo ""
	@echo "Days 00-04 are shell-based (bash + curl + jq) and don't need a venv;"
	@echo "run their src/setup.sh directly."

list:
	@for d in day_* team_*; do \
	    if [ -f "$$d/requirements.txt" ]; then echo "$$d (root reqs)"; \
	    elif [ -f "$$d/src/requirements.txt" ]; then echo "$$d (src/ reqs)"; \
	    else echo "$$d (no requirements.txt)"; \
	    fi; \
	done

install:
	@if [ -z "$(REQS)" ]; then echo "No requirements.txt found in $(DAY_DIR) or $(DAY_DIR)/src"; exit 1; fi
	python -m venv $(VENV)
	$(PYTHON) -m pip install --upgrade pip setuptools wheel
	$(PIP) install -r $(REQS)
	@echo "Installed $(REQS) into $(VENV)"

jupyter: install
	$(PIP) install jupyterlab
	$(PYTHON) -m jupyter lab $(DAY_DIR)

clear:
ifeq ($(OS), Windows_NT)
	if exist $(VENV) rmdir /s /q $(VENV)
else
	rm -rf $(VENV)
endif
