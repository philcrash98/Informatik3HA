#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <curses.h>

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
sensorData data[1000];

//Prototypen definieren
void parseStringToStruct(const char* input, sensorData* data, int maxCount);


// Quelle: https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

/**
 *
 * @param data
 */
void setAlert(sensorData data) {

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
    if (kbhit()) {
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
                    break;
                case 'n':
                    validInput = 1;
                    return 0;
                    break;
            }
        } while (validInput == 0);
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
    for (;;) {
        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return 0 ;
        } else {
            /* Import Values */

            printf("Dateinamen waehlen!\n");
            fflush(stdin);
            scanf("%s", filename);

            FILE *fptr;
            fptr = fopen(filename, "r");
            
            char myString[100];
            int i = 0;
            while(fgets(myString, 100, fptr)) {
            parseStringToStruct(myString, &data[i], 5);
            i++;
            }

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

            for (size_t i = 0; i < 10; i++)
            {
                fprintf(fptr, "%f;%f;%f;%f;%f\n", data[i].temp, data[i].airhum, data[i].grdhum, data[i].brightness, data[i].alert);
                
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
void parseStringToStruct(const char* input, sensorData* data, int maxCount) {
    char* inputCopy = strdup(input);
    char* token = strtok(inputCopy, ";");

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
                break;
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
void formatValues(double value, char* result) {
    if (value == 0.0) {
        sprintf(result, "%19s", "0.00");
    } else {
        sprintf(result, "%19.2f", value);
    }
}

/**
 * Gibt eine Tabelle mit den Daten aus
 */
void dataTableOutput(sensorData dataArray[], int arraySize) {
    system("@cls||clear");
    printf(""
           "Um die Messung abzubrechen, 'ESC' drücken."
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
int readDataOutput() {
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (size_t i = 0; i < 1000; i++)
    {
        //Mock daten zum Testen
        //const char* input = "23.80;50.00;89.00;72.00;1";
        // Wenn sensordaten empfangen
        getSensorData();

        // Sensordaten als String in das Struct speichern
        parseStringToStruct(rawData, &data[i], 5);
        // Daten ausgeben
        dataTableOutput(data, 5);
        //setAlert(data);

        sleep(3);

        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return 0;
        }
    }
    
}

/**
 * Funktion um das Hauptmenu in der Konsole auszuführen
 */
void mainMenu() {
    char myChar;
    int validInput;
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    printf("\n\nHauptmenu\n");
    printf("1. Messung\n");
    printf("2. Messung importieren\n");
    printf("3. Messung exportieren\n");
    printf("4. Einstellungen\n");
    printf("5. Programm beenden\n\n");
    fflush(stdin);
    do {
        scanf("%c", &myChar);
        switch (myChar) {
            case '1':
                printf("Messung\n");
                validInput = 1;
                readDataOutput();
                break;
            case '2':
                printf("importieren\n");
                validInput = 1;
                importData();
                break;
            case '3':
                printf("exportieren\n");
                validInput = 1;
                exportData();
                break;
            case '4':
                printf("Einstellungen\n");
                validInput = 1;
                settings();
                break;
            case '5':
                validInput = 1;
                _Exit(0);
                break;
            default:
                printf("Falsche Eingabe\n");
                validInput = 0;
                break;
        }
    } while (validInput == 0);
}

int main() {
    // Serielle Schnittstelle öffnen
    serial_port = open("/dev/ttyACM0", O_RDWR);

    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Serielle Schnittstellenkonfiguration
    tty.c_cflag = B9600;  // Baudrate
    tty.c_cflag |= CS8;   // 8 Datenbits
    tty.c_cflag |= CLOCAL | CREAD;  // Lokale Verbindung, Empfang aktivieren

    tcsetattr(serial_port, TCSANOW, &tty);  // Konfiguration anwenden

    for (;;) {
        mainMenu();
    }

    close(serial_port);
    return 0;
}
