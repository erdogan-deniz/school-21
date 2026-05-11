# Reproducible setup for machine_learning/project_01.
# Mirrors data_science/project_01/Makefile but without the spaCy model
# step (this project is classical ML, not NLP).
#
# Usage:
#     make install     # create .venv and install requirements
#     make notebook    # open Jupyter Lab on the workflow notebook
#     make check       # print Python version + path
#     make clear       # drop .venv
#
# Tested with Python 3.12 on Linux, macOS, Windows.

VENV_NAME = .venv

# Cross-platform venv path resolution.
ifeq ($(OS), Windows_NT)
	PIP=$(VENV_NAME)/Scripts/pip.exe
	PYTHON=$(VENV_NAME)/Scripts/python.exe
else
	PIP=$(VENV_NAME)/bin/pip
	PYTHON=$(VENV_NAME)/bin/python
endif

.PHONY: check venv install notebook clear help

help:
	@echo "Targets:"
	@echo "  install   create .venv + pip install -r requirements.txt"
	@echo "  notebook  launch Jupyter Lab on notebooks/workflow.ipynb"
	@echo "  check     print resolved Python version + path"
	@echo "  clear     drop .venv"

check:
	python --version
ifeq ($(OS), Windows_NT)
	@where python
else
	@which python
endif

venv:
	python -m venv $(VENV_NAME)

install: venv
	$(PYTHON) -m pip install --upgrade pip setuptools wheel
	$(PIP) install -r requirements.txt

notebook: install
	$(PIP) install jupyterlab
	$(PYTHON) -m jupyter lab notebooks/workflow.ipynb

clear:
ifeq ($(OS), Windows_NT)
	if exist $(VENV_NAME) rmdir /s /q $(VENV_NAME)
else
	rm -rf $(VENV_NAME)
endif
