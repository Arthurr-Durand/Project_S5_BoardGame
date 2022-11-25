#include <stdio.h>
#include <stdlib.h>

#include "players.h"
#include "world.h"
struct players_t;



void players_set_initial_set(int nb_player,struct players_t* player[])
{
    for(int i=0;i<nb_player;i++){
        for(int k=(HEIGHT/nb_player)*WIDTH;k<((HEIGHT/nb_player)+1)*WIDTH;k++)
            sets_add(&player[i]->initial_set,(i+1)*k);
    }
}