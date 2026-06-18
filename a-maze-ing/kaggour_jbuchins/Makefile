PKG_DIR = mazegen_pkg

.PHONY: install run debug clean lint lint-strict build

run:
	python3 a_maze_ing.py config.txt

install:
	python3 -m venv .venv
	.venv/bin/python -m pip install --upgrade pip
	.venv/bin/python -m pip install build
	.venv/bin/python -m pip install mazegen-1.0.0-py3-none-any.whl

build:
	cd $(PKG_DIR) && python -m build --wheel

debug:
	python3 -m pdb a_maze_ing.py config.txt

clean:
	rm -rf build dist *.egg-info
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type d -name ".mypy_cache" -exec rm -rf {} +
	find . -type d -name "dist" -exec rm -rf {} +
	find . -type f -name "maze.txt" -exec rm -rf {} +
lint:
	python -m flake8 .
	python -m mypy . \
	  --warn-return-any \
	  --warn-unused-ignores \
	  --ignore-missing-imports \
	  --disallow-untyped-defs \
	  --check-untyped-defs \
	  --explicit-package-bases
