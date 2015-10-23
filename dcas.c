#include <dcas.h>
#include <stdio.h>
#include <map.h>
#define NUM_DRONES	100


int main(int argc, char *argv[]) {

	pthread_mutex_init(&mapMutex, NULL);
	pthread_mutex_init(&deliveryMutex, NULL);
	pthread_t threads[NUM_DRONES];

	//Set Control Center at 1
	//setPosition(0, 0, 1);
	int DeliveryDrone_init(void *self)
	{
		DeliveryDrone *DeliveryDrone = self;
		return 1;
	}

	Drone DeliveryDroneProto = {
		.init = DeliveryDrone_init
	};

	DeliveryDrone* drones[NUM_DRONES];
int ch;int i,j=0;int num_of_drones;
printf("\x1b[34m Press 0 for level 0: 1 Drone\n\x1b[0m");
printf("\x1b[34m Press 1 for level 1A: 10 Drones No Avoidence\n\x1b[0m");
printf("\x1b[34m Press 2 for level 1B: 10 Drones Obsticle Avoidence\n\x1b[0m");
printf("\x1b[34m Press 3 for level 2: 10 Drones Obsticle and Drone Avoidence\n\x1b[0m");
printf("\x1b[31m Press ctrl+c to Exit\n\x1b[0m");


while(1){
scanf("%d", &ch);
make_map();
switch(ch){
	case 0:
		printf("\x1b[34m Level 0: 1 Drone\n\x1b[0m");
		num_of_drones=1;
		for(i=1;i<=num_of_drones;i++){
			drones[i] = new_drone(DeliveryDrone, &i);
			pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
		}
	break;

	case 1:
		printf("\x1b[34m Level 1A: 10 Drones No Avoidence\n\x1b[0m");
		num_of_drones=10; int rc;
		setPosition(0,10,1);
		setPosition(1,15,1);
		setPosition(15,5,1);
		for(i=1;i<=num_of_drones;i++){
			drones[i] = new_drone(DeliveryDrone, &i);
			pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
		}

	break;
	case 2:
	printf("\x1b[34m Level 1B: 10 Drones Obsticle Avoidence\n\x1b[0m");
	num_of_drones=10;
	setPosition(0,10,1);
	setPosition(1,15,1);
	setPosition(15,5,1);
	for(i=1;i<=num_of_drones;i++){
		drones[i] = new_drone(DeliveryDrone, &i);
		pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
	}
	break;
	case 3:
	printf("\x1b[34m Level 2: 10 Drones Obsticle and Drone Avoidence\n\x1b[0m");
	num_of_drones=1;
	for(i=1;i<=num_of_drones;i++){
		drones[i] = new_drone(DeliveryDrone, &i);
		pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
	}
	break;
	default:
	printf("\x1b[34m Press ctrl+c to Exit\n\x1b[0m");
	pthread_exit(NULL);
	break;
}
}


	pthread_exit(NULL);


	return(0);
}
