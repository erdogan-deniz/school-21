# Name of a virtual environment:
VENV_NAME=.venv

# spaCy launguage model URL (English):
SPACY_MODEL_URL=https://github.com/explosion/spacy-models/releases/download/en_core_web_lg-3.6.0/en_core_web_lg-3.6.0-py3-none-any.whl


# Define a venv path:
ifeq ($(OS), Windows_NT)
	PIP=$(VENV_NAME)/Scripts/pip.exe
	PYTHON=$(VENV_NAME)/Scripts/python.exe
else
	PIP=$(VENV_NAME)/bin/pip
	PYTHON=$(VENV_NAME)/bin/python
endif


check:
	python --version

ifeq ($(OS), Windows_NT)
	@where python
else
	@which python
endif

venv:
	py -3.11 -m venv $(VENV_NAME)

install: venv
	$(PYTHON) -m pip install --upgrade pip
	$(PYTHON) -m pip install --upgrade pip setuptools wheel
	$(PIP) install -r requirements.txt
	$(PYTHON) -m pip install --no-cache-dir $(SPACY_MODEL_URL)

clear:
ifeq ($(OS), Windows_NT)
	if exist $(VENV_NAME) rmdir /s /q $(VENV_NAME)
else
	rm -rf $(VENV_NAME)
endif
