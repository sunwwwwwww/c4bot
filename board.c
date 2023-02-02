#include <stdlib.h>
#include <stdio.h>
#include "board.h"

#define HEIGHT 6
#define WIDTH 7

// rows first, columns second
enum square board[HEIGHT][WIDTH];

void board_init() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void board_display() {
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (board[i][j])
            {
            case 'r':
                // colour to red
                printf("\033[0;31m");
                break;
            case 'y':
                // colour to yellow
                printf("\033[0;33m");
                break;
            default:
                // colour to white
                printf("\033[0;37m");
                break;
            }
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    // colour to white
    printf("\033[0;37m");
    printf("1 2 3 4 5 6 7\n");
}

// finds the lowest empty row in the given column
int find_lowest_empty_index(int column) {
    int row;
    for(row = 0;
        row < HEIGHT && board[row][column] == EMPTY;
        row++);
    return row-1;
}

void put_in_column(char put_red, int column) {
    int row = find_lowest_empty_index(column);
    if (put_red)
        board[row][column] = RED;
    else
        board[row][column] = YELLOW;
}

void board_bot_move(char as_red) {
    int column = rand()%7+1;
    if (as_red)
        put_in_column(0, column);
    else
        put_in_column(1, column);
}

void board_accept_input(char as_red) {
    printf("enter your move: ");

    // no, this can't be a character
    // don't ask me why idk either
    char move_str[1];

    scanf("%s", &move_str);
    int column = move_str[0] - 49;
    put_in_column(as_red, column);
}