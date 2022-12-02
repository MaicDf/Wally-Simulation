#ifndef movement
#define movement
typedef enum
{
    FRONT = 0,
    BACK,
    LEFT,
    RIGHT,
    UKNOWN
} direction;

typedef struct
{
    float USfront;
    float USback;
    float USleft;
    float USright;
} USdistances;

void init(void);
direction furthest(float front_, float back_, float left_, float right_);
direction nearest(float front_, float back_, float left_, float right_);
#endif