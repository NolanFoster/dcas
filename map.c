#include <dcas.h>
#include <stdio.h>
#include <map.h>
#include <pthread.h>
#include <stdlib.h>

int map [100][100] ;

void make_map();


void make_map(){
	int i=0;
	int j=0;
	for(i=0;i<100;i++){
		for(j =0;j<100;j++){
			map[i][j]==0;
		}
	}
	map[50][50] = 1024;

}

int getPosition(int x, int y){
	if(map[x][y]!=0){
		return 1;
	}
}

void setPosition(int x, int y, int val){
	pthread_mutex_unlock(&mapMutex);
	pthread_mutex_lock(&mapMutex);
	map[x][y] = val;
	pthread_mutex_unlock(&mapMutex);
}

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
