#include "neighbors.h"
#include "sets.h"
#include "geometry.h"

/** A struct representing a piece */
struct pawns_t {
    int max_dep;
    int idx;
};
int len_voisins(const struct neighbors_t voisin);
/** Inits a pawn */
struct pawns_t* pawns_init(int max_dep, int idx);

/** Returns all free neighbors */
struct sets_t* pawns_all_moves(struct pawns_t* piece, struct world_t* world);

/** Move a Pawn */
void pawns_moves(struct pawns_t* piece,int idx);