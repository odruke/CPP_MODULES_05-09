#!/usr/bin/env python3
"""
Input parser test runner for the btc program.

This script keeps the existing databases/data.csv, generates one input file with
many malformed input lines, runs ./btc once, and validates that each expected
error appears in the output.
"""

from __future__ import annotations

import re
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import List


# This regex removes ANSI color escape sequences so output matching is robust.
ANSI_ESCAPE_RE = re.compile(r"\x1B\[[0-?]*[ -/]*[@-~]")


# This data class models one malformed input line and its expected error snippet.
@dataclass
class InputCase:
    label: str
    line: str
    expected_snippet: str


# This helper strips color codes and trims whitespace for stable matching.
def normalize_output(text: str) -> str:
    return ANSI_ESCAPE_RE.sub("", text).strip()


# This helper executes ./btc once and returns merged stdout/stderr output.
def run_btc(root_dir: Path, input_file: Path) -> str:
    # stderr is merged into stdout so we can read one single ordered stream.
    result = subprocess.run(
        ["./btc", str(input_file)],
        cwd=root_dir,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        check=False,
    )
    # Normalize output to make string comparisons cleaner.
    return normalize_output(result.stdout)


# This function returns malformed input lines that cover parser error branches.
def build_input_cases() -> List[InputCase]:
    # NOTE: The expected messages mirror the current C++ exception text format.
    return [
        InputCase(
            label="Missing spaces around separator",
            line="2011-01-03|1",
            expected_snippet="Error: bad input =>",
        ),
        InputCase(
            label="Invalid date separators",
            line="2011/01/03 | 1",
            expected_snippet="Error: bad input => 2011/01/03",
        ),
        InputCase(
            label="Date month out of range",
            line="2011-13-03 | 1",
            expected_snippet="Error: bad input => 2011-13-03",
        ),
        InputCase(
            label="Date day out of range",
            line="2011-04-31 | 1",
            expected_snippet="Error: bad input => 2011-04-31",
        ),
        InputCase(
            label="Date year below allowed range",
            line="2008-12-31 | 1",
            expected_snippet="Error: bad input => 2008-12-31",
        ),
        InputCase(
            label="Negative value",
            line="2011-01-03 | -1",
            expected_snippet="Error: not a positive number.",
        ),
        InputCase(
            label="Value above MAX_BTC_INPUT",
            line="2011-01-03 | 1001",
            expected_snippet="Error: too large a number.",
        ),
        InputCase(
            label="Value above MAX_FLOAT",
            line="2011-01-03 | 10017777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777",
            expected_snippet="Error: too large a number.",
        ),
        InputCase(
            label="Value very above MAX_FLOAT",
            line="2011-01-03 | 1003777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777",
            expected_snippet="Error: too large a number.",
        ),
        InputCase(
            label="date very above MAX_FLOAT",
            line="2011-01-033777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777 | 100",
            expected_snippet="Error: bad input => 2011-01-033777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777 | 100",
        ),
        InputCase(
            label="Value with invalid character",
            line="2011-01-03 | 1a",
            expected_snippet="Error: bad input => 1a",
        ),
        InputCase(
            label="Value with invalid character",
            line="2011-01-03 | 1-",
            expected_snippet="Error: bad input => 1-",
        ),
        InputCase(
            label="Value with invalid character",
            line="2011-01-03 | 1-1",
            expected_snippet="Error: bad input => 1-1",
        ),
        InputCase(
            label="Value with invalid character",
            line="2011-01-03 | --1",
            expected_snippet="Error: bad input => --1",
        ),
        InputCase(
            label="Value starts with dot",
            line="2011-01-03 | .5",
            expected_snippet="Error: bad input => .5",
        ),
        InputCase(
            label="Value ends with dot",
            line="2011-01-03 | 5.",
            expected_snippet="Error: bad input => 5.",
        ),
        InputCase(
            label="Value has multiple dots",
            line="2011-01-03 | 1.2.3",
            expected_snippet="Error: bad input => 1.2.3",
        ),
        InputCase(
            label="Raw malformed line",
            line="2001-42-42",
            expected_snippet="Error: bad input => 2001-42-42",
        ),
        InputCase(
            label="lap year",
            line="2012-02-29 | 1",
            expected_snippet="2012-02-29 => 1 = 4.98",
        ),
        InputCase(
            label="not lap year",
            line="2011-02-29 | 1",
            expected_snippet="Error: bad input => 2011-02-29",
        ),
        InputCase(
            label="Empty line",
            line="",
            expected_snippet="Error: bad input =>",
        ),
    ]


# This helper checks if expected snippets appear in order inside collected output lines.
def ordered_match(actual_lines: List[str], expected_snippets: List[str]) -> List[bool]:
    # Compare each expected snippet against the line at the same index.
    # This avoids cursor shifts where one broad snippet can consume a later line.
    results: List[bool] = []
    for index, snippet in enumerate(expected_snippets):
        if index >= len(actual_lines):
            results.append(False)
            continue
        results.append(snippet in actual_lines[index])
    return results


# This is the main orchestration function for one-run input parsing validation.
def main() -> int:
    # Resolve project root as the folder where this script is located.
    root_dir = Path(__file__).resolve().parent

    # Resolve required executable and temporary input path.
    btc_path = root_dir / "btc"
    input_path = root_dir / "input_parser_test.txt"

    # Fail with explicit guidance if the executable is not present.
    if not btc_path.exists():
        print("[FATAL] Missing executable: ./btc")
        print("[HINT ] Build first with: make")
        return 1

    # Build malformed input cases list and create final file lines.
    cases = build_input_cases()
    file_lines = ["date | value"] + [case.line for case in cases]

    # Write a single input file that contains all malformed lines.
    input_path.write_text("\n".join(file_lines) + "\n", encoding="utf-8")

    # Run btc exactly once with the generated malformed input file.
    output = run_btc(root_dir=root_dir, input_file=input_path)

    # Split output into non-empty lines preserving program output order.
    output_lines = [line.strip() for line in output.splitlines() if line.strip()]

    # Build expected snippets in the same order as malformed input lines.
    expected_snippets = [case.expected_snippet for case in cases]

    # Validate expected snippets in-order against full produced output.
    matches = ordered_match(actual_lines=output_lines, expected_snippets=expected_snippets)

    # Print per-case status so each malformed line is clearly marked.
    passed = 0
    total = len(cases)
    for index, (case, ok) in enumerate(zip(cases, matches), start=1):
        status = "OK" if ok else "WRONG"
        if ok:
            passed += 1
        print(f"[{index:02d}/{total:02d}] {status} - {case.label}")
        print(f"  input line: {case.line!r}")
        print(f"  expected : {case.expected_snippet}")

    # Print the captured program output for full transparency/debugging.
    print("\n========== RAW PROGRAM OUTPUT ==========")
    for line in output_lines or ["<empty output>"]:
        print(line)

    # Print final summary and return non-zero on failures.
    print("\n========== SUMMARY ==========")
    print(f"Passed: {passed}/{total}")
    print(f"Failed: {total - passed}/{total}")

    # Remove temporary generated input file before exiting.
    if input_path.exists():
        input_path.unlink()

    return 0 if passed == total else 2


# Entry point guard so the script can be imported without executing tests.
if __name__ == "__main__":
    raise SystemExit(main())
