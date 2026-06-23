#include<stdlib.h>
#include<time.h>

#define MAP_SIZE 15
#define WALL '#'
#define EMPTY' '

extern char map[MAP_SIZE][MAP_SIZE];

  void placeWalls(){
	  int placed =0;
	  srand(time(NULL));

   while (placed<30){
	   int x =rand()%(MAP_SIZE-2)+1;
	   int y =rand()%(MAP_SIZE-2)+1;

    if(map[x][y] ==EMPTY){
	    map[x][y] =WALL;
	    placed++;

          }
     }
 
 }
