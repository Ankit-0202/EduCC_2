from __future__ import annotations

from dataclasses import dataclass, field, replace
from pathlib import Path
from typing import Mapping, Sequence

import pytest

PROJECT_ROOT = Path(__file__).resolve().parents[1]
C_TESTS_ROOT = PROJECT_ROOT / "tests"
LINKER_TEST_ROOT = C_TESTS_ROOT / "integration" / "linker"


@dataclass(frozen=True, slots=True)
class CompilerTestCase:
    """Description of a single compiler behaviour test."""

    rel_path: Path
    mode: str = "frontend"
    compiler_args: tuple[str, ...] = ()
    runtime_args: tuple[str, ...] = ()
    env: Mapping[str, str] | None = None
    id: str | None = None
    marks: Sequence[pytest.MarkDecorator] = field(default_factory=tuple)

    @property
    def path(self) -> Path:
        return C_TESTS_ROOT / self.rel_path

    @property
    def pytest_id(self) -> str:
        return self.id or self.rel_path.as_posix()

    def apply_overrides(self, overrides: Mapping[str, object]) -> CompilerTestCase:
        if not overrides:
            return self
        normalized = dict(overrides)
        if "marks" in normalized:
            normalized["marks"] = tuple(_normalize_marks(normalized["marks"]))
        return replace(self, **normalized)  # type: ignore[arg-type]


def _normalize_marks(
    marks: Sequence[pytest.MarkDecorator | str],
) -> Sequence[pytest.MarkDecorator]:
    normalized: list[pytest.MarkDecorator] = []
    for mark in marks:
        if isinstance(mark, str):
            normalized.append(getattr(pytest.mark, mark))
        else:
            normalized.append(mark)
    return tuple(normalized)


# Map of relative test paths (as POSIX strings) to override dictionaries.
TEST_OVERRIDES: dict[str, Mapping[str, object]] = {}


def _discover_cases() -> list[CompilerTestCase]:
    cases: list[CompilerTestCase] = []
    if not C_TESTS_ROOT.exists():
        return cases

    for path in sorted(C_TESTS_ROOT.rglob("*.c")):
        rel_path = path.relative_to(C_TESTS_ROOT)
        mode = "linker" if LINKER_TEST_ROOT in path.parents else "frontend"
        case = CompilerTestCase(rel_path=rel_path, mode=mode)
        overrides = TEST_OVERRIDES.get(rel_path.as_posix())
        if overrides:
            case = case.apply_overrides(overrides)
        cases.append(case)
    return cases


ALL_CASES = tuple(_discover_cases())
FRONTEND_CASE_PARAMS = tuple(
    pytest.param(case, id=case.pytest_id, marks=case.marks)
    for case in ALL_CASES
    if case.mode == "frontend"
)
LINKER_CASE_PARAMS = tuple(
    pytest.param(case, id=case.pytest_id, marks=case.marks)
    for case in ALL_CASES
    if case.mode == "linker"
)




