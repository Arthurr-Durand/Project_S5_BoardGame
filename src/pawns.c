#include <stdio.h>
#include <stdlib.h>

#include "neighbors.h"
#include "sets.h"
#include "world.h"
#include "pawns.h"

#define UINT_MAX WORLD_SIZE

struct pawns_t;

void pawns_init(struct pawns_t* pawn, int max_dep, enum color_t color, enum type_t type, int position)
{
    pawn->max_dep = max_dep;
    pawn->color = color;
    pawn->type = type;
    pawn->position = position;
}

enum type_t pawns_get_type(const struct pawns_t* pawn)
{
    return pawn->type;
}

int pawns_get_position(const struct pawns_t* pawn)
{
    return pawn->position;
}

int pawns_get_neighbors_nb(const struct neighbors_t neighbors)
{
    int k = 0;
    while (neighbors.n[k].i != UINT_MAX)
        k++;
    return k;
}

void pawns_get_all_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world)
{   
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(piece->position))); ++k) {
        idx = get_neighbors(piece->position).n[k].i;
        d = get_neighbors(piece->position).n[k].d;
        for (int i=0;i<piece->max_dep;i++) {
            if (!world_get_sort(world, idx))
                sets_add(places, idx);
            idx = get_neighbor(idx,d);
        }
    }
}

void pawns_get_all_tower_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world)
{   
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(piece->position))); ++k) {
        idx = get_neighbors(piece->position).n[k].i;
        d = get_neighbors(piece->position).n[k].d;
        switch (d)
        {
        case EAST:
        case WEST:
        case SOUTH:
        case NORTH:
            for (int i=0;i<piece->max_dep;i++) {
            if (world_get_sort(world, idx))
                break;
            else{
                sets_add(places, idx);
            }
            idx = get_neighbor(idx,d);
            }
            break;
        default:
        break;
        }
        
        
    }
}
void pawns_get_all_elefun_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world)
{
    {   
    int idx, d;
    for (int k = 0; k < (pawns_get_neighbors_nb(get_neighbors(piece->position))); ++k) {
        idx = get_neighbors(piece->position).n[k].i;
        d = get_neighbors(piece->position).n[k].d;
        switch (d)
        {
        case EAST:
        case WEST:
        case SOUTH:
        case NORTH:
        for (int i=0;i<piece->max_dep;i++) {
            if (!world_get_sort(world, idx))
                sets_add(places, idx);
            idx = get_neighbor(idx,d);
        }
            break;
        default:
            for (int i=0;i<piece->max_dep-1;i++) {
                if (!world_get_sort(world, idx))
                    sets_add(places, idx);
                idx = get_neighbor(idx,d);
        }
        break;
        }
    }
}
}

void pawns_moves(struct world_t* world, struct pawns_t* pawn, int new_position)
{
    int position = pawns_get_position(pawn);
    world_set_sort(world, position, NO_SORT);
    world_set(world, position, NO_COLOR);
    pawn->position = new_position;
    world_set_sort(world, new_position, PAWN);
    world_set(world, new_position, pawn->color);
}
