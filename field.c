#include "dcas.h"
#include <stdio.h>
#include "field.h"
#include <pthread.h>
#include <stdlib.h>
//	Field is 100 x 100
//	Control Center is at 0,0
//	0 means position (x,y) is unoccupied
//	1 means position (x,y) is occupied


int field [100][100] ;

void makeField();


void makeField(){
	int i=0;
	int j=0;
	for(i=0;i<100;i++){
		for(j =0;j<100;j++){
			field[i][j]==0;
		}
	}
	field[50][50] = 1024;

}

int getPosition(int x, int y){
	if(field[x][y]!=0){
		return 1;
	}
}

void setPosition(int x, int y, int val){
	pthread_mutex_unlock(&fieldMutex);
	pthread_mutex_lock(&fieldMutex);
	field[x][y] = val;
	pthread_mutex_unlock(&fieldMutex);
}

void Pos(int x){
	int i=0;
	pthread_mutex_unlock(&fieldMutex);
	pthread_mutex_lock(&fieldMutex);
	int done = 0;
	int j=0;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){
			if(field[i][j]==x){
				printf("%d", i);
				printf(" ,");
				printf("%d", j);
				done = 1;
				pthread_mutex_unlock(&fieldMutex);
				break;
			}
		}
		if(done==1){
			pthread_mutex_unlock(&fieldMutex);
			break;
		}
	}
}
