#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <drone.h>
#include <assert.h>

int Drone_init(void *self)
{
		// do nothing really
		return 1;
}


void Drone_boot(void *self){
	Drone *obj = self;
	obj->state = 1;
	obj->busy =1;
	int id = obj->id;
	printf("\x1b[34m Drone[%d] : Boot Sequece started.\n\x1b[0m",id);
	sleep(1);
	printf("\x1b[34m Drone[%d] : GPS Online\n\x1b[0m",id);
	sleep(1);
	printf("\x1b[34m Drone[%d] : Motor 1 Ready\n\x1b[0m",id);
	sleep(1);
	printf("\x1b[34m Drone[%d] : Motor 2 Ready\n\x1b[0m",id);
	sleep(1);
	printf("\x1b[34m Drone[%d] : Motor 3 Ready\n\x1b[0m",id);
	sleep(1);
	printf("\x1b[34m Drone[%d] : Motor 4 Ready\n\x1b[0m",id);
	printf("\x1b[34m Drone[%d] : Boot Completed\n\x1b[0m",id);
	obj->busy =0;
	printf("\x1b[32m Drone[%d] Standing By  \n\x1b[0m", id);
	//pthread_exit(0);
}


void Drone_stand_by(void *self){
	Drone *obj = self;
	obj->state = 2;
	obj->busy =1;
	while(	obj->state==2){
	printf("\x1b[32mDrone Standing By  \x1b[0m");
}
obj->busy =0;
pthread_exit(0);
}

void Drone_navigate(void *self, int x, int y){
	Drone *obj = self;
	obj->state = 5;
	obj->busy =1;
	int id = (obj->id);
	sleep(1);
	printf("%d", id );
	printf("\x1b[34m : Navigating to  (\x1b[0m");
	printf("%d", x);printf("\x1b[34m, \x1b[0m");	printf("%d", y);printf("\x1b[34m) \n\x1b[0m");
	int curr_x = (*obj).curr_x;
	int curr_y = (*obj).curr_y;
	printf("%d", id );
	printf("\x1b[33m : Planned Path (x+\x1b[0m");printf("%d", x-curr_x);printf("\x1b[33m, y+\x1b[0m");	printf("%d", y-curr_y);printf("\x1b[33m) \n\x1b[0m");
	int i;
	for(i=0;i<=(x-curr_x);++i){
		printf("%d", id );
		printf("\x1b[33m : Moving to  (\x1b[0m");
		printf("%d", i);printf("\x1b[33m, \x1b[0m");	printf("%d", curr_y);printf("\x1b[33m) \n\x1b[0m");
	}
	curr_x = (x-curr_x);
	for(i=0;i<=(y-curr_y);++i){
		printf("%d", id );
		printf("\x1b[33m : Moving to  (\x1b[0m");
		printf("%d", curr_x);printf("\x1b[33m, \x1b[0m");	printf("%d", i);printf("\x1b[33m) \n\x1b[0m");
	}
	curr_y = (y-curr_y);
	obj->busy =0;
//	pthread_exit(0);
}

int Drone_pick_up(void *self){
	Drone *obj = self;
	obj->state = 4;
	obj->busy =1;
	sleep(1);
	printf("\x1b[32mDrone ready for pick up  \n\x1b[0m");
	sleep(1);
	printf("\x1b[34mDrone requesting payload \n\x1b[0m");
	sleep(1);
	printf("\x1b[32mDrone payload picked up \n\x1b[0m");
	obj->busy =0;
//	pthread_exit(0);
	return 0;
}

void Drone_lift_off(void *self){
	Drone *obj = self;
	obj->state = 3;
	obj->busy =1;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	obj->busy =0;
	pthread_exit(0);
}

int Drone_deliver(void *self){
	Drone *obj = self;
	obj->state = 6;
	obj->busy =1;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	obj->busy =0;
	pthread_exit(0);
	return 0;
}

void Drone_return_home(void *self){
	Drone *obj = self;
	obj->state = 7;
	obj->busy =1;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	obj->busy =0;
	pthread_exit(0);
}

void Drone_land(void *self){
	Drone *obj = self;
	obj->state = 8;
	obj->busy =1;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	obj->busy =0;
	pthread_exit(0);
}

void Drone_destroy(void *self)
{
		Drone *obj = self;

		if(obj) {
				if(obj->id) free(obj->id);
				free(obj);
		}
}
void *Drone_new(size_t size, Drone proto, int id)
{
		// setup the default functions in case they aren't set
		if(!proto.init) proto.init = Drone_init;
		if(!proto.boot) proto.boot = Drone_boot;
		if(!proto.stand_by) proto.stand_by = Drone_stand_by;
		if(!proto.navigate) proto.navigate = Drone_navigate;
		if(!proto.pick_up) proto.pick_up = Drone_pick_up;
		if(!proto.lift_off) proto.lift_off = Drone_lift_off;
		if(!proto.deliver) proto.deliver= Drone_deliver;
		if(!proto.return_home) proto.return_home = Drone_return_home;
		if(!proto.land) proto.land = Drone_land;

		// this seems weird, but we can make a struct of one size,
		// then point a different pointer at it to "cast" it
		Drone *el = calloc(1, size);
		*el = proto;

		// copy the id over

		el->id = id;
		el->state = 0;
		el->busy = 0;
		el->curr_x=0;
		el->curr_y=0;

		// initialize it with whatever init we were given
		if(!el->init(el)) {
				// looks like it didn't initialize properly
				el->destroy(el);
				return NULL;
		} else {
				// all done, we made an object of any type
				return el;
		}
}
