#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "position.h"
#include "square.h"

// rows first, columns second
position* pos = NULL;

// x and y are the directions (-1, 0 or 1)
// returns whether the given variables are a win
char square_won(int row, int column, int x, int y) {
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

void check_who_won() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            for (int k = -1; k < 2; k++) {
                for (int l = -1; l < 2; l++) {
                    if (k == 0 && l == 0)
                        continue;
                    if (square_won(i, j, k, l)) {
                        square winner = pos->board[i][j];
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

void board_init(square colour_to_play) {
    position_init(pos, colour_to_play);
}

void board_display() {
    position_print(pos);
}

void board_bot_move(square player_colour) {
    int column = rand()%7;
    position_put_in_column(pos, square_opposite_colour(player_colour), column);
    printf("the bot played: %d", column+1);
    check_who_won();
}

void board_accept_input(square player_colour) {
    printf("enter your move: ");
    // no, this can't be a character
    // don't ask me why idk either
    char move_str[1];
    scanf("%s", &move_str);
    int column = move_str[0] - 49;
    position_put_in_column(pos, player_colour, column);
    check_who_won();
}
