#include <ncurses.h>
#include <unistd.h>
#ifndef _drone_h
#define _drone_h
//Drone Commands
typedef struct Loc{
  void *self;
  int x;
  int y;
}Loc;

typedef long unsigned int size_t;

typedef struct {
    int id;
    int state;
    int *curr_x;
    int *curr_y;
    int (*init)(void *self);
    void (*boot)(void *self);
    void (*stand_by)(void *self);
    void (*navigate)(Loc *l);
    int (*pick_up)(void *self);
    void (*lift_off)(void *self);
    int (*deliver)(void *self);
    void (*return_home)(void *self);
    void (*land)(void *self);
    void (*destroy)(void *self);
} Drone;

#define new_drone(T, N) Drone_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif

int Drone_init(void *self);
int Drone_state(void *self);
void Drone_boot(void *self);
void Drone_stand_by(void *self);
void Drone_navigate(Loc *l);
int Drone_pick_up(void *self);
void Drone_lift_off(void *self);
int Drone_deliver(void *self);
void Drone_return_home(void *self);
void Drone_land(void *self);
void Drone_destroy(void *self);
void *Drone_new(size_t size, Drone proto, int *id);
