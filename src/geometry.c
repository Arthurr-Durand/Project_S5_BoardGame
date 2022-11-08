#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char* place_to_string(enum color_t c,enum sort_t s)
{
    const char* T="";
    const char* S="";
    char P[100];
    switch (c)
    {
    case 0:
        T="No color";
        break;
    case 1:
        T="Black";
        break;
    case 2:
        T="White";
        break;
    
    default:
        return "Pas compris";
    }
    strcpy(P,T);
     switch (s)
    {
    case 0:
         S="Nothing en";
         break;
    case 1:
        S="Pawn en";
        break;
    default:
        return "Pas compris";
    }
    const char* R=strcat(S,P);
    return R;
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


























/*
int main(int agrc, char* argv[])
{
    printf("%s\n",place_to_string(atoi(argv[1]),atoi(argv[2])));
    return 0; 
}
*/
