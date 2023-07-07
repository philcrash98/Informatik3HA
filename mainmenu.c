#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

typedef struct {
    double temp;
    double airhum;
    double grdhum;
    double brightness;
    double alert;
} sensorData;

void mainMenu() // Funktion um das Hauptmenu in der Konsole auszuführen
{
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
	do
	{
		scanf("%c", &myChar);
		switch (myChar)
		{
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

int backToMenu()
{
	char myChar;
	int validInput;
	if (kbhit())
	{
		printf("Zurueck zum Hauptmenu?  y/n \n");
		fflush(stdin);
		do
		{
			scanf("%c", &myChar);
			switch (myChar)
			{
			case 'y':
				validInput = 1;
				return 1;
				readDataOutput();
				break;
			case 'n':
				validInput = 1;
				return 0;
				break;
			default:
				printf("Falsche Eingabe\n");
				validInput = 0;
				break;
			}
		} while (validInput == 0);
	}
}

int readDataOutput()
{
	char c;
	char sensorValues;

	system("@cls||clear");
	printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
	for (;;)
	{
		int value = backToMenu();
		if (value == 1)
		{
			/* return to Mainmenu */
			return 0;
		}
		else
		{
			sensorData data;
			// Hier sensordaten empfangen
			sensorValues = getSensorValues();
			/* Print Values */
			parseStringToStruct(sensorValues, &data, 1);

			// Ausgabe der gemessenen Werte
			printf("Temperature: %.2f\n", data.temp);
			printf("Air Humidity: %.2f\n", data.airhum);
			printf("Ground Humidity: %.2f\n", data.grdhum);
			printf("Brightness: %.2f\n", data.brightness);
			printf("Alert: %.2f\n", data.alert);
		}
	}
}

void importData()
{
	system("@cls||clear");
	printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
	for (;;)
	{
		int value = backToMenu();
		if (value == 1)
		{
			/* return to Mainmenu */
			return 0;
		}
		else
		{
			/* Print Values */
		}
	}
}

void exportData()
{
	char filename[128];
	system("@cls||clear");
	printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
	for (;;)
	{
		int value = backToMenu();
		if (value == 1)
		{
			/* return to Mainmenu */
			return 0;
		}
		else
		{
			/* Print Values */
			printf("Dateinamen waehlen!\n");
			fflush(stdin);
			scanf("%s", filename);
			strcat(filename, ".txt");

			/* 	FILE *fptr;
			fptr = fopen("filename.txt", "w"); */
		}
	}
}

void settings()
{
	system("@cls||clear");
	printf("\n---------------------------\n| Messstation Blumentopf! |\n---------------------------\n\n");
	for (;;)
	{
		int value = backToMenu();
		if (value == 1)
		{
			/* return to Mainmenu */
			return 0;
		}
		else
		{
			/* shwo Settings */
		}
	}
}

void dataConsoleOutput(temp, airhum, grdhum, occupacy, alert) // Funktion um Daten in Tabellarischer Form auszugeben
{

	printf("|  Temperatur   | Luftfeuchtigkeit | Bodenfeuchtigkeit |   Helligkeit  | Alarm |");
	printf("|%s|%s|%s|%s|%s|", &temp, &airhum, &grdhum, &occupacy, &alert);
}

void formatValues(double value, char *result) // Funktion um Double Daten in Formatierten String umzuwandeln
{

	snprintf(result, 21, "%f", value);
	int len = strlen(result);
	for (int i = len; i < 20; i++)
	{
		result[i] = ' ';
	}
	result[20] = '\0';
}

void parseStringToStruct(const char *input, sensorData *data, int maxCount)
{
	char *inputCopy = strdup(input);
	char *token = strtok(inputCopy, ";");

	int count = 0;
	while (token != NULL && count < maxCount)
	{
		switch (count)
		{
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

void getSensorValues(){

}

int main()
{
	
	for (;;)
	{
		mainMenu();
	}

	return 0;
}