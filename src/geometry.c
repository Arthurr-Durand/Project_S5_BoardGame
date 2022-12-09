#include <stdio.h>

#include "geometry.h"

static const char* place_strings[MAX_SORT][MAX_COLOR] = {{"NO_COLOR NO_SORT", "BLACK NO_SORT", "WHITE NO_SORT"},
                                                    {"NO_COLOR PAWN", "BLACK PAWN", "WHITE PAWN"}};

const char* place_to_string(enum color_t c, enum sort_t s)
{
    if ((c < 0 || c >= MAX_COLOR) || (s < 0 || s >= MAX_SORT))
        return "ERROR";
    return place_strings[(s!=NO_SORT)][c];
}

const char* dir_to_string(enum dir_t d)
{
    switch (d) {
        case NO_DIR:
            return "NO_DIR";
        case EAST:
            return "EAST";
        case NEAST:
            return "NEAST";
        case NORTH:
            return "NORTH";
        case NWEST:
            return "NWEST";
        case WEST:
            return "WEST";
        case SWEST:
            return "SWEST";
        case SOUTH:
            return "SOUTH";
        case SEAST: 
            return "SEAST";
        default:
            return "ERROR";
    }
}
