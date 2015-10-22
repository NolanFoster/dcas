/*
* Filename: drone_func.c
* Description: Functions for Parent Drone Object
* Author: Nolan Foster
* Date Created: 10/7/15
*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <drone.h>
#include <assert.h>
#include <time.h>
#include <map.h>


/*
* Drone instanciation
*/
int Drone_init(void *self)
{
		// do nothing really depends on proto object
		return 1;
}

int Drone_state(void *self){
	Drone *obj = self;
	return obj->state;
}

/*
* Drone Boot Sequence
*/
void Drone_boot(void *self){
	Drone *obj = self;
	int* id = obj->id;
	obj->state=0;
	obj->curr_x=id+1;
	obj->curr_y=0;
	//setPosition(*id,0, 2);
	sleep(rand()%2);
	obj->state=1;
}


/*
* Drone stand by
* Input: Self
* Description: Drone hovers and waits for command from command center
*/
void Drone_stand_by(void *self){
	Drone *obj = self;
	obj->state=1;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
pthread_exit(0);
}

/*
* Drone Navigate
* Input: Destination Coordinates
* Description: Navigates Drone to Destination
*/
void Drone_navigate(Loc *l){
	printf("\x1b[32mNavigate \x1b[0m");
	Drone *obj = l->self;
	int id = (obj->id);
	sleep(1);
	int curr_x = (*obj).curr_x;
	int curr_y = (*obj).curr_y;

	printf("\x1b[32mset positions  \x1b[0m");
	setPosition(curr_x, curr_y, 1);
	int i;
	for(i=0;i<=(l->x-curr_x);++i){
		setPosition(i-1, curr_y, 0);
		setPosition(i, curr_y, 1);
	}
	curr_x = (l->x-curr_x);
	for(i=0;i<=(l->y-curr_y);++i){
		setPosition(curr_x, i-1, 0);
		setPosition(curr_x, i, 1);
	}
	curr_y = (l->y-curr_y);
	pthread_exit(0);
}

/*
* Drone stand by
* Input: Self
* Description: Drone picks up package
*/
int Drone_pick_up(void *self){
	Drone *obj = self;
	sleep(1);
	printf("\x1b[32mDrone ready for pick up  \n\x1b[0m");
	sleep(1);
	printf("\x1b[34mDrone requesting payload \n\x1b[0m");
	sleep(1);
	printf("\x1b[32mDrone payload picked up \n\x1b[0m");
	pthread_exit(0);
	return 0;
}

/*
* Drone stand by
* Input: Self
* Description: Drone lifts off fron ground
*/
void Drone_lift_off(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
}

/*
* Drone deliver
* Input: Self
* Description: Drone drop off package
*/
int Drone_deliver(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
	return 0;
}

/*
* Drone Return Home
* Input: Self
* Description: Drone Returns to Control Center
*/
void Drone_return_home(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
}

/*
* Drone Land
* Input: Self
* Description: Drone lands
*/
void Drone_land(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
}


/*
* Drone destroy
* Input: Self
* Description: Restores memory allocated by drone object
*/
void Drone_destroy(void *self)
{
		Drone *obj = self;

		if(obj) {
				if(obj->id) free(obj->id);
				free(obj);
		}
}

/*
* Drone destroy
* Input: size_t, Drone, int
* Description: Creates new Drone object refernce and allocates memory
*/
void *Drone_new(size_t size, Drone proto, int *id)
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

		el->id = *id;
		el->state = 0;
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
