#ifndef POSITION_H
#define POSITION_H

#include "square.h"

#define HEIGHT 6
#define WIDTH 7

#define INF 1000000

typedef struct {
    char board[HEIGHT][WIDTH];
} position;

// ...don't ask
typedef struct {
    int eval;
    int column;
} eval_and_column;

square position_check_who_won(position* pos);
void position_put_in_column(position* pos, square piece, int column);
int position_eval(position* pos, square player_to_play);
eval_and_column position_minimax(position* pos, int depth, int alpha, int beta, square player_to_play);

#endif