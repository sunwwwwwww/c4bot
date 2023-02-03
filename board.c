#include <stdlib.h>
#include <stdio.h>
#include "board.h"

#define HEIGHT 6
#define WIDTH 7

// rows first, columns second
square board[HEIGHT][WIDTH];

// x and y are the directions (-1, 0 or 1)
// returns whether the given variables are a win
char square_won(int row, int column, int x, int y) {
    square colour = board[row][column];
    if (colour == EMPTY)
        return 0;
    for (int k = 1; k < 4; k++) {
        if (row + y*k < 0 || column + x*k < 0
            || row + y*k >= HEIGHT || column + x*k >= WIDTH) {
            return 0;
        }
        if (colour != board[row + y*k][column + x*k])
            return 0;
    }
    return 1;
}

// finds the lowest empty row in the given column
int find_lowest_empty_index(int column) {
    int row;
    for(row = 0;
        row < HEIGHT && board[row][column] == EMPTY;
        row++);
    return row-1;
}

// returns the colour which won
void check_who_won() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    if (k == 0 && l == 0)
                        continue;
                    if (square_won(i, j, k, l)) {
                        square winner =  board[i][j];
                        // green
                        printf("\033[0;32m");
                        printf("%c won!", winner);
                        // white
                        printf("\033[0;37m");
                        exit(0);
                    }
                }
            }
        }
    }
}

void put_in_column(square piece, int column) {
    int row = find_lowest_empty_index(column);
    board[row][column] = piece;
}

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
                // red
                printf("\033[0;31m");
                break;
            case 'y':
                // yellow
                printf("\033[0;33m");
                break;
            default:
                // white
                printf("\033[0;37m");
                break;
            }
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    // white
    printf("\033[0;37m");
    printf("1 2 3 4 5 6 7\n");
    check_who_won();
}

void board_bot_move(char as_red) {
    int column = rand()%7+1;
    if (as_red) put_in_column(YELLOW, column);
    else put_in_column(RED, column);
}

void board_accept_input(char as_red) {
    printf("enter your move: ");

    // no, this can't be a character
    // don't ask me why idk either
    char move_str[1];

    scanf("%s", &move_str);
    int column = move_str[0] - 49;
    if (as_red) put_in_column(RED, column);
    else put_in_column(YELLOW, column);
}