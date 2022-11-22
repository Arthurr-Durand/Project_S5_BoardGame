#include "neighbors.h"
#include "sets.h"
#include "geometry.h"
#include "world.h"

#define UINT_MAX WORLD_SIZE

//fonction de BG
struct pawn{
    int maxdep;
    int idx;
};


int len_voisins(const struct neighbors_t voisin)
{
    int k=0;
    while (voisin.n[k].i!=UINT_MAX){
        k++;
    }
    return k;
}

struct sets_t* sets_all_moves(struct pawn piece,struct world_t* world)
{   
    int idx;
    int d;
    struct sets_t* places = sets_init();
    for(int k=0;k<(len_voisins(get_neighbors(piece.idx))-1);k++){
        idx=get_neighbors(piece.idx).n[k].i;
        d=get_neighbors(piece.idx).n[k].d;
        for(int i=0;i<piece.maxdep;i++){
            if  (world_get_sort(world,idx)==0){
                sets_add(places,idx);
            }
            idx=get_neighbor(idx,d);
        
        }
    }
    return places;
}
