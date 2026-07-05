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

// Player stats
typedef struct {
    int x, y;
    int hp;
    int score;
    int keys;
    char symbol;
} Player;

Player players[3]; // up to 3 players

// Arrays to store hidden trap positions
int trapX[TRAP_COUNT];
int trapY[TRAP_COUNT];

// --- Grid setup ---
void initializeGrid() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1)
                map[i][j] = WALL;
            else
                map[i][j] = EMPTY;
        }
    }
}

void placeWalls() {
    int placed = 0;
    while (placed < 30) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            map[x][y] = WALL;
            placed++;
        }
    }
}

void placeTreasures() {
    int placed = 0;
    while (placed < 12) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            map[x][y] = TREASURE;
            placed++;
        }
    }
}

void placeHealthPacks() {
    int placed = 0;
    while (placed < 5) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            map[x][y] = HEALTH;
            placed++;
        }
    }
}

void placeKeys() {
    int placed = 0;
    while (placed < 3) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            map[x][y] = KEY;
            placed++;
        }
    }
}

void placeDoors() {
    int placed = 0;
    while (placed < 3) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            map[x][y] = DOOR;
            placed++;
        }
    }
}

// --- Hidden traps ---
void placeTraps() {
    int placed = 0;
    while (placed < TRAP_COUNT) {
        int x = rand() % (MAP_SIZE - 2) + 1;
        int y = rand() % (MAP_SIZE - 2) + 1;
        if (map[x][y] == EMPTY) {
            trapX[placed] = x;
            trapY[placed] = y;
            placed++;
        }
    }
}

int checkTrap(int x, int y) {
    for (int i = 0; i < TRAP_COUNT; i++) {
        if (trapX[i] == x && trapY[i] == y) {
            trapX[i] = -1; // remove trap after first contact
            trapY[i] = -1;
            return 1;
        }
    }
    return 0;
}

// --- Place players randomly ---
void placePlayers(int count) {
    for (int i = 0; i < count; i++) {
        int placed = 0;
        while (!placed) {
            int x = rand() % (MAP_SIZE - 2) + 1;
            int y = rand() % (MAP_SIZE - 2) + 1;
            if (map[x][y] == EMPTY) {
                players[i].x = x;
                players[i].y = y;
                players[i].hp = 100;
                players[i].score = 0;
                players[i].keys = 0;
                players[i].symbol = (i == 0 ? PLAYER1 : (i == 1 ? PLAYER2 : PLAYER3));
                map[x][y] = players[i].symbol;
                placed = 1;
            }
        }
    }
}

void printGrid() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    initializeGrid();
    placeWalls();
    placeTreasures();
    placeHealthPacks();
    placeKeys();
    placeDoors();
    placeTraps();
    placePlayers(3); // place 1–3 players
    printGrid();

    // Show player stats
    for (int i = 0; i < 3; i++) {
        printf("Player %c -> HP: %d | Score: %d | Keys: %d\n",
               players[i].symbol, players[i].hp, players[i].score, players[i].keys);
    }

    return 0;
}
