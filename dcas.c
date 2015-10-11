#include <dcas.h>
#include <stdio.h>
#include <map.h>
#define NUM_DRONES	10


int main(int argc, char *argv[]) {

	pthread_mutex_init(&mapMutex, NULL);
	pthread_mutex_init(&deliveryMutex, NULL);
	pthread_t threads[NUM_DRONES];

	make_map();
	//Set Control Center at 1
	setPosition(0, 0, 1);
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
	for(i=1;i<=NUM_DRONES;i++){
		drones[i] = new_drone(DeliveryDrone, &i);
		pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
	}

	pthread_exit(NULL);


	return(0);
}
