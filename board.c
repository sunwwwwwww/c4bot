#include <stdlib.h>
#include <stdio.h>
#include "board.h"

#define NO_OF_ROWS 6
#define NO_OF_COLUMNS 7

// 7 vertical columns, 6 horizontal rows
enum square board[NO_OF_ROWS][NO_OF_COLUMNS];

void board_init() {
    for (int i = 0; i < NO_OF_ROWS; i++) {
        for (int j = 0; j < NO_OF_COLUMNS; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void board_display() {
    for (int i = 0; i < NO_OF_ROWS; i++) {
        for (int j = 0; j < NO_OF_COLUMNS; j++) {
            switch (board[i][j])
            {
            case 'r':
                // colour to red
                printf("\033[0;31m");
                break;
            case 'y':
                // color to yellow
                printf("\033[0;33m");
                break;
            default:
                printf("\033[0;37m");
                break;
            }
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("1 2 3 4 5 6 7");
}