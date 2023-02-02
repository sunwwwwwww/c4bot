#ifndef BOARD_H
#define BOARD_H

enum square {EMPTY = '.', RED = 'r', YELLOW = 'y'};

void board_init();
void board_display();

#endif