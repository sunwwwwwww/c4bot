#ifndef SQUARE_H
#define SQUARE_H

enum square {EMPTY = '.', RED = 'r', YELLOW = 'y'};
typedef enum square square;

square square_opposite_colour(square colour);

#endif