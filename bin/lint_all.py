"""
Lint all Src/.* and Inc/*.h files of current CMSIS project

Input parameter : path to *.csolution.yml file of current CMSIS project
"""
import json
import os
import sys
import yaml
import subprocess
import atexit
from typing import Optional
from typing import Optional, List, TextIO


class Logger:
    """ 
    Schreibt auf stdout und in dynamisch hinzugefügte Dateien.
    """

    def __init__(self):
        self.targets: List[TextIO] = [sys.stdout]
        atexit.register(self.close)  # Registriert close() für das Programmende

    def add_file(self, file_path: str) -> None:
        try:
            file = open(file_path, "w")
            self.targets.append(file)
        except IOError as e:
            print(f"Fehler beim Öffnen der Datei: {e}", file=sys.stderr)

    def log(self, message: str) -> None:
        # Ersetze literale \n durch echte Zeilenumbrüche
        message = message.replace("\\n", "\n")
        # Füge einen Zeilenumbruch hinzu, falls nicht vorhanden
        if not message.endswith("\n"):
            message += "\n"
        for target in self.targets:
            print(message, file=target, end="", flush=True)

    def close(self) -> None:
        for target in self.targets:
            if target != sys.stdout:
                try:
                    target.close()
                except Exception as e:
                    print(f"Fehler beim Schließen der Datei: {e}", file=sys.stderr)
        self.targets = [sys.stdout]

# Instanziere Logger als globale Variablen, auch wenn explizite 
# Übergabe oder ein Singleton schöner sind :). Reicht 
logger = Logger()
logger.log("Hallo, Welt!")


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

        proj_contexts = []

        # Durchsuche die Struktur nach "target-set" -> "set" -> "images"
        # Zuerst zwei dictionaries; exceptions erkennen Fehlerfall
        data = data.get("solution").get("target-types")
        for target_type in data:
            for target in target_type.get("target-set"):
                for image in target.get("images"):
                    proj_contexts.append(image.get("project-context"))
        assert len(proj_contexts) == 1 # nur ein project-context erwartet
        assert '.' in proj_contexts[0] # project-context endet mit Build Type
        # Extrahiere den Teilstring, der den Build Typ festlegt
        erg = proj_contexts[0].split(".")[-1]
        return erg
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
            logger.log(f"Linting {file_path}.")
            logger.log(os.getcwd())
            result = subprocess.run(
                ["clang-tidy", "-p", cmsis_comp_cmds_dir, file_path],
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                universal_newlines=True,
                check=True
            )
            logger.log(result.stdout)
            logger.log(result.stderr)
            logger.log("\n")
        except subprocess.CalledProcessError as e:
            exit_on_error(f"Failed to lint {file_path}: {e.stderr.decode('utf-8')}")

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
