#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <dcas.h>
#include <assert.h>

int Dcas_init(void *self)
{
		// do nothing really
		return 1;
}


void Dcas_navigate(void *self){
	pthread_exit(0);
}

void Dcas_destroy(void *self)
{
		Dcas *obj = self;

		if(obj) {
				if(obj->id) free(obj->id);
				free(obj);
		}
}
void *Dcas_new(size_t size, Dcas proto, int *id)
{
		// setup the default functions in case they aren't set
		if(!proto.init) proto.init = Dcas_init;
		if(!proto.boot) proto.boot = Dcas_boot;
		if(!proto.stand_by) proto.stand_by = Dcas_stand_by;
		if(!proto.navigate) proto.navigate = Dcas_navigate;
		if(!proto.pick_up) proto.pick_up = Dcas_pick_up;
		if(!proto.lift_off) proto.lift_off = Dcas_lift_off;
		if(!proto.deliver) proto.deliver= Dcas_deliver;
		if(!proto.return_home) proto.return_home = Dcas_return_home;
		if(!proto.land) proto.land = Dcas_land;

		// this seems weird, but we can make a struct of one size,
		// then point a different pointer at it to "cast" it
		Dcas *el = calloc(1, size);
		*el = proto;

		// copy the id over
		el->id = *id;
		el->state = 0;
		el->busy =0;

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
