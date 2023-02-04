#ifndef POSITION_H
#define POSITION_H

#include "square.h"

#define HEIGHT 6
#define WIDTH 7

typedef struct node{
    char board[HEIGHT][WIDTH];

    // the colour which is to play now
    char colour_to_play;

    // array of other possible position nodes
    struct node* branches[7];
} position;

void position_init(position* pos, square colour);
void position_print(position* pos);
void position_put_in_column(position* pos, square piece, int column);

#endif