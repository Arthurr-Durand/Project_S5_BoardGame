#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "game.h"

#define UNIT_MAX WORLD_SIZE

static const char* pawn_strings[MAX_COLOR][MAX_TYPE] = {{"\u265d", "\u265c", "\u265e"},
                                                    {"\u2657", "\u2656", "\u2658"}};

void print_game(struct players_t players[], int nb_players)
{
    int world_list[WORLD_SIZE][2];
    for (int i = 0; i < WORLD_SIZE; i++)
        world_list[i][0] = -1;
    
    int nb_pawns, position;
    for (int x = 0; x < nb_players; x++) {
        nb_pawns = players_get_nb_pawns(&players[x]);
        for (int y = 0; y < nb_pawns; y++) {
            position = pawns_get_position(players_get_pawn_at_index(&players[x], y));
            world_list[position][0] = players_get_color(&players[x])-1;
            world_list[position][1] = pawns_get_type(players_get_pawn_at_index(&players[x], y));
        }
    }

    for (int i = 0; i < WORLD_SIZE; i++) {
        (world_list[i][0] == -1) ? printf("\u00b7 ") : printf("%s ", pawn_strings[world_list[i][0]][world_list[i][1]]);
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
