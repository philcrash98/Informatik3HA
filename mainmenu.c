#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

struct sensorData
{
	double temp;
	double airhum;
	double grdhum;
	double brightness;
	double alert;
};

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
			strcat(filename,".txt");

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

int main()
{

	for (;;)
	{
		mainMenu();
	}

	return 0;
}