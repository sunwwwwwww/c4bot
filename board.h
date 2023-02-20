#ifndef BOARD_H
#define BOARD_H

#include "square.h"

void board_init();
void board_display();
void board_accept_input(square player_colour);
void board_bot_move(square player_colour);

#endif