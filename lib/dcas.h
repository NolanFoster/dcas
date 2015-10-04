#ifndef _dcas_h
#define _dcas_h
//Drone Commands
typedef long unsigned int size_t;

typedef struct {
    int *drones;
    int *tasks;
    int *can_land;
    int *can_take_off;
    int (*init)(void *self);
    void (*planned_paths)(void *self);
    void (*cas)(void *self);
    void (*destroy)(void *self);
} Dcas;

#define new_dcas(T, N) Dcas_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif

int Dcas_init(void *self);
void Dcas_cas(void *self);
void Dcas_planned_paths(void *self);
void Dcas_destroy(void *self);
void *Dcas_new(size_t size, Dcas proto);
