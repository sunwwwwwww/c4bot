#include <stdlib.h>
#include <stdio.h>
#include "position.h"
#include "square.h"

// pos = the pointer to the position to initialize
// colour = the colour of the player which WILL move in this position
void position_init(position* pos, square colour) {
    pos = malloc(sizeof(position));
    pos->colour_to_play = colour;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            pos->board[i][j] = EMPTY;
        }
    }
}

void position_print(position* pos) {
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (pos->board[i][j])
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
                printf(". ");
                goto next;
            }
            printf("%c ", pos->board[i][j]);
            next:
        }
        printf("\n");
    }
    // white
    printf("\033[0;37m");
    printf("1 2 3 4 5 6 7\n");
}

// finds the lowest empty row in the given column
int position_find_lowest_empty_index(position* pos, int column) {
    int row;
    for(row = 0;
        row < HEIGHT && pos->board[row][column] == EMPTY;
        row++);
    return row-1;
}

// piece is the kind of piece to put in the column
// column is the column number to put the piece in (0-6)
void position_put_in_column(position* pos, square piece, int column) {
    int row = position_find_lowest_empty_index(pos, column);
    pos->board[row][column] = piece;
}

void position_generate_branches(position* pos) {
    for (int i = 0; i < WIDTH; i++) {
        position* curr_branch = pos->branches[i];
        position_init(curr_branch, square_opposite_colour(pos->colour_to_play));
        position_put_in_column(curr_branch, (square) curr_branch->colour_to_play, i);
    }
}