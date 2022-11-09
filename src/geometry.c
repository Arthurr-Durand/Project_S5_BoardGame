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
    const char* D="No_dir";
    const char* E="East";
    const char* NE="Neast";
    const char* N="North";
    const char* NW="Nwest";
    const char* W="West";
    const char* SW="Swest";
    const char* S="South";
    const char* SE="Seast";
    switch (d)
    {
    case 0:
        return D;
    case 1:
        return E;
    case 2:
        return NE;
    case 3:
        return N;
    case 4:
        return NW;
    case -1:
        return W;
    case -2:
        return SW;
    case -3:
        return S;
    case -4: 
        return SE;
    
    default:
        return "pas compris";
    }    
}
