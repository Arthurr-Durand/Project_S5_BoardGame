#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

#include "game.h"
#include "world.h"
#include "geometry.h"
#include "players.h"
#include "sets.h"

#define UNIT_MAX WORLD_SIZE
#define PLAYERS_NB 2
#define MAX_DEP 1

int main(int argc, char* argv[])
{
    // Set options
    char* colors[] = {"No color", "Black", "White"};
    unsigned int end_type = 0; // 0 : victoire simple, 1 : victoire complexe
    unsigned int max_rounds = 2*WIDTH*HEIGHT;
    unsigned int rand_seed = (unsigned int)time(NULL);

    // Get options
    int opts;
    while ((opts = getopt(argc, argv, ":s:t:m:")) != -1) {
        switch (opts) {
        case 's':
            rand_seed = atoi(optarg);
            break;
        case 't':
            end_type = (optarg[0] == 'c') ? 1 : 0;
            break;
        case 'm':
            max_rounds = atoi(optarg);
        default:
            break;
        }
    }
    printf("[-] Random seed set to : %d.\n", rand_seed);
    printf("[-] Maximum number of rounds set to : %d.\n", max_rounds);
    printf("[-] Victory type is set to : %s.\n\n", end_type ? "complex" : "simple");
    
    // Init rand
    srand(rand_seed);

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
    printf("\n");

    // Game start
    unsigned int game = 1, round = 0, turn = rand()%PLAYERS_NB;
    
    while (game) {
        // Round
        round++;
        printf("=============== Round %d ================\n", round);

        // Turn
        turn = (turn+1)%PLAYERS_NB;
        printf("> Turn of player n°%d (%s)\n", turn+1, colors[players_get_color(&players[turn])]);

        // Get random pawn
        struct pawns_t* pawn = players_get_random_pawn(&players[turn]);

        // Get random free place
        struct sets_t set;
        sets_init(&set);
        pawns_get_all_moves(&set, pawn, world);
        int old_place = pawns_get_position(pawn);
        int new_place = sets_get_random_place(&set);
        
        // Move the pawn
        pawns_moves(world, pawn, new_place);
        printf("> Player %d move the pawn from the case %d to the case %d.\n", turn+1, old_place, new_place);

        // Print the current world
        puts("> Print game state .\n");
        print_game(world);
        
        // Check stop conditions
        if ((!end_type && game_winning_cond(&players[turn], sets, pawn, PLAYERS_NB)) || (end_type && game_complex_winning_cond(&players[turn], sets, PLAYERS_NB))) {
            printf("> Player %d win the %s game !\n", turn+1, (end_type ? "compex" : "simple"));
            game = 0;
        }
        
        // End round
        printf("============ End of round %d ============\n\n", round);
        
        // Check max round
        if (round >= max_rounds)
            game = 0;
    }

    return 0;
}
