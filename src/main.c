#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <getopt.h>
#include <math.h>

#include "game.h"

#define UNIT_MAX WORLD_SIZE
#define PLAYERS_NB 2
#define STARTING_POSITION 0 // 0 : classic, 1 : BATTLEGROUND
#define MAX_DEP 1
#define PAWN_TYPE PAWN_SIMPLE
#define FORMAT 3 // max 3 for classic and min 3 pour BATTLEGROUND
#define FORMAE 3 // max 3 for classic and min 3 pour BATTLEGROUND
#define CHANCE_OF_RELEASE 50 // between 0 and 100, the % of chances to release a captured pawn

int main(int argc, char* argv[])
{
    // Set default options
    char* colors[] = {"No color", "Black", "White"};
    unsigned int end_type = 0; // 0 : simple victory, 1 : complex victory
    unsigned int max_rounds = 2*WIDTH*HEIGHT;
    unsigned int rand_seed = (unsigned int)time(NULL);
    unsigned int earthquake = 0;
    // Get options
    int opts;
    while ((opts = getopt(argc, argv, ":s:t:m:e:")) != -1) {
        switch (opts) {
        case 's':
            rand_seed = atoi(optarg);
            break;
        case 't':
            end_type = (optarg[0] == 'c') ? 1 : 0;
            break;
        case 'm':
            max_rounds = atoi(optarg);
            break;
        case 'e':
            if (atoi(optarg) > 0)
                earthquake = atoi(optarg);
            break;
        default:
            break;
        }
    }
    if (!earthquake)
        earthquake = sqrt(max_rounds);
    printf("[-] Random seed set to : %d.\n", rand_seed);
    printf("[-] Maximum number of rounds set to : %d.\n", max_rounds);
    printf("[-] Victory type is set to : %s.\n", end_type ? "complex" : "simple");
    printf("[-] Number of rounds before each earthquake is set to : %d.\n\n", earthquake);
    
    // Init rand
    srand(rand_seed);

    // Init world
    puts("[-] Init world, players, sets.\n");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, PLAYERS_NB, STARTING_POSITION, MAX_DEP, PAWN_TYPE, FORMAT, FORMAE);
    int p = 0;
    init_neighbors(0);

    // Print the current world
    puts("[-] Print current world.\n");
    print_game(world_ext_get_world(&world_ext));
    printf("\n");

    // Game start
    unsigned int game = 1, round = 0, turn = rand()%PLAYERS_NB;
    while (game) {

        if (round != 0 && (round%earthquake)==0){
            puts("!GLISSEMENT DE TERRAIN!\n");
            p++;
            init_neighbors(p%3);
        }

        // Round
        round++;
        printf("=============== Round %d ================\n", round);

        // Release
        if (world_ext_get_nb_captured_pawns(&world_ext))
            world_ext_try_release(&world_ext, CHANCE_OF_RELEASE);

        // Turn
        turn = (turn+1)%PLAYERS_NB;
        struct players_t* current_player = world_ext_get_player_nb(&world_ext, turn);
        printf("> Turn of player n°%d (%s)\n", turn+1, colors[players_get_color(current_player)]);

        // Get a random pawn
        struct pawns_t* pawn;
        // pawn = players_get_random_pawn(current_player);
        pawn = word_ext_get_random_pawn(&world_ext, players_get_index(current_player));

        // Get a random moves
        int old_place;
        int new_place;
        struct sets_t set;
        sets_init(&set);
        world_ext_get_all_moves(&world_ext, &set, pawn);
        // for(int i=0;i<sets_get_nb(&set);i++)
        //     printf("du set %d\n",sets_get_place_at(&set,i));
        // sets_get_good_places(&set,&world_ext_get_initial_sets(&world_ext)[turn%PLAYERS_NB+1]);
        // for(int i=0;i<sets_get_nb(&set);i++)
        //     printf(" du pas set %d\n",sets_get_place_at(&set,i));
        if (sets_get_nb(&set)) { // If the pawn can go somewhere.
            old_place = pawns_get_position(pawn);
            new_place = sets_get_random_place(&set);

            // Move the pawn
            int capture = world_ext_pawn_moves(&world_ext, pawn, new_place);
            printf("> Player %d moves the pawn from the case %d to the case %d.\n", turn+1, old_place, new_place);
            if (capture != UNIT_MAX)
                printf("> Pawn at the place %d has been captured.\n", capture);
        
            // Print the current world
            puts("> Game state :");
            print_game(world_ext_get_world(&world_ext));
            puts("\n> Captured pawns :");
            print_captured_pawns(&world_ext);
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
    }

    return 0;
}
