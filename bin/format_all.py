"""
Format all Src/.* and Inc/*.h files of current CMSIS project

Input parameter : path to *.csolution.yml file of current CMSIS project
"""
import json
import os
import sys
import subprocess
from typing import Optional

def exit_on_error(s) -> None :
    print(f"❌ Error: {s}")
    sys.exit(1)

def assert_is_directory(path: str) -> None:
    """
    Checks if the given path is a directory.
    Raises a FileNotFoundError if the path does not exist.
    Raises a NotADirectoryError if the path is not a directory.
    Args:
        path (str): The path to check.
    """
    if not os.path.exists(path):
        exit_on_error(f"Path '{path}' does not exist.")
    if not os.path.isdir(path):
        exit_on_error(f"Path '{path}' is not a directory.")

def apply_clang_format_to_directory(directory: str, extension: str) -> None:
    """
    Applies clang-format to all files in the specified directory with the given extension.
    Args:
        directory (str): The directory to search for files.
        extension (str): The file extension to target (e.g., "cpp", "h", "c", "hpp").
    """
    # Check if the directory exists and is a directory
    assert_is_directory(directory)

    # Ensure the extension starts with a dot
    if not extension.startswith("."):
        extension = f".{extension}"

    # Find all files with the specified extension in the directory (recursively)
    matching_files = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(extension):
                matching_files.append(os.path.join(root, file))

    if not matching_files:
        exit_on_error(f"No files with extension '{extension}' found in '{directory}'.")
        return

    # Apply clang-format to each file
    for file_path in matching_files:
        try:
            # Modify the file in-place
            subprocess.run(
                ["clang-format", "-i", file_path],
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
            )
            print(f"{file_path} formatted.")
        except subprocess.CalledProcessError as e:
            exit_on_error(f"Failed to format {file_path}: {e.stderr.decode('utf-8')}")

if __name__ == "__main__":
    # Check first parameter
    if len(sys.argv) != 2:
        exit_on_error("Path to csolution.yml file of current CMSIS expected\n" +
                      "as first argument");

    csolution_file = sys.argv[1]
    cmsis_project_dir = os.path.dirname(csolution_file)
    assert_is_directory(cmsis_project_dir)

    # Start pretty printing
    apply_clang_format_to_directory(cmsis_project_dir + "/Inc", ".h")
    apply_clang_format_to_directory(cmsis_project_dir + "/Src", ".c")

    print("Pretty printing of CMSIS project " + cmsis_project_dir + "done.\n")
# EOF
