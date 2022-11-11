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
    case 0:
        return "NO_DIR";
    case 1:
        return "EAST";
    case 2:
        return "NEAST";
    case 3:
        return "NORTH";
    case 4:
        return "NWEST";
    case -1:
        return "WEST";
    case -2:
        return "SWEST";
    case -3:
        return "SOUTH";
    case -4: 
        return "SEAST";
    default:
        return "ERROR";
    }
}
