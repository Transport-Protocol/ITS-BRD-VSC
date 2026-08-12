# Tipps zur Entwicklung unter VSCode auf dem ITS-Board
## Beschreibung des Systems
- STM32F429 auf dem NUCLEO-F439ZI Board
- VSCode mit CMSIS
- STLink
- GDB Debugger
- GNU Arm Embedded Toolchain (arm-none-eabi-gcc, arm-none-eabi-gdb)
- PyOCD wird fürs Laden und Debugging verwendet. PyOCD ist ein Python-basiertes Open-Source-Tool für das Debugging und Flashen von ARM-Cortex-M-Mikrocontrollern (inkl. STM32). Es ersetzt in diesem Fall ST-Link GDB Server oder OpenOCD und kommuniziert direkt mit dem ST-Link-Adapter auf dem Nucleo-Board. Der Aufruf enthält eine yml Datei, die Infos wie Prozessor etc. enthält. 
- Eine Solution enthält alle Daten zur Entwicklung eines Programms für das ITS-Board.
- Bei der Auswahl einer Solution unter CMSIS werden die Dateien unter .vscode/ von CMSIS angepasst bzw. modifiziert. Insbesondere
	- beschreibt .vscode/launch.json die Schnittstelle zum Debugger.
	- beschreibt die Datei .vscode/tasks.json den Compilations- und Link Prozess.
	- wird die Datei .vscode/settions.json nur teilweise überschrieben.
## Aufbau der Entwicklungsumgebung
### Verwendete Komponenten
- VSCode als Editor
- CMSIS-Toolbox für den STM32 spezifischen Teil
- cbuild als zentrales Build Tool
- CMake als make System, das cbuild nutzt
- PyOCD als Schnittstelle zum STM32F4 für Load und Debugging
### Projektkonfiguration (YAML-Dateien)
- **`*.csolution.yml `**: Globale Einstellungen (Compiler, Build-Typen, Abhängigkeiten, device ...).
- **`*.cproject.yml`**: Projekt-spezifische Einstellungen mit Blick auf C
- Beim Erzeugen eines neuen Projekts werden diese Dateien aus den entsprechenden Skripten generiert.
### Build-Prozess (CMSIS-Toolbox + CMake)
- Auf Basis der Daten aus den Dateien csolution.yml und cproject.yml generiert cbuild alle anderen Dateien wie z.B.:
	- CMakeLists.txt im tmp/*.Debug+ITSboard/
	- *.cbuild-run.yml im out/ Ordner (für PyOCD).
	- Binärdateien (.elf, .bin, .hex) im out/ Ordner.
- Der Build Prozess wird über die Build Task in CMSIS View gestartet, die nur cbuild mit passenden Parametern aufruft. Dabei generiert cbuild automatisch eine CMakeLists.txt, um CMake als "Frontend" für VSCode. Die Datei wird aus den YAML-Dateien generiert (z. B. mit cbuild2cmake).
### Debugging/Flashing (PyOCD)
- Wird über PyOCD umgesetzt
- Die entsprechenden Aufrufe vom PyOCD, die an den Tasten von CMSIS gebunden sind, stehen in .vscode/launch.json und .vscode/tasks.json. Diese Dateien werden generiert.
### Einflussnahme auf den Build-Prozess
- Man stellt die relevanten Aspekte in den *.yml Dateien ein. Dabei können einige Einstellungen andere Einstellungen überschreiben. Zum Beispiel überschreibt die Einstellung des Optimierungslevels die entsprechenden Compiler Optionen.
	- In *. cproject.yml werden zum Beispiel Quelldateien eingetragen. Die Daten fließen in die erzeugten Dateien CMakeLists.txt und cbuild-run.yml ein.
	- In *.cproject.yml werden z.B. Infos zu einzubindenden Bibliotheken/Treiber eingestellt.
## Tipps und Tricks
### Board kann nicht geflashed werden - keine Verbindung
Eine Lösung, die oft funktioniert:
- Den ST-Link manuell startet 
              st-util -p 61234 -d
  Wird das device nicht erkannt, es es oftmals ein USB Problem der Art „schlechtes Kabel“, „zu wenig Strom“ oder Treiber veraltet.
- Wenn Kabel und Strom als Fehlerquellen ausgeschlossen sind, das ITS-Board im Board Loader starten. Dazu trennt man die USB Verbindung, hält den Reset Button für mindestens 5 Sekunden gedrückt während man das USB Kabel wieder in den PC steckt.
  Der Befehl
              st-util -p 61234 -d
  sollte nun liefern, dass das Board angeschlossen ist.
- Anschließend das Board erneut trennen, wieder verbinden und dann Flash erneut probieren.
- Wenn das alles nichts gebracht hat, den stlink Treiber neu installieren.
						  brew reinstall stlink
### Compiler Flags in der Ausgabe sehen
- Eigentlich übergibt man ein --verbose dem cbuild Aufruf. Dann wird aber nicht der Generierungsprozess der Dateien beachtet.
- Daher in der *.cproject.yml Datei unter setups:mics:C:- -v einfügen.
- In tmp/1/build.ninja findet man auch die Flags, die übergeben werden.
- Man kann sich auch tmp/1/compile_commands.json anschauen
### Verwendung von printf
- printf wird auf den USB-UART umgelenkt. Das Programm TestStdinoutUSART aus dem Repo ITS-BRD-VSC enthält ein einfaches Beispiel.
### ARM Debugger Befehle eingeben
1. Verfahren
	- Es werden erstmal die Ausgaben des Debugger angezeigt. Will man einen Befehl wie „set $format = ’d‘“ an den Debugger schicken, dann muss im GDB Terminal vor den Befehl ein „>“ setzen. Also „> set $format = ’d’“
2. Verfahren
- Es wird eine zweite Instanz des gdb gestartet und mit stlink verbunden. Das geht wie folgt:
	- Starte in einem Terminal den Debugger über arm-none-eabi-gdb xxx.axf
	- Verbindung zum Debug Server über target remote :3333
	- Lese zum Beispiel eine Speicherzelle über  print/x *(int*)0x20000000
	- Schreibe zum Beispiel einen Speicherzelle über set {int}0x20000000 = 0xFFFFFFFF
### Open Disassembler View
- Debugger starten.
- Über Shift-Command-P (Shift-Strg-P) wird die Befehls-Palette geöffnet und die “GDB: Open Disassembly View“ Anwendung manuell gestartet.
- Oftmals gibt es eine Fehlermeldung, dass ein Adresszugriff fehlerhaft ist. Das ist o.k., weil der Disassembly View die richtige Adresse noch nicht kennt. 
- Einen Schritt im Debugger machen. Jetzt kennt der Disassembly View die richtige Adresse und arbeitet wie erwartet.
### Darstellung des Memory Inhalts
1. Verfahren: Nur lesender Zugriff auf den Speicher
	- Dieses Verfahren hat eine gute übersichtliche Darstellung 
	- Starte den Debugger und gehe zum ersten Breakpoint
	- Über Shift-Command-P (Shift-Strg-P) wird die Befehls-Palette geöffnet und die “GDB: Open Memory Browser“ Anwendung gestartet.
	- Im Feld Location wird eine Adresse, eine Variable die eine Adresse speichert, ein Zeiger auf eine Variable oder &Assembler-Label einer Speicherstelle eingegeben. Über Go wird dann das Fenster aktualisiert (Das Drücken auf Go wird gerne mal vergessen :)).
	- Auf dem ITS-Board wird in der Regel Little-Endian Darstellung verwendet. In den ersten beiden Praktika von GTP beachten, dass man „Bytes Per Group“ auf 1 setzt, da Big und Little Endian noch nicht bekannt ist.
	- Little/Big Endian bezieht sich auf „Bytes per Group“ - die Gruppe wird als Little bzw. Big Endian Wert dargestellt.
2. Verfahren: Nur lesender Zugriff auf den Speicher
	- Das Verfahren hat keine so schöne Darstellung wie das erste Verfahren. Bei der Verwendung von Assembler Labeln wird nicht auf die Debug Informationen zugegriffen (werden vermutlich vom Assembler nicht erzeugt), so dass Adressen nicht korrekt dargestellt werden.
	- Start des Debuggers
	- Aktiviere über “...“ den Memory-Viewer
	- Gebe in den Memory Viewer eine Adresse, eine Variable die eine Adresse speichert, ein Zeiger auf eine Variable oder &Assembler-Label einer Speicherstelle ein.
	- Über Drücken des runden File Buttons wird ein Update der Darstellung gefordert - wird gerne mal vergessen. Die Enter Taste sorgt nicht für den Update.
3. Verfahren: Lesender **und schreibender** Zugriff auf den Speicher
	- Das Verfahren verwendet das Watch Fenster.
	- Zur Darstellung der Werte im Hex Format muss die Default Darstellung des Debuggers umgestellt werden. Das geht zum Beispiel im GDB Terminal mit der Eingabe “> set output-radix 16“.
	- Der entscheidende Vorteil von diesem Weg ist, dass man auf den Speicher schreiben kann.
	- Start des Debuggers
	- An einem Breakpoint wird die „gecarstete“ Adresse im Watch Bereich des Debuggers eingegeben, z.B.: *((uint8_t *)0x2000000c)@32
	- Es kann auch eine Variable oder ein Assembler Label verwendet werden, z.B.: *((uint8_t *)&VariableB)@32 
	- Man kann die einzelnen Feldelemente auswählen und neue Werte setzen, indem man in Kontext Menü “Set Value“ wählt. Hier sind dann auch Hex Werte erlaubt.
### In main.s kann man keinen Breakpoint setzen
- Ein typischer Fall ist, dass der Language Mode für main.s nicht auf arm-debugger.arm“ steht. Wenn man in Editor in der Datei main.s ist, kann man unten rechts in der Status Leiste den Language Mode entsprechend einstellen. 
- In aktuellen Repos sollte in .vscode/settings.json der Eintrag 
       "files.associations": {
          "*.s": "arm-debugger.arm"
       }
  stehen. Dann ist der Language Mode für alle *.s Dateien entsprechend gesetzt.
### VSCode-Benutzerdaten-Cache
- Wenn alles nicht zusammenpasst, dann einfach mal den Cache löschen - Tat aus Verzweiflung :). 
- VSCode schließen
- Cache löschen. Der Cache liegt an folgender Stelle:
  - macOS: ~/Library/Application Support/Code/Cache/
  - Windows: %APPDATA%\Code\Cache\
  - Linux: ~/.config/Code/Cache/
### Debugger hält nicht beim ersten Befehl einer Assembler Prozedur
- Der vom Compiler generierte Code zu einer Funktion hat einen Prolog und einen Epilog. Das ist der Code zur Verwaltung von Stackframes etc. Wenn man C-Level debugt, möchte man bei einen StepInto nach dem Prolog Code anhalten. Dafür fügt der Compiler entsprechende Informationen für den Debugger ein (gdwarf-2 oder gdwarf-4). 
  Der von uns verwendete Assembler armasm fügt diese Infos leider nicht ein. Man kann sie auch nicht über Assembler Direktiven (wie .loc und .file beim gas Assembler) einfügen. Also rät der Debugger bei einer Assembler Prozedur, wo der Prolog fertig ist. Das führt dazu, dass man in einer *.s Datei in der Regel keinen Breakpoint auf den ersten Befehl einer Assembler Prozedur setzen kann bzw. StepInto erst beim zweiten Befehl der Assembler  Prozedur hält.
  Es gibt drei Möglichkeiten, wie man trotzdem beim ersten Befehl einer Assembler Prozedur anhalten kann.
- Man fügt als ersten Befehl der Assembler Prozedur einen NOP Befehl ein. Der Debugger geht bei dem Befehl NOP davon aus, dass der Prolog fertig ist. Somit kann man auf den NOP Befehl einen Breakpoint setzen.
- Man setzt den Breakpoint im Disassembler View auf den ersten Befehl der Assembler Prozedur (typischer Weise der PUSH).
- Man setzt einen Breakpoint bei dem BL Befehl, der in die Assembler Prozedur springt. Über den Debugger Befehl stepi (Kurzform si) führt der Debugger genau eine Instruktion aus (daher das i wie Instruktion :)) - also den BL Befehl. Dann hält der Debugger am ersten Befehl der Assembler Prozedur an.
  Leider gibt es für den Befehl si keinen Button im Debugger View. Daher muss man in der Konsole des Debugger den Befehl „> si“ eingeben (Das „>“ ist wichtig, siehe Kommentar oben)
- Anmerkung: Man könnten auf lange Sicht den armasm durch den gas Assembler ersetzen. Dann kann man mit .loc und .file Assembler Direktiven für den Debugger einfügen.
### Probleme mit clang-tidy
- clangd unterstützt auch clang-tidy. Dazu wird eine entsprechende Bibliothek mit clang-tidy Funktionen angebunden. Lint-all.py verwendet eine eigenständige clang-tidy Version. Die Anzahl der Warnungen der clangd internen clang-tidy Version und der eigenständigen clang-tidy Version unterscheiden sich manchmal. 
- Manchmal ist es sinnvoll, dass der Language Server clangd neu gestartet wird und seinen Meldungen in Output Fenster unter clangd angeschaut werden. Ein Update des CMSIS Projekts ist oftmals nicht sinnvoll, da CMSIS die Datei settings.json überschreibt und dann auch Argumente, die zum Test bei Aufruf von clangd genutzt werden, überschriebt.
- clangd wird wie folgt neu gestartet: Shift-Cltl-P (bzw. Shift-Cmd-P auf MAC) und dann den Befehl „“clangd: Restart language server“ ausführen. Oftmals ist es hilfreich, wenn man vorab den Output von clangd löschen. Weiterhin ist es hilfreich wenn in settings.json das folgende eingefügt wird: "clangd.arguments": ["--clang-tidy","--log=verbose“] 
- 


