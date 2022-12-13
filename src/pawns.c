#include <stdio.h>
#include <stdlib.h>

#include "pawns.h"

#define UINT_MAX WORLD_SIZE

struct pawns_t;

void pawns_init(struct pawns_t* pawn, int player_index, int max_dep, enum color_t color, enum sort_t type, int position)
{
    pawn->player_index = player_index;
    pawn->max_dep = max_dep;
    pawn->color = color;
    pawn->type = type;
    pawn->position = position;
    pawn->captured = 0;
}

int pawns_get_player_index(const struct pawns_t* pawn)
{
    return pawn->player_index;
}

int pawns_get_max_dep(const struct pawns_t* pawn)
{
    return pawn->max_dep;
}

enum sort_t pawns_get_type(const struct pawns_t* pawn)
{
    return pawn->type;
}

int pawns_get_position(const struct pawns_t* pawn)
{
    return pawn->position;
}

int pawns_get_captured(const struct pawns_t* pawn)
{
    return pawn->captured;
}

int pawns_get_neighbors_nb(const struct neighbors_t neighbors)
{
    int k = 0;
    while (neighbors.n[k].i != UINT_MAX)
        k++;
    return k;
}

void pawns_set_captured(struct pawns_t* pawn, int captured)
{
    pawn->captured = captured;
}

void pawns_set_position(struct pawns_t* pawn, int new_position)
{
    pawn->position = new_position;
}
