#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAP_SIZE 15
#define WALL '#'
#define EMPTY ' '
#define TREASURE 'T'
#define HEALTH 'H'
#define KEY 'K'
#define DOOR 'D'

char map[MAP_SIZE][MAP_SIZE];

void intializeGrid(){
   for(int i=0;i<MAP_SIZE;i++){
       for(int j=0;j<MAP_SIZE;j++){
	   if(i==0||i==MAP_SIZE-1||j==0||j==MAP_SIZE-1)
             map[i][j]=WALL;
          else
	     map[i][j]=EMPTY;
       }
   }
}


void placeWalls(){
	int placed=0;
	while(placed<30){
	  int x=rand()%(MAP_SIZE-2)+1;
	  int y=rand()%(MAP_SIZE-2)+1;
	  if(map[x][y]==EMPTY){
		  map[x][y]=WALL;
		  placed++;
		 }
	  }
}

void placeTreasures(){
	int placed=0;
        while(placed<12){
	       int x=rand()%(MAP_SIZE-2)+1;
	       int y=rand()%(MAP_SIZE-2)+1;
	       if(map[x][y]==EMPTY){
		       map[x][y]=TREASURE;
		       placed++;
		      }
	}
}

void placeHealthPacks(){
	int placed=0;
	while(placed<5){
		int x=rand()%(MAP_SIZE-2)+1;
		int y=rand()%(MAP_SIZE-2)+1;
		if(map[x][y]==EMPTY){
			map[x][y]=HEALTH;
			placed++;
		       }
	    }
}



void placeKeys(){
	int placed=0;
	while(placed<3){
		int x=rand()%(MAP_SIZE-2)+1;
		int y=rand()%(MAP_SIZE-2)+1;
		if(map[x][y]==EMPTY){
			map[x][y]=KEY;
			placed++;
		       }
	    }
}


void placeDoors(){
	int placed=0;
	while(placed<3){
		int x=rand()%(MAP_SIZE-2)+1;
		int y=rand()%(MAP_SIZE-2)+1;
		if(map[x][y]==EMPTY){
			map[x][y]=DOOR;
			placed++;
		       }
	     }
}


void printGrid(){
	for(int i=0;i<MAP_SIZE;i++){
		for(int j=0;j<MAP_SIZE;j++){
		printf("%C",map[i][j]);
	      }
	      printf("\n");
	    }
}

int main(){
	srand(time(NULL));

	intializeGrid();
	placeWalls();
	placeTreasures();
	placeHealthPacks();
	placeKeys();
	placeDoors();
	printGrid();

	return 0;


}

	       


