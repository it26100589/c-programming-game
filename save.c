#include<stdio.h>
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

// --- Save system ---
void saveGame(const char *filename, int playerCount) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("Error saving game!\n"); return; }

    // Save map
    for (int i=0;i<MAP_SIZE;i++) {
        for (int j=0;j<MAP_SIZE;j++) {
            fputc(map[i][j], f);
        }
        fputc('\n', f);
    }

    // Save players
    fprintf(f, "%d\n", playerCount);
    for (int i=0;i<playerCount;i++) {
        fprintf(f, "%c %d %d %d %d %d\n",
            players[i].symbol, players[i].x, players[i].y,
            players[i].hp, players[i].score, players[i].keys);
    }

    // Save traps
    for (int i=0;i<TRAP_COUNT;i++) {
        fprintf(f, "%d %d\n", trapX[i], trapY[i]);
    }

    fclose(f);
    printf("Game saved to %s\n", filename);
}

// --- Load system ---
void loadGame(const char *filename, int *playerCount) {
    FILE *f = fopen(filename, "r");
    if (!f) { printf("Error loading game!\n"); return; }

    // Load map
    for (int i=0;i<MAP_SIZE;i++) {
        for (int j=0;j<MAP_SIZE;j++) {
            char c = fgetc(f);
            if (c=='\n') c=fgetc(f);
            map[i][j] = c;
        }
    }

    // Load players
    fscanf(f, "%d", playerCount);
    for (int i=0;i<*playerCount;i++) {
        fscanf(f, " %c %d %d %d %d %d",
            &players[i].symbol, &players[i].x, &players[i].y,
            &players[i].hp, &players[i].score, &players[i].keys);
    }

    // Load traps
    for (int i=0;i<TRAP_COUNT;i++) {
        fscanf(f, "%d %d", &trapX[i], &trapY[i]);
    }

    fclose(f);
    printf("Game loaded from %s\n", filename);
}

// --- Example main to test save/load ---
int main() {
    srand(time(NULL));

    // Normally you would initialize and place items here
    // For demo, just set one player
    players[0] = (Player){1,1,100,0,0,PLAYER1};
    map[1][1] = PLAYER1;

    // Save game
    saveGame("save.txt", 1);

    // Reset player and reload
    players[0].hp = 50;
    int count;
    loadGame("save.txt", &count);

    printf("After load: Player %c HP=%d Score=%d Keys=%d\n",
           players[0].symbol, players[0].hp, players[0].score, players[0].keys);

    return 0;
}
