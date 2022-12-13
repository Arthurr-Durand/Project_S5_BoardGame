#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>

#include "game.h"

#define UNIT_MAX WORLD_SIZE
#define PLAYERS_NB 2
#define STARTING_POSITION 0 // 0 : classic, 1 : BATTLEGROUND
#define MAX_DEP 1
#define PAWN_TYPE PAWN_SIMPLE
#define FORMAT 0  // max 3 pour normal et min 3 pour BG
#define FORMAE 0 // max 3 pour normal et min 3 pour BG

int main(int argc, char* argv[])
{
    // Set default options
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
    puts("[-] Init world, players, sets.\n");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, PLAYERS_NB, STARTING_POSITION, MAX_DEP, PAWN_TYPE, FORMAT, FORMAE);

    // Print the current world
    puts("[-] Print current world.\n");
    print_game(world_ext_get_world(&world_ext));
    printf("\n");

    // Game start
    unsigned int game = 1, round = 0, turn = rand()%PLAYERS_NB;

    int i=0;
    int p=0;
    while (game) {
        if ((i%10)==0){
            puts("!GLISSEMENT DE TERRAIN!\n");
            init_neighbors(p);
            p++;
        }

        // Round
        round++;
        printf("=============== Round %d ================\n", round);

        // Turn
        turn = (turn+1)%PLAYERS_NB;
        struct players_t* current_player = world_ext_get_player_nb(&world_ext, turn);
        printf("> Turn of player n°%d (%s)\n", turn+1, colors[players_get_color(current_player)]);

        // Get a random pawn
        struct pawns_t* pawn;
        pawn = players_get_random_pawn(current_player);

        // Get a random moves
        int old_place;
        int new_place;
        struct sets_t set;
        sets_init(&set);
        world_ext_get_all_moves(&world_ext, &set, current_player, pawn);
        if (sets_get_nb(&set)) { // If the pawn can go somewhere.
            old_place = pawns_get_position(pawn);
            new_place = sets_get_random_place(&set);

            // Move the pawn
            world_ext_pawn_moves(&world_ext, pawn, current_player, new_place);
            printf("> Player %d moves the pawn from the case %d to the case %d.\n", turn+1, old_place, new_place);
        
            // Print the current world
            puts("> Print game state .\n");
            print_game(world_ext_get_world(&world_ext));
        } else
            printf("> Player %d has chosen a pawn that cannot move !\n", turn+1);
        
        // Check stop conditions
        if ((!end_type && game_winning_cond(current_player, world_ext_get_initial_sets(&world_ext), pawn, PLAYERS_NB)) || (end_type && game_complex_winning_cond(current_player, world_ext_get_initial_sets(&world_ext), PLAYERS_NB))) {
            printf("\n> Player %d win the %s game !\n", turn+1, (end_type ? "compex" : "simple"));
            game = 0;
        }
        
        // End round
        printf("============ End of round %d ============\n\n", round);
        
        // Check max round
        if (round >= max_rounds) {
            printf("> Maximum number of rounds reached, there is no winner !\n");
            game = 0;
        }
    i++;
    }

    return 0;
}
