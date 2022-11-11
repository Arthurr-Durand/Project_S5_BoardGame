#include <stdio.h>

#include "geometry.h"

const char* place_to_string(enum color_t c,enum sort_t s)
{
    if ((c < 0 || c > 3) || (s < 0 || s > 2))
        return "ERROR";
    char* colors[] = {"NO_COLOR", "BLACK", "WHITE", "MAX_COLOR"};
    char* sorts[] = {"NO_SORT", "PAWN", "MAX_SORT"};
    static char result[20];
    sprintf(result, "%s %s", colors[c], sorts[s]);
    return result;
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
