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

void players_add_pawn(struct players_t* player, int max_dep, int position)
{
    pawns_init(&player->pawns[players_get_nb_pawns(player)], max_dep, position);
    player->pawns_nb++;
}

int players_get_nb_pawns(const struct players_t* player)
{
    return player->pawns_nb;
}


void players_set_initial_pawns(struct world_t* world, struct players_t players[], const int nb_players, const struct sets_t sets[], int max_dep)
{
    for (int i = 0; i < nb_players; ++i) {
        int nb_places = sets_get_nb(&sets[i]);
        for (int y = 0; y < nb_places; ++y) {
            int position = sets_get_place_at(&sets[i], y);
            players_add_pawn(&players[i], max_dep, position);
            world_set_sort(world, position, PAWN);
        }
    }
}

struct pawns_t* players_get_random_pawn(struct players_t* player)
{
    return &player->pawns[rand()%players_get_nb_pawns(player)];
}
