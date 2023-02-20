#include "square.h"

square square_opposite_colour(square colour) {
    if (colour == RED) return YELLOW;
    if (colour == YELLOW) return RED;
}
