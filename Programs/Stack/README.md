## Inhaltsverzeichnis
1. [Allgemein: TCP Echo Server (ITS) (HAW Hamburg)](#allgemein-lwip-projekt-des-rn-its-haw-hamburg)
2. [Anmerkungen](#anmerkungen)


## Allgemein: TCP Echo Server (ITS) (HAW Hamburg)

Das Projekt erstellt einen einfachen TCP-Echo-Server auf dem ITS-Board, der eingehende Verbindungen akzeptiert und eine "Hello World"-Nachricht sendet. Empfangene Daten werden als Echo zurückgesendet und auf dem LCD-Display angezeigt. Es demonstriert grundlegende Netzwerkprogrammierung mit der LWIP-Bibliothek auf Mikrocontrollern.

### Anmerkungen
Wenn das Interface zum ITS Brd mit einer Adresse aus 192.169.33.0/24 konfiguiert ist (nicht 192.168.33.99), kann das Setup getestet werden mit:
```bash
nc 192.168.33.99 7
```

Die IP Adressen können natürlich auch angepasst werden. 
### Empfehlung: 

Zum besseren Verständis werden die Branche lwip, mqtt mit Livevideos angeraten. 

#### Lizenz und rechtliche Rahmenbedingungen

Ein weiteres wichtiges Thema ist die BSD-Lizenz, unter der der Lightway IP Stack bereitgestellt wird. Die BSD-Lizenz erlaubt eine flexible Nutzung und Anpassung des Codes, ohne dass für die Nutzung im Rahmen eines proprietären Produkts eine Offenlegung des Quellcodes erforderlich ist. Diese Lizenzierung ist besonders für kommerzielle Anwendungen auf Mikrocontroller-Basis von Interesse, da sie sowohl Anpassungen als auch die Integration in eigene Projekte ermöglicht.

##### Architektur und Konfigurationsdateien

Im praktischen Teil werden wir die Datei `lwipopts.h.h` näher betrachten, die eine Vielzahl der grundlegenden Konfigurationsparameter definiert und somit als Ausgangspunkt für die Netzwerkkonfiguration dient. Neben dieser Datei sind auch spezifische C-Dateien notwendig, die die Funktionalitäten des Netzwerkinterfaces abdecken und die Struktur des Stacks definieren. Die Parameter in diesen Konfigurationsdateien legen unter anderem fest, welche Protokolle (wie z. B. TCP und UDP) aktiv sind und wie die Speichermanagementpraxis gestaltet wird. Dies ist für eine Bare-Metal-Implementierung auf einem STM32-Mikrocontroller besonders relevant, da hier ohne Betriebssystem gearbeitet wird.

##### Netzwerkkonfiguration und Hardwareanbindung

Die Netzwerkkonfiguration konzentriert sich dabei insbesondere auf die Initialisierung und Anpassung der Ethernet-Schnittstelle des Boards. Da die Effizienz dieser Implementierung stark von einer präzisen Anpassung abhängt, sind Anpassungen der Interrupt-Routinen notwendig, um Verzögerungen zu minimieren und eine stabile Kommunikation sicherzustellen. Die Zuweisung von MAC-Adressen sowie die Handhabung der Paketdatenströme sind hierbei entscheidende Aspekte, da sie für die reibungslose Funktion der Netzwerkanfragen verantwortlich sind.
