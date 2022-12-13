#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "pawns.h"

/** A struct representing a player */
struct players_t {
    int index;
    int pawns_nb;
    int captured_pawns_nb;
    struct pawns_t pawns[WORLD_SIZE];
    enum color_t color;
};

/** Inits a list of players */
void players_init(struct players_t players[], int nb_players);

/** Returns the index of the player */
int players_get_index(const struct players_t* player);

/** Returns the number of player's pawns */
int players_get_nb_pawns(const struct players_t* player);

/** Returns the pawn of an index */
struct pawns_t* players_get_pawn_at_index(struct players_t* player, int index);

/** Return the color of a player */
enum color_t players_get_color(const struct players_t* players);

/** Adds a pawn to a player */
void players_add_pawn(struct players_t* player, int max_dep, enum sort_t type, int position);

/** Sets all world sort in inital sets to pawns */
void players_set_initial_pawns(struct world_t* world, struct players_t players[], const int nb_players, const struct sets_t sets[], int max_dep, enum sort_t type, int foramt, int forame);

#endif // __PLAYERS_H__
