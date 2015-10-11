#include <dcas.h>
#include <stdio.h>
#include "field.h"
#define NUM_DRONES	3


int main(int argc, char *argv[]) {

	pthread_mutex_init(&fieldMutex, NULL);
	pthread_mutex_init(&deliveryMutex, NULL);
	pthread_t threads[NUM_DRONES];

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

	DeliveryDrone* drones[NUM_DRONES];

	int i=0;
	for(i=1;i<=NUM_DRONES;++i){
		printf("%d\n", i);
		drones[i] = new_drone(DeliveryDrone, i);
		pthread_create(&threads[i], NULL, drones [i]->_(boot), &drones[i]);
	}

	pthread_exit(NULL);


	return(0);
}
