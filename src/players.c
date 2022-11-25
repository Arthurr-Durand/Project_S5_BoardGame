#include <stdio.h>
#include <stdlib.h>

#include "players.h"
#include "world.h"
struct players_t;

struct players_t* _player_init(int idx)
{
    static struct players_t player;
    player.index = idx;
    player.pawns_nb = 0;
    return &player;
}

void players_init(struct players_t* players[], int nb_players)
{
    for(int i = 0; i < nb_players; ++i)
        players[i] = _player_init(i);
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

void players_set_initial_set(int nb_player,struct players_t* player[])
{
    for(int i=0;i<nb_player;i++){
        for(int k=(HEIGHT/nb_player)*WIDTH;k<((HEIGHT/nb_player)+1)*WIDTH;k++)
            sets_add(&player[i]->initial_set,(i+1)*k);
    }
}