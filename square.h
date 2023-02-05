#ifndef SQUARE_H
#define SQUARE_H

#include <stdlib.h>

enum square {EMPTY = '.', RED = 'r', YELLOW = 'y'};

// these shenanigans are because enums are integers and you can't change that
// except if you do this, in which case square now means a char
// use enum square to refer to the enum itself
typedef char square;

square square_opposite_colour(square colour);
#endif