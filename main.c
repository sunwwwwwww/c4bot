#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "square.h"

#define PLAYER_COLOUR YELLOW

int main() {
    board_init();
    while (1) {
        board_display();
        board_accept_input(PLAYER_COLOUR);
        board_bot_move(PLAYER_COLOUR);
    }
    return 0;
}