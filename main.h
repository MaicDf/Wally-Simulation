#ifndef mainH
#define mainH

#include <stdbool.h>


typedef enum
{
    FRONT = 0,
    BACK,
    LEFT,
    RIGHT,
    EQUAL,
    NONVALID
} direction;

typedef struct
{
    float USfront;
    float USback;
    float USleft;
    float USright;
} USdistances;

typedef struct
{
	int AbsPosx;
	int AbsPosy;
    int AbsPosx_inv;
    int AbsPosy_inv;
	bool obstacle; // * indicar� obstaculo, ser� vacio
} GridPoint;

bool V_OpositeWallFound=false;
bool H_OpositeWallFound=false;
USdistances measurement1;
direction Wall_to_allign = NONVALID; //a que pared se pega para mapear
GridPoint Grid[100][100]; //el mapa
direction CurrentDirectionMovement;



void init(void);
direction furthest(float front_, float back_, float left_, float right_);
direction nearest(float front_, float back_, float left_, float right_);
#endif
