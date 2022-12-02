#include<stdio.h>

#include<stdlib.h>
#include "map.c"
#include "ultrasonido.c"
#include "main.h"



USdistances measurement1;

// aqui va a estar el "cerebro"
int main()
{
    // Para el mapeo
    DebugPrint("hola", 5, 5.5);
    mapping();
    while(1){
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(RIGHT);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(BACK);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(LEFT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
        moveAheadSimulation(FRONT);
    }
    // 1.init: Distancias iniciales y acercarse a la pared más cercana

    return 0;
}

void init()
{
    getAll(&measurement1);
    if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == FRONT)
    {
        // turnToNearest()
        // while(getMeasurementFront<=20){
        // moveFront()}
    }
    else if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == BACK)
    {
        // moveBack ->Adjust Front==BACK
    } //....

    // MeasurementRight and Left
    //  Turn to the nearest
    //  Go front
    // Always keeping the distances wether it is right or left (controling this constanly).
    // Finding the edge and turn to the void side.
    // StartMapping.
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
        return UKNOWN;
    }
}

direction nearest(float front_, float back_, float left_, float right_)
{
    if (front_ < back_ && front_ < left_ && front_ < right_)
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
        return UKNOWN;
    }
}

