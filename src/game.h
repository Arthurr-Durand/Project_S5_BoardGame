#ifndef __GAME_H__
#define __GAME_H__

#include "world_ext.h"

/** Print the current world */
void print_game(const struct world_t* world);

/** Print captured pawns */
void print_captured_pawns(struct world_ext_t* world_ext);

/** Check simple winning conditions */
int game_winning_cond(struct players_t* player, struct sets_t set[], struct pawns_t* pawn, int nb_players);

/** Check complex winning conditions */
int game_complex_winning_cond(struct players_t* player, struct sets_t set[], int nb_players);

#endif	// __GAME_H__
