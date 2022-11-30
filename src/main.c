#include <stdlib.h>
#include <stdio.h>

#include "game.h"
#include "world.h"
#include "geometry.h"
#include "players.h"
#include "sets.h"

#define UNIT_MAX WORLD_SIZE
#define PLAYERS_NB 2
#define MAX_DEP 1

int main()
{
    // Init world
    puts("[-] Init world.\n");
    struct world_t* world = world_init();

    // Init players
    puts("[-] Init players.\n");
    struct players_t players[PLAYERS_NB];
    players_init(players, PLAYERS_NB);

    // Init players sets
    puts("[-] Init players sets.\n");
    struct sets_t sets[PLAYERS_NB];
    sets_list_init(sets, PLAYERS_NB);
    sets_set_initial_sets(PLAYERS_NB, sets);

    //Init players pawns
    puts("[-] Init players pawns.\n");
    players_set_initial_pawns(world, players, PLAYERS_NB, sets, MAX_DEP);

    // Print the current world
    puts("[-] Print current world.\n");
    print_game(world);

    // Game start
    int game = 1, round = 0, turn = rand()%PLAYERS_NB;
    
    while (game) {
        // Round
        round++;
        printf("> Round %d:\n", round);

        // Turn
        turn = (turn+1)%PLAYERS_NB;
        printf("> Turn of player n°%d\n", turn);

        // Get random pawn
        struct pawns_t* pawn = players_get_random_pawn(&players[turn]);
        printf("> Player %d choose to move the pawn at the case %d.\n", turn, pawns_get_position(pawn));
        // Get random free place
        
        // Move the pawn
        
        // Checl stop conditions
        
        // End round
        printf("> End of round %d.\n\n", round);
        if (round > 10)
            game = 0;
    }


    return 0;
}
