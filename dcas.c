	/*
	* Filename: dcas.c
	* Description: Driver for Drone Colision Avoidnce System
	* Author: Nolan Foster
	* Date Created: 10/7/15
	*/
	#include <ncurses.h>
	#include <unistd.h>
	#include <dcas.h>
	#include <stdio.h>
	#include <map.h>
	#define NUM_DRONES	10
	#define TASK 1
	#define DELAY 60000

	void draw_borders(WINDOW *screen) {
		int x, y, i;
		getmaxyx(screen, y, x);
		// 4 corners
		mvwprintw(screen, 0, 0, "+");
		mvwprintw(screen, y - 1, 0, "+");
		mvwprintw(screen, 0, x - 1, "+");
		mvwprintw(screen, y - 1, x - 1, "+");
		// sides
		for (i = 1; i < (y - 1); i++) {
			mvwprintw(screen, i, 0, "|");
			mvwprintw(screen, i, x - 1, "|");
		}
		// top and bottom
		for (i = 1; i < (x - 1); i++) {
			mvwprintw(screen, 0, i, "-");
			mvwprintw(screen, y - 1, i, "-");
		}
	}

	int main(int argc, char *argv[]) {

		pthread_mutex_init(&mapMutex, NULL);
		pthread_mutex_init(&deliveryMutex, NULL);
		pthread_t threads[NUM_DRONES];

	/*
	* Create new Proto Object For Delivery Drone
	*/
		int DeliveryDrone_init(void *self)
		{
			DeliveryDrone *DeliveryDrone = self;
			DeliveryDrone->x = 0;
			DeliveryDrone->y = 0;
			DeliveryDrone->xf=0;
			return 1;
		}

		Drone DeliveryDroneProto = {
			.init = DeliveryDrone_init
		};

		DeliveryDrone* drones[NUM_DRONES];
		make_map();

		printf("\x1b[32mMap \x1b[0m");
	/*
	* Boot all required drones
	*/
	int i;int j=0;
	for(i=1;i<=NUM_DRONES;i++){
		drones[i] = new_drone(DeliveryDrone, &i);
		pthread_create(&threads[i], NULL, drones[i]->_(boot), &drones[i]);
		}
	//
//	Loc* l;
//	l->self=drones[1];
//	l->x=10;
//	l->y=10;
	//pthread_create(&threads[1], NULL, drones[1]->_(navigate), (void *)l);

			int parent_x, parent_y;
			int x = 0, y = 0;
			int score_size = NUM_DRONES+3;
			int max_y = 0, max_x = 0;
			int next_x = 0;
			int direction = 1;
			initscr();
			noecho();
			curs_set(FALSE);

			getmaxyx(stdscr, max_y, max_x);
			// get our maximum window dimensions
			getmaxyx(stdscr, parent_y, parent_x);
			// set up initial windows
			WINDOW *field = newwin(parent_y - score_size, parent_x, 0, 0);
			WINDOW *score = newwin(score_size, parent_x, parent_y - score_size, 0);
	// draw to our windows
	mvwprintw(field, 0, 0, "CC");
	mvwprintw(score, 0, 0, "Console");
	// draw our borders
	draw_borders(field);
	draw_borders(score);
	// simulate the drone loop
	while(1) {
		// draw to our windows
		mvwprintw(field, 1, 1, "CC");
		mvwprintw(score, 1, 1, "Console");
		for(i=0; i<NUM_DRONES;i++){
			mvwprintw(score, 1+i, 1,  "Drone %d: ", i);
			mvwprintw(score, 1+i, 9,  "Booted");
		}


		// draw our borders
		draw_borders(field);
		draw_borders(score);
		for(i=0; i<100;i++){
			for(j=0;j<30;j++){
				int space =  get_position(i,j);

				switch (space){
					case 0:
					break;
					case 1:
						mvwprintw(field, j+1, i+1, "#");
					break;
					case 2:
						mvwprintw(field, j+1, i+1, "X"); // Print drone at the current xy position
					break;
					default:
					break;
				}
	}
	}
	  refresh();
	  usleep(DELAY);       // Shorter delay between movements
		next_x = x + direction;
	if (next_x >= max_x || next_x < 0) {
	direction*= -1;
	} else {
	x+= direction;
	}
		// refresh each window
		wrefresh(field);
		wrefresh(score);

		//clear display
		wclear(field);
		wclear(score);
	}
	// clean up
		delwin(field);
		delwin(score);


		pthread_exit(NULL);



		return(0);
	}
