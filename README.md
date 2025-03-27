

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

[Download VSCode](https://code.visualstudio.com/)

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

# Installation von Arm Keil Studio Pack in VS Code

1. Starten Sie Visual Studio Code und öffnen Sie die Erweiterungsansicht durch Klicken auf das Erweiterungssymbol in der Aktivitätsleiste oder durch Drücken von `Strg+Shift+X`.

2. Suchen Sie im Suchfeld nach "Keil Studio Pack" und klicken Sie auf die Schaltfläche "Installieren", um alle Erweiterungen im Arm Keil Studio Pack zu installieren.

3. Visual Studio Code installiert nun die Erweiterungen. Nach Abschluss der Installation sind die Erweiterungen in der Aktivitätsleiste verfügbar.

4. Sie werden aufgefordert, eine MDK Community-Lizenz für die nicht-kommerzielle Nutzung zu aktivieren. Akzeptieren Sie diese Option, wenn Sie keine Lizenz haben und der nicht-kommerziellen Nutzung zustimmen. Wenn Sie eine kommerzielle Lizenz für Keil MDK installiert haben, lehnen Sie diese Option ab.

6. Es hat sich auch als sinnvoll erwiesen die `ibm-assembler` Erweiterung zu installieren. 

Das Arm Keil Studio Pack installiert die folgenden empfohlenen Erweiterungen für die Embedded- und IoT-Softwareentwicklung auf Arm-basierten Mikrocontroller-Geräten:

- Arm CMSIS Solution: Unterstützung für die Arbeit mit CMSIS-Lösungen (csolution-Projekte)
- Arm Device Manager: Verwalten von Geräteverbindungen für Arm Cortex-M-basierte Mikrocontroller, Entwicklungsboards und Debug-Probes
- Arm Embedded Debugger: Flashen und Debuggen auf Arm Cortex-M-Targets, die das Microsoft Debug Adapter Protocol (DAP) implementieren
- Arm Remote Build: Durchführen von Remote-Builds von Projekten für Arm Cortex-M-Targets
- Arm Virtual Hardware: Verwalten von Arm Virtual Hardware und Ausführen von Embedded-Anwendungen darauf

# Anleitung zum Auschecken eines GitHub-Projekts in VS Code

Folgen Sie diesen Schritten, um das GitHub-Projekt mit der URL  [https://github.com/...](https://github.com/Transport-Protocol/ITS-BRD-VSC) in Visual Studio Code auszuchecken:

1. Öffnen Sie Visual Studio Code.

2. Öffnen Sie die Befehlspalette, indem Sie `Strg+Shift+P` (Windows/Linux) oder `Cmd+Shift+P` (macOS) drücken.

3. Geben Sie "Git: Clone" in die Befehlspalette ein und wählen Sie den Befehl "Git: Clone" aus.

4. Geben Sie die URL des GitHub-Repositorys ein: [https://github.com/...](https://github.com/Transport-Protocol/ITS-BRD-VSC) oder wählen Sie aus GitHub clonen (bevorzugt) und wählen Sie ITS-BRD/ITS-BRD.

5. Wählen Sie einen Ordner auf Ihrem lokalen Computer aus, in den das Repository geklont werden soll.

6. VS Code klont nun das Repository in den ausgewählten Ordner und öffnet es anschließend.

7. Wenn Sie von GitHub dazu aufgefordert werden, authentifizieren Sie sich bei GitHub. VS Code verwendet die Git-Authentifizierung, die vom Betriebssystem bereitgestellt wird (z. B. macOS Keychain oder Windows Credential Manager).

8. Nach erfolgreicher Authentifizierung sollte das Repository erfolgreich in VS Code geklont und geöffnet sein.

9. Sie können nun mit dem Projekt arbeiten, Änderungen vornehmen, Commits erstellen und Branches verwalten - alles direkt in der VS Code-Benutzeroberfläche.

### Nur für die Integration 

10. Klicken Sie in der unteren linken Ecke des VS Code-Fensters auf den aktuellen Branch-Namen (standardmäßig `master`). Dadurch öffnet sich die Branch-Liste.

11. Suchen Sie in der Branch-Liste nach dem Branch `(aus der Vorlesung)`. Wenn der Branch nicht in der Liste angezeigt wird, klicken Sie auf "Alle Branches abrufen", um die aktuelle Liste der Remote-Branches abzurufen.

### Submodule initieren

12. Öffnen Sie das Terminal in VS Code durch Klicken auf "Terminal" > "Neues Terminal" in der Menüleiste oder durch Drücken von `Strg+Shift+ö` (Windows/Linux) oder `Cmd+Shift+ö` (macOS).

13. Um die Submodule zu initialisieren, führen Sie den folgenden Befehl im Terminal aus:
    
``` git submodule init ```     

Dieser Befehl initialisiert die Submodule und bereitet sie für die Verwendung vor.

14. Um die Submodule rekursiv zu aktualisieren und sicherzustellen, dass sie auf dem neuesten Stand sind, führen Sie den folgenden Befehl aus:
   
``` git submodule update --recursive ```     

Dieser Befehl lädt den Inhalt der Submodule herunter und aktualisiert sie auf den neuesten Stand. Die Option `--recursive` stellt sicher, dass auch verschachtelte Submodule aktualisiert werden.     
 
Bitte warten Sie bis die Befehle abgeschlossen sind.    

Wenn Sie in Zukunft die Submodule erneut aktualisieren möchten, führen Sie einfach den Befehl `git submodule update --recursive` im Terminal aus.   
# Anleitung zur Verwendung von vcpkg-configuration und Aktivierung der Umgebung

15. Das Projekt, beispielhaft "TestNewFont", ist in Visual Studio Code geöffnet     
16. Klicken Sie im Explorer-Fenster von Visual Studio Code mit der rechten Maustaste auf die vcpkg-configuration.json-Datei.     
17. Wählen Sie im Kontextmenü die Option "Activate Environment" aus.     
    Visual Studio Code aktiviert nun die vcpkg-Umgebung basierend auf Ihrer Konfiguration. Dies kann beim ersten Mal einige Zeit in Anspruch nehmen, da die erforderlichen Pakete heruntergeladen und installiert werden. Nachdem die Aktivierung abgeschlossen ist, können Sie Ihr Projekt wie gewohnt erstellen und ausführen. Die benötigten Abhängigkeiten sollten nun korrekt aufgelöst werden.

Sie werden aufgefordert, eine MDK Community-Lizenz für die nicht-kommerzielle Nutzung zu aktivieren. Akzeptieren Sie diese Option, wenn Sie keine Lizenz haben und der nicht-kommerziellen Nutzung zustimmen. Wenn Sie eine kommerzielle Lizenz für Keil MDK installiert haben, lehnen Sie diese Option ab.     

# Building

18. Klicken Sie in der Aktivitätsleiste von Visual Studio Code auf das CMSIS-Symbol (das CMSIS-Logo), um die CMSIS-Ansicht zu öffnen.    
19. Visual Studio Code aktiviert nun die ausgewählte CMSIS-Solution. Der Name der aktiven Solution wird in der Statusleiste angezeigt.
20. Sie können nun durch Auswahl der Solution auch ein anderes Zielprojekt wählen, wenn vorhanden, wie beispielhaft TestNewFontAssembler

Das war's! Sie haben erfolgreich das GitHub-Projekt in Visual Studio Code ausgecheckt und können nun bequem daran arbeiten, ohne die Kommandozeile verwenden zu müssen.

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
