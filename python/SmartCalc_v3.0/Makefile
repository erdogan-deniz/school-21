ifeq ($(OS),Windows_NT)
    PYTHON := .venv/Scripts/python
else
    PYTHON := .venv/bin/python
endif

ifneq ($(OS),Windows_NT)
_PY_VER    := $(shell $(PYTHON) -c "import sys; print('%d.%d' % sys.version_info[:2])" 2>/dev/null)
ifneq ($(_PY_VER),3.11)
$(error Python 3.11 required, found '$(_PY_VER)'. Run: python3.11 -m venv .venv && make install-dev)
endif
endif

# Path to the C sources from smart_calculator.
# Resolution order:
#   1. SMARTCALC_C_SRC environment variable
#   2. smart_calculator/src/ inside this repo (bundled copy)
#   3. c_src/ subdirectory (fallback / git submodule)
# Example: export SMARTCALC_C_SRC=/path/to/smart_calculator/src
ifdef SMARTCALC_C_SRC
    C_SRC := $(SMARTCALC_C_SRC)
else ifneq ($(wildcard smart_calculator/src),)
    C_SRC := smart_calculator/src
else
    C_SRC := c_src
endif
LIB_DIR := src/libs

ifeq ($(OS),Windows_NT)
    LIB_EXT := dll
    RM := del /Q
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME),Darwin)
        LIB_EXT := dylib
    else
        LIB_EXT := so
    endif
    RM := rm -f
endif

LIB_FILE := $(LIB_DIR)/libsmartcalc.$(LIB_EXT)

C_SOURCES := \
    $(C_SRC)/s21_calculator.c \
    $(C_SRC)/calculate/s21_calculate.c \
    $(C_SRC)/parser/s21_parser.c \
    $(C_SRC)/transform/s21_delete_spaces.c \
    $(C_SRC)/stack/s21_push_stack.c \
    $(C_SRC)/stack/s21_pop_stack.c \
    $(C_SRC)/stack/s21_free_stack.c \
    $(C_SRC)/stack/s21_create_stack.c \
    $(C_SRC)/stack/s21_create_node_stack.c \
    $(C_SRC)/stack/s21_clear_node_stack.c \
    $(C_SRC)/stack/s21_fill_node_stack.c \
    $(C_SRC)/stack/s21_get_node_priority.c \
    $(C_SRC)/list/s21_push_list.c \
    $(C_SRC)/list/s21_pop_list.c \
    $(C_SRC)/list/s21_free_list.c \
    $(C_SRC)/list/s21_free_node_list.c \
    $(C_SRC)/list/s21_create_list.c \
    $(C_SRC)/list/s21_create_node_list.c \
    $(C_SRC)/list/s21_clear_node_list.c \
    $(C_SRC)/list/s21_fill_node_list.c \
    $(C_SRC)/list/s21_size_list.c \
    $(C_SRC)/list/s21_stack_to_list.c \
    $(C_SRC)/list/s21_put_x_value.c \
    $(C_SRC)/validation/s21_validation.c \
    $(C_SRC)/validation/s21_number_validation.c \
    $(C_SRC)/validation/s21_binary_operator_validation.c \
    $(C_SRC)/validation/s21_unary_operator_validation.c \
    $(C_SRC)/validation/s21_double_number_validation.c \
    $(C_SRC)/validation/s21_double_symbol_validation.c \
    $(C_SRC)/validation/s21_empty_brackets_validation.c \
    $(C_SRC)/validation/s21_glued_values_validation.c \
    $(C_SRC)/validation/s21_is_equality_brackets.c \
    $(C_SRC)/validation/s21_is_valid_string.c \
    $(C_SRC)/validation/s21_sin_sqrt_validation.c \
    $(C_SRC)/validation/s21_cos_validation.c \
    $(C_SRC)/validation/s21_tan_validation.c \
    $(C_SRC)/validation/s21_acos_asin_atan_validation.c \
    $(C_SRC)/validation/s21_ln_log_validation.c \
    $(C_SRC)/validation/s21_mod_validation.c \
    $(C_SRC)/additional/s21_char_to_int.c \
    $(C_SRC)/additional/s21_char_to_string.c \
    $(C_SRC)/additional/s21_string_to_int.c \
    $(C_SRC)/additional/s21_string_to_long_double.c \
    $(C_SRC)/additional/s21_get_priority_token.c \
    $(C_SRC)/additional/s21_is_unary_token.c \
    $(C_SRC)/additional/s21_get_value.c \
    $(C_SRC)/additional/s21_set_value.c \
    $(C_SRC)/additional/s21_count_points.c \
    $(C_SRC)/additional/s21_have_number.c \
    $(C_SRC)/additional/s21_have_point.c \
    $(C_SRC)/additional/s21_have_x.c \
    $(C_SRC)/additional/s21_is_int.c \
    $(C_SRC)/additional/s21_is_sign.c \
    $(C_SRC)/additional/s21_is_valid_symbol.c

.PHONY: all lib install install-dev install-app test run dist installer clean


all: lib

lib:
	@echo "Compiling C shared library..."
	$(PYTHON) scripts/build_lib.py
	@echo "Library built: $(LIB_FILE)"

install:
	pip install .

install-dev:
	pip install -e ".[dev]"

install-app:
	$(PYTHON) scripts/install.py

test:
	$(PYTHON) -m pytest

run:
	$(PYTHON) src/main.py

dist:
	$(PYTHON) -m PyInstaller smartcalc.spec --noconfirm

installer: dist
	@echo "Run 'iscc installer.iss' with Inno Setup to build the .exe installer."
	@echo "Download Inno Setup from: https://jrsoftware.org/isinfo.php"

clean:
	$(RM) $(LIB_FILE)
	find src -name "*.pyc" -delete 2>/dev/null || true
	find src -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true
	rm -rf build dist
