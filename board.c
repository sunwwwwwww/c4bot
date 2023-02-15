#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "square.h"
#include "position.h"

#define DEPTH 8

// rows first, columns second
position current_pos;

// initializes the board (all squares empty)
void board_init() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            current_pos.board[i][j] = EMPTY;
        }
    }
}

void board_display() {
    printf("\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (current_pos.board[i][j])
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
            printf("%c ", current_pos.board[i][j]);
        }
        printf("\n");
    }
    // white
    printf("\033[0;37m");
    printf("1 2 3 4 5 6 7\n");
}

void board_bot_move(square player_colour) {
    square bot_colour = square_opposite_colour(player_colour);
    int column = position_minimax(&current_pos, DEPTH, -INF, INF, bot_colour).column;
    position_put_in_column(&current_pos, bot_colour, column);
    printf("bot played: %d", column+1);
    square winner = position_check_who_won(&current_pos);
    if (!winner)
        return;
    board_display();
    // green
    printf("\033[0;32m");
    printf("%c won!", winner);
    // white
    printf("\033[0;37m");
    exit(0);
}

void board_accept_input(square player_colour) {
    printf("\nenter your move: ");

    // no, this can't be a character
    // don't ask me why idk either
    char move_str[1];

    scanf("%s", &move_str);
    int column = move_str[0] - '1';
    if (column < 0) {
        printf("that column is filled!\nenter another move:");
        board_accept_input(player_colour);
    } else {
        position_put_in_column(&current_pos, player_colour, column);
    }
    square winner = position_check_who_won(&current_pos);
    if (!winner)
        return;
    board_display();
    // green
    printf("\033[0;32m");
    printf("%c won!", winner);
    // white
    printf("\033[0;37m");
    exit(0);
}