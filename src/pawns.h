#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "neighbors.h"
#include "sets.h"

/** A struct representing a piece */
struct pawns_t {
    int max_dep;
    enum color_t color;
    enum sort_t type;
    int position;
};

/** Inits a pawn */
void pawns_init(struct pawns_t* pawn, int max_dep, enum color_t color, enum sort_t type, int position);

/** Returns the type of a pawn */
enum sort_t pawns_get_type(const struct pawns_t* pawn);

/** Returns the maximum depth of a pawn */
int pawns_get_max_dep(const struct pawns_t* pawn);

/** Returns the position of a pawn */
int pawns_get_position(const struct pawns_t* pawn);

/** Returns the numbers of pawn's neighbors */
int pawns_get_neighbors_nb(const struct neighbors_t neighbors);

/** Move a Pawn */
void pawns_moves(struct world_t* world, struct pawns_t* pawn, int new_position);

#endif // __PAWNS_H__
