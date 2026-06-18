.PHONY: install build run debug clean lint lint-strict

PYTHON = python3
VENV = .venv
PIP = $(VENV)/bin/pip
PYTHON_VENV = $(VENV)/bin/python
MAIN = a_maze_ing.py
CONFIG = config.txt

install:
	$(PYTHON) -m venv $(VENV)
	$(PIP) install -r requirements.txt

build: install
	.venv/bin/python -m pip install --upgrade build
	.venv/bin/python -m build

run: 
	$(PYTHON_VENV) $(MAIN) $(CONFIG)

debug: 
	$(PYTHON_VENV) -m pdb $(MAIN) $(CONFIG)

clean:
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type f -name "*.pyc" -delete
	find . -type f -name "*.pyo" -delete
	rm -rf .mypy_cache
	find . -type d -name "*.egg-info" -exec rm -rf {} +
	rm -rf dist/ build/ 


lint: 
	$(VENV)/bin/flake8 . --exclude=.venv
	$(VENV)/bin/mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict: 
	$(VENV)/bin/flake8 . --exclude=.venv
	$(VENV)/bin/mypy . --strict