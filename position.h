#ifndef POSITION_H
#define POSITION_H

#include "square.h"

#define HEIGHT 6
#define WIDTH 7

typedef struct {
    char board[HEIGHT][WIDTH];
} position;

square position_check_who_won(position* pos);
void position_put_in_column(position* pos, square piece, int column);
int position_eval(position* pos);

#endif