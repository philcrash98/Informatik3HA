# Informatik3HA
Hausarbeit im Modul Informatik

## Aufgabenstellung.
Ziel der Arbeit ist es, die erlernte Programmiersprache C anzuwenden. Da es sich um eine sehr hardwarenahe Sprache handelt, soll dies mit einem praktischen Aufbau verknüpft werden. Die folgenden Anforderungen beziehen sich daher sowohl auf die Software wie auch auf die Hardware

## Anforderungen:
1. Für den Aufbau der Hardware sollen ein Raspberry Pi und verschiedene Sensoren/Aktoren verwendet werden.
2. Der Aufbau soll mindestens vier Sensoren und/oder Aktoren beinhalten.
3. Der Aufbau muss in einem Dokument beschrieben werden.
4. Der Hardwareaufbau soll mit einer Software gesteuert werden, die in der Programmiersprache C geschrieben ist.
5. Es müssen mindestens fünf unterschiedliche Methoden implementiert sein.
6. Die Software muss sowohl Schleifen wie auch Verzweigungen beinhalten.
7. Es muss mindestens ein eigener, strukturierter Datentyp verwendet werden.
8. Weiterhin muss ein Array verwendet werden.
9. Ergebnisse sollen permanent in einer Datei gespeichert werden.
10. Durch Eingaben über die Konsole sollen die Ergebnisse aus der Datei ausgelesen und ausgegeben werden können.
11. Pointer müssen sinnvoll integriert werden.
12. Der Programmcode muss den Qualitätskriterien entsprechen und dabei insbesondere sinnvoll kommentiert sein.

## Qualitätskriterien:

- Bezeichner sind aussagekräftig
- Bezeichner für Variablen beginnen mit kleinem Buchstaben. Mehrere Wörter als CamelCase zusammengesetzt.
- Bezeichner für Dateien beginnen mit großem Buchstaben. Mehrere Wörter als CamelCase zusammengesetzt.
- Bezeichner für Konstanten bestehen nur aus Großbuchstaben. Mehrere Wörter durch Unterstrich zusammengesetzt.
- Öffnende geschweifte Klammern nicht in einer neuen Zeile. Nach öffnender geschweifter Klammer Zeilenumbruch.
- Nach schließender geschweifter Klammer erfolgt ein Zeilenumbruch. Ausnahme: Schlüsselwort else steht in gleicher Zeile.
- Vor logischen Abschnitten innerhalb einer Methode steht ein Kommentar als Überschrift
- Jede Blockebene um eine Tabulatorstufe horizontal eingerückt
- Zwischen Methoden steht eine Leerzeile.
- Nicht mehr als eine Leerzeile hintereinander
- Reihenfolge innerhalb einer Datei:
  1. Kommentarkopf
  2. Einbinden von Header-Dateien
  3. Definition von Datentypen (struct, typedef etc.) und Makros
  4. Deklaration von Funktionen
  5. [In Ausnahmefällen Definition von globalen Variablen]
  6. Hauptprogramm main(), wenn vorhanden
  7. Definition (Implementierung) der Funktionen


## Pinbelegung GPIO
````{verbatim}
+-----+-----+---------+------+---+---Pi 4B--+---+------+---------+-----+-----+
| BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
+-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
|     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
|   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5v      |     |     |
|   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
|   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | IN   | TxD     | 15  | 14  |
|     |     |      0v |      |   |  9 || 10 | 1 | IN   | RxD     | 16  | 15  |
|  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
|  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
|  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
|     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
|  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
|   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
|  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
|     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
|   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
|   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
|   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
|  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
|  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
|  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
|     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
+-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
| BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
+-----+-----+---------+------+---+---Pi 4B--+---+------+---------+-----+-----+
````