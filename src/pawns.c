#include <stdio.h>
#include <stdlib.h>

#include "neighbors.h"
#include "sets.h"
#include "world.h"
#include "pawns.h"

#define UINT_MAX WORLD_SIZE

struct pawns_t;

struct pawns_t* pawns_init(int max_dep, int idx)
{
    static struct pawns_t pawns;
    pawns.max_dep = max_dep;
    pawns.idx = idx;
    return &pawns;
}

int pawns_get_neighbors_nb(const struct neighbors_t neighbors)
{
    int k = 0;
    while (neighbors.n[k].i != UINT_MAX)
        k++;
    return k;
}

struct sets_t* pawns_all_moves(struct pawns_t* piece, struct world_t* world)
{   
    int idx, d;
    struct sets_t* places = sets_init();
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(piece->idx))); ++k) {
        idx = get_neighbors(piece->idx).n[k].i;
        d = get_neighbors(piece->idx).n[k].d;
        for (int i=0;i<piece->max_dep;i++) {
            if (!world_get_sort(world, idx))
                sets_add(places, idx);
            idx = get_neighbor(idx,d);
        }
    }
    return places;
}

void pawns_moves(struct pawns_t* piece,int idx)
{
    piece->idx=idx;
}
