#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "geometry.h"
#include "pawns.h"
#include "sets.h"

/** A struct representing a player */
struct players_t {
    int index;
    int pawns_nb;
    struct pawns_t pawns[WORLD_SIZE];
    enum color_t color;
};

/** Inits a list of players */
void players_init(struct players_t players[], int nb_players);

/** Returns the index of the player */
int players_get_index(const struct players_t* player);

/** Returns the number of player's pawns */
int players_get_nb_pawns(const struct players_t* player);

/** Adds a pawn to a player */
void players_add_pawn(struct players_t* player, int max_dep, int position);

/** Sets all world sort in inital sets to pawns */
void players_set_initial_pawns(struct world_t* world, struct players_t players[], const int nb_players, const struct sets_t sets[], int max_dep);

/** Return a random player's pawn */
struct pawns_t* players_get_random_pawn(struct players_t* player);

#endif // __PLAYERS_H__
