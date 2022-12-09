#include <stdio.h>
#include <stdlib.h>

#include "players.h"


struct players_t;

void _player_init(struct players_t* player, int index, enum color_t color)
{
    player->index = index;
    player->pawns_nb = 0;
    player->color = color;
}

void players_init(struct players_t players[], int nb_players)
{
    for (int i = 0; i < nb_players; ++i)
        _player_init(&players[i], i, i%(MAX_COLOR-1)+1);
}

int players_get_index(const struct players_t* player)
{
    return player->index;
}

int players_get_nb_pawns(const struct players_t* player)
{
    return player->pawns_nb;
}

struct pawns_t* players_get_pawn_at_index(struct players_t* player, int index)
{
    return &player->pawns[index];
}

enum color_t players_get_color(const struct players_t* players)
{
    return players->color;
}

void players_add_pawn(struct players_t* player, int max_dep, enum type_t type, int position)
{
    pawns_init(&player->pawns[players_get_nb_pawns(player)], max_dep, player->color, type, position);
    player->pawns_nb++;
}

void players_set_initial_pawns(struct world_t* world, struct players_t players[], const int nb_players, const struct sets_t sets[], int max_dep, enum type_t type)
{
    for (int i = 0; i < nb_players; ++i) {
        int nb_places = sets_get_nb(&sets[i]);
        for (int y = 0; y < nb_places; ++y) {
            int position = sets_get_place_at(&sets[i], y);
            players_add_pawn(&players[i], max_dep, type, position);
            world_set_sort(world, position, PAWN);
            world_set(world, position, players[i].color);
        }
    }
}

struct pawns_t* players_get_random_pawn(struct players_t* player)
{
    return &player->pawns[rand()%players_get_nb_pawns(player)];
}
