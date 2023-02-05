#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "square.h"
#include "position.h"

// x and y are the directions (-1, 0 or 1)
// returns whether the given variables are a win
char position_square_won(position* pos, int row, int column, int x, int y) {
    square colour = pos->board[row][column];
    if (colour == EMPTY)
        return 0;
    for (int k = 1; k < 4; k++) {
        if (row + y*k < 0 || column + x*k < 0
            || row + y*k >= HEIGHT || column + x*k >= WIDTH) {
            return 0;
        }
        if (colour != pos->board[row + y*k][column + x*k])
            return 0;
    }
    return 1;
}

// finds the lowest empty row in the given column
int position_find_lowest_empty_index(position* pos, int column) {
    int row;
    for(row = 0;
        row < HEIGHT && pos->board[row][column] == EMPTY;
        row++);
    return row-1;
}

int get_sequence_length(position* pos, int row, int column, int x, int y) {
    square colour = pos->board[row][column];
    int length;
    square checking_colour = pos->board[row+y][column+x];
    for (length = 1; checking_colour == colour; length++) {
        if (column + length * x >= WIDTH || row + length * y >= HEIGHT)
            return length-1;
        checking_colour = pos->board[row + length*y][column + length*x];
    }
    return length;
}

int position_eval(position* pos) {
    int eval = 0;
    // looping through all the columns
    for (int column = 0; column < WIDTH; column ++) {
        int row = position_find_lowest_empty_index(pos, column);
        if (row < 0)
            continue;
        for (int x = -1; x < 2; x++) {
            for (int y = -1; y < 2; y++) {
                if (x == 0 && y == 0)
                    continue;
                if (x == 0 && y == -1)
                    continue;
                if (row+y >= HEIGHT || row+y < 0)
                    continue;
                if (column+x >= WIDTH || column+x < 0)
                    continue;
                square adjacent_colour = pos->board[row+y][column+x];
                if (adjacent_colour == RED) {
                    int length = get_sequence_length(pos, row+y, column+x, x, y);
                    eval += length * length;
                }
                if (adjacent_colour == YELLOW) {
                    int length = get_sequence_length(pos, row+y, column+x, x, y);
                    eval -= length * length;
                }
            }
        }
    }
    return eval;
}

// returns the colour which won
square position_check_who_won(position* pos) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (pos->board[i][j] == EMPTY)
                continue;
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    if (k == 0 && l == 0)
                        continue;
                    if (position_square_won(pos, i, j, k, l)) {
                        return pos->board[i][j];
                    }
                }
            }
        }
    }
    return 0;
}

void position_put_in_column(position* pos, square piece, int column) {
    int row = position_find_lowest_empty_index(pos, column);
    pos->board[row][column] = piece;
}