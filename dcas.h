#ifndef _dcas_h
#define _dcas_h

#include <drone.h>
#include <pthread.h>

typedef struct coordinate{
  double latitude, longtitude;
}coordinate;



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
pthread_mutex_t mapMutex;
pthread_mutex_t deliveryMutex;
