## Inhaltsverzeichnis
1. [Allgemein: lwIP-Projekt des RN ITS (HAW Hamburg)](#allgemein-lwip-projekt-des-rn-its-haw-hamburg)
2. [Anmerkungen](#anmerkungen)
3. [LiveCoding Video 03](#livecoding-video-02)

## Allgemein: lwIP-Projekt des RN ITS (HAW Hamburg)

Das lwIP (lightweight IP)-Projekt ist ein Open-Source-Stack zur Implementierung des TCP/IP-Protokolls, das speziell für eingebettete Systeme mit begrenztem Speicher und Ressourcen entwickelt wurde. Es ermöglicht die Netzwerkanbindung solcher Systeme, ohne dass die volle Komplexität und die Speicheranforderungen traditioneller TCP/IP-Stacks benötigt werden. lwIP unterstützt gängige Protokolle wie TCP, UDP, ICMP, DHCP und PPP und ist in C geschrieben, was es besonders anpassungsfähig macht. Durch seine modulare Struktur lässt es sich leicht in Systeme mit verschiedenen Hardware-Architekturen integrieren.

In einer Vorlesung kann lwIP auf mehreren Ebenen didaktisch genutzt werden. Einerseits bietet es eine hervorragende Möglichkeit, die Grundlagen der Internetprotokolle und Netzwerkkommunikation in einer praxisnahen Umgebung zu vermitteln. Studierende können die Funktionsweise des TCP/IP-Stacks verstehen, indem sie lwIP auf Mikrocontrollern oder Entwicklungskits wie STM32 Nucleo verwenden.


### Anmerkungen
1. Dies ist ein Beispiel Projekt das in eine Vorlesung vom Zeitumfang besprochen werden muss, daher wird für die Beschleunigung des Codings auf KI Support gesetzt und es ist nicht gänzlich vollständig. 
2. Die Live Coding Videos sind wirklich Live Coding Videos, sie sind nur dahingehend geschnitten um die Maximale Github Größe nicht zu überschreiten. 
3. Da wir mit Live-Coding-Videos arbeiten, wird die maximal zulässige Dateigröße bei GitHub (50 MB) häufig ausgeschöpft. Es kann daher gelegentlich zu Problemen mit dem `http.postBuffer` kommen. Sollte dies der Fall sein, kann der Puffer wie folgt vergrößert werden:

```bash
git config http.postBuffer 104857600
```

### LiveCoding Video 03

Das Ziel dieses Beispielprojektes ist es, eine Anwendung für das ITS BRD zu entwickeln, die es uns ermöglicht, Basisdaten über das Netzwerk-Interface zu erfassen und den Durchsatz zu messen. Dazu setzen wir auf eine Kombination aus Delay-Messungen (ping) und iPerf, einem leistungsfähigen Tool für große Datenübertragungen und Durchsatzanalyse. Diese Tools helfen uns, die Empfindlichkeit des Systems gegenüber verschiedenen Aufrufzyklen und die Auswirkungen auf die Gesamtperformance zu analysieren.

#### Implementierungsübersicht

1. **Aufbau eines neuen Tasks**  
   Im Rahmen der Entwicklung wird ein neuer Task namens `IPERF` in unserem bestehenden Projekt erstellt. Dieser Task soll eine optimale Durchsatzerfahrung bieten. Dafür greifen wir auf Codes aus der `lwip`-Bibliothek zurück.

2. **Integration der iPerf-Bibliothek**  
   Die `IPPerf`-Bibliothek von `lwip` stellt eine Basis für TCP-basierte Kommunikationsanwendungen dar und wird hier zur Leistungsbewertung des Netzwerks genutzt. Die Bibliothek bietet einfache Performance-Messungen, besonders für Bandbreitenmessungen in kleinen Services. Diese Grundlagen nutzen wir, um unsere erste Anwendung weiterzuentwickeln ohne besondere Protokollkenntnisse mitzubringen.

3. **Praktische Einbindung und Optimierung**  
   Die Header-Datei `lwip/apps/lwiperf.h` wird eingebunden, und wir setzen uns intensiv mit der Initialisierung asueinander. 

#### Fortschritt und Ergebnisse

Im Verlauf des Projekts haben wir einen neuen Branch für die iPerf-Integration erstellt und die Ressourcen optimiert, um eine saubere Entwicklungsumgebung zu gewährleisten. Erste Tests mit dem Standard-TCP-Server, der auf Port 5001 läuft, zeigen jedoch eine suboptimale Übertragungsgeschwindigkeit von 1,27 Mbit/s. Durch Anpassungen am Task-Management konnten wir die Performance verbessern und die Kommunikation zwischen Server und Client maximieren. Es ist wichtig hierfür ein Verständniss aufzubauen.

#### Wichtige Optimierungsschritte

- **Exklusive Ausführung des iPerf-Tasks**: Durch die Fokussierung auf die Kernfunktionalität ohne Ablenkungen oder Pausen wurde eine deutliche Steigerung der Leistung erreicht.
- **Callback-Integration**: Eine Callback-Funktion wird implementiert, um während der Tests direkt auf dem Board Rückmeldungen anzeigen zu können. Dies unterstützt die Visualisierung und Bewertung der Leistungsgrenzen des Systems.

#### Erweiterungen und GUI-Darstellung

Wir arbeiten weiter an der Darstellung statischer und dynamischer Informationen auf einem LCD-Bildschirm. Die statischen Werte werden einmalig eingetragen, während dynamische Werte kontinuierlich aktualisiert werden. Diese Vorgehensweise minimiert die Blockierung des Ablaufs, besonders bei langen iPerf-Tests. Die `LCD GUI.h`-Bibliothek spielt hierbei eine zentrale Rolle für die Benutzeroberfläche.

### Aufruf auf Client Seite

##### Installation von iPerf

Um die Netzwerkleistung mit iPerf messen zu können, muss iPerf auf dem System installiert werden. Die Installation erfolgt je nach Betriebssystem unterschiedlich.

**Hinweis:** Stellen Sie sicher, dass Sie `iperf` installieren und nicht `iperf3`, da `iperf` die Version 2 ist und in einigen Fällen kompatibler für Netzwerkumgebungen, insbesondere in Projekten, die ältere Netzwerkprotokolle verwenden.

###### Windows

1. Besuchen Sie die [offizielle iPerf2-Website](https://iperf.fr/iperf-download.php) und laden Sie das Windows-Binary herunter.
2. Entpacken Sie die ZIP-Datei und speichern Sie die Dateien an einem leicht zugänglichen Ort, z. B. `C:\iperf`.
3. Öffnen Sie die Eingabeaufforderung (CMD) und navigieren Sie in das Verzeichnis, in dem sich `iperf.exe` befindet, z. B.:
   ```cmd
   cd C:\iperf
   ```
4. Führen Sie iPerf aus, indem Sie den entsprechenden Befehl eingeben (siehe unten für die Nutzung).

###### macOS

1. Öffnen Sie das Terminal.
2. Installieren Sie iPerf über [Homebrew](https://brew.sh/), indem Sie folgenden Befehl ausführen:
   ```bash
   brew install iperf
   ```
3. Überprüfen Sie die Installation, indem Sie `iperf` aufrufen:
   ```bash
   iperf --version
   ```

###### Linux

1. Öffnen Sie ein Terminal.
2. Installieren Sie iPerf über den Paketmanager Ihrer Distribution.

   - **Debian/Ubuntu**:
     ```bash
     sudo apt update
     sudo apt install iperf
     ```
   - **Fedora**:
     ```bash
     sudo dnf install iperf
     ```
   - **Arch Linux**:
     ```bash
     sudo pacman -S iperf
     ```

3. Prüfen Sie die Installation, indem Sie `iperf` aufrufen:
   ```bash
   iperf --version
   ```

###### Nutzung von iPerf zur Netzwerkleistungsmessung

Nach der Installation können Sie iPerf verwenden, um die Netzwerkleistung zwischen zwei Geräten zu messen. In diesem Projekt verwenden wir iPerf im **Client-Modus** mit folgendem Befehl:

```bash
iperf -c 192.168.33.99 -t 300 -i 10
```

###### Erklärung der Befehlsoptionen:

- **`-c 192.168.33.99`**: Startet iPerf im Client-Modus und verbindet sich mit dem iPerf-Server unter der IP-Adresse `192.168.33.99`.
- **`-t 300`**: Legt die Testdauer auf 300 Sekunden (5 Minuten) fest.
- **`-i 10`**: Gibt alle 10 Sekunden eine Zwischenstatistik über die aktuelle Übertragungsrate aus.

**Hinweis:** Verwenden Sie iPerf auf dem Server mit dem `-s`-Parameter, um die Server-Seite zu starten. Der Client wird dann Verbindungen zu dieser Adresse initiieren.
