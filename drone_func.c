#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <drone.h>
#include <assert.h>
#include <map.h>
#include <time.h>

int Drone_init(void *self)
{
		// do nothing really
		return 1;
}

int Drone_state(void *self, int get, int set){
	pthread_mutex_unlock(&stateMutex);
	pthread_mutex_lock(&stateMutex);
	Drone *obj = self;
	if(!get)
	obj->curr_state=set;
	return obj->curr_state;
	pthread_mutex_unlock(&stateMutex);
}

void Drone_boot(void *self){
	Drone *obj = self;
	int* id = obj->id;
	obj->curr_x=*id-1;
	obj->curr_y=0;
	sleep(*id);
	setPosition(0, 0, *id);
	print_map();
	printf("\x1b[32m Drone %d  Booted \n\x1b[0m", *id);
	Drone_stand_by(self, *id);
}


void Drone_stand_by(void *self, int id){
	Drone_state(self, 0,1);
	Drone *obj = self;
	Assignment assign;
	assign.self=obj;
	assign.x=rand()%40;
	assign.y=rand()%20;
	assign.id=id;
	sleep(id);
	print_map();
	printf("\x1b[32mDrone %d Standing By  \n\x1b[0m", id);
	sleep(5);
	Drone_navigate(&assign);
}

void Drone_navigate(Assignment *assign){
	Drone_state(assign->self, 0,2);
	int x= assign->x;
	int y= assign->y;
	Drone *obj = assign->self;

	int curr_x = 0;
	int curr_y = 0;
	int i;
//	sleep(assign->id*2);
	printf("\x1b[32mDrone %d Picked up Package  \n\x1b[0m", assign->id);
	setPosition(curr_y, curr_x, 0);
	for(i=1;i<=(x-curr_x);++i){
		if(get_position(curr_y, i)!=0){
						curr_y++;
			if(get_position(curr_y, i)!=0){
							curr_y--;i++;
				if(get_position(curr_y, i)!=0){
					i--;curr_y++;
				}
			}
			print_map();
			printf("\x1b[31mCOLLISION!!! with %d  \n\x1b[0m", get_position(curr_y, i));
		}
		printf("\x1b[31m%d  \n\x1b[0m", get_position(curr_y, i));
		setPosition(curr_y, i, assign->id);
		print_map();
		printf("\x1b[32mDrone %d moved to %d , %d  \n\x1b[0m", assign->id, i, curr_y);
		sleep(1);
		setPosition(curr_y, i, 0);
		print_map();

	}
	curr_x = (x-curr_x);

	for(i=0;i<=(y-curr_y);++i){
		if(get_position(i, curr_x)!=0){
						curr_x--;
			if(get_position(i, curr_x)!=0){
							curr_x++;i--;
				if(get_position(i, curr_x)!=0){
					i++;curr_x--;
				}
			}
			print_map();
			printf("\x1b[31mCOLLISION!!! with %d  \n\x1b[0m", get_position(i, curr_x));
		}
		setPosition(i, curr_x, assign->id);
		print_map();
		printf("\x1b[32mDrone %d moved to %d , %d  \n\x1b[0m",assign->id, curr_x, i);
		sleep(1);
		setPosition(i, curr_x, 0);
		print_map();

	}
	curr_y = (y-curr_y);

	obj->curr_x=curr_x;
	obj->curr_y=curr_y;
	setPosition((*obj).curr_y, (*obj).curr_x, assign->id);

	Drone_pick_up(assign->self, assign->id);
}

void Drone_pick_up(void *self, int id){
	Drone *obj = self;
	setPosition((*obj).curr_y, (*obj).curr_x, id);
	print_map();
	printf("\x1b[32mDrone %d ready for pick up  \n\x1b[0m", id);
	sleep(1);
	print_map();
	printf("\x1b[33mDrone %d requesting payload \n\x1b[0m", id);
	sleep(1);
	print_map();
	printf("\x1b[32mDrone %d payload picked up \n\x1b[0m", id);

	Drone_return_home(self, id);
}

void Drone_lift_off(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
}

int Drone_deliver(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
	pthread_exit(0);
	return 0;
}

void Drone_return_home(void *self, int id){
	int x= 0;
	int y= 0;
	Drone *obj = self;
	printf("\x1b[32mDrone %d Returning Home  \n\x1b[0m", id);

	int curr_x = (*obj).curr_x;
	int curr_y = (*obj).curr_y;
	int i;
	setPosition(curr_y, curr_x, 0);
	print_map();
	printf("\x1b[32mDrone %d is at %d , %d  \n\x1b[0m", id, curr_x, curr_y);
	sleep(1);
	while(curr_y>0){
		if(get_position(curr_y, curr_x)!=0){
			curr_x--;
			setPosition(curr_y, curr_x, id);
			print_map();
			sleep(1);
			setPosition(curr_y, curr_x, 0);
			curr_y--;
			setPosition(curr_y, curr_x, id);
			print_map();
			sleep(1);
			setPosition(curr_y, curr_x, 0);
			curr_x++;
			setPosition(curr_y, curr_x, id);
			print_map();
			printf("\x1b[31mCOLLISION!!! with %d  \n\x1b[0m", get_position(curr_y, curr_x));
		}
		setPosition(curr_y, curr_x, id);
		print_map();
		printf("\x1b[32mDrone %d moved to %d , %d  \n\x1b[0m", id, curr_x, curr_y);
		sleep(1);
		setPosition(curr_y, curr_x, 0);
		print_map();
		curr_y--;
	}
	while(curr_x>0){
		if(get_position(curr_y, curr_x)!=0){
						curr_y++;
						setPosition(curr_y, curr_x, id);
						print_map();
						sleep(1);
						setPosition(curr_y, curr_x, 0);
						curr_x--;
						setPosition(curr_y, curr_x, id);
						print_map();
						sleep(1);
						setPosition(curr_y, curr_x, 0);
						curr_y--;
						setPosition(curr_y, curr_x, id);
						print_map();
			printf("\x1b[31mCOLLISION!!! with %d  \n\x1b[0m", get_position(curr_y, curr_x));
			sleep(1);
		}
		setPosition(curr_y, curr_x, id);
		print_map();
		printf("\x1b[32mDrone %d moved to %d , %d  \n\x1b[0m", id, curr_x, curr_y);
		sleep(1);
		setPosition(curr_y, curr_x, 0);
		print_map();
		curr_x--;
	}
	curr_y = (y-curr_y);
	printf("\x1b[32mDrone %d is Home  \n\x1b[0m", id);
}

void Drone_land(void *self){
	Drone *obj = self;
	printf("\x1b[32mDrone Standing By  \x1b[0m");
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
		if(!proto.state) proto.state = Drone_state;

		// this seems weird, but we can make a struct of one size,
		// then point a different pointer at it to "cast" it
		Drone *el = calloc(1, size);
		*el = proto;

		// copy the id over

		el->id = *id;
		el->curr_state = 0;
		el->busy = 0;
		el->curr_x = 0;
		el->curr_y = 0;

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
