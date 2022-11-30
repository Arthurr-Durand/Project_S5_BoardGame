#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "world.h"
#include "geometry.h"

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
