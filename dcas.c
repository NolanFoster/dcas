#include <dcas.h>
#include <stdio.h>
#include <map.h>
#define NUM_DRONES	100


int main(int argc, char *argv[]) {

	pthread_mutex_init(&mapMutex, NULL);
	pthread_mutex_init(&deliveryMutex, NULL);
	pthread_t threads[NUM_DRONES];

	make_map();
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
printf("\x1b[34m Press 0 for level 0\n\x1b[0m");
printf("\x1b[34m Press 1 for level 1A\n\x1b[0m");
printf("\x1b[34m Press 2 for level 1B\n\x1b[0m");
printf("\x1b[34m Press 3 for level 2\n\x1b[0m");
printf("\x1b[31m Press ctrl+c to Exit\n\x1b[0m");


while(1){
scanf("%d", &ch);
switch(ch){
	case 0:
		printf("\x1b[34m Level 0\n\x1b[0m");
		num_of_drones=1;
		for(i=1;i<=num_of_drones;i++){
			drones[i] = new_drone(DeliveryDrone, &i);
			pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
		}
	break;

	case 1:
		printf("\x1b[34m Level 1A\n\x1b[0m");
		num_of_drones=5; int rc;
		for(i=1;i<=num_of_drones;i++){
			drones[i] = new_drone(DeliveryDrone, &i);
			pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
		}


//	Assignment assign2;
//	assign2.self=&drones[2];
//	assign2.x=10;
//	assign2.y=6;
	//pthread_create(&threads[2], NULL, drones[2]->_(navigate), &assign2);
/*	int check=10;
	while(check!=10){
		printf("ERROR: return code %d\n", drones[1]->_(state)(&drones[1],1,0));
	for(i=1;i<num_of_drones;i++){
		if(drones[i]->_(state)(&drones[i],1,0)==1){
			printf("\x1b[34m Level 1A\n\x1b[0m");
			Assignment assign1;
			assign1.self=&drones[i];
			assign1.x=5;
			assign1.y=3;
			pthread_create(&threads[i], NULL, drones[i]->_(navigate), &assign1);
			check++;
		}
		}
	}*/
	break;
	case 2:
	printf("\x1b[34m Level 1B\n\x1b[0m");
	break;
	case 3:
	printf("\x1b[34m Level 2\n\x1b[0m");
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
