#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    // Init rand
    srand((unsigned int) time(NULL));

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

    // Init players pawns
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
        printf("=============== Round %d ================\n", round);

        // Turn
        turn = (turn+1)%PLAYERS_NB;
        printf("> Turn of player n°%d (color %d)\n", turn+1, players[turn].color);

        // Get random pawn
        struct pawns_t* pawn = players_get_random_pawn(&players[turn]);

        // Get random free place
        struct sets_t set;
        sets_init(&set);
        pawns_get_all_moves(&set, pawn, world);
        int new_place = sets_get_random_place(&set);
        
        // Move the pawn
        pawns_moves(world, pawn, new_place);
        printf("> Player %d move the pawn from the case %d to the case %d.\n", turn, pawns_get_position(pawn), new_place);

        // Print the current world
        puts("> Print game state .\n");
        print_game(world);
        
        // Check stop conditions TO DO
        
        // End round
        printf("============ End of round %d ============\n\n", round);
        if (round > 15)
            game = 0;
    }

    return 0;
}
