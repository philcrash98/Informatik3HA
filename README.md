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
