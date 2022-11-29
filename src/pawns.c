#include <stdio.h>
#include <stdlib.h>

#include "neighbors.h"
#include "sets.h"
#include "world.h"
#include "pawns.h"

#define UINT_MAX WORLD_SIZE

struct pawns_t;

void pawns_init(struct pawns_t* pawn, int max_dep, int idx)
{
    pawn->max_dep = max_dep;
    pawn->idx = idx;
}

int pawns_get_neighbors_nb(const struct neighbors_t neighbors)
{
    int k = 0;
    while (neighbors.n[k].i != UINT_MAX)
        k++;
    return k;
}

void pawns_all_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world)
{   
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(piece->idx))); ++k) {
        idx = get_neighbors(piece->idx).n[k].i;
        d = get_neighbors(piece->idx).n[k].d;
        for (int i=0;i<piece->max_dep;i++) {
            if (!world_get_sort(world, idx))
                sets_add(places, idx);
            idx = get_neighbor(idx,d);
        }
    }
}

void pawns_moves(struct pawns_t* piece,int idx)
{
    piece->idx=idx;
}
