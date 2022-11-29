#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "geometry.h"
#include "pawns.h"
#include "sets.h"

/** A struct representing a player */
struct players_t {
    int index;
    int pawns_nb;
    struct pawns_t* pawns[WORLD_SIZE+1];
};

/** Inits a list of players */
void players_init(struct players_t players[], int nb_players);

/** Adds a pawn to a player */
void players_add_pawn(struct players_t* player, struct pawns_t* pawn);

/** Returns the number of player's pawns */
int players_get_nb_pawns(struct players_t* player);

#endif // __PLAYERS_H__
