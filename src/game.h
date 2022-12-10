#ifndef __GAME_H__
#define __GAME_H__

#include "world_ext.h"

/** Print the current world */
void print_game(const struct world_t* world);

/** Check the simple winning conditions */
int game_winning_cond(struct players_t* player, struct sets_t set[], struct pawns_t* pawn, int nb_players);

/** Check the complex winning conditions */
int game_complex_winning_cond(struct players_t* player, struct sets_t set[],int nb_players);

#endif // __GAME_H__
