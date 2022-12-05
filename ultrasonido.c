#include <stdio.h>
#include "main.h"
#include "map.c"
#include <stdbool.h>
float getDistanceFront(USdistances *measurement);
float getDistanceBack(USdistances *measurement);
float getDistanceLeft(USdistances *measurement);
float getDistanceRight(USdistances *measurement);
void mapFront(float measure);
void mapBack(float measure);
void mapRigth(float measure);
void mapLeft(float measure);
void Map_From_currentPoint(int currentPointGridX, int currentPointGridY, float incertidumbre);
float secureReading(direction myDir,float inc);
bool igualdad(float v1, float v2, float v3, float inc);

float getDistanceFront(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USfront > 200) // distance where we don't rely on the measurement
    {
        measurement->USfront = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USfront; // function in zephyr, here is a function in the sim.
}

float getDistanceBack(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USback > 200) // distance where we don't rely on the measurement
    {
        measurement->USback = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USback;
}

float getDistanceLeft(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USleft > 200) // distance where we don't rely on the measurement
    {
        measurement->USleft = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USleft;
}

float getDistanceRight(USdistances *measurement)
{
    usReading(measurement);
    if (measurement->USright > 200) // distance where we don't rely on the measurement
    {
        measurement->USright = 10000; // un valor grande,para que tenga el flag de  que no se confía
    }
    return measurement->USright;
}

void getAll(USdistances *measurement)
{
    measurement->USback = getDistanceBack(measurement);
    measurement->USfront = getDistanceFront(measurement);
    measurement->USleft = getDistanceLeft(measurement);
    measurement->USright = getDistanceRight(measurement);
}

void Map_From_currentPoint(int currentPointGridX, int currentPointGridY, float incertidumbre)
{
    float M_R, M_L, M_F, M_B;
	M_R = secureReading(RIGHT, incertidumbre);
    M_L = secureReading(LEFT ,incertidumbre);
    M_F = secureReading(FRONT, incertidumbre);
    M_B = secureReading(BACK ,incertidumbre);

    if (CurrentDirectionMovement == FRONT)
    {
        mapFront(M_F);
        mapBack(M_B);
        mapRigth(M_R);
        mapLeft(M_L);
    }
    else if (CurrentDirectionMovement == BACK)
    {
        mapFront(M_B);
        mapBack(M_F);
        mapRigth(M_L);
        mapLeft(M_R);
    }
    else if (CurrentDirectionMovement == RIGHT)
    {
        mapFront(M_R);
        mapBack(M_L);
        mapRigth(M_B);
        mapLeft(M_F);
    }
    else if (CurrentDirectionMovement == LEFT)
    {
        mapFront(M_L);
        mapBack(M_R);
        mapRigth(M_F);
        mapLeft(M_B);
    }
}

float secureReading(direction myDir, float inc)
{ // 3 mediciones para asegurarse que el valor medido tiene sentido
    float medicion1, medicion2, medicion3, result;
    while (1)
        if (myDir == FRONT)
        {
            medicion1 = getDistanceFront(&measurement1);
            medicion2 = getDistanceFront(&measurement1);
            medicion3 = getDistanceFront(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == BACK)
        {
            medicion1 = getDistanceBack(&measurement1);
            medicion2 = getDistanceBack(&measurement1);
            medicion3 = getDistanceBack(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == RIGHT)
        {
            medicion1 = getDistanceRight(&measurement1);
            medicion2 = getDistanceRight(&measurement1);
            medicion3 = getDistanceRight(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }
        else if (myDir == LEFT)
        {
            medicion1 = getDistanceLeft(&measurement1);
            medicion2 = getDistanceLeft(&measurement1);
            medicion3 = getDistanceLeft(&measurement1);
            if (igualdad(medicion1, medicion2, medicion3, inc))
            {
                result = (medicion1 + medicion2 + medicion3) / 3;
                break;
            }
            else
            {
                continue;
            }
        }

    return result;
}

bool igualdad(float v1, float v2, float v3, float inc)
{
    if ((v1 > (v2 - inc)) && (v1 > (v2 - inc)) && (v1 > (v3 - inc)) && (v1 > (v3 - inc)))
        return true;
    else
        return false;
}

void mapFront(float measure)
{
    if(CurrentDirectionMovement==FRONT&&V_OpositeWallFound){

    }else if(CurrentDirectionMovement==RIGHT||H_OpositeWallFound){
    	
    }
}
void mapBack(float measure)
{
}
void mapRigth(float measure)
{
}
void mapLeft(float measure)
{
}
