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
#define PLAYER 'P'
#define TRAP_COUNT 10

char map[MAP_SIZE][MAP_SIZE];
int playerX = 1, playerY = 1;
int keysCollected = 0;
int health = 100;
int treasuresCollected = 0;

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
    map[playerX][playerY] = PLAYER;
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
            // remove trap after first contact
            trapX[i] = -1;
            trapY[i] = -1;
            return 1;
        }
    }
    return 0;
}

// --- Player movement with doors and traps ---
void movePlayer(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;

    if (map[newX][newY] == WALL) return;

    if (map[newX][newY] == KEY) {
        keysCollected++;
        printf("Picked up a key! Keys: %d\n", keysCollected);
    }

    if (map[newX][newY] == HEALTH) {
        health += 20;
        printf("Collected health pack! Health: %d\n", health);
    }

    if (map[newX][newY] == TREASURE) {
        treasuresCollected++;
        printf("Found a treasure! Total treasures: %d\n", treasuresCollected);
    }

    if (map[newX][newY] == DOOR) {
        if (keysCollected > 0) {
            keysCollected--;
            printf("Unlocked a door! Keys left: %d\n", keysCollected);
            map[newX][newY] = EMPTY;
        } else {
            printf("Door is locked! Need a key.\n");
            return;
        }
    }

    if (checkTrap(newX, newY)) {
        health -= 20;
        printf("Oh no! You stepped on a trap! Health: %d\n", health);
    }

    map[playerX][playerY] = EMPTY;
    playerX = newX;
    playerY = newY;
    map[playerX][playerY] = PLAYER;
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
    placeTraps(); // NEW STEP: hidden traps
    printGrid();

    char command;
    while (health > 0) {
        printf("Move (W/A/S/D): ");
        scanf(" %c", &command);

        if (command == 'W' || command == 'w') movePlayer(-1, 0);
        else if (command == 'S' || command == 's') movePlayer(1, 0);
        else if (command == 'A' || command == 'a') movePlayer(0, -1);
        else if (command == 'D' || command == 'd') movePlayer(0, 1);

        printGrid();
        printf("Health: %d | Keys: %d | Treasures: %d\n", health, keysCollected, treasuresCollected);
    }

    printf("Game Over! You ran out of health.\n");
    return 0;
}
