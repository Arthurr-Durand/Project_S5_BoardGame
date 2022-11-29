#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "world.h"
#include "geometry.h"
#include "players.h"
#include "sets.h"

#define UNIT_MAX WORLD_SIZE

#define PLAYERS_NB 2

int main(int argc, char* argv[])
{
    // Init world
    puts("[-] Init world.\n");
    struct world_t* world = world_init();

    // Init players
    puts("[-] Init players.\n");
    struct players_t players[PLAYERS_NB];
    players_init(players, PLAYERS_NB);

    // Init players initial sets
    puts("[-] Init players sets.\n");
    struct sets_t sets[PLAYERS_NB];
    sets_list_init(sets, PLAYERS_NB);
    sets_set_initial_sets(PLAYERS_NB, sets);

    // Print the current world
    puts("[-] Print current world.\n");

    print_game(world);

    return 0;
}
