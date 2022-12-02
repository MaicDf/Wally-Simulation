#include <stdio.h>
#include <windows.h>
#include "main.h"
#include <time.h>

typedef struct
{
	int posx;
	int posy;
	char state; // * indicar� obstaculo, ser� vacio
} MapPoint;

direction CurrentDirectionMovement = RIGHT; // comienza mirando al frente
//just for simulation

int myDelay = 100;
int startpointx = 10;
int startpointy = 5;
int anchoWally = 10;
int altoWally = 10;
void display_map();
void fillVoidLine(int line);
void robotPrint(int posxInit, int posyInit, direction dir);
void usReading(USdistances *Measurement);
void delay(int milli_seconds);
void robotCleanH(int posx, int posy);
float check_US_RIGHT();
float check_US_LEFT();
float check_US_UP();
float check_US_DOWN();

int rows = 50;
int columns = 50;
MapPoint FullMap[50][50];
COORD c = {0, 0};
int robotPosX = 15, robotPosy = 13;

void setxy(int x, int y)
{
	c.X = x;
	c.Y = y; // Set X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int mapping()
{
	int robotPosX = 15, robotPosy = 13;
	display_map();
	robotPrint(robotPosX, robotPosy, FRONT);
	return 0;
}

void display_map()
{

	int i, j;
	// Equivalencias array y pos    ->>FILA=Y, COLUMNA=X
	//[0][0] = (y,x) 10,5

	// render fila 0,columna j (top)
	setxy(startpointx, startpointy);
	for (j = 0; j < columns; j++)
	{
		FullMap[0][j].posx = startpointx;
		FullMap[0][j].posy = startpointy + j;
		FullMap[0][j].state = '*';
		printf("%c", FullMap[0][j].state);
	}

	// render fila 400,columna j (bottom)
	setxy(startpointx, startpointy + rows);
	for (j = 0; j <= columns; j++)
	{
		FullMap[rows - 1][j].posx = columns + startpointx;
		FullMap[rows - 1][j].posy = startpointy + j;
		FullMap[rows - 1][j].state = '*';
		printf("%c", FullMap[rows - 1][j].state);
	}

	// fill the rest, fila i, columna j

	for (i = 1; i < rows - 1; i++)
	{
		fillVoidLine(i);
	}

	printf("\n");
}
void fillVoidLine(int line)
{
	int j;
	// llenando los bordes
	setxy(startpointx, startpointy + line);
	FullMap[line][0].posx = startpointx;
	FullMap[line][0].posy = line;
	FullMap[line][0].state = '*';
	printf("%c", FullMap[line][0].state);

	setxy(columns + startpointx, startpointy + line);
	FullMap[line][columns - 1].posx = columns + startpointx;
	FullMap[line][columns - 1].posy = line;
	FullMap[line][columns - 1].state = '*';
	printf("%c", FullMap[line][columns - 1].state);

	for (j = 1; j < columns - 1; j++)
	{
		setxy(startpointx + j, startpointy + line);
		FullMap[line][j].posx = startpointx + j;
		FullMap[line][j].posy = line;
		FullMap[line][j].state = ' ';
		printf("%c", FullMap[line][j].state);
	}
}
void robotPrint(int posxInit, int posyInit, direction dir)
{
	if (dir == RIGHT)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 2);
		printf("|   Yo    %c|\n", 26);
		setxy(posxInit, posyInit + 3);
		printf("|   Soy   %c|\n", 26);
		setxy(posxInit, posyInit + 4);
		printf("|   Wally %c|\n", 26);
		setxy(posxInit, posyInit + 5);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 6);
		printf("|  Virtual%c|\n", 26);
		setxy(posxInit, posyInit + 7);
		printf("|    xD   %c|\n", 26);
		setxy(posxInit, posyInit + 8);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == LEFT)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 2);
		printf("|%c  Yo     |\n", 27);
		setxy(posxInit, posyInit + 3);
		printf("|%c  Soy    |\n", 27);
		setxy(posxInit, posyInit + 4);
		printf("|%c  Wally  |\n", 27);
		setxy(posxInit, posyInit + 5);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 6);
		printf("|%c Virtual |\n", 27);
		setxy(posxInit, posyInit + 7);
		printf("|%c   xD    |\n", 27);
		setxy(posxInit, posyInit + 8);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == FRONT)
	{
		setxy(posxInit, posyInit);
		printf("-%c%c%c%c%c%c%c%c%c-\n", 24, 24, 24, 24, 24, 24, 24, 24, 24);
		setxy(posxInit, posyInit + 1);
		printf("|          |\n");
		setxy(posxInit, posyInit + 2);
		printf("|   Yo     |\n");
		setxy(posxInit, posyInit + 3);
		printf("|   Soy    |\n");
		setxy(posxInit, posyInit + 4);
		printf("|   Wally  |\n");
		setxy(posxInit, posyInit + 5);
		printf("|          |\n");
		setxy(posxInit, posyInit + 6);
		printf("|  Virtual |\n");
		setxy(posxInit, posyInit + 7);
		printf("|    xD    |\n");
		setxy(posxInit, posyInit + 8);
		printf("|          |\n");
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == BACK)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 2);
		printf("|%c  Yo     |\n");
		setxy(posxInit, posyInit + 3);
		printf("|%c  Soy    |\n");
		setxy(posxInit, posyInit + 4);
		printf("|%c  Wally  |\n");
		setxy(posxInit, posyInit + 5);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 6);
		printf("|%c Virtual |\n");
		setxy(posxInit, posyInit + 7);
		printf("|%c   xD    |\n");
		setxy(posxInit, posyInit + 8);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 9);
		printf("-%c%c%c%c%c%c%c%c%c-\n", 25, 25, 25, 25, 25, 25, 25, 25, 25);
	}
}
void robotCleanH(int posxc, int posyc)
{
	setxy(posxc, posyc);
	printf(" ");
	setxy(posxc, posyc + 1);
	printf(" ");
	setxy(posxc, posyc + 2);
	printf(" ");
	setxy(posxc, posyc + 3);
	printf(" ");
	setxy(posxc, posyc + 4);
	printf(" ");
	setxy(posxc, posyc + 5);
	printf(" ");
	setxy(posxc, posyc + 6);
	printf(" ");
	setxy(posxc, posyc + 7);
	printf(" ");
	setxy(posxc, posyc + 8);
	printf(" ");
	setxy(posxc, posyc + 9);
	printf(" ");
}
void DebugPrint(char message[64], int valI, float valf)
{
	setxy(0, 0);
	printf("\n");
	printf(message);
	printf(" --valor entero: %i, valor flotante: %f \n", valI, valf);
}

void moveAheadSimulation()
{
	if (CurrentDirectionMovement == FRONT)
	{
		if (FullMap[robotPosy - startpointy - 1][robotPosX - startpointx].state == ' ') // Restricting upside
		{
			robotPrint(robotPosX, robotPosy--, FRONT);
			setxy(robotPosX, robotPosy + 10);
			printf("             ");
			delay(myDelay);
		}
	}
	else if (CurrentDirectionMovement == BACK)
	{
		if (FullMap[robotPosy - startpointy + altoWally][robotPosX - startpointx].state == ' ')
		{
			robotPrint(robotPosX, robotPosy++, BACK);
			setxy(robotPosX, robotPosy - 1);
			printf("             ");
			delay(myDelay);
		}
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx - 1].state == ' ')
		{ // as long as the next pos isnt filled (' '), allow movement.
			robotPrint(robotPosX--, robotPosy, LEFT);
			robotCleanH(robotPosX + 12, robotPosy);
			delay(myDelay);
		}
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx + 2 + anchoWally].state == ' ') // Restrict bat on right side wall
		{
			robotPrint(robotPosX++, robotPosy, RIGHT);
			robotCleanH(robotPosX - 1, robotPosy);
			delay(myDelay);
		}
	}
}
void turnFrontSimulation()
{
	if (CurrentDirectionMovement == FRONT)
	{
		CurrentDirectionMovement = FRONT;
	}
	else if (CurrentDirectionMovement == BACK)
	{
		CurrentDirectionMovement = BACK;
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		CurrentDirectionMovement = LEFT;
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		CurrentDirectionMovement = RIGHT;
	}
}
void turnBackSimulation()
{
	if (CurrentDirectionMovement == FRONT)
	{
		CurrentDirectionMovement = BACK;
	}
	else if (CurrentDirectionMovement == BACK)
	{
		CurrentDirectionMovement = FRONT;
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		CurrentDirectionMovement = LEFT;
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		CurrentDirectionMovement = RIGHT;
	}
}
void turnLeftSimulation()
{
	if (CurrentDirectionMovement == FRONT)
	{
		CurrentDirectionMovement = LEFT;
	}
	else if (CurrentDirectionMovement == BACK)
	{
		CurrentDirectionMovement = RIGHT;
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		CurrentDirectionMovement = BACK;
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		CurrentDirectionMovement = FRONT;
	}
}
void turnRightSimulation()
{
	if (CurrentDirectionMovement == FRONT)
	{
		CurrentDirectionMovement = RIGHT;
	}
	else if (CurrentDirectionMovement == BACK)
	{
		CurrentDirectionMovement = LEFT;
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		CurrentDirectionMovement = FRONT;
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		CurrentDirectionMovement = BACK;
	}
}

void usReading(USdistances *Measurement)
{
	if (CurrentDirectionMovement == FRONT)
	{
		Measurement->USfront = check_US_UP();
		Measurement->USback = check_US_DOWN();
		Measurement->USleft = check_US_LEFT();
		Measurement->USright = check_US_RIGHT();
	}
	else if (CurrentDirectionMovement == BACK)
	{
		Measurement->USfront = check_US_DOWN();
		Measurement->USback = check_US_UP();
		Measurement->USleft = check_US_RIGHT();
		Measurement->USright = check_US_LEFT();
	}
	else if (CurrentDirectionMovement == LEFT)
	{
		Measurement->USfront = check_US_LEFT();
		Measurement->USback = check_US_RIGHT();
		Measurement->USleft = check_US_DOWN();
		Measurement->USright = check_US_UP();
	}
	else if (CurrentDirectionMovement == RIGHT)
	{
		Measurement->USfront = check_US_RIGHT();
		Measurement->USback = check_US_LEFT();
		Measurement->USleft = check_US_UP();
		Measurement->USright = check_US_DOWN();
	}
}

float check_US_RIGHT(){
	return 1;
}
float check_US_LEFT(){
	return 1;
}
float check_US_UP(){
	return 1;
}
float check_US_DOWN(){
	return 1;
}

void delay(int milli_seconds)
{

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}
