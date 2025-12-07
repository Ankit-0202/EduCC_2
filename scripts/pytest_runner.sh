#!/usr/bin/env bash
set -euo pipefail

EXTRA_OPTS=()

PYTEST_BIN=${PYTEST_BIN:-pytest}
PYTEST_PATH=$(command -v "$PYTEST_BIN" || true)
if [[ -z "$PYTEST_PATH" ]]; then
  echo "[pytest-runner] pytest executable not found on PATH." >&2
  exit 127
fi

PYTHON_BIN=$(head -n 1 "$PYTEST_PATH" 2>/dev/null | sed 's/^#!//')
if [[ -z "$PYTHON_BIN" || ! -x "$PYTHON_BIN" ]]; then
  PYTHON_BIN=${PYTHON_BIN:-python3}
fi

if "$PYTHON_BIN" - <<'PY'
import importlib.util
import sys
sys.exit(0 if importlib.util.find_spec("xdist") else 1)
PY
then
  EXTRA_OPTS+=("-n" "auto")
else
  echo "[pytest-runner] pytest-xdist not installed; running tests serially." >&2
fi

exec "$PYTHON_BIN" -m pytest "${EXTRA_OPTS[@]}" "$@"
