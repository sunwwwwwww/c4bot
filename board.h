#ifndef BOARD_H
#define BOARD_H

enum square {EMPTY = '.', RED = 'r', YELLOW = 'y'};
typedef enum square square;

void board_init();
void board_display();
void board_accept_input(char as_red);
void board_bot_move(char as_red);

#endif