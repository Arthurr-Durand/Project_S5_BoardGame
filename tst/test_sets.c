#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "test_utilities.h"


void test_sets()
{
    puts("\ttest_sets :");
    // world init
    struct world_t* world = world_init();
    // sets init
    struct sets_t set;
    sets_init(&set);
    int_test(sets_get_nb(&set), 0);
    // add place 0 et 1 to set
    sets_add(&set, 1);
    sets_add(&set, 2);
    int_test(sets_get_nb(&set), 2);
    int_test(world_get(world, 0), NO_COLOR);
    // change color of set to BLACK
    sets_set_colors(&set, world, BLACK);
    int_test(world_get(world, 0), BLACK);
    int_test(world_get_sort(world, 0), NO_SORT);
    // change sort of set to PAWN
    sets_set_sorts(&set, world, PAWN_SIMPLE);
    int_test(world_get_sort(world, 0), PAWN_SIMPLE);
}

void test_sets_set_initial_sets()
{
    puts("\ttest_sets_set_initial_sets");
    // init 3 players
    struct players_t players[3];
    players_init(players, 3);
    // init 3 sets
    struct sets_t sets[3];
    sets_init(&sets[0]);
    sets_init(&sets[1]);
    sets_init(&sets[2]);
    struct sets_t c_sets[3];
    sets_init(&c_sets[0]);
    sets_init(&c_sets[1]);
    sets_init(&c_sets[2]);
    // set_initials_sets
    sets_set_initial_sets(3, sets, c_sets);
    int_test(sets_get_nb(&sets[0]), 10);
    int_test(sets_get_nb(&sets[2]), 10);
}

void test_sets_get_random()
{
    puts("\ttest_sets_get_random :");
    struct world_ext_t world_ext;
    init_neighbors(2);
    world_ext_init(&world_ext, 2, 0, 1, PAWN_SIMPLE, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    for (int i = 0; i < 5; ++i)
        printf("\t\t> %d\n", sets_get_random_place(&set));
}

void test_sets_add_remove()
{
    puts("\ttest_sets_add :");
    struct sets_t set;
    sets_init(&set);
    sets_add(&set, 5);
    int_test(sets_get_nb(&set), 1);
    int_test(sets_get_place_at(&set, 0), 5);
    puts("\ttest_sets_remove :");
    sets_remove(&set, 5);
    int_test(sets_get_nb(&set), 0);
    int_test(sets_get_place_at(&set, 0), WORLD_SIZE);
}

void test_sets_is_in_set(){
    puts("\ttest_sets_is_in_set");
    struct sets_t set;
    sets_init(&set);
    for(int i=0; i<10; i++)
        sets_add(&set,i);
    int_test(sets_is_in_set(&set,9),1);
    int_test(sets_is_in_set(&set,100),0);
    int_test(sets_is_in_set(&set,-15),0);
    int_test(sets_is_in_set(&set,6),1);
    int_test(sets_is_in_set(&set,200),0);
    int_test(sets_is_in_set(&set,4),1);
    int_test(sets_is_in_set(&set,1),1);
}

// void test_sets_get_good_places()
// {
//     puts("\ttest_sets_get_good_places");
//     // init 2 players
//     struct players_t players[2];
//     players_init(players, 2);
//     // init 2 sets
//     struct sets_t sets[2];
//     sets_init(&sets[0]);
//     sets_init(&sets[1]);
//     struct sets_t c_sets[2];
//     sets_init(&c_sets[0]);
//     sets_init(&c_sets[1]);
//     // set_initials_sets
//     sets_set_initial_sets(2, sets, c_sets);
//     sets_get_good_places(&c_sets[0],&sets[1]);
//     printf("%d\n",sets_get_nb(&c_sets[0]));
//     for (int i=0; i<sets_get_nb(&c_sets[0]);i++){
//         printf("%d\n",sets_get_place_at(&c_sets[0],i));
//     }
// }

int main()
{
    srand((unsigned int) time(NULL));

    puts("test_sets.c : ");
    test_sets();
    test_sets_set_initial_sets();
    test_sets_get_random();
    test_sets_add_remove();
    test_sets_is_in_set();
    //test_sets_get_good_places();

    return 0;
}
