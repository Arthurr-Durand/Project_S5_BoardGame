#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "geometry.h"
#include "neighbors.h"
#include "sets.h"

/** A struct representing a piece */
struct pawns_t {
    int max_dep;
    int idx;
};

/** Inits a pawn */
void pawns_init(struct pawns_t* pawn, int max_dep, int idx);

/** Returns the position of a pawn */
int pawns_get_position(const struct pawns_t* pawn);

/** Returns the numbers of pawn's neighbors */
int pawns_get_neighbors_nb(const struct neighbors_t neighbors);

/** Returns all free neighbors */
void pawns_get_all_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world);

/** Move a Pawn */
void pawns_moves(struct pawns_t* piece,int idx);

#endif // __PAWNS_H__
