#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "square.h"

#define PLAYER_COLOUR RED

int main() {
    board_init(PLAYER_COLOUR);
    while (1) {
        board_display();
        board_accept_input(PLAYER_COLOUR);
        board_bot_move(PLAYER_COLOUR);
    }
    return 0;
}