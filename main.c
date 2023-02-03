#include <stdio.h>
#include <stdlib.h>
#include "board.h"

// #define AS_RED

int main() {
    board_init();
    while (1) {
        board_display();
        #ifdef AS_RED
            board_accept_input(1);
            board_bot_move(1);
        #else
            board_accept_input(0);
            board_bot_move(0);
        #endif
    }
    return 0;
}