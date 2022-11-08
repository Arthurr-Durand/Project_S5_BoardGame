#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>

const char* place_to_string(enum color_t c,enum sort_t s)
{
    //à remplir 
        const char* t="bla";
    return t;
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



























int main(int agrc, char* argv[])
{
    printf("%s\n",dir_to_string(atoi(argv[1])));
    return 0; 
}