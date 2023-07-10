#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

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
    double grdhum;
} alerts;

char rawData[255];
alerts alertSettings;
int serial_port;
sensorData dataArray[1000];
int arraySize = 0;
int arrayMaxSize = 1000;
int dataIndex = 0;

//Prototypen definieren
void parseStringToStruct(const char *input, sensorData *data, int maxCount);

int backToMenu();

int getSensorData();

/**
 *
 * @param data
 */
void setAlert(sensorData senData) {

}

/**
 * Versucht die Sensordaten auszulesen
 * @return
 */
int getSensorData() {
    while (1) {
        ssize_t len = read(serial_port, &rawData, sizeof(rawData));  // Daten von der seriellen Schnittstelle lesen
        if (len > 0) {
            return 1;
        }
    }
}

// TODO: Ablauf statisch machen
int backToMenu() {
    char myChar = 'n';
    int validInput = 0;
    fflush(stdin);
    printf("Zurueck zum Hauptmenu?  y/n \n");
    fflush(stdin);
    do {
        scanf("%c", &myChar);
        if (myChar != 'y' && myChar != 'n') {
            printf("Falsche Eingabe\n");
            validInput = 0;
            break;
        }
        switch (myChar) {
            case 'y':
                validInput = 1;
                return 1;
            case 'n':
                validInput = 1;
                return 0;
        }
    } while (validInput == 0);
    return 0;
}

/**
 * Funktion für das Importieren von Daten
 */
int importData() {
    char filename[128];
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (;;) {
        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return 0;
        } else {
            /* Import Values */

            printf("Dateinamen waehlen!\n");
            fflush(stdin);
            scanf("%s", filename);

            FILE *fptr;
            fptr = fopen(filename, "r");

            char myString[100];
            int i = 0;
            while (fgets(myString, 100, fptr)) {
                parseStringToStruct(myString, &dataArray[i], 5);
                i++;
            }
            // Globalen Index setzten damit die importierten Daten vor den neuen geschoben werden.
            dataIndex = i;
            printf("%d", dataIndex);
            sleep(2);
            fclose(fptr);
            return i;
        }
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
                fprintf(fptr, "%f;%f;%f;%f;%f\n", dataArray[i].temp, dataArray[i].airhum, dataArray[i].grdhum, dataArray[i].brightness,
                        dataArray[i].alert);
            }
            fclose(fptr);
            printf("Datei erstellt!!\n");
            sleep(2);
            return 0;
        }
    }
}

/**
 * Funktion für die Einstellungen
 */
int settings() {
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (;;) {
        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return 0;
        } else {
            /* show Settings */
        }
    }
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
                break;
            case 4:
                data->brightness= atof(token);
                break;
            case 5:
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
           "Um die Messung abzubrechen, 'ESC' drücken.\n"
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
 *
 * @return
 */
void readDataOutput() {
    char key = 27;

    if (arraySize != 0) {
        for(int j = 0; j < arraySize; j++) {
            dataTableOutput();
        }
    }

    for (; arraySize < arrayMaxSize; arraySize++) {
        // Wenn sensordaten empfangen
        getSensorData();
        // Sensordaten als String in das Struct speichern
        parseStringToStruct(rawData, &dataArray[arraySize], 5);
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
            settings();
            break;
        case '5':
            return 0;
        default:
            return 1;
    }
    return 1;
}

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

    do {
        cont = mainMenu();
    } while (cont == 1);

    close(serial_port);
    return 0;
}
