#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <wiringPi.h>

// Datentypen definieren
typedef struct {
    double temp;
    double airhum;
    double grdhum;
    double brightness;
    double alert;
} sensorData;

typedef struct {
    double tempMax;
    double tempMin;
    double grdHum;
} alerts;

//Prototypen definieren
int mainMenu();

int backToMenu();

int settingsMenu();

int saveSettings();

int loadSettings();

int changeSettings();

int importData();

int exportData();

int getSensorData();

int setAlert();

void dataTableOutput();

void readDataOutput();

void formatValues(double value, char *result);

void parseStringToStruct(const char *input, sensorData *data, int maxCount);

// Globale Variablen definieren
int LED_PIN = 2;
char settingsFile[128] = "settings.txt";
char serialRead[255];
int arraySize = 0;
int arrayMaxSize = 1000;
int dataIndex = 0;
int serial_port;
alerts alertSettings = {
        .tempMax = 50.00,
        .tempMin = 2.00,
        .grdHum = 20.00};
sensorData dataArray[1000];
sensorData lastRead;


// Main Funktion definieren
/**
 * Main Funktion
 * @return
 */
int main() {
    int cont;
    // Serielle Schnittstelle öffnen
    serial_port = open("/dev/ttyACM0", O_RDWR);

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Serielle Schnittstellenkonfiguration
    tty.c_cflag = B9600;  // Baudrate
    tty.c_cflag |= CS8;   // 8 Datenbits
    tty.c_cflag |= CLOCAL | CREAD;  // Lokale Verbindung, Empfang aktivieren

    tcsetattr(serial_port, TCSANOW, &tty);  // Konfiguration anwenden

    // Wiring Pi initialisieren
    if (wiringPiSetup() == -1)
        exit(1);

    wiringPiSetup();
    pinMode(LED_PIN, OUTPUT);

    // Einstellungen laden
    loadSettings();

    // Hauptmenu anzeigen
    do {
        cont = mainMenu();
    } while (cont == 1);

    close(serial_port);
    return 0;
}

// Funktionen definieren
/**
 *  Funktion die den LED Alarm bei bestimmten Schwellenwerten auslöst
 * @param data
 */
int setAlert() {
    // HIGH Gelb
    // LOW Rot
    if (
            lastRead.grdhum < alertSettings.grdHum ||
            lastRead.temp < alertSettings.tempMin ||
            lastRead.temp > alertSettings.tempMax) {
        digitalWrite(LED_PIN, LOW);
    } else {
        digitalWrite(LED_PIN, HIGH);
    }
    return 0;
}

/**
 * Versucht die Sensordaten auszulesen
 * @return
 */
int getSensorData() {
    // Daten von der seriellen Schnittstelle lesen
    while (1) {
        ssize_t len = read(serial_port, &serialRead, sizeof(serialRead));
        if (len > 0) {
            return 1;
        }
    }
}

/**
 * Abfrage ob ins Hauptmenu gewecheslt werden soll
 * Abfrage nach y oder n Eingabe 
 * @return
 */
int backToMenu() {
    char myChar;
    printf("Zurueck zum Hauptmenu?  y/n \n");
    fflush(stdin);
    scanf("%c", &myChar);
    if (myChar == 'y') {
        return 1;
    } else if (myChar == 'n') {
        return 0;
    } else {
        printf("Falsche Eingabe\n");
        backToMenu();
    }
    return 0;
}

/**
 * Funktion für das Importieren von Daten
 */
int importData() {
    char filename[128];
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");

    // Dateinamen vom User abfragen
    printf("Dateinamen waehlen!\n");
    fflush(stdin);
    scanf("%s", filename);
    // An den Dateinamen die .txt endung hinzufügen
    strcat(filename, ".txt");

    // File pointer definieren und datei öffnen
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (!fptr) {
        return 0;
    }
    // Variable für eine Zeile definieren
    char myString[100];
    int i = 0;
    // Datei Zeile für Zeile lesen und in das Struct laden
    while (fgets(myString, 100, fptr)) {
        parseStringToStruct(myString, &dataArray[i], 5);
        i++;
    }
    // Globalen Index setzten damit die importierten Daten vor den neuen geschoben werden.
    arraySize = i;
    printf("%d", dataIndex);
    sleep(2);
    fclose(fptr);
    return 0;

    int value = backToMenu();
    if (value == 1) {
        /* return to Mainmenu */
        return 0;
    }
}

/**
 * Funktion für das Exportieren von Daten
 */
int exportData() {
    char filename[128];
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (;;) {
        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return 0;
        } else {
            /* Export Values */
            printf("Dateinamen waehlen!\n");
            fflush(stdin);
            scanf("%s", filename);
            strcat(filename, ".txt");

            FILE *fptr;
            fptr = fopen(filename, "w");

            for (size_t i = 0; i < 10; i++) {
                fprintf(fptr, "%f;%f;%f;%f;%f\n", dataArray[i].temp, dataArray[i].airhum, dataArray[i].grdhum,
                        dataArray[i].brightness,
                        dataArray[i].alert);
            }
            fclose(fptr);
            printf("Datei erstellt!!\n");
            sleep(2);
            return 0;
        }
    }
}

int saveSettings() {
    FILE *fptr;
    fptr = fopen(settingsFile, "w");
    fprintf(fptr, "%f;%f;%f\n", alertSettings.tempMax, alertSettings.tempMin, alertSettings.grdHum);
    fclose(fptr);
    sleep(2);
    return 0;
}

int loadSettings() {
    // File pointer definieren und datei öffnen
    FILE *fptr;
    fptr = fopen(settingsFile, "r");
    if (!fptr) {
        return 0;
    }
    // Variable für eine Zeile definieren
    char myString[100];
    fgets(myString, 100, fptr);

    char *inputCopy = strdup(myString);
    char *token = strtok(inputCopy, ";");

    int count = 0;
    while (token != NULL && count < 3) {
        switch (count) {
            case 0:
                alertSettings.tempMax = atof(token);
                break;
            case 1:
                alertSettings.tempMin = atof(token);
                break;
            case 2:
                alertSettings.grdHum = atof(token);
                break;
        }
        token = strtok(NULL, ";");
        count++;
    }
    free(inputCopy);

    fclose(fptr);
    sleep(2);
    return 0;
}

/**
 * Funktion um die Schwellenwerte zu ändern
 */
int changeSettings() {
    char choiceKey;
    printf(""
           "Einstellungen ändern? y/n\n");
    fflush(stdin);
    scanf("%c", &choiceKey);
    if (choiceKey == 'y') {
        printf("Temperatur Obergrenze eingeben:\n");
        fflush(stdin);
        scanf("%lf", &alertSettings.tempMax);
        printf("Temperatur Untergrenze eingeben:\n");
        fflush(stdin);
        scanf("%lf", &alertSettings.tempMin);
        printf("Feuchtigkeitsgrenze eingeben:\n");
        fflush(stdin);
        scanf("%lf", &alertSettings.grdHum);
    } else if (choiceKey == 'n') {
        backToMenu();
    } else {
        printf("Falsche Eingabe.\n");
        settingsMenu();
    }
    saveSettings();
    return 0;
}

/**
 * Funktion für die Einstellungen
 */
int settingsMenu() {
    system("@cls||clear");
    printf(""
           "\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n"
           "Einstellungen:\n"
           "Temperatur Obergrenze:   %f\n"
           "Temperatur Untergrenze:  %f\n"
           "Grenze Bodenfeuchte:     %f\n",
           alertSettings.tempMax, alertSettings.tempMin, alertSettings.grdHum);
    fflush(stdin);
    changeSettings();
    fflush(stdin);
    fflush(stdout);
    return 0;
}

/**
 * Funktion um aus einem String Daten in ein Stuct umzuwandeln
 * @param input
 * @param data
 * @param maxCount
 */
void parseStringToStruct(const char *input, sensorData *data, int maxCount) {
    char *inputCopy = strdup(input);
    char *token = strtok(inputCopy, ";");

    int count = 0;
    while (token != NULL && count < maxCount) {
        switch (count) {
            case 0:
                data->temp = atof(token);
                break;
            case 1:
                data->airhum = atof(token);
                break;
            case 2:
                data->grdhum = atof(token);
                break;
            case 3:
                data->brightness = atof(token);
                break;
            case 4:
                data->alert = atof(token);
        }
        token = strtok(NULL, ";");
        count++;
    }
    free(inputCopy);
}

/**
 * Funktion um Double Daten in Formatierten String umzuwandeln
 * Der Wert wird mit Leerzeichen auf 20 Zeichen erweitert
 * @param value
 * @param result
 */
void formatValues(double value, char *result) {
    sprintf(result, "%19.2f", value);
}

/**
 * Gibt eine Tabelle mit den Daten aus
 */
void dataTableOutput() {
    system("@cls||clear");
    printf(""
           "Um die Messung abzubrechen, 'ESC' eingeben.\n"
           "|Temperatur         |Luftfeuchtigkeit   |Bodenfeuchtigkeit  |Helligkeit         |Alarm              |\n"
           "|-------------------|-------------------|-------------------|-------------------|-------------------|\n");

    for (int i = 0; i < arraySize; i++) {
        char ctemp[20], cairhum[20], cgrdhum[20], cbrightness[20], calert[20];
        formatValues(dataArray[i].temp, ctemp);
        formatValues(dataArray[i].airhum, cairhum);
        formatValues(dataArray[i].grdhum, cgrdhum);
        formatValues(dataArray[i].brightness, cbrightness);
        formatValues(dataArray[i].alert, calert);
        printf("|%s|%s|%s|%s|%s|\n", ctemp, cairhum, cgrdhum, cbrightness, calert);
    }
}

/**
 *  Funktion um die Daten in einer Tabelle anzuzeigen
 * Wenn Daten Importiert werden, werden diese vor den neuen Messungen geschoben
 * @return
 */
void readDataOutput() {
    char key = 27;
    // Wenn bereits werte Importiert wurden
    if (arraySize != 0) {
        // Gebe alle Importierten Werte aus
        for (int j = 0; j < arraySize; j++) {
            dataTableOutput();
        }
    }
    // Messwerte empfangen
    for (; arraySize < arrayMaxSize; arraySize++) {
        // Wenn sensordaten empfangen
        getSensorData();
        // Sensordaten als String in das Struct speichern
        parseStringToStruct(serialRead, &dataArray[arraySize], 4);
        // Daten ausgeben
        dataTableOutput();
        if (getchar() == key) {
            break;
        }
    }
}

/**
 * Funktion um das Hauptmenu in der Konsole auszuführen
 */
int mainMenu() {
    char myChar;
    system("@cls||clear");
    printf(""
           "\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n"
           "\n\nHauptmenu\n"
           "1. Messung\n"
           "2. Messung importieren\n"
           "3. Messung exportieren\n"
           "4. Einstellungen\n"
           "5. Programm beenden\n\n");
    fflush(stdin);
    scanf("%c", &myChar);
    switch (myChar) {
        case '1':
            readDataOutput();
            break;
        case '2':
            printf("importieren\n");
            importData();
            break;
        case '3':
            printf("exportieren\n");
            exportData();
            break;
        case '4':
            printf("Einstellungen\n");
            settingsMenu();
            break;
        case '5':
            return 0;
        default:
            return 1;
    }
    return 1;
}
