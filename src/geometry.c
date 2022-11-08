#include "geometry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char* place_to_string(enum color_t c,enum sort_t s)
{
    if (s==0 && c==0){
        return "No color and no pawn";
    }
    if (s==1 && c==0){
        return "Pawn and no color";
    }
      if (s==0 && c==1){
        return "Black and no pawn";
    }
      if (s==0 && c==2){
        return "White and no pawn";
    }
      if (s==1 && c==1){
        return "Pawn and Black";
    }
      if (s==1 && c==2){
        return "Pawn and white";
    }
    else {
        return "pas compris";
    }
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
