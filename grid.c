#include <stdio.h>

#define SIZE 15
#define WALL '#'
#define EMPTY ' '

char map[SIZE][SIZE];


void buildGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == 0 || i == SIZE-1 || j == 0 || j == SIZE-1)
                map[i][j] = WALL;   
            else
                map[i][j] = EMPTY;  
        }
    }
}


void printGrid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int main() {
    buildGrid();
    printGrid();
    return 0;
}
