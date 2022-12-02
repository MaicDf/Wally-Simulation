#include <stdio.h>
#include "main.h"
#include "map.c"
float getDistanceFront(USdistances *measurement)
{   
    usReading( measurement);
    return measurement->USfront;// function in zephyr, here is a function in the sim.
}

float getDistanceBack(USdistances *measurement)
{
    usReading( measurement);
    return measurement->USback;
}

float getDistanceLeft(USdistances *measurement)
{   
    usReading( measurement);
    return measurement->USleft;
}

float getDistanceRight(USdistances *measurement)
{
    usReading( measurement);
    return measurement->USright;
}

void getAll(USdistances *measurement)
{
    usReading( measurement);
}
