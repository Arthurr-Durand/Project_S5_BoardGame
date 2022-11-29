#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "geometry.h"

#define UNIT_MAX WIDTH*HEIGHT

void print_game(struct world_t* world){
    
    for(int i=0; i<UNIT_MAX; i++){
        int n=0;
        switch (world_get_sort(world,i))
        {
        case PAWN:
            if (world_get(world,i) == BLACK)
                printf("B\t");
            else
                print("W\t");
            break;
        
        default:
            printf("-\t");
            break;
        }
        n++;
        if ((n%10)==0)
            printf("\n");
        
    }

}