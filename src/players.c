#include <stdio.h>
#include <stdlib.h>

#include "players.h"
#include "sets.h"
#include "world.h"

struct players_t;

void _player_init(struct players_t* player, int idx)
{
    player->index = idx;
    player->pawns_nb = 0;
}

void players_init(struct players_t players[], int nb_players)
{
    for (int i = 0; i < nb_players; ++i)
        _player_init(&players[i], i);
}

void players_add_pawn(struct players_t* player, struct pawns_t* pawn)
{
    player->pawns_nb++;
    player->pawns[player->pawns_nb] = pawn;
}

int players_get_nb_pawns(struct players_t* player)
{
    return player->pawns_nb;
}
