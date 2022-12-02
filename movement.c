#include <stdio.h>
#include <stdlib.h>
#include "main.h"



void moveAhead()
{
    // turn motors on

    // Code that only works for the simulation environment
    moveAheadSimulation();
}

void turnFront()
{
     //aquí es necesario actualizar la dirección actual
     //mensaje de confirmación cuando no haya simulación
    turnFrontSimulation();
}

void turnBack()
{
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
