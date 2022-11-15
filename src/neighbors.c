#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#define UINT_MAX WORLD_SIZE
/** Initializes the relation between the neighbors, based on an
    integer `seed`. `seed` must be less than MAX_RELATIONS.
    Can be called multiple times. */
void init_neighbors(unsigned int seed);

/** Returns the neighbor of the place `idx`, in direction `d`, and
    UINT_MAX if there is no such neighbor (or any other kind of error) */


unsigned int get_neighbor(unsigned int idx, enum dir_t d) //fonction faite pour un tore
{
    switch(idx){      // les coins 
        case(0):
            if (d==NWEST)
            return (HEIGHT)*WIDTH;
        case(WIDTH):
            if (d==NEAST)
            return 1+((HEIGHT-1)*WIDTH);
        case(1+((HEIGHT-1)*WIDTH)):
            if (d==SWEST)
            return WIDTH;
        case((HEIGHT)*WIDTH):
            if (d==SEAST)
            return 0;

    }
    switch(d) {  
        case(NEAST):
        if (idx<WIDTH)      //si bord supp  
            return idx+1+(HEIGHT-1)*WIDTH;     //pour un rectangle retourner UNIT_MAX
        case(NORTH):
        if (idx<WIDTH)
            return idx+(HEIGHT-1)*WIDTH;
        case(NWEST):
        if (idx<WIDTH)
            return idx-1+(HEIGHT-1)*WIDTH;
        return idx-(WIDTH+d-3);  
        case(SEAST):
        if (idx>(HEIGHT*(WIDTH-1)))   //si bord inf
            return idx+1-(HEIGHT-1)*WIDTH;
        case(SOUTH):
        if (idx>(HEIGHT*(WIDTH-1)))
            return idx-(HEIGHT-1)*WIDTH;
        case(SWEST):
        if (idx>(HEIGHT*(WIDTH-1)))
            return idx-1-(HEIGHT-1)*WIDTH;
        return idx+(WIDTH-d-3);
        case(EAST):
        if (idx%WIDTH==0)     //si bord droit 
            return idx-WIDTH+1;
        case(WEST):
        if (idx%WIDTH==1)   //si bord gauche 
            return idx+WIDTH-1;
        return idx+d;
        default:
        return UINT_MAX;
    }
}
/** Returns the list of the neighbors of the place `idx`, terminated
    by UINT_MAX.  */
struct neighbors_t get_neighbors(unsigned int idx);
