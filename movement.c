#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void moveAheadSimulation();
void turnFrontSimulation();
void turnBackSimulation();
void turnLeftSimulation();
void turnRightSimulation();

void moveAhead()
{
    // turn motors on

    // Code that only works for the simulation environment
    moveAheadSimulation();
}

void turnFront()
{
}

void turnBack()
{
}

void turnLeft()
{
}

void turnRight()
{
}

void moveAheadSimulation(direction CurrentDirectionMovement)
{
    if (CurrentDirectionMovement == FRONT)
    {
    }
    else if (CurrentDirectionMovement == BACK)
    {
    }
    else if (CurrentDirectionMovement == LEFT)
    {
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
    }
}
direction turnFrontSimulation(direction CurrentDirectionMovement)
{
    if (CurrentDirectionMovement == FRONT)
    {
        return FRONT;
    }
    else if (CurrentDirectionMovement == BACK)
    {
        return BACK;
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        return LEFT;
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        return RIGHT;
    }
}
void turnBackSimulation(direction CurrentDirectionMovement)
{
    if (CurrentDirectionMovement == FRONT)
    {
        return BACK;
    }
    else if (CurrentDirectionMovement == BACK)
    {
        return FRONT;
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        return LEFT;
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        return RIGHT;
    }
}
void turnLeftSimulation(direction CurrentDirectionMovement)
{
    if (CurrentDirectionMovement == FRONT)
    {
        return LEFT;
    }
    else if (CurrentDirectionMovement == BACK)
    {
        return RIGHT;
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        return BACK;
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        return FRONT;
    }
}
void turnRightSimulation(direction CurrentDirectionMovement)
{
    if (CurrentDirectionMovement == FRONT)
    {
        return RIGHT;
    }
    else if (CurrentDirectionMovement == BACK)
    {
        return LEFT;
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        return FRONT;
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        return BACK;
    }
}