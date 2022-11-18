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
                return (HEIGHT)*WIDTH-1;
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
            return idx-(WIDTH+d-3);
        case NORTH:
            if (idx < WIDTH)
                return idx+(HEIGHT-1)*WIDTH;
            return idx-(WIDTH+d-3);
        case NWEST:
            if (idx < WIDTH)
                return idx-1+(HEIGHT-1)*WIDTH;
            return idx-(WIDTH+d-3);  
        case SEAST:
            if (idx > (HEIGHT*(WIDTH-1))) //si bord inf
                return idx+1-(HEIGHT-1)*WIDTH;
            return idx+(WIDTH-d-3);
        case SOUTH:
            if (idx > (HEIGHT*(WIDTH-1)))
                return idx-(HEIGHT-1)*WIDTH;
            return idx+(WIDTH-d-3);
        case SWEST:
            if (idx > (HEIGHT*(WIDTH-1)))
                return idx-1-(HEIGHT-1)*WIDTH;
            return idx+(WIDTH-d-3);
        case EAST:
            if (idx%WIDTH == 9) //si bord droit 
                return idx-WIDTH+1;
            return idx+d;
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
    int p = 0;
    for (enum dir_t d = SEAST; d <= (MAX_DIR/2); d++){
        if (get_neighbor(idx,d) != UINT_MAX){
            voisins.n[p].i = get_neighbor(idx,d);
            voisins.n[p].d = d;
            p++;
        }
    }
    voisins.n[p].i = UINT_MAX;
    voisins.n[p].d = NO_DIR;
    return voisins;
}

//fonction de BG

// int len_voisins(struct neighbors_t);

// struct set_t get_all_moves(struct piece,int idx_piece)
// {   
//     int idx=0;
//     struct set_t places;
//     for(int k=0;k<len_voisins(get_neighbors(idx_piece)-1);k++){
//         idx=get_neighbors(idx_piece).n[k].i;
//         d=get_neighbors(idx_piece).n[k].d;
//         for(int i=0;i<piece.Maxdep;i++){
//             if  (world_get_sort(world,idx)==0){
//                 places[p]=idx;
//             }
//             idx=get_neighbor(idx,d);
        
//         }
//     }
//     return places;
// }
