#!/usr/bin/py

import os
import sys
import re
import subprocess

BASE_DIR = os.path.dirname(os.path.realpath(__file__))
CPPLINT_CMD = "cpplint"

CPPLINT_OPTIONS = {
    "--linelength": "120",
    "--output": "vs7",
    "--root": "include",
    "--counting": "detailed"
}

ALLOWED_ERRORS_PER_LINE = 0.1

FILE_INCLUDE_REGEX = re.compile(
    r"""
    (
        ^.*\.hpp$   # All .hpp files
        |           # Or
        ^.*\.cpp$   # All .cpp files
    )
    """,
    re.VERBOSE
)

FILE_EXCLUDE_REGEX = re.compile(
    r"""
    (^.*/CMakeFiles/.*?$)   # xxx/CMakeFiles/xxx/...
    |                       # Or
    (^{}/test/.*?$)         # ./test/...
    """.format(BASE_DIR),
    re.VERBOSE
)

TOTAL_ERROR_COUNT_REGEX = re.compile(
    r"^Total errors found: ([0-9]+?)\s*?$", re.MULTILINE
)

def get_abspaths_to_files_under_path(base_path: str):
    return [os.path.join(BASE_DIR, os.path.join(root, file_name))
    for root, dirs, files in os.walk(BASE_DIR) for file_name in files ]

def filter_files_by_regex(file_list: list, regex: re.Pattern, reverse=False):
    def is_included(file_name):
        if not reverse:
            return regex.match(file_name) is not None
        else:
            return regex.match(file_name) is None

    return [file_name for file_name in file_list if is_included(file_name)]

def call_subprocess(exec_file: str, flags: dict, arguments: list):
    flag_list = [elem for key, value in flags.items() for elem in [key, value]]
    return subprocess.run([exec_file] + flag_list + arguments,
                          stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

def get_error_count_from_cpplint_output(output: str, regex: re.Pattern):
    return int(regex.search(output)[1])

def count_lines_in_files(file_list: list):
    tot_lines = 0
    for file_name in file_list:
        with open(file_name, "r") as f:
            tot_lines += len(f.read().split("\n"))
    return tot_lines


all_files = get_abspaths_to_files_under_path(BASE_DIR)

cpp_files = filter_files_by_regex(all_files, FILE_INCLUDE_REGEX)
cpp_files = filter_files_by_regex(cpp_files, FILE_EXCLUDE_REGEX, True)

result = call_subprocess(CPPLINT_CMD, CPPLINT_OPTIONS, cpp_files)

print(result.stdout.decode("utf-8"))

error_count = get_error_count_from_cpplint_output(result.stdout.decode("utf-8"),
                                                  TOTAL_ERROR_COUNT_REGEX)

total_line_count = count_lines_in_files(cpp_files)

allowed_errors = total_line_count*ALLOWED_ERRORS_PER_LINE

if allowed_errors < error_count:
    print(
        "Too many errors found.\n"
        "\tTotal errors: {},\n"
        "\tallowed errors: {},\n"
        "\tallowed errors per line: {}\n"
        .format(error_count, allowed_errors, ALLOWED_ERRORS_PER_LINE), file=sys.stderr)

    exit(error_count-allowed_errors)
else:
    print("Found {} errors which is lower than limit: {} ({} errors per line)"
          .format(error_count, allowed_errors, ALLOWED_ERRORS_PER_LINE))
    exit(0)