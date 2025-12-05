from __future__ import annotations

import subprocess
from pathlib import Path
from typing import Iterable, Mapping, Sequence

import pytest

from .cases import CompilerTestCase


class CommandError(RuntimeError):
    """Raised when a subprocess exits with a non-zero status."""

    def __init__(
        self,
        cmd: Sequence[str],
        result: subprocess.CompletedProcess[str],
    ) -> None:
        self.cmd = cmd
        self.result = result
        message = (
            f"Command '{' '.join(cmd)}' exited with status {result.returncode}.\n"
            f"stdout:\n{result.stdout}\n"
            f"stderr:\n{result.stderr}"
        )
        super().__init__(message)


def _run_command(
    cmd: Sequence[str],
    *,
    cwd: Path | None = None,
    env: Mapping[str, str] | None = None,
) -> subprocess.CompletedProcess[str]:
    result = subprocess.run(
        cmd,
        cwd=cwd,
        env=env,
        text=True,
        capture_output=True,
        check=False,
    )
    if result.returncode != 0:
        raise CommandError(cmd, result)
    return result


def _run_program(
    executable: Path,
    *,
    args: Iterable[str] = (),
    cwd: Path | None = None,
    env: Mapping[str, str] | None = None,
) -> subprocess.CompletedProcess[str]:
    cmd = [str(executable), *list(args)]
    return subprocess.run(
        cmd,
        cwd=cwd,
        env=env,
        text=True,
        capture_output=True,
        check=False,
    )


def execute_case(
    case: CompilerTestCase,
    compiler_binary: Path,
    toolchain: Mapping[str, str],
    tmp_path_factory: pytest.TempPathFactory,
    base_env: Mapping[str, str],
) -> None:
    workdir = tmp_path_factory.mktemp(f"educc-{_slugify(case)}")
    env = dict(base_env)
    if case.env:
        env.update(case.env)

    if case.mode == "linker":
        _execute_linker_case(case, compiler_binary, toolchain, workdir, env)
    else:
        _execute_frontend_case(case, compiler_binary, toolchain, workdir, env)


def _execute_frontend_case(
    case: CompilerTestCase,
    compiler_binary: Path,
    toolchain: Mapping[str, str],
    workdir: Path,
    env: Mapping[str, str],
) -> None:
    ll_file = workdir / "program.ll"
    obj_file = workdir / "program.o"
    our_exe = workdir / "educc.out"
    gcc_exe = workdir / "gcc.out"

    compiler_cmd = [str(compiler_binary), str(case.path), str(ll_file)]
    compiler_cmd.extend(case.compiler_args)
    _run_command(compiler_cmd, cwd=workdir, env=env)

    _run_command(
        [toolchain["llc"], str(ll_file), "-filetype=obj", "-o", str(obj_file)],
        cwd=workdir,
        env=env,
    )
    _run_command(
        [toolchain["clang"], str(obj_file), "-o", str(our_exe)],
        cwd=workdir,
        env=env,
    )
    _run_command(
        [toolchain["gcc"], str(case.path), "-o", str(gcc_exe)],
        cwd=workdir,
        env=env,
    )

    our_result = _run_program(our_exe, args=case.runtime_args, cwd=workdir, env=env)
    gcc_result = _run_program(gcc_exe, args=case.runtime_args, cwd=workdir, env=env)
    _assert_behaviour(case, our_result, gcc_result)


def _execute_linker_case(
    case: CompilerTestCase,
    compiler_binary: Path,
    toolchain: Mapping[str, str],
    workdir: Path,
    env: Mapping[str, str],
) -> None:
    ir_file = workdir / "program.ll"
    our_exe = workdir / "educc.out"
    gcc_exe = workdir / "gcc.out"

    _run_command(
        [toolchain["clang"], "-S", "-emit-llvm", str(case.path), "-o", str(ir_file)],
        cwd=workdir,
        env=env,
    )

    compiler_cmd = [
        str(compiler_binary),
        "--link-from-ir",
        str(ir_file),
        "--exe",
        str(our_exe),
    ]
    compiler_cmd.extend(case.compiler_args)
    _run_command(compiler_cmd, cwd=workdir, env=env)

    _run_command(
        [toolchain["gcc"], str(case.path), "-o", str(gcc_exe)],
        cwd=workdir,
        env=env,
    )

    our_result = _run_program(our_exe, args=case.runtime_args, cwd=workdir, env=env)
    gcc_result = _run_program(gcc_exe, args=case.runtime_args, cwd=workdir, env=env)
    _assert_behaviour(case, our_result, gcc_result)


def _assert_behaviour(
    case: CompilerTestCase,
    ours: subprocess.CompletedProcess[str],
    gcc: subprocess.CompletedProcess[str],
) -> None:
    if ours.returncode != gcc.returncode:
        pytest.fail(
            _format_mismatch_message(
                case,
                "return code",
                ours.returncode,
                gcc.returncode,
                ours,
                gcc,
            )
        )

    if ours.stdout != gcc.stdout:
        pytest.fail(
            _format_mismatch_message(
                case,
                "stdout",
                ours.stdout,
                gcc.stdout,
                ours,
                gcc,
            )
        )


def _format_mismatch_message(
    case: CompilerTestCase,
    field: str,
    ours_value: object,
    gcc_value: object,
    ours: subprocess.CompletedProcess[str],
    gcc: subprocess.CompletedProcess[str],
) -> str:
    return (
        f"{field} mismatch for '{case.pytest_id}'.\n"
        f"EduCC: {ours_value!r}\n"
        f"GCC:   {gcc_value!r}\n"
        f"EduCC stderr:\n{ours.stderr}\n"
        f"GCC stderr:\n{gcc.stderr}"
    )


def _slugify(case: CompilerTestCase) -> str:
    slug = case.pytest_id.replace("/", "__").replace(".", "_")
    return slug


