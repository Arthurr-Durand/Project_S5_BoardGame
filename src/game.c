#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

#define UNIT_MAX WORLD_SIZE

static const char* pawn_strings[MAX_COLOR][MAX_SORT] = {{"\u00b7", "\u2657", "\u2656", "\u2658"},
                                                    {"\u00b7","\u265d", "\u265c", "\u265e"}};

void print_game(const struct world_t* world, enum sort_t type)
{
    for (int i = 0; i < UNIT_MAX; i++) {
        if (world_get_sort(world, i))
            printf("%s ", pawn_strings[world_get(world, i)-1][type]);
        else
            printf("\u00b7 ");
        if (i%WIDTH == WIDTH-1)
            printf("\n");
    }
}

int game_winning_cond(struct players_t* player, struct sets_t set[], struct pawns_t* pawn,int nb_players)
{   
    int i = (players_get_index(player)+1)%nb_players;
    while (i != players_get_index(player)) {
        if (set_appartient_sets(&set[i], pawns_get_position(pawn)))
            return 1;
        i = (i+1)%nb_players;
    }
    return 0;
}

int game_complex_winning_cond(struct players_t* player, struct sets_t set[],int nb_players)
{   
    int w=0;
    int p=players_get_nb_pawns(player);
    for(int k=0;k<p;k++){
        w=game_winning_cond(player,set,&player->pawns[k],nb_players);
        if (w==0)
            return 0;
    }
    return 1;
}
