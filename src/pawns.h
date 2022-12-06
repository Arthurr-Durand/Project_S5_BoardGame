#ifndef __PAWNS_H__
#define __PAWNS_H__

#include "geometry.h"
#include "neighbors.h"
#include "sets.h"

/** An enum representing a pawn type */
enum type_t {
    SIMPLE = 0,
    TOWER,
};

/** A struct representing a piece */
struct pawns_t {
    int max_dep;
    enum color_t color;
    enum type_t type;
    int position;
};

/** Inits a pawn */
void pawns_init(struct pawns_t* pawn, int max_dep, enum color_t color, enum type_t type, int position);

/** Returns the type of a pawn */
enum type_t pawns_get_type(const struct pawns_t* pawn);

/** Returns the position of a pawn */
int pawns_get_position(const struct pawns_t* pawn);

/** Returns the numbers of pawn's neighbors */
int pawns_get_neighbors_nb(const struct neighbors_t neighbors);

/** Returns all free neighbors */
void pawns_get_all_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world);

/** Returns all free tower's neighbors */
void pawns_get_all_tower_moves(struct sets_t* places, struct pawns_t* piece, struct world_t* world);

/** Move a Pawn */
void pawns_moves(struct world_t* world, struct pawns_t* pawn, int new_position);

#endif // __PAWNS_H__
