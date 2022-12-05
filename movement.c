#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <stdbool.h>
#include "ultrasonido.c"

bool controlDistance(direction relativeDir, float referenceDistance, float incertidumbre);
bool controlV_position(int currentX, int currentY, float incertidumbre);
bool controlH_position(int currentX, int currentY, float incertidumbre);

bool controlDistance(direction relativeDir, float referenceDistance, float incertidumbre)
{
    bool controlDoneFlag = false;
    float measured_Distance;
    if (relativeDir == RIGHT)
    {
        measured_Distance = getDistanceRight(&measurement1);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
            turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    if (relativeDir == LEFT)
    {

        measured_Distance = getDistanceLeft(&measurement1);
        // DebugPrint2("leftDistance",0,measured_Distance);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    return controlDoneFlag;
}

// la referencia es la que se guarda en el mapeo.

bool controlH_position(int currentX, int currentY, float incertidumbre)
{

    bool controlDoneFlag = false;
    int referenceDistance;

    // dependiendo de la dirección se basa en una u otra posición absoluta
    if (CurrentDirectionMovement == FRONT || CurrentDirectionMovement == BACK)
    {
        // Aquí se observa si está más cerca las referencias de grilla normales o invertidas, para saber con cual dis hacer control
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx;
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
        }
    }
    else if (CurrentDirectionMovement == RIGHT || CurrentDirectionMovement == LEFT)
    {
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
        }
    }

    float measured_Distance;
    if (Wall_to_allign == LEFT)
    {
        measured_Distance = getDistanceLeft(&measurement1);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead();     // certain time
            turnRight();     // 1grado o algo así.
            moveBackwards(); // certain time
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    if (Wall_to_allign == RIGHT)
    {

        measured_Distance = getDistanceRight(&measurement1);
        // DebugPrint2("leftDistance",0,measured_Distance);
        if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
        {
            controlDoneFlag = true;
        }
        else if (measured_Distance < (referenceDistance - incertidumbre))
        {
            moveAhead(); // certain time
            turnLeft();  // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false;
        }
        else if (measured_Distance > (referenceDistance + incertidumbre))
        {
            moveAhead(); // certain time
            turnRight(); // 1grado o algo así.
            moveBackwards();
            controlDoneFlag = false; // significa que todavía falta verificar el control
        }
    }
    return controlDoneFlag;
}

bool controlV_position(int currentX, int currentY, float incertidumbre)
{
    bool controlDoneFlag = false;
    int referenceDistance;
    float measured_Distance;

    // dependiendo de la dirección se basa en una u otra posición absoluta
    if (CurrentDirectionMovement == FRONT)
    {
        // Aquí se observa si está más cerca las referencias de grilla normales o invertidas, para saber con cual dis hacer control
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveAhead(); //##FALTA->hacer una funcion de while(measured distance+-= reference)
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == BACK)
    {
        if (Grid[currentX][currentY].AbsPosy <= Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosy > Grid[currentX][currentY].AbsPosy_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosy_inv;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx;
            measured_Distance = getDistanceBack(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
            measured_Distance = getDistanceFront(&measurement1);

            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        if (Grid[currentX][currentY].AbsPosx <= Grid[currentX][currentY].AbsPosx_inv)
        {
            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
            referenceDistance = Grid[currentX][currentY].AbsPosx;
            measured_Distance = getDistanceFront(&measurement1);
        }
        else if (Grid[currentX][currentY].AbsPosx > Grid[currentX][currentY].AbsPosx_inv)
        {
            referenceDistance = Grid[currentX][currentY].AbsPosx_inv;
            measured_Distance = getDistanceBack(&measurement1);
            if ((measured_Distance >= (referenceDistance - incertidumbre)) && (measured_Distance <= (referenceDistance + incertidumbre)))
            {
                controlDoneFlag = true;
            }
            else if (measured_Distance < (referenceDistance - incertidumbre))
            {
                moveAhead();
                controlDoneFlag = false;
            }
            else if (measured_Distance > (referenceDistance + incertidumbre))
            {
                moveBackwards();
                controlDoneFlag = false; // significa que todavía falta verificar el control
            }
        }
    }
    return controlDoneFlag;
}

void moveAhead()
{
    // turn motors on

    // Code that only works for the simulation environment
    moveAheadSimulation();
}

void moveBackwards()
{
    moveBackwardsSimulation();
}

void stop()
{
    stopSimualtion();
}

void turnBack()
{
    // aquí es necesario actualizar la dirección actual
    // mensaje de confirmación cuando no haya simulación
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
