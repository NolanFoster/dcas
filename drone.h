#ifndef _drone_h
#define _drone_h
//Drone Commands
typedef long unsigned int size_t;

typedef struct Assignment{
void *self;
 int id, x, y;
}Assignment;

typedef struct {
    int id;
    int *curr_state;
    int *busy;
    int *curr_x;
    int *curr_y;
    int (*state)(void *self, int get, int set);
    int (*init)(void *self);
    void (*boot)(void *self);
    void (*stand_by)(void *self, int id);
    void (*navigate)(Assignment *assign);
    void (*pick_up)(void *self, int id);
    void (*lift_off)(void *self);
    int (*deliver)(void *self);
    void (*return_home)(void *self, int id);
    void (*land)(void *self);
    void (*destroy)(void *self);
} Drone;

#define new_drone(T, N) Drone_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif

int Drone_init(void *self);
void Drone_boot(void *self);
void Drone_stand_by(void *self, int id);
void Drone_navigate(Assignment *assign);
void Drone_pick_up(void *self, int id);
void Drone_lift_off(void *self);
int Drone_deliver(void *self);
void Drone_return_home(void *self, int id);
void Drone_land(void *self);
void Drone_destroy(void *self);
int Drone_state(void *self, int get, int set);
void *Drone_new(size_t size, Drone proto, int *id);
