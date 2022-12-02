#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "map.c"


void moveAhead()
{
    // turn motors on

    // Code that only works for the simulation environment
    moveAheadSimulation();
}


void turnBack()
{
    //aquí es necesario actualizar la dirección actual
     //mensaje de confirmación cuando no haya simulación
    turnBackSimulation();

}

void turnLeft()
{
    turnLeftSimulation();
}

void turnRight()
{
    turnRightSimulation();
}
