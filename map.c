/*
* Filename: map.c
* Description: Tracks Drone locations and static objects
* Author: Nolan Foster
* Date Created: 10/7/15
*/

#include <map.h>
#include <dcas.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>


int *map [100][100];

void make_map();

/*
* Make Map
* Description: Creates static map(2D Array)
*/
void make_map(){
	int i,j=0;
	for(i=0;i<50;i++){
		for(j =0;j<50;j++){
			*map[i][j]==1;
		}
	}
	map[50][50] = 1024;

}

/*
* Print Map
* Description: Prints map if not being used
*/
void print_map(){
	pthread_mutex_lock(&mapMutex);
	int i,j=0;
	printf("\033[2J\033[1;1H");
	for(i=0;i<25;i++){
		for(j=0;j<50;j++){
			if(map[i][j]!=0)
				printf("\x1b[31m%d\x1b[0m",map[i][j]);
			else
			 printf("%d",map[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&mapMutex);
}
/*
* Get Position
* Input: int x, int y
* Output: 0-Empty, 1- Occupied
* Description: Checks if position is clear
*/
int get_position(int x, int y){
		return map[x][y];
}

/*
* Set Position
* Input: int x, int y, int val
* Description: Sets new positon on the map
*/
void setPosition(int x, int y, int val){
	pthread_mutex_lock(&mapMutex);
	//if((x==0&&y==0)||map[x][y]==0||val==0)
		map[x][y] = val;
	pthread_mutex_unlock(&mapMutex);
}

/*
* Pos

* Input: int x
* Description: Finds all objects on map
*/
void Pos(int x){
	int i=0;
	pthread_mutex_unlock(&mapMutex);
	pthread_mutex_lock(&mapMutex);
	int done = 0;
	int j=0;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){
			if(map[i][j]==x){
				printf("%d", i);
				printf(" ,");
				printf("%d", j);
				done = 1;
				pthread_mutex_unlock(&mapMutex);
				break;
			}
		}
		if(done==1){
			pthread_mutex_unlock(&mapMutex);
			break;
		}
	}
}
