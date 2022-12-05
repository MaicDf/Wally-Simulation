#include <stdio.h>

#include <stdlib.h>

#include "movement.c"
#include "main.h"

// cambiar a uint8_t

// Incertidumbres
float incertidumbre_control = 1;
float incertidumbre_ajuste = 1;
float incertidumbre_medicion = 0.5;

// variables para mapeo y movimiento
int SafeDistance = 6; // distancia para que el robot pueda voltear comodamente (cm)
int stepGrid = 2;     // Separacion de cada punto en la grid

float currentPosx;
float currentposy;
int currentPointGridX = 3;
int currentPointGridY = 3;
// auxiliares
int NearestPlace1;

void init();
void Map_around();
void fillGrid();

// aqui va a estar el "cerebro"
int main()
{
    // Para el mapeo
    mapping();
    DebugPrint("All fine", 0, 0);
    // llena el mapa
    fillGrid();

    // 1.init: Distancias iniciales y acercarse a la pared más cercana
    init();
    /* 2.edgeSearching: Al acercarse a la pared más cercana, considera las distancias
    perpendiculares, y se va a la más cercana. En este momento se debe buscar estar
    paralelo a la pared, luego a cada movimiento hacia adelante se hará
    una corrección de distancia para siempre mantenerse al margen */
    edgeSearching();
    /* 3.initialMapping(), va llenar un arreglo de 200*200 .............................................................................. v
     */
    Map_around();
    printGrid(Grid, Wall_to_allign);
    return 0;
}

void init()
{
    getAll(&measurement1);
    NearestPlace1 = nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright);

    if (NearestPlace1 == FRONT)
    {
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == BACK)
    {
        turnBack();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == RIGHT)
    {
        turnRight();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));

            moveAhead();
        }
    }
    else if (NearestPlace1 == LEFT)
    {
        turnLeft();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else if (NearestPlace1 == EQUAL)
    { // significará que son iguales las distancias
        moveAhead();
        init();
    }
    else
    {
        /*NearestPLACE1 == NONVALID
        (todas las distancias son asignadas con 10k),
        que es el valor que se escogió para asignar un error en la medición, o una distancia muy grande .*/
        moveAhead();
        init();
    }
}

void edgeSearching()
{
    NearestPlace1 = nearest(10000, 10000, getDistanceLeft(&measurement1), getDistanceRight(&measurement1));
    if (NearestPlace1 == LEFT)
    {
        turnLeft();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            bool ctrlDistance = controlDistance(RIGHT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {
                moveAhead();
                ctrlDistance = controlDistance(RIGHT, SafeDistance, incertidumbre_control);
            }
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
        turnLeft();
        Wall_to_allign = RIGHT;
    }
    else if (NearestPlace1 == RIGHT)
    {
        turnRight();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            bool ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {
                ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            } // función para que siempre se mantenga paralelo a la pared.
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
        turnRight();
        Wall_to_allign = LEFT;
    }
    else if (NearestPlace1 == EQUAL)
    { // significará que son iguales las distancias
        turnRight();
        while (getDistanceFront(&measurement1) >= SafeDistance)
        {
            bool ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            while (!ctrlDistance)
            {
                ctrlDistance = controlDistance(LEFT, SafeDistance, incertidumbre_control);
            } // función para que siempre se mantenga paralelo a la pared.
            DebugPrint("FrontDistance:", 0, getDistanceFront(&measurement1));
            moveAhead();
        }
    }
    else
    { // NON valid
        turnRight();
        moveAhead();
        init();
    }
}

void Map_around()
{
    /*
    Para moverse alrededor:
    1. Verifica que está en la posición adecauda haciendo el control, primero horizontal y luego V
    2. Luego de estar en la posición adecuada, mapea el punto y sus alrededores.
    3. Gira si necesita girar
    4. se mueve hacia adelante 1 punto en la grilla,  y vuelve a repetir.
    */
    bool end_flag = false;
    while (!end_flag)
    {

        bool ctrlH_position = controlH_position(currentPointGridX, currentPointGridY, incertidumbre_ajuste);
        while (!ctrlH_position)
        {
            ctrlH_position = controlH_position(currentPointGridX, currentPointGridY, incertidumbre_ajuste);
        }
        bool ctrlV_position = controlV_position(currentPointGridX, currentPointGridY, incertidumbre_ajuste);
        while (!ctrlV_position)
        {
           ctrlV_position = controlV_position(currentPointGridX, currentPointGridY, incertidumbre_ajuste);
        }

       // Map_From_currentPoint(currentPointGridX, currentPointGridY, incertidumbre_medicion);
       // turnEvaluation(currentPointGridX, currentPointGridY); // si queda tiempo, es posible evaluar giros más complicados

        //moveAhead_grid(currentPointGridX, currentPointGridY);

        if (currentPointGridX == 1 && currentPointGridY == 1)
        {
            end_flag == true; // volvió al inicio.
        }
    }
}

direction nearest(float front_, float back_, float left_, float right_)
{
    if (front_ == 10000 && back_ == 10000 && left_ == 10000 && right_ == 10000)
    {
        return NONVALID;
    }
    else if (front_ < back_ && front_ < left_ && front_ < right_)
    {
        return FRONT;
    }
    else if (back_ < front_ && back_ < left_ && back_ < right_)
    {
        return BACK;
    }
    else if (left_ < front_ && left_ < right_ && left_ < back_)
    {
        return LEFT;
    }
    else if (right_ < left_ && right_ < front_ && right_ < back_)
    {
        return RIGHT;
    }
    else
    {
        return EQUAL;
    }
}

direction furthest(float front_, float back_, float left_, float right_)
{
    if (front_ > back_ && front_ > left_ && front_ > right_)
    {
        return FRONT;
    }
    else if (back_ > front_ && back_ > left_ && back_ > right_)
    {
        return BACK;
    }
    else if (left_ > front_ && left_ > right_ && left_ > back_)
    {
        return LEFT;
    }
    else if (right_ > left_ && right_ > front_ && right_ > back_)
    {
        return RIGHT;
    }
    else
    {
        return EQUAL; // si hay la misma distancia en dos lugares, ir adelante
    }
}

direction directionOpposite(direction myDir)
{

    if (myDir == LEFT)
        return RIGHT;
    else if (myDir == RIGHT)
        return LEFT;
    else if (myDir == FRONT)
        return BACK;
    else if (myDir == BACK)
        return FRONT;
}
void fillGrid()
{
    int x, y;
    for (x = 0; x < 100; x++)
    {
        for (y = 0; y < 100; y++)
        {
            Grid[x][y].AbsPosy = y * stepGrid;
            Grid[x][y].AbsPosy_inv = 100 * stepGrid - y * stepGrid;

            Grid[x][y].AbsPosx = x * stepGrid;
            Grid[x][y].AbsPosx_inv = 100 * stepGrid - x * stepGrid;

            Grid[x][y].obstacle = false;
        }
    }
    //  DebugPrint2("entre aqui0->", Wall_to_allign, Grid[0][0].obstacle);
}
