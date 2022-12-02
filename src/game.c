#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "world.h"
#include "geometry.h"
#include "players.h"
#include "sets.h"

#define UNIT_MAX WORLD_SIZE

void print_game(const struct world_t* world)
{
    for(int i = 0; i < UNIT_MAX; i++) {
        switch (world_get_sort(world,i)) {
            case PAWN:
                switch (world_get(world, i)) {
                    case BLACK:
                        printf("B ");
                        break;
                    case WHITE:
                        printf("W ");
                        break;
                    default:
                        printf("N ");
                        break;
                }
                break;
            default:
                printf(". ");
                break;
        }
        if (i%10 == 9)
            printf("\n");
    }
    printf("\n");
}


int game_winning_cond(struct players_t* player, struct sets_t set[], struct pawns_t* pawn,int nb_players)
{   
    int i=(players_get_index(player)+1)%nb_players;
    while (i!=players_get_index(player)){
        if (set_appartient_sets(&set[i],pawns_get_position(pawn)))
            return 1;
        i=(i+1)%nb_players;
    }
    return 0;
}
