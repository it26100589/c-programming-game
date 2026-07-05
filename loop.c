#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 15
#define WALL '#'
#define EMPTY ' '
#define TREASURE 'T'
#define HEALTH 'H'
#define KEY 'K'
#define DOOR 'D'
#define PLAYER1 '1'
#define PLAYER2 '2'
#define PLAYER3 '3'
#define TRAP_COUNT 10

char map[MAP_SIZE][MAP_SIZE];

typedef struct {
    int x, y;
    int hp;
    int score;
    int keys;
    char symbol;
} Player;

Player players[3];
int trapX[TRAP_COUNT], trapY[TRAP_COUNT];

// --- Setup ---
void initializeGrid() {
    for (int i=0;i<MAP_SIZE;i++)
        for (int j=0;j<MAP_SIZE;j++)
            map[i][j] = (i==0||i==MAP_SIZE-1||j==0||j==MAP_SIZE-1) ? WALL : EMPTY;
}

void placeRandom(char tile,int count){
    int placed=0;
    while(placed<count){
        int x=rand()%(MAP_SIZE-2)+1, y=rand()%(MAP_SIZE-2)+1;
        if(map[x][y]==EMPTY){map[x][y]=tile;placed++;}}
}

void placeTraps(){
    int placed=0;
    while(placed<TRAP_COUNT){
        int x=rand()%(MAP_SIZE-2)+1, y=rand()%(MAP_SIZE-2)+1;
        if(map[x][y]==EMPTY){trapX[placed]=x;trapY[placed]=y;placed++;}}
}

int checkTrap(int x,int y){
    for(int i=0;i<TRAP_COUNT;i++)
        if(trapX[i]==x&&trapY[i]==y){trapX[i]=-1;trapY[i]=-1;return 1;}
    return 0;
}

void placePlayers(int count){
    for(int i=0;i<count;i++){
        int placed=0;
        while(!placed){
            int x=rand()%(MAP_SIZE-2)+1,y=rand()%(MAP_SIZE-2)+1;
            if(map[x][y]==EMPTY){
                players[i]=(Player){x,y,100,0,0,(i==0?PLAYER1:(i==1?PLAYER2:PLAYER3))};
                map[x][y]=players[i].symbol;placed=1;
            }
        }
    }
}

// --- Movement + effects ---
void movePlayer(Player *p,char cmd){
    int dx=0,dy=0;
    if(cmd=='W'||cmd=='w')dx=-1;
    else if(cmd=='S'||cmd=='s')dx=1;
    else if(cmd=='A'||cmd=='a')dy=-1;
    else if(cmd=='D'||cmd=='d')dy=1;
    else return;

    int nx=p->x+dx, ny=p->y+dy;
    if(map[nx][ny]==WALL) return;

    if(checkTrap(nx,ny)){p->hp-=20;printf("Player %c hit trap! HP=%d\n",p->symbol,p->hp);}
    if(map[nx][ny]==TREASURE){p->score+=10;map[nx][ny]=EMPTY;printf("Player %c got treasure! Score=%d\n",p->symbol,p->score);}
    if(map[nx][ny]==HEALTH){p->hp+=20;map[nx][ny]=EMPTY;printf("Player %c got health! HP=%d\n",p->symbol,p->hp);}
    if(map[nx][ny]==KEY){p->keys++;map[nx][ny]=EMPTY;printf("Player %c got key! Keys=%d\n",p->symbol,p->keys);}
    if(map[nx][ny]==DOOR){
    if(p->keys>0){p->keys--;map[nx][ny]=EMPTY;printf("Player %c opened door! Keys=%d\n",p->symbol,p->keys);}
        else{                                                                                                                                                                   printf("Player %c needs a key!\n",p->symbol);                                                                                                                                return;}
    }

    map[p->x][p->y]=EMPTY;
    p->x=nx;p->y=ny;
    map[p->x][p->y]=p->symbol;
}

// --- Print ---
void printGrid(){
    for(int i=0;i<MAP_SIZE;i++){for(int j=0;j<MAP_SIZE;j++)printf("%c ",map[i][j]);printf("\n");}
}
void printStats(int count){
    for(int i=0;i<count;i++)
        printf("Player %c -> HP:%d Score:%d Keys:%d\n",players[i].symbol,players[i].hp,players[i].score,players[i].keys);
}

// --- Main game loop (no end conditions) ---
int main(){
    srand(time(NULL));
    initializeGrid();
    placeRandom(WALL,30);
    placeRandom(TREASURE,12);
    placeRandom(HEALTH,5);
    placeRandom(KEY,3);
    placeRandom(DOOR,3);
    placeTraps();
    placePlayers(3);

    while(1){
        printGrid();printStats(3);

        for(int i=0;i<3;i++){
            if(players[i].hp<=0)continue;
            printf("Player %c moves (up to 4 WASD): ",players[i].symbol);
            for(int m=0;m<4;m++){
                char c;scanf(" %c",&c);
                movePlayer(&players[i],c);
                if(players[i].hp<=0){printf("Player %c died!\n",players[i].symbol);break;}
            }
        }
    }
    return 0;
}
