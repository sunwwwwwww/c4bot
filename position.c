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
// returns zero-indexed row
// returns -1 if the row is full
int position_find_lowest_empty_index(position* pos, int column) {
    int row;
    for(row = 0;
        row < HEIGHT && pos->board[row][column] == EMPTY;
        row++);
    return row-1;
}

// returns length of the sequence
// x and y is the direction
// row and column is the first square of the sequence
int get_sequence_length(position* pos, int row, int column, int x, int y) {
    square colour = pos->board[row][column];
    int length;
    square checking_colour = pos->board[row+y][column+x];
    for (length = 1; checking_colour == colour; length++) {
        int new_col = column + length * x;
        int new_row = row + length * y;
        if (new_col >= WIDTH || new_row >= HEIGHT)
            return length;
        if (new_col < 0 || new_row < 0)
            return length;
        checking_colour = pos->board[new_row][new_col];
    }
    return length;
}

int position_eval(position* pos, square player_to_play) {
    int eval = 0;
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
                if (adjacent_colour != EMPTY) {
                    int length = get_sequence_length(pos, row+y, column+x, x, y);
                    // -1 or 1 depending on what the adjacent colour is
                    // this is a funky way to do this I know
                    char coeff = adjacent_colour - 's';
                    coeff = (coeff < 0) - (coeff > 0);
                    if (length == 4) {
                        eval += (INF/1000) * coeff;
                        continue;
                    }
                    eval += length * length * coeff;
                }
            }
        }
    }
    return eval;
}

// returns the colour which won
// returns 0 if no one won
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

// in-depth analysis

// eval_and_column position_minimax(position* pos, int depth, int alpha, int beta, square player_to_play) {
//     for (int j = 0; j < 2 - depth; j++) printf("\t");
//     printf("entered depth %d:\n", depth);
//     if (depth == 0 || position_check_who_won(pos)) {
//         int eval = position_eval(pos, player_to_play);
//         for (int j = 0; j < 2 - depth; j++) printf("\t");
//         printf("returning static eval of %d\n", eval);
//         return (eval_and_column) {eval, 0};
//     }
    
//     if (player_to_play == RED) {
//         int maxeval = -INF-1;
//         int column = 0;
//         for (int i = 0; i < 7; i++) {
//             for (int j = 0; j < 2 - depth; j++) printf("\t");
//             printf("checking column %d\n", i);
//             position temp = *pos;
//             position_put_in_column(&temp, player_to_play, i);
//             int eval = position_minimax(&temp, depth-1, alpha, beta, YELLOW).eval;
//             if (maxeval < eval) {
//                 maxeval = eval;
//                 column = i;
//             }
//             maxeval = fmax(maxeval, eval);
//             alpha = fmax(alpha, eval);
//             if (beta <= alpha)
//                 break;
//         }
//         for (int j = 0; j < 2 - depth; j++) printf("\t");
//         printf("returning eval of %d\n", maxeval);
//         return (eval_and_column) {maxeval, column};
//     } else {
//         int mineval = INF+1;
//         int column = 0;
//         for (int i = 0; i < 7; i++) {
//             for (int j = 0; j < 2 - depth; j++) printf("\t");
//             printf("checking column %d\n", i);
//             position temp = *pos;
//             position_put_in_column(&temp, player_to_play, i);
//             int eval = position_minimax(&temp, depth-1, alpha, beta, RED).eval;
//             if (mineval > eval) {
//                 mineval = eval;
//                 column = i;
//             }
//             alpha = fmin(alpha, eval);
//             if (beta <= alpha)
//                 break;
//         }
//         for (int j = 0; j < 2 - depth; j++) printf("\t");
//         printf("returning eval of %d\n", mineval);
//         return (eval_and_column) {mineval, column};
//     }
// }

eval_and_column position_minimax(position* pos, int depth, int alpha, int beta, square player_to_play) {
    if (depth == 0 || position_check_who_won(pos)) {
        int eval = position_eval(pos, player_to_play);
        return (eval_and_column) {eval, 0};
    }
    
    if (player_to_play == RED) {
        int maxeval = -INF-1;
        int column = 0;
        for (int i = 0; i < 7; i++) {
            position temp = *pos;
            if (position_find_lowest_empty_index(pos, i) == -1)
                continue;
            position_put_in_column(&temp, player_to_play, i);
            int eval = position_minimax(&temp, depth-1, alpha, beta, YELLOW).eval;
            if (maxeval < eval) {
                maxeval = eval;
                column = i;
            }
            maxeval = fmax(maxeval, eval);
            alpha = fmax(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return (eval_and_column) {maxeval, column};
    } else {
        int mineval = INF+1;
        int column = 0;
        for (int i = 0; i < 7; i++) {
            position temp = *pos;
            if (position_find_lowest_empty_index(pos, i) == -1)
                continue;
            position_put_in_column(&temp, player_to_play, i);
            int eval = position_minimax(&temp, depth-1, alpha, beta, RED).eval;
            if (mineval > eval) {
                mineval = eval;
                column = i;
            }
            alpha = fmin(alpha, eval);
            if (beta <= alpha)
                break;
        }
        return (eval_and_column) {mineval, column};
    }
}