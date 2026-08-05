"""
Einfacher Logger, der auf stdout und in dynamisch hinzufügbare 
Dateien schreibt. 

Der Logger wird über eine globale Variable instanziert, auch 
wenn eine explizite Übergabe oder ein Singleton schöner. Der 
Weg reicht für diese einfache Anwendung :).
"""
import os
import sys
import atexit
from typing import List, TextIO


class _Logger:
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

logger = _Logger()

