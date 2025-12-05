from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path

import pytest


@pytest.fixture(scope="session")
def project_root() -> Path:
    return Path(__file__).resolve().parents[1]


@pytest.fixture(scope="session")
def compiler_binary(project_root: Path) -> Path:
    build_cmd = ["make", "-C", str(project_root), "all"]
    result = subprocess.run(
        build_cmd,
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode != 0:
        pytest.fail(
            "Failed to build EduCC via make.\n"
            f"Command: {' '.join(build_cmd)}\n"
            f"stdout:\n{result.stdout}\n"
            f"stderr:\n{result.stderr}"
        )
    binary = project_root / "build" / "educc"
    if not binary.exists():
        pytest.fail(f"Expected compiler binary at '{binary}' but it was not created.")
    return binary


@pytest.fixture(scope="session")
def toolchain() -> dict[str, str]:
    required = ("llc", "clang", "gcc")
    resolved: dict[str, str] = {}
    missing = []
    for tool in required:
        path = shutil.which(tool)
        if path is None:
            missing.append(tool)
        else:
            resolved[tool] = path
    if missing:
        pytest.skip(
            f"Skipping EduCC tests because the following tools are missing: {', '.join(missing)}"
        )
    return resolved


@pytest.fixture(scope="session")
def base_env() -> dict[str, str]:
    return os.environ.copy()




