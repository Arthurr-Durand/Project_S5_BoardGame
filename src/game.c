#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "world.h"
#include "geometry.h"

#define UNIT_MAX WORLD_SIZE

void print_game(const struct world_t* world)
{
    for(int i = 0; i < UNIT_MAX; i++) {
        switch (world_get_sort(world,i))
        {
            case PAWN:
                if (world_get(world, i) == BLACK)
                    printf("B ");
                else
                    printf("W ");
                break;
            default:
                printf("0 ");
                break;
        }
        if ((i%10)==9)
            printf("\n");
    }
    printf("\n");
}
