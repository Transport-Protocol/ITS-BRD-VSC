

# Inhaltsverzeichnis
- [Anleitung zur Installation von ST-Link](#anleitung-zur-installation-von-st-Link)
- [Anleitung zur Installation von Visual Studio Code und MDK 6](#anleitung-zur-installation-von-visual-studio-code-und-mdk-6)
  - [Systemanforderungen](#systemanforderungen)
  - [Schritte zur Installation](#schritte-zur-installation)
  - [Windows](#windows)
  - [macOS](#macos)
  - [Linux](#linux)
   
- [Installation von Arm Keil Studio Pack in VS Code](#installation-von-arm-keil-studio-pack-in-vs-code)
- [Anleitung zum Auschecken eines GitHub-Projekts in VS Code](#anleitung-zum-auschecken-eines-github-projekts-in-vs-code)
    - [Nur für die Integration](#nur-für-die-integration)
    - [Submodule initieren](#submodule-initieren)
- [Anleitung zur Verwendung von vcpkg-configuration und Aktivierung der Umgebung](#anleitung-zur-verwendung-von-vcpkg-configuration-und-aktivierung-der-Umgebung)
- [Building](#building)
- [Keil µVision GUI](#keil-gui)


# Anleitung zur Installation von ST-Link

ST-Link ist notwendig zum Flashen und Debuggen von Mikrocontrollern, die von STMicroelectronics hergestellt werden. Diese Anleitung führt Sie durch die Installation von ST-Link auf verschiedenen Betriebssystemen.

## Windows

1. **Download:** Laden Sie die ST-Link Treiber und das ST-Link Utility von der offiziellen STMicroelectronics Website herunter: [https://www.st.com/en/development-tools/stsw-link009.html](https://www.st.com/en/development-tools/stsw-link009.html)
2. **Installation:**
   * Führen Sie die heruntergeladene `.exe` Datei aus, um die Treiber und das Utility zu installieren.
   * Folgen Sie den Anweisungen auf dem Bildschirm, um die Installation abzuschließen.
3. Stellen Sie eine vollständige Installation von git sicher.
## Linux

1. **Installation (über Paketmanager):**
   * **Debian/Ubuntu:**
     ```bash
     sudo apt update
     sudo apt install stlink-tools
     ```
   * **Fedora:**
     ```bash
     sudo dnf install stlink-tools
     ```
   * **Andere Distributionen:** Verwenden Sie den entsprechenden Paketmanager Ihrer Distribution.

2. **Manuelle Installation (falls erforderlich):**
   * Klonen Sie das ST-Link Repository von GitHub:
     ```bash
     git clone [https://github.com/stlink-org/stlink.git](https://github.com/stlink-org/stlink.git)
     ```
   * Navigieren Sie in das geklonte Verzeichnis und führen Sie die folgenden Befehle aus:
     ```bash
     cd stlink
     ./autogen.sh
     ./configure
     make
     sudo make install
     ```

## macOS

1. **Installation (mit Homebrew):**
   * Stellen Sie sicher, dass Homebrew installiert ist. Wenn nicht, folgen Sie den Anweisungen auf der Homebrew Website: [https://brew.sh/](https://brew.sh/)
   * Installieren Sie ST-Link mit dem folgenden Befehl:
     ```bash
     brew install stlink
     ```


# Anleitung zur Installation von Visual Studio Code und MDK 6

Visual Studio Code (VSCode) ist ein leistungsfähiger und kostenloser Code-Editor, der für verschiedene Programmiersprachen verwendet werden kann.

## Systemanforderungen
- **Windows:** Windows 7, 8, 10 oder 11 (64-bit)
- **macOS:** macOS 10.11 oder höher
- **Linux:** Ubuntu, Debian, Red Hat, Fedora, SUSE (64-bit)

## Schritte zur Installation

### 1. Visual Studio Code Webseite besuchen
Öffne deinen bevorzugten Webbrowser und gehe auf die offizielle Webseite von Visual Studio Code:

[Download VSCode](https://code.visualstudio.com/) oder öffne diese Seite https://code.visualstudio.com/

### 2. Passende Version herunterladen
Auf der Webseite wird automatisch die passende Version für dein Betriebssystem vorgeschlagen. Sollte dies nicht der Fall sein, wähle dein Betriebssystem manuell aus.

- **Windows Nutzer**: Klicke auf "Windows" und lade das Installationspaket (`.exe`).
- **macOS Nutzer**: Wähle die Option für macOS und lade das `.zip`-Archiv.
- **Linux Nutzer**: Wähle das passende Paket für deine Distribution, z.B. `.deb` für Debian-basierte Systeme oder `.rpm` für Red Hat-basierte Systeme.

## Windows

1. Laden Sie den Visual Studio Code Installer für Windows herunter.    
2. Führen Sie den heruntergeladenen Installer (VSCodeUserSetup-{version}.exe) aus. Dies dauert nur eine Minute.     
3. VS Code wird standardmäßig unter `C:\Users\{Benutzername}\AppData\Local\Programs\Microsoft VS Code` installiert.    

## macOS

1. Laden Sie Visual Studio Code für macOS herunter.    
2. Öffnen Sie die Download-Liste des Browsers und suchen Sie das heruntergeladene Archiv.    
3. Extrahieren Sie den Inhalt des Archivs. Verwenden Sie einen Doppelklick für einige Browser oder wählen Sie das "Lupensymbol" bei Safari.     
4. Ziehen Sie `Visual Studio Code.app` in den **Anwendungen**-Ordner, um es im macOS Launchpad verfügbar zu machen.    
5. Öffnen Sie VS Code aus dem **Anwendungen**-Ordner, indem Sie auf das Symbol doppelklicken.    

## Linux

### Debian- und Ubuntu-basierte Distributionen

1. Laden Sie das .deb-Paket (64-Bit) für Visual Studio Code herunter.    
2. Installieren Sie das Paket über das grafische Softwarecenter, falls verfügbar, oder über die Befehlszeile mit:     
   ```bash
   sudo apt install ./<datei>.deb
   ```

# Installation von Arm Keil Studio Pack in VS Code

1. Starten Sie Visual Studio Code und klicken auf der linken Seite auf Extentions oder drücken `Strg+Shift+X`.

2. Suchen Sie in dem Extentions-Suchfeld nach "Arm Keil Studio Pack" und klicken Sie auf die Schaltfläche "Installieren", um alle Erweiterungen im Arm Keil Studio Pack zu installieren.

3. Visual Studio Code installiert nun die Erweiterungen. Nach Abschluss der Installation ist auf der linken Seite (Aktivitätsleiste) die Schaltfläche CMSIS verfügbar. Mit Hilfe von CMSIS (Cortex Microcontroller Software Interface Standard) kann ein Programm im Embedded Bereich gehandelt werden. 

4. Sie werden aufgefordert, eine MDK Community-Lizenz für die nicht-kommerzielle Nutzung zu aktivieren. Akzeptieren Sie diese Option, wenn Sie keine Lizenz haben und der nicht-kommerziellen Nutzung zustimmen. Wenn Sie eine kommerzielle Lizenz für Keil MDK installiert haben, lehnen Sie diese Option ab. In der Fussleiste wird nun "Keil MDK Community (non-commercial free of charge)" stehen

5. Es hat sich auch als sinnvoll erwiesen die `ibm-assembler` Erweiterung zu installieren. 

Das Arm Keil Studio Pack installiert die folgenden empfohlenen Erweiterungen für die Embedded- und IoT-Softwareentwicklung auf Arm-basierten Mikrocontroller-Geräten:

- Arm  - Arm CMSIS Debugger
       - Arm CMSIS Solution: Unterstützung für die Arbeit mit CMSIS-Lösungen (csolution-Projekte)
       - Arm Debugger
       - Arm Device Manager: Verwalten von Geräteverbindungen für Arm Cortex-M-basierte Mikrocontroller, Entwicklungsboards und Debug-Probes
       - Arm Embedded Debugger: Flashen und Debuggen auf Arm Cortex-M-Targets, die das Microsoft Debug Adapter Protocol (DAP) implementieren
       - Arm Keil Studio Pack (MDK c6)
       - Arm Remote Build: Durchführen von Remote-Builds von Projekten für Arm Cortex-M-Targets
       - Arm Virtual Hardware: Verwalten von Arm Virtual Hardware und Ausführen von Embedded-Anwendungen darauf
       - Arm Tools Environment Manager
- clangd
- CDT - CDT GDB Debug Adapter Extension
      - Memory Inspector 
      - Peripheral Inspector

# Anleitung zur Installation des C-Pretty-Printer
Der Pretty-Printer basiert auf dem clang Pretty-Printer. Dieser wird über das Python Script bin/format_all.py gestartet. Das Skript formatiert alle *.c und *.h Dateien des aktuellen CMSIS Projekts.

## Installation der Python-Extension in VSCode
- Öffnen Sie die Ansicht der VSCode Extension über die Tastenkombination “Ctrl + Shift + X“. Für MAC Systeme ist die Tastenkombination “Cmd + Shift + X“.
- Suchen Sie die Erweiterung "Python" **(von Microsoft)** und installieren diese - falls noch nicht geschehen.
- Wählen Sie einen python3 Interpreter wie folgt aus: Über die Tastenkombination “Ctrl + Shift + P“ (bzw. “Cmd + Shift + P“ auf einem MAC Rechner) wird die Auswahl eines Befehls gestartet. Definieren Sie über den Befehl “Python: Select Interpreter“ einen python3 Interpreter.

## Installation der clang Pretty-Printers 
### MAC
Führen Sie in der Shell den Befehl 
<center>brew install clang-format</center>
aus.
### Linux
Führen Sie in der Shell den Befehl 
<center> sudo apt-get install clang-format </center>
aus.
### Windows
Führen Sie im Terminal den Befehl 
<center> choco install llvm </center> 
aus.

## Konfiguration des clang Pretty-Printers 
Die Datei “.clang-format“ im Wurzelverzeichnis des VSCode Projekts legt die Formatierung fest. Passen Sie diese bei Bedarf an Ihre Bedürfnisse an.

## Ausführung des Pretty-Printers
Sie können die Pretty-Printer auf drei Arten starten:
1. Führen Sie im Terminal den Befehl 
     <center> python3 \<Pfad zum VScode Projekt\>/bin/format_all.py \<Pfad zum aktuellen CMSIS Projekt\> </center>
   aus.
2. Ausführung der VSCode Task “C-Pretty-Printer“. Starten Sie über “Ctrl-Shift-P“ (bzw. “Cmd-Shift-P“ auf einem MAC System) die Ausführung eines Programms. Wählen Sie das Programm “Tasks: Run Task“ aus und starten es. Wählen Sie die Ausführung der Task „“C-Pretty-Printer“ aus.
3. Richten Sie ein Keybinding ein und hängen die Task “C-Pretty-Printer“ an die entsprechende Tastenkombination. Die Keybindings sind benutzerspezifisch und stehen somit in der benutzerspezifischen Datei keybindings.json. Auf einen MAC System liegt diese Datei keybindings.json im Verzeichnis /Users/<DeinBenutzername>/Library/Application Support/Code/User/.
   Keybindings werden wie folgt eingefügt. Starten Sie über “Ctrl-Shift-P“ (bzw. “Cmd-Shift-P“ auf einem MAC System) die Ausführung eines Programms. Wählen Sie „“Open Keyboard Shortcuts (JSON)“ aus. In die sich öffnende JSON Datei fügen Sie folgendes Keybinding ein:
   
   ```
   [
	    {   "key": "shift+alt+p",
	        "command": "workbench.action.tasks.runTask",
	        "args": "C-Pretty-Printer"
	    }
    ]
    ```
    Nun kann über “Shift+Alt+P“ der C-Pretty-Printer für das aktuelle CMSIS Projekt gestartet werden.
   
# Anleitung zum Auschecken eines GitHub-Projekts in VS Code

Folgen Sie diesen Schritten, um das GitHub-Projekt mit der URL "https://github.com/Transport-Protocol/ITS-BRD-VSC/ITS-BRD-VSC.git" in Visual Studio Code auszuchecken:

1. Öffnen Sie Visual Studio Code.

2. Öffnen Sie die Befehlspalette, indem Sie `Strg+Shift+P` (Windows/Linux) oder `Cmd+Shift+P` (macOS) drücken.

3. Geben Sie "Git: Clone" in die Befehlspalette ein und wählen Sie den Befehl "Git: Clone" aus. Wenn dort "Git: Clone" nicht erscheint, muss erst git installiert werden.

4. Geben Sie die URL des GitHub-Repositorys ein: `https://github.com/Transport-Protocol/ITS-BRD-VSC.git` ein.
(Wenn Sie die GitHub Erweiterung installiert haben, können Sie das Projekt auch  mit ITS-BRD/ITS-BRD clonen )

5. Wählen Sie einen Ordner auf Ihrem lokalen Computer aus, in den das Repository geklont werden soll. ( In diesem Ordner wird der Ordner ITS-BRD-VSC angelegt. Dort werden alle notwendigen Dateien hinein kopiert )

6. VS Code klont nun das Repository in den ausgewählten Ordner und öffnet es anschließend.

7. Wenn Sie von GitHub dazu aufgefordert werden, authentifizieren Sie sich bei GitHub. VS Code verwendet die Git-Authentifizierung, die vom Betriebssystem bereitgestellt wird (z. B. macOS Keychain oder Windows Credential Manager).

8. Nach erfolgreicher Authentifizierung sollte das Repository erfolgreich in VS Code geklont und geöffnet sein.

### Nur für die Integration (für das VS Praktikum)

1. Klicken Sie in der unteren linken Ecke des VS Code-Fensters auf den aktuellen Branch-Namen (standardmäßig `main`). Dadurch öffnet sich die Branch-Liste.
2. Suchen Sie in der Branch-Liste nach dem Branch `(aus der Vorlesung)`. Wenn der Branch nicht in der Liste angezeigt wird, klicken Sie auf "Alle Branches abrufen", um die aktuelle Liste der Remote-Branches abzurufen.

### Submodule initieren

1. Öffnen Sie das Terminal in VS Code durch Klicken auf "Terminal" > "Neues Terminal" in der Menüleiste oder durch Drücken von `Strg+Shift+ö` (Windows/Linux) oder `Cmd+Shift+ö` (macOS).

2. Um die Submodule zu initialisieren, führen Sie den folgenden Befehl im Terminal aus:
    
``` git submodule init ```     

Dieser Befehl initialisiert die Submodule und bereitet sie für die Verwendung vor.

3. Um die Submodule rekursiv zu aktualisieren und sicherzustellen, dass sie auf dem neuesten Stand sind, führen Sie den folgenden Befehl aus:
   
``` git submodule update --recursive ```     

Dieser Befehl lädt den Inhalt der Submodule herunter und aktualisiert sie auf den neuesten Stand. Die Option `--recursive` stellt sicher, dass auch verschachtelte Submodule aktualisiert werden.     
 
Bitte warten Sie bis die Befehle abgeschlossen sind.    

Wenn Sie in Zukunft die Submodule erneut aktualisieren möchten, führen Sie einfach den Befehl `git submodule update --recursive` im Terminal aus.   

# Ein Projekt wählen, builden und auf das Board übertragen

1. Um zu testen, ob alles richtig installiert ist, soll das Projekt "TestNewFont" genutzt werden. Dazu klicken Sie in der Aktivierungsleiste (linke Seite) auf das CMSIS Symbol. 
2. In dem sich öffnenden CMSIS Fenster wird oben, über die "..." -> "Select active Solution from Workspace" und dann `Programs/TestNewFonts/TestNewFonts` gewählt.
3. Anschließend über das gleiche Menue  "..." ->Refresh (reload packs, update RTE)
4. Klicken Sie nun auf das Explorer Symbol (oben links) 
5. Öffnen Sie das Kontextmenü (rechte Maustaste) von der Datei vcpkg-configuration.json. Wählen Sie zuerst "Update Tool registry" und anschließend "Reactivate Environment" (Das kaann eine gewisse Zeit dauern)

Sie werden aufgefordert, eine MDK Community-Lizenz für die nicht-kommerzielle Nutzung zu aktivieren. Akzeptieren Sie diese Option, wenn Sie keine Lizenz haben und der nicht-kommerziellen Nutzung zustimmen. Wenn Sie eine kommerzielle Lizenz für Keil MDK installiert haben, lehnen Sie diese Option ab.     

# Building

1. Klicken Sie auf das CMSIS-Symbol
2. Klicken Sie in dem CMSIS Menü auf den Hammer ("Build Solution") Das Projekt sollte nun ohne Fehler gebaut werden.
3. Klicken Sie in dem CMSIS Menü auf das Pfeil (Load & Run) um das Projekt auf das Board zu übertragen und dort laufen zu lassen, oder auf den Käfer (Load & Debug) , um das Projekt auf das Board zu übertragen und dort das Programm im Einzelschritt Modus laufen zu lassen. 

# Neues Projekt erstellen

1. Öffnen Sie das Terminal in VS Code durch Klicken auf "Terminal" > "Neues Terminal" in der Menüleiste oder durch Drücken von `Strg+Shift+ö` (Windows/Linux) oder `Cmd+Shift+ö` (macOS).
2. Gehen Sie mit Hilfe von cd (Change Direktorie) in den Ordner bin 
(ITS-BRD-VSC/bin)
3. Führen Sie den Befehl createNewProjectC.bat (Windows) / ./createNewProjectC.sh (macOS / Linux)  aus um ein neues c Projekt zu erzeugen. 
Führen Sie den Befehlt createNewProjectASM.bat (Windows) / ./createNewProjectASM.sh (macOS/Linux) aus, um ein neues Assembler Projekt zu erzeugen. 
Sie werden aufgefordert ein Projekt Name einzugeben. Der Name muss mit einem Großbuchstabe beginnen.
Nun wird ein neues Projekt erstellt.

4. Klicken Sie auf CMSIS 
5. In dem sich öffnenden CMSIS Fenster wird oben, über die "..." -> "Select active Solution from Workspace" und dann `Programs/<Name des Projekt>/<Name des Projekt>` gewählt.
6. Anschließend über das gleiche Menue  "..." ->Refresh (reload packs, update RTE)
7. Klicken Sie nun auf das Explorer Symbol (oben links) 
8. Öffnen Sie das Kontextmenü (rechte Maustaste) von der Datei vcpkg-configuration.json. Wählen Sie zuerst "Update Tool registry" und anschließend "Reactivate Environment" 
9. Nun weiter mit dem Menü Punkt Building (siehe Anleitung weiter oben)


# Neue C Module in vs Code integrieren

1. Klicken Sie nun auf das Explorer Symbol (oben links) 
2. Mit Hilfe der rechten Maustaste auf dem Ordner Src kann ein neues C-File erstellt wreden.
3. Mit Hilfe der rechten Maustaste auf dem Ordner Inc kann ein neues h-File erstellt wreden.
4. Öffnen Sie die Datei <Projekt Name>.cproject.yml
5. Ganz unten in der Datei, in der group Program/User/Src muss das neue File mit hilfe von - file: <file name> hinzu gefügt werden.



# Keil GUI

#### Preparation
Mit `winget` auf Windows die notwendigen Packete installieren. 
```
winget install --id=Ninja-build.Ninja  -e
winget install -e --id Kitware.CMake
```
Wenn die Keil µVision GUI  gestartet wird, ist häufig noch unter Debug der ULink2/ME Cortex Debugger (abhängig der Installation) eingestellt. 
Dieser wurde in diesem Setup auf den ST-Link Debugger umgestellt, wie in dem VSCode Setup. 
Note: Keil selbst möchte gerne Device Upgrades durchführen. 

Mehr: [https://developer.arm.com/documentation/101407/0541/User-Interface/Project-Menu-and-Commands](https://developer.arm.com/documentation/101407/0541/User-Interface/Project-Menu-and-Commands)

## Dokumentation (To be fixed)
- s. [Wiki ITS_BRD](https://git.haw-hamburg.de/tiboard_dev/its_brd/-/wikis/**Dokumentation-der-Software-des-ITS-Board**)


## Troubleshooting

### Probleme Submodule
Sollte es Probleme bei dem checkout der Submodule geben, oder Fehlermeldungen erscheinen, die auf die Submodule verweisen, sollte folgendes probiert werden. 

```
git submodule foreach --recursive git reset --hard
git submodule foreach --recursive git clean -fd
git submodule update --init --recursive --force
```
