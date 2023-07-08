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
 *
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

void importData() {
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (;;) {
        int value = backToMenu();
        if (value == 1) {
            /* return to Mainmenu */
            return;
        } else {
            /* Import Values */
        }
    }
}

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

            /* 	FILE *fptr;
            fptr = fopen("filename.txt", "w"); */
        }
    }
}

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
 * Funktion um Double Daten in Formatierten String umzuwandeln
 * @param value
 * @param result
 */
void formatValues(double value, char *result) {
    snprintf(result, 21, "%f", value);
    int len = strlen(result);
    for (int i = len; i < 20; i++) {
        result[i] = ' ';
    }
    result[20] = '\0';
}

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
                break;
        }

        token = strtok(NULL, ";");
        count++;
    }

    free(inputCopy);
}

// TODO: Explizit neu messen
int readDataOutput() {
    system("@cls||clear");
    printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
    for (;;) {
        sensorData data;
        // Hier sensordaten empfangen
        getSensorData();
        /* Print Values */
        parseStringToStruct(rawData, &data, 4);
        setAlert(data);
        // Ausgabe der gemessenen Werte
        printf("Temperature: %.2f\n", data.temp);
        printf("Air Humidity: %.2f\n", data.airhum);
        printf("Ground Humidity: %.2f\n", data.grdhum);
        printf("Brightness: %.2f\n", data.brightness);
        printf("Alert: %.2f\n", data.alert);
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
