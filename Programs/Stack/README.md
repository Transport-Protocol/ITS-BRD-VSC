## Inhaltsverzeichnis
1. [Allgemein: lwIP-Projekt des RN ITS (HAW Hamburg)](#allgemein-lwip-projekt-des-rn-its-haw-hamburg)
2. [Anmerkungen](#anmerkungen)
3. [LiveCoding Video 02](#livecoding-video-02)

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

### LiveCoding Video 02

In dem aktuellen schritt vertiefen wir die Implementierung des Lightway IP Stacks auf dem Embedded Test System (ETS) Board und führen Sie durch eine praxisorientierte Live-Coding-Demonstration. Ziel ist es, Ihnen in Echtzeit Einblicke in die zentralen Funktionen und Konfigurationen des Lightway IP Stacks zu vermitteln. Diese Implementierung ermöglicht uns, eine leistungsfähige Netzwerklösung auf ressourcenbeschränkten Mikrocontrollern wie dem STM32 zu realisieren und dabei grundlegende Netzwerkprotokolle wie TCP, UDP, ICMP und DHCP zu integrieren.

Der Lightway IP Stack, den wir einsetzen, ist speziell darauf ausgelegt, mit einem minimalen Ressourcenaufwand auszukommen und dabei dennoch den wesentlichen Anforderungen eines TCP/IP-Netzwerks gerecht zu werden. Die modulare Architektur des Stacks ist hier von besonderem Vorteil, da sie uns Flexibilität bietet, Speicher- und Verarbeitungsparameter dynamisch anzupassen und auf spezifische Anforderungen einzugehen. Diese Struktur ermöglicht eine effiziente Aufteilung der Netzwerkfunktionen auf verschiedene Module und bietet Entwicklern damit eine hohe Kontrolle über Ressourcenmanagement und Funktionsumfang.

#### Lizenz und rechtliche Rahmenbedingungen

Ein weiteres wichtiges Thema ist die BSD-Lizenz, unter der der Lightway IP Stack bereitgestellt wird. Die BSD-Lizenz erlaubt eine flexible Nutzung und Anpassung des Codes, ohne dass für die Nutzung im Rahmen eines proprietären Produkts eine Offenlegung des Quellcodes erforderlich ist. Diese Lizenzierung ist besonders für kommerzielle Anwendungen auf Mikrocontroller-Basis von Interesse, da sie sowohl Anpassungen als auch die Integration in eigene Projekte ermöglicht.

##### Architektur und Konfigurationsdateien

Im praktischen Teil werden wir die Datei `lwipopts.h.h` näher betrachten, die eine Vielzahl der grundlegenden Konfigurationsparameter definiert und somit als Ausgangspunkt für die Netzwerkkonfiguration dient. Neben dieser Datei sind auch spezifische C-Dateien notwendig, die die Funktionalitäten des Netzwerkinterfaces abdecken und die Struktur des Stacks definieren. Die Parameter in diesen Konfigurationsdateien legen unter anderem fest, welche Protokolle (wie z. B. TCP und UDP) aktiv sind und wie die Speichermanagementpraxis gestaltet wird. Dies ist für eine Bare-Metal-Implementierung auf einem STM32-Mikrocontroller besonders relevant, da hier ohne Betriebssystem gearbeitet wird.

##### Netzwerkkonfiguration und Hardwareanbindung

Die Netzwerkkonfiguration konzentriert sich dabei insbesondere auf die Initialisierung und Anpassung der Ethernet-Schnittstelle des Boards. Da die Effizienz dieser Implementierung stark von einer präzisen Anpassung abhängt, sind Anpassungen der Interrupt-Routinen notwendig, um Verzögerungen zu minimieren und eine stabile Kommunikation sicherzustellen. Die Zuweisung von MAC-Adressen sowie die Handhabung der Paketdatenströme sind hierbei entscheidende Aspekte, da sie für die reibungslose Funktion der Netzwerkanfragen verantwortlich sind.

##### Live-Demonstration und praktische Anwendung

Während der Live-Coding-Phase wird die Implementierung des Stacks Stück für Stück erläutert und durch die Zuweisung und Konfiguration der Netzwerkparameter ergänzt. Hierbei führen wir Testmethoden ein, um die Netzwerkkommunikation zu verifizieren. Ein einfaches, aber sehr effektives Verfahren stellt der Ping-Test dar, der durch Senden von ICMP-Paketen die Reaktionszeiten des Boards prüft und somit eine schnelle Überprüfung der Netzwerkstabilität erlaubt.

Diese live umgesetzte Struktur vermittelt nicht nur ein praktisches Verständnis der Netzwerkprotokolle und deren Implementierung auf einem Mikrocontroller, sondern erlaubt auch, die typischen Herausforderungen und Optimierungsmöglichkeiten im Ressourcenmanagement eines STM32 in einem Netzwerkumfeld zu erfahren. Die Studierenden werden so befähigt, das Gelernte im eigenen Umfeld direkt anzuwenden und eine vertiefte Einsicht in die Problematik der Netzwerkimplementierung auf Embedded-Systemen zu entwickeln.