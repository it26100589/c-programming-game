#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 15
#define WALL '#'
#define EMPTY ' '

char map[MAP_SIZE][MAP_SIZE];

// Step 1: Initialize the grid with borders
void initializeGrid() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == 0 || i == MAP_SIZE - 1 || j == 0 || j == MAP_SIZE - 1) {
                map[i][j] = WALL;   // border walls
            } else {
                map[i][j] = EMPTY;  // empty space
            }
        }
    }
}

// Step 2: Place 30 random interior walls
void placeWalls(int count) {
    int placed = 0;
    while (placed < count) {
        int x = rand() % (MAP_SIZE - 2) + 1; // avoid borders
        int y = rand() % (MAP_SIZE - 2) + 1;

        if (map[x][y] == EMPTY) {
            map[x][y] = WALL;
            placed++;
        }
    }
}

// Print the grid
void printGrid() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // seed random generator
    initializeGrid();
    placeWalls(30);    // place 30 random walls
    printGrid();
    return 0;
}
