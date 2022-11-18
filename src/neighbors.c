#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "neighbors.h"

#define UINT_MAX WORLD_SIZE

struct neighbors_t neighbors[WORLD_SIZE];

/** Initializes the relation between the neighbors, based on an
    integer `seed`. `seed` must be less than MAX_RELATIONS.
    Can be called multiple times. */
void init_neighbors(unsigned int seed);

/** Returns the neighbor of the place `idx`, in direction `d`, and
    UINT_MAX if there is no such neighbor (or any other kind of error) */
unsigned int get_neighbor(unsigned int idx, enum dir_t d) // Fonction faite pour un tore
{
    switch (idx) { // les coins 
        case 0:
            if (d == NWEST)
                return (HEIGHT)*WIDTH;
            break;
        case WIDTH:
            if (d == NEAST)
                return 1+((HEIGHT-1)*WIDTH);
            break;
        case 1+((HEIGHT-1)*WIDTH):
            if (d == SWEST)
                return WIDTH;
            break;
        case WORLD_SIZE-1:
            if (d == SEAST)
                return 0;
            break;
    }
    
    switch (d) {
        case NEAST:
            if (idx < WIDTH) //si bord supp  
                return idx+1+(HEIGHT-1)*WIDTH; //pour un rectangle retourner UNIT_MAX
            break;
        case NORTH:
            if (idx < WIDTH)
                return idx+(HEIGHT-1)*WIDTH;
            break;
        case NWEST:
            if (idx < WIDTH)
                return idx-1+(HEIGHT-1)*WIDTH;
            return idx-(WIDTH+d-3);  
        case SEAST:
            if (idx > (HEIGHT*(WIDTH-1))) //si bord inf
                return idx+1-(HEIGHT-1)*WIDTH;
            break;
        case SOUTH:
            if (idx > (HEIGHT*(WIDTH-1)))
                return idx-(HEIGHT-1)*WIDTH;
            break;
        case SWEST:
            if (idx > (HEIGHT*(WIDTH-1)))
                return idx-1-(HEIGHT-1)*WIDTH;
            return idx+(WIDTH-d-3);
        case EAST:
            if (idx%WIDTH == 9) //si bord droit 
                return idx-WIDTH+1;
            break;
        case WEST:
            if (idx%WIDTH == 0) //si bord gauche 
                return idx+WIDTH-1;
            return idx+d;
        default:
            return UINT_MAX;
    }

    return UINT_MAX;
}
/** Returns the list of the neighbors of the place `idx`, terminated
    by UINT_MAX.  */
struct neighbors_t get_neighbors(unsigned int idx)
{
    struct neighbors_t voisins;
    int p=0;
    for(enum dir_t i=SEAST;i<=MAX_DIR/2;i++){
        if (get_neighbor(idx,i)!=UINT_MAX){
            voisins.n[p].i = get_neighbor(idx,i);
            voisins.n[p].d = i;
            printf("idx:%d, dir:%s\n",voisins.n[p].i,dir_to_string(voisins.n[p].d));
            p++;
        }
    }
    voisins.n[p].i=UINT_MAX;
    voisins.n[p].i=NO_DIR;
    printf("idx:%d, dir:%s\n\n",voisins.n[p].i,dir_to_string(voisins.n[p].d));
    return voisins;
}