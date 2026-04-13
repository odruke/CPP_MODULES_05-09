#!/usr/bin/env python3
"""Simple test runner for the 42 CPP09 ex01 RPN program.

Checks two rounds:
1) valid expressions: expected numeric result on stdout, empty stderr
2) invalid expressions: expected "Error" on stderr, empty stdout
"""

import os
import subprocess
import sys
from dataclasses import dataclass
from typing import List


class C:
    RESET = "\033[0m"
    BOLD = "\033[1m"
    CYAN = "\033[36m"
    GREEN = "\033[32m"
    RED = "\033[31m"
    YELLOW = "\033[33m"


@dataclass
class TestCase:
    name: str
    expr: str
    expected_stdout: str
    expected_stderr: str
    expect_code: int = 0


def run_case(executable: str, case: TestCase):
    proc = subprocess.run(
        [executable, case.expr],
        capture_output=True,
        text=True,
    )
    stdout = proc.stdout.strip()
    stderr = proc.stderr.strip()

    ok = (
        proc.returncode == case.expect_code
        and stdout == case.expected_stdout
        and stderr == case.expected_stderr
    )

    return ok, proc.returncode, stdout, stderr


def print_case_result(index: int, case: TestCase, ok: bool, code: int, stdout: str, stderr: str):
    status = f"{C.GREEN}PASS{C.RESET}" if ok else f"{C.RED}FAIL{C.RESET}"
    print(f"[{index:02d}] {case.name}")
    print(f"  expr     : {case.expr!r}")
    print(
        "  expected : "
        f"stdout={case.expected_stdout!r}, stderr={case.expected_stderr!r}, exit={case.expect_code}"
    )
    print(f"  received : stdout={stdout!r}, stderr={stderr!r}, exit={code}")
    print(f"  result   : {status}\n")


def run_round(title: str, cases: List[TestCase], executable: str, start_index: int):
    print(f"{C.BOLD}{C.CYAN}{title}{C.RESET}")
    passed = 0
    idx = start_index

    for case in cases:
        ok, code, stdout, stderr = run_case(executable, case)
        print_case_result(idx, case, ok, code, stdout, stderr)
        if ok:
            passed += 1
        idx += 1

    print(f"Round score: {passed}/{len(cases)}\n")
    return passed, len(cases), idx


def build_power_tokens(base: str, exponent: int) -> List[str]:
    if exponent < 1:
        raise ValueError("exponent must be >= 1")

    tokens = [base]
    for _ in range(exponent - 1):
        tokens.extend([base, "*"])
    return tokens


def build_expr(tokens: List[str]) -> str:
    return " ".join(tokens)


def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    executable = os.path.join(script_dir, "RPN")

    if len(sys.argv) > 1:
        executable = sys.argv[1]

    print(f"{C.BOLD}{C.YELLOW}WARNING:{C.RESET} compile your program without debug mode before running this test.")
    print("Expected error output in this test is exactly: 'Error' on stderr.\n")

    if not os.path.isfile(executable) or not os.access(executable, os.X_OK):
        print(f"{C.RED}Executable not found or not executable:{C.RESET} {executable}")
        return 1

    p9_20 = pow(9, 20)
    p9_18 = pow(9, 18)
    p9_10 = pow(9, 10)
    p9_9 = pow(9, 9)

    valid_cases = [
        TestCase("Subject sample 1", "8 9 * 9 - 9 - 9 - 4 - 1 +", "42", ""),
        TestCase("Subject sample 2", "7 7 * 7 -", "42", ""),
        TestCase("Subject sample 3", "1 2 * 2 / 2 * 2 4 - +", "0", ""),
        TestCase("Simple addition", "3 4 +", "7", ""),
        TestCase("Simple subtraction", "9 5 -", "4", ""),
        TestCase("Simple multiplication", "6 7 *", "42", ""),
        TestCase("Simple division", "8 2 /", "4", ""),
        TestCase("Negative result", "3 5 -", "-2", ""),
        TestCase("Two-step expression", "2 3 4 + *", "14", ""),
        TestCase("Long multiplication chain", "9 9 9 9 9 9 9 9 9 9 9 * * * * * * * * * *", "31381059609", ""),
        TestCase("Negative plus negative", "-1 -5 +", "-6", ""),
        TestCase("Positive plus negative", "2 -2 +", "0", ""),
        TestCase("Positive minus negative", "2 -2 -", "4", ""),
        TestCase("Negative times positive", "-9 3 *", "-27", ""),
        TestCase("Negative divided by positive", "-8 2 /", "-4", ""),
        TestCase("Negative divided by negative", "-8 -2 /", "4", ""),
        TestCase(
            "BigInt power 9^20",
            build_expr(build_power_tokens("9", 20)),
            str(p9_20),
            "",
        ),
        TestCase(
            "BigInt division 9^20 / 9^10",
            build_expr(build_power_tokens("9", 20) + build_power_tokens("9", 10) + ["/"]),
            str(p9_10),
            "",
        ),
        TestCase(
            "BigInt subtraction 9^20 - 9^18",
            build_expr(build_power_tokens("9", 20) + build_power_tokens("9", 18) + ["-"]),
            str(p9_20 - p9_18),
            "",
        ),
        TestCase(
            "BigInt addition 9^20 + 9^18",
            build_expr(build_power_tokens("9", 20) + build_power_tokens("9", 18) + ["+"]),
            str(p9_20 + p9_18),
            "",
        ),
        TestCase(
            "BigInt mixed signs -9^10 + 9^9",
            build_expr(build_power_tokens("-9", 10) + build_power_tokens("9", 9) + ["+"]),
            str(pow(-9, 10) + p9_9),
            "",
        ),
        TestCase(
            "BigInt negative result 9^18 - 9^20",
            build_expr(build_power_tokens("9", 18) + build_power_tokens("9", 20) + ["-"]),
            str(p9_18 - p9_20),
            "",
        ),
    ]

    invalid_cases = [
        TestCase("Subject sample invalid token", "(1 + 1)", "", "Error"),
        TestCase("Operator only", "+", "", "Error"),
        TestCase("Not enough operands", "1 +", "", "Error"),
        TestCase("Too many operands", "1 2", "", "Error"),
        TestCase("Double spaces", "1  2 +", "", "Error"),
        TestCase("Leading space", " 1 2 +", "", "Error"),
        TestCase("Trailing space", "1 2 + ", "", "Error"),
        TestCase("Invalid alpha token", "1 a +", "", "Error"),
        TestCase("Two-digit operand", "10 1 +", "", "Error"),
        TestCase("Division by zero", "4 0 /", "", "Error"),
        TestCase("Division by BigInt zero", "9 9 * 0 /", "", "Error"),
        TestCase("Invalid symbol", "9 9 ^", "", "Error"),
        TestCase("Consecutive operators", "2 3 + *", "", "Error"),
        TestCase("Expression starts with operator", "* 2 3", "", "Error"),
        TestCase("Unary plus token", "+1 2 +", "", "Error"),
        TestCase("Invalid negative token spacing", "- 1 2 +", "", "Error"),
        TestCase("Missing space before operator", "2 3+", "", "Error"),
        TestCase("Missing space after operator", "2 +3", "", "Error"),
    ]

    total_passed = 0
    total_tests = 0
    next_index = 1

    passed, count, next_index = run_round("ROUND 1: VALID EXPRESSIONS", valid_cases, executable, next_index)
    total_passed += passed
    total_tests += count

    passed, count, next_index = run_round("ROUND 2: INVALID EXPRESSIONS", invalid_cases, executable, next_index)
    total_passed += passed
    total_tests += count

    color = C.GREEN if total_passed == total_tests else C.RED
    print(f"{C.BOLD}FINAL SCORE:{C.RESET} {color}{total_passed}/{total_tests}{C.RESET}")

    return 0 if total_passed == total_tests else 1


if __name__ == "__main__":
    raise SystemExit(main())
