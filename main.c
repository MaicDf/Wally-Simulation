#include <stdio.h>

#include <stdlib.h>

#include "movement.c"
#include "ultrasonido.c"

#include "main.h"

direction CurrentDirectionMovement;
USdistances measurement1;
void init();
// aqui va a estar el "cerebro"
int main()
{
    // Para el mapeo
    mapping();
    DebugPrint("All fine", 0, 0);

    // 1.init: Distancias iniciales y acercarse a la pared más cercana
    init();
    /* 2.edgeSearching: Al acercarse a la pared más cercana, considera las distancias
    perpendiculares, y se va a la más cercana. En este momento se debe buscar estar
    paralelo a la pared, luego a cada movimiento hacia adelante se hará 
    una corrección de distancia para siempre mantenerse al margen */
    return 0;
}

void init()
{
    getAll(&measurement1);
    if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == FRONT)
    {
        while (getDistanceFront(&measurement1) >= 4)
        {   
            moveAhead();
        }
    }
    else if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == BACK)
    {
        turnBack();
        while (getDistanceFront(&measurement1) >= 4)
        {
            moveAhead();
        }
    }
    else if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == RIGHT)
    {
        turnRight();
        while (getDistanceFront(&measurement1) >= 4)
        {
            moveAhead();
        }
    }
        else if (nearest(measurement1.USfront, measurement1.USback, measurement1.USleft, measurement1.USright) == LEFT)
    {
        turnLeft();
        while (getDistanceFront(&measurement1) >= 4)
        {
            moveAhead();
        }
    }
}

void edgeSearching(){

}
   // MeasurementRight and Left
    //  Turn to the nearest
    //  Go front
    // Always keeping the distances wether it is right or left (controling this constanly).
    // Finding the edge and turn to the void side.
    // StartMapping.

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
