#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include "geometry.h"
#include "pawn.h"
#include "sets.h"

struct players_t {
    int index;
    int pawns_nb;
    struct pawns_t* pawns[WORLD_SIZE+1];
};

void players_init(struct players_t* players[], int nb_players);

void players_add_pawn(struct players_t* player, struct pawns_t* pawn);

int players_get_nb_pawns(struct players_t* player);

#endif // __PLAYERS_H__
