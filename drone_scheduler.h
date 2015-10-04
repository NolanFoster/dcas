#ifndef _drone_scheduler_h
#define _drone_scheduler_h

#include "drone.h"

struct DeliveryDrone {
    Drone proto;
    int x,y,xf,yf;
    char payload;
};

typedef struct DeliveryDrone DeliveryDrone;
int DeliveryDrone_init(void *self);

struct Task {
    int xf,yf;
    char payload;
};

typedef struct Task Task;
#endif
