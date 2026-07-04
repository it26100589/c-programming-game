#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAP_SIZE 15
#define WALL '#'
#define EMPTY ' '
#define TREASURE 'T'
#define HEALTH 'H'
#define KEY 'K'

char map[MAP_SIZE][MAP_SIZE];

//initialize the grid with borders
void initializeGrid(){
	for(int i=0;i<MAP_SIZE;i++){
	   for(int j=0;j<MAP_SIZE;j++){
	       if(i==0||i==MAP_SIZE-1||j==0||j==MAP_SIZE-1){
		    map[i][j]=WALL; // border walls
		  }else{
		    map[i][j]=EMPTY; //empty space
		  }
	     }
	}
}

//place 30 random interior walls
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


//place 12 random treasures
void placeTreasures(){
   int placed =0;
   while(placed<12){
      int x=rand()%(MAP_SIZE-2)+1;
      int y=rand()%(MAP_SIZE-2)+1;

      if(map[x][y]==EMPTY){
	 map[x][y]=TREASURE;
	 placed++;
	}
     }
}

//place 5 random healthpacks
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

//place 3random keys
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


//print grid
void printGrid(){
     for(int i=0;i<MAP_SIZE;i++){
	for(int j=0;j<MAP_SIZE;j++){
           printf("%c",map[i][j]);
	  }
	  printf("\n");
       }
}


int main(){
	srand(time(NULL)); //seed random generator once here
		
	initializeGrid();	//create grid
	placeWalls();		 //add 30 walls
	placeTreasures();     //add 12 treasures
	placeHealthPacks();  //add 5 health packs
	placeKeys();	   //add 3 keys
	printGrid();	  //show final grid




       return 0;

}
