from __future__ import annotations

import pytest

from .cases import CompilerTestCase, FRONTEND_CASE_PARAMS
from .utils import CommandError, execute_case


@pytest.mark.parametrize("case", FRONTEND_CASE_PARAMS)
def test_frontend_behaviour(
    case: CompilerTestCase,
    compiler_binary,
    toolchain,
    tmp_path_factory,
    base_env,
) -> None:
    try:
        execute_case(case, compiler_binary, toolchain, tmp_path_factory, base_env)
    except CommandError as error:
        pytest.fail(str(error))


