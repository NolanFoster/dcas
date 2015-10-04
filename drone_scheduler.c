#include <drone_scheduler.h>
#include <pthread.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

	/* this variable is our reference to the second thread */
	pthread_t thread_test,thread_test1,thread_test2,thread_test3;
	int  i = 1;

	int DeliveryDrone_init(void *self)
	{
			DeliveryDrone *DeliveryDrone = self;
			DeliveryDrone->x = 0;
			DeliveryDrone->y = 0;
			return 1;
	}

	Drone DeliveryDroneProto = {
		.init = DeliveryDrone_init
	};



  //initialize new delivery drone
	DeliveryDrone *d = new_drone(DeliveryDrone, &i);
	/* create a thread which executes */
	pthread_create(&thread_test, NULL, d->_(boot), &d);
//	pthread_create(&thread_test1, NULL, d->_(navigate), (&d,1,1));
//	pthread_join(thread_test1,NULL);
	pthread_join(thread_test,NULL);
	d->_(navigate)(&d,3,7);
	d->_(pick_up)(&d);

	return(0);
}
