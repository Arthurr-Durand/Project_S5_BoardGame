#include <stdio.h>
#include <stdlib.h>


#include "neighbors.h"

#define UINT_MAX WORLD_SIZE

// static enum dir_t t[MAX_DIR];

struct neighbors_t neighbors[WORLD_SIZE];

/** Initializes the relation between the neighbors, based on an
    integer `seed`. `seed` must be less than MAX_RELATIONS.
    Can be called multiple times. */
void init_neighbors(unsigned int seed);
// {
//     int p=0;
//     switch(seed) {
//         case 0: // hocto
//         p=0;
//             for(int i=-4;i<MAX_DIR-4;i++){
//                 t[p] = i;
//                 p++;
//             }
//             t[p]=MAX_DIR;
//             break;

//         case 1:  // triangular
//             p=0;
//             for(int i=2;i<5;i++){
//                 if ((i%2)!=0)
//                     t[p]=i;
//                 else
//                     t[p]=-i;
//                 p++;
//             }   
//             for(int i=-4;i<-1;i++){
//                 if ((i%2)!=0)
//                     t[p]=i;
//                 else 
//                     t[p]=-i;
//                 p++;
//             }
//             t[p]=MAX_DIR;
//             break;
//         case 2: // square
//         p=0; 
//             for(int i=-3;i<MAX_DIR-5;i=i+2){
//                 t[p]= i;
//                 p++;
//             }
//             t[p]=MAX_DIR;
//             break;
//     }
//     //for(int i=0;i!=MAX_DIR;i++)
//     //    printf("%d\n",t[i]);
// }

/** Returns the neighbor of the place `idx`, in direction `d`, and
    UINT_MAX if there is no such neighbor (or any other kind of error) */
unsigned int get_neighbor(unsigned int idx, enum dir_t d) // Fonction faite pour un tore
{
    switch (idx) { // les coins 
        case 0:
            if (d == NWEST)
                return (HEIGHT)*WIDTH-1;
            break;
        case WIDTH-1:
            if (d == NEAST)
                return ((HEIGHT-1)*WIDTH);
            break;
        case ((HEIGHT-1)*WIDTH):
            if (d == SWEST)
                return WIDTH-1;
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
            else if (idx%WIDTH==9)
                return (idx-(2*WIDTH)+1)%WORLD_SIZE;
            return idx-(WIDTH+d-3);
        case NORTH:
            if (idx < WIDTH)
                return idx+(HEIGHT-1)*WIDTH;
            return idx-(WIDTH+d-3);
        case NWEST:
            if (idx < WIDTH)
                return idx-1+(HEIGHT-1)*WIDTH;
            else if (idx%WIDTH==0)
                return (idx-1)%WORLD_SIZE;
            return idx-(WIDTH+d-3);  
        case SEAST:
            if (idx >= (HEIGHT*(WIDTH-1))) //si bord inf
                return idx+1-(HEIGHT-1)*WIDTH;
            else if (idx%WIDTH==9)
                return (idx+1)%WORLD_SIZE;
            return idx+(WIDTH-d-3);
        case SOUTH:
            if (idx >= (HEIGHT*(WIDTH-1)))
                return idx-(HEIGHT-1)*WIDTH;
            return idx+(WIDTH-d-3);
        case SWEST:
            if (idx >= (HEIGHT*(WIDTH-1)))
                return idx-1-(HEIGHT-1)*WIDTH;
            else if (idx%WIDTH==0)
                return (idx+(2*WIDTH)-1)%WORLD_SIZE;
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
// struct neighbors_t get_neighbors(unsigned int idx)
// {
//     struct neighbors_t voisins;
//     int p = 0;
//     int l=0;
//     int debut;
//     int fin;
//     while (t[l]!=MAX_DIR){
//         l++;
//     //   printf("%d\n",l);
//     }
//     if (l!=6){
//         for (int k=0 ;t[k]!=MAX_DIR ;k++){
//             if (get_neighbor(idx,t[k]) != UINT_MAX){
//                 voisins.n[p].i = get_neighbor(idx,t[k]);
//                 voisins.n[p].d = t[k];
//                 p++;
//             }
//         }
//     }
//     else{
//         if (idx%2!=0){
//             debut=0 ;
//             fin=3;
//         } 
//         else {
//             debut=3 ;
//             fin=MAX_DIR-3;
//         }
//     }
//     //printf("%d <> %d \n",debut,fin);
//     for (int k=debut ;k<fin ;k++){
//             if (get_neighbor(idx,t[k]) != UINT_MAX){
//                 voisins.n[p].i = get_neighbor(idx,t[k]);
//                 voisins.n[p].d = t[k];
//                 p++;
//             }
//         } 

//     voisins.n[p].i = UINT_MAX;
//     voisins.n[p].d = NO_DIR;
//     return voisins;
// }

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