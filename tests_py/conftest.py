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
    resolved: dict[str, str] = {}
    missing = []

    for tool in ("llc", "clang"):
        path = shutil.which(tool)
        if path is None:
            missing.append(tool)
        else:
            resolved[tool] = path

    # Prefer a real GCC (for GNU extensions like nested functions) if available.
    gcc_candidates = ["gcc", "gcc-15", "gcc-14", "gcc-13", "gcc-12", "gcc-11"]
    for candidate in gcc_candidates:
        path = shutil.which(candidate)
        if not path:
            continue
        try:
            version = subprocess.run(
                [path, "--version"], capture_output=True, text=True, check=False
            ).stdout
            if "clang" in version and candidate == "gcc":
                continue
        except Exception:
            pass
        resolved["gcc"] = path
        break

    if "gcc" not in resolved:
        missing.append("gcc")

    if missing:
        pytest.skip(
            f"Skipping EduCC tests because the following tools are missing: {', '.join(missing)}"
        )
    return resolved


@pytest.fixture(scope="session")
def base_env() -> dict[str, str]:
    return os.environ.copy()


REGRESSION_CACHE_KEY = "educc/last_status"
_previous_status: dict[str, str] = {}
_current_status: dict[str, str] = {}


def pytest_configure(config: pytest.Config) -> None:
    global _previous_status, _current_status
    if getattr(config, "cache", None) is None:
        _previous_status = {}
        _current_status = {}
        return
    _previous_status = config.cache.get(REGRESSION_CACHE_KEY, {})
    _current_status = {}


def _status_from_report(report: pytest.TestReport) -> str:
    if report.failed:
        return "xfailed" if getattr(report, "wasxfail", False) else "failed"
    if report.passed:
        return "xpassed" if getattr(report, "wasxfail", False) else "passed"
    return "skipped"


def pytest_runtest_logreport(report: pytest.TestReport) -> None:
    if report.when not in ("setup", "call", "teardown"):
        return
    outcome = _status_from_report(report)
    if (
        report.when == "call"
        or report.nodeid not in _current_status
        or outcome == "failed"
    ):
        _current_status[report.nodeid] = outcome


def pytest_terminal_summary(
    terminalreporter: pytest.TerminalReporter, exitstatus: int
) -> None:
    regressions = [
        nodeid
        for nodeid, status in _current_status.items()
        if status == "failed" and _previous_status.get(nodeid) == "passed"
    ]
    if regressions:
        terminalreporter.write_sep("=", "New test regressions (previously passed)")
        for nodeid in regressions:
            terminalreporter.write_line(f"- {nodeid}")


def pytest_sessionfinish(session: pytest.Session, exitstatus: int) -> None:
    if getattr(session.config, "cache", None) is not None:
        session.config.cache.set(REGRESSION_CACHE_KEY, _current_status)
