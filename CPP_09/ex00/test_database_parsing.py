#!/usr/bin/env python3
"""
Database parser test runner for the btc program.

This script intentionally writes malformed CSV content to databases/data.csv,
runs ./btc repeatedly with a simple input file, and checks whether the emitted
error text matches what is expected for each malformed case.
"""

from __future__ import annotations

import re
import subprocess
from dataclasses import dataclass
from pathlib import Path
from typing import List


# This regex removes ANSI color escape sequences so string matching is stable.
ANSI_ESCAPE_RE = re.compile(r"\x1B\[[0-?]*[ -/]*[@-~]")


# This data class defines one test case for database parsing.
@dataclass
class DbCase:
    name: str
    csv_lines: List[str]
    expected_snippets: List[str]


# This helper strips color codes and leading/trailing whitespace from output text.
def normalize_output(text: str) -> str:
    return ANSI_ESCAPE_RE.sub("", text).strip()


# This helper runs ./btc with a provided input file and returns merged stdout/stderr.
def run_btc(root_dir: Path, input_file: Path) -> str:
    # We merge stderr into stdout so we preserve message order in one stream.
    result = subprocess.run(
        ["./btc", str(input_file)],
        cwd=root_dir,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        check=False,
    )
    # We normalize text to simplify comparisons.
    return normalize_output(result.stdout)


# This helper checks whether all expected snippets are present in output.
def output_matches(output: str, expected_snippets: List[str]) -> bool:
    return all(snippet in output for snippet in expected_snippets)


# This function builds the list of malformed database cases we want to validate.
def build_db_cases() -> List[DbCase]:
    # NOTE: The messages below match the current exception messages in C++.
    return [
        DbCase(
            name="Wrong header line",
            csv_lines=[
                "date,rate",
                "2011-01-03,1.0",
            ],
            expected_snippets=[
                "Unkown DataBase header line",
                "DataBase line [1]",
            ],
        ),
        DbCase(
            name="Date too short",
            csv_lines=[
                "date,exchange_rate",
                "2011-01,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date too short",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-1,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date too long",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-011,1.0",
            ],
            expected_snippets=[
                "Wrong date size or database separator format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date extremely long",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-01112313123123123123123123131231312312312313123123123123123123123123131312312313212322222222222222222222222222222222222222222222222222222222222,1.0",
            ],
            expected_snippets=[
                "Wrong date size or database separator format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Bad date separators",
            csv_lines=[
                "date,exchange_rate",
                "2011/01/03,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="no separators",
            csv_lines=[
                "date,exchange_rate",
                "2011001003,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Too many date separators",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03-,1.0",
            ],
            expected_snippets=[
                "Wrong date size or database separator format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date has non-digit fields",
            csv_lines=[
                "date,exchange_rate",
                "2011-0A-03,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date year below allowed range",
            csv_lines=[
                "date,exchange_rate",
                "2008-12-31,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date month out of range",
            csv_lines=[
                "date,exchange_rate",
                "2011-13-03,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date day out of range",
            csv_lines=[
                "date,exchange_rate",
                "2011-04-31,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Date day out of range not lap year",
            csv_lines=[
                "date,exchange_rate",
                "2011-02-29,1.0",
            ],
            expected_snippets=[
                "Wrong date format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Missing comma separator",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03 1.0",
            ],
            expected_snippets=[
                "Wrong date size or database separator format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Value has invalid character",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03,12a",
            ],
            expected_snippets=[
                "Wrong database value format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Value has multiple dots",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03,1.2.3",
            ],
            expected_snippets=[
                "Wrong database value format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Value starts with dot",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03,.5",
            ],
            expected_snippets=[
                "Wrong database value format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Value ends with dot",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03,5.",
            ],
            expected_snippets=[
                "Wrong database value format",
                "DataBase line [2]",
            ],
        ),
        DbCase(
            name="Negative value",
            csv_lines=[
                "date,exchange_rate",
                "2011-01-03,-1",
            ],
            expected_snippets=[
                "Wrong database value format",
                "DataBase line [2]",
            ],
        ),
    ]


# This is the main orchestration function for the script.
def main() -> int:
    # Resolve project root as the folder where this script is located.
    root_dir = Path(__file__).resolve().parent

    # Resolve all files used by this script.
    btc_path = root_dir / "btc"
    db_path = root_dir / "databases" / "data.csv"
    input_path = root_dir / "input_db_test.txt"

    # Fail fast with a clear message if executable does not exist.
    if not btc_path.exists():
        print("[FATAL] Missing executable: ./btc")
        print("[HINT ] Build first with: make")
        return 1

    # Read and keep original database content so we can always restore it.
    original_db_content = db_path.read_text(encoding="utf-8")

    # Create a minimal valid input file because btc expects one argument file.
    input_path.write_text("date | value\n2011-01-03 | 1\n", encoding="utf-8")

    # Build all malformed database test cases.
    cases = build_db_cases()

    # Keep total and pass counters for summary reporting.
    passed = 0
    total = len(cases)

    # Always restore original DB and remove temp input file, even on failures.
    try:
        # Execute every malformed DB case as an independent program run.
        for index, case in enumerate(cases, start=1):
            # Write malformed DB content for this specific case.
            db_path.write_text("\n".join(case.csv_lines) + "\n", encoding="utf-8")

            # Run btc and capture merged output text.
            output = run_btc(root_dir=root_dir, input_file=input_path)

            # Validate output against expected snippets for this case.
            ok = output_matches(output, case.expected_snippets)
            if ok:
                passed += 1

            # Print one concise status line so you can scan the full run quickly.
            status = "OK" if ok else "WRONG"
            print(f"[{index:02d}/{total:02d}] {status} - {case.name}")

            # Print what was expected and what was actually produced.
            print("  expected snippets:")
            for snippet in case.expected_snippets:
                print(f"    - {snippet}")
            print("  program output:")
            for line in output.splitlines() or ["<empty output>"]:
                print(f"    {line}")

        # Print final summary after all independent runs are completed.
        print("\n========== SUMMARY ==========")
        print(f"Passed: {passed}/{total}")
        print(f"Failed: {total - passed}/{total}")

        # Return non-zero status if any case failed, so CI/shell can detect failures.
        return 0 if passed == total else 2
    finally:
        # Restore the original database file so this script is non-destructive.
        db_path.write_text(original_db_content, encoding="utf-8")

        # Remove the temporary input file if it still exists.
        if input_path.exists():
            input_path.unlink()


# Entry point guard so the script can be imported without auto-running.
if __name__ == "__main__":
    raise SystemExit(main())
