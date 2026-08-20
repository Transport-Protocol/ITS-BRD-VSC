"""
Lint all Src/.* and Inc/*.h files of current CMSIS project

Input parameter : path to *.csolution.yml file of current CMSIS project
"""
import json
import os
import sys
import yaml
import subprocess
from logger import logger
from typing import Optional, List, TextIO

def exit_on_error(s) -> None :
    txt = f"❌ Error: {s}"
    print(txt, file=sys.stderr, flush=True)
    logger.log(txt)
    logger.close()
    sys.exit(1)

def assert_is_dir(path: str) -> None:
    """
    Checks if the given path is a directory.
    If this check fails, the program stops with an error message
    Args:
        path (str): The path to check.
    """
    if not os.path.exists(path):
        exit_on_error(f"Path '{path}' does not exist.")
    if not os.path.isdir(path):
        exit_on_error(f"Path '{path}' is not a directory.")

def extract_target_build_type(file_path):
    """
    Liest aus der *.csolution.yml-Datei den Build Type aus 
    Args:
        file_path (str): Pfad zur *.csolution.yml-Datei.
    Returns:
        Der Build Type - in der Regel Release oder Debug
        Existiert kein eindeutiger Build Type, wird das Programm mit einer Fehlermeldung beendet
    """
    try:
        with open(file_path, 'r') as file:
            data = yaml.safe_load(file)

        # Bestimmung des default Build Type, was der erste Eintrag unter build-types ITSboard
        build_type = data.get("solution").get("build-types")[0].get("type")
   
        # Überschreibe ggf. default Build Type durch project-context Einstellung
        proj_context_list = []
        for target_type in data.get("solution").get("target-types"):
            if "target-set" in target_type:
                for target in target_type.get("target-set"):
                    if "images" in target:
                        for image in target.get("images"):
                            proj_context_list.append(image.get("project-context"))

        assert len(proj_context_list) <= 1 # nur ein project-context erwartet
        if len(proj_context_list) == 1:
            assert '.' in proj_context_list[0] # project-context endet mit Build Type
            # Extrahiere den Teilstring, der den Build Typ festlegt
            build_type = proj_context_list[0].split(".")[-1]

        return build_type

    except FileNotFoundError:
        exit_on_error(f"File '{file_path}' not found.")
    except yaml.YAMLError as e:
        exit_on_error(f"Parsing YAML-file {e} failed.")
    except Exception as e:
        exit_on_error(f"Unexpected format of file {file_path}: {e}")

def apply_clang_tidy(cmsis_comp_cmds_dir: str, dir: str, extension: str) -> None:
    """
    Applies clang-tidy to all files in directory dir with the given extension.
    """
    # Check if the directory exists and is a directory
    assert_is_dir(dir)

    # Find all files with the specified extension in the directory (recursively)
    matching_files = []
    for root, _, files in os.walk(dir):
        for file in files:
            if file.endswith(extension):
                matching_files.append(os.path.join(root, file))

    if not matching_files:
        exit_on_error(f"No files with extension '{extension}' found in '{dir}'.")

    # Apply clang-tidy to each file
    for file_path in matching_files:
        try:
            # logger.log(f"Linting {file_path}.")
            result = subprocess.run(
                ["clang-tidy", "-p", cmsis_comp_cmds_dir, file_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                universal_newlines=True,
                check=True
            )
            if len(result.stdout) != 0 and not result.stdout.isspace():
                logger.log(result.stdout)
                logger.log("\n")
            # logger.log(result.stderr)
        
        except subprocess.CalledProcessError as e:
            exit_on_error(f"Failed to lint {file_path}: {e.stderr.encode('utf-8')}")

if __name__ == "__main__":
    # Check first parameter
    if len(sys.argv) != 2:
        exit_on_error("Path to csolution.yml file of current CMSIS expected\n" +
                      "as first argument.");
    csolution_file = sys.argv[1]
    cmsis_proj_dir = os.path.dirname(csolution_file)
    assert_is_dir(cmsis_proj_dir)
    log_file = cmsis_proj_dir + "/clang_tidy_result.txt"
    logger.add_file(log_file)
    cmsis_proj_name = os.path.basename(cmsis_proj_dir)
    build_type = extract_target_build_type(csolution_file)
    cmsis_comp_cmds_dir = cmsis_proj_dir + "/out/" + cmsis_proj_name + "/ITSboard/" + build_type
    cmsis_comp_cmds = cmsis_comp_cmds_dir + "/compile_commands.json"
    if not os.path.exists(cmsis_comp_cmds):
        exit_on_error("Please build the CMSIS project before linting.")
   
    # Start linting
    apply_clang_tidy(cmsis_comp_cmds_dir, cmsis_proj_dir + "/Inc", ".h")
    apply_clang_tidy(cmsis_comp_cmds_dir, cmsis_proj_dir + "/Src", ".c")
    logger.log("Linting of CMSIS project " + cmsis_proj_dir + " done.")
    logger.close()

    


# EOF
