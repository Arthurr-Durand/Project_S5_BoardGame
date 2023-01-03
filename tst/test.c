#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"

void str_test(const char str1[], const char str2[])
{
    (!strcmp(str1, str2)) ? printf("\t\tPASSED\n") : printf("\t\tRecieve %s instead of %s.\n", str1, str2);
}

void int_test(const int int1, const int int2)
{
    (int1 == int2) ? printf("\t\tPASSED\n") : printf("\t\tRecieve %d instead of %d.\n", int1, int2);
}

void test_place_to_string()
{
    puts("\ttest_place_to_string :");
    str_test(place_to_string(2, 1), "WHITE PAWN");
    str_test(place_to_string(1, 0), "BLACK NO_SORT");
    str_test(place_to_string(3, 0), "ERROR");
    str_test(place_to_string(0, 3), "NO_COLOR PAWN");
    str_test(place_to_string(-5, 3), "ERROR");
}

void test_dir_to_string()
{
    puts("\ttest_dir_to_string :");
    str_test(dir_to_string(-2), "SWEST");
    str_test(dir_to_string(3), "NORTH");
    str_test(dir_to_string(-5), "ERROR");
    str_test(dir_to_string(12), "ERROR");
}

void test_world_set_get()
{
    puts("\ttest_world_set_get :");
    // init world
    struct world_t* world = world_init();
    // set index 0 to WHITE PAWN
    world_set(world, 0, WHITE);
    world_set_sort(world, 0, PAWN_SIMPLE);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "WHITE PAWN");
    // set index 0 to NO_COLOR NO_SORT
    world_set(world, 0, NO_COLOR);
    world_set_sort(world, 0, NO_SORT);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "NO_COLOR NO_SORT");
}

void test_get_neighbor()
{
    puts("\ttest_get_neighbor :");
    // init_neighbors(0);
    int_test(get_neighbor(90, NEAST), 81);
    int_test(get_neighbor(6, EAST), 7);
    int_test(get_neighbor(28, SEAST), 39);
    int_test(get_neighbor(46, NWEST), 35);
    int_test(get_neighbor(99, SWEST), 8);
}

void test_get_neighbors0()
{
    puts("\ttest_get_neighbors 0 :");
    init_neighbors(0);
    int_test(get_neighbors2(0).n[0].i, 11);
    int_test(get_neighbors2(0).n[0].d, SEAST);
    int_test(get_neighbors2(33).n[0].i, 44);
    int_test(get_neighbors2(33).n[1].d, SOUTH);
    int_test(get_neighbors2(19).n[0].i, 20);
    int_test(get_neighbors2(19).n[3].d, WEST);
}

void test_get_neighbors1()
{
    puts("\ttest_get_neighbors 1 :");
    init_neighbors(1);
    int_test(get_neighbors2(33).n[0].i, 42);
    int_test(get_neighbors2(33).n[0].d, SWEST);
    int_test(get_neighbors2(33).n[1].i, 23);
    int_test(get_neighbors2(33).n[1].d, NORTH);
    int_test(get_neighbors2(33).n[2].i, 44);
    int_test(get_neighbors2(33).n[2].d, SEAST);
}


void test_get_neighbors2()
{
    puts("\ttest_get_neighbors 2 :");
    init_neighbors(2);
    int_test(get_neighbors2(33).n[0].i, 43);
    int_test(get_neighbors2(33).n[0].d, SOUTH);
    int_test(get_neighbors2(33).n[1].i, 32);
    int_test(get_neighbors2(33).n[1].d, WEST);
    int_test(get_neighbors2(33).n[2].i, 34);
    int_test(get_neighbors2(33).n[2].d, EAST);
}

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

void test_pawns_get_neighbors_nb()
{
    puts("\ttest_pawns_get_neighbors_nb:");
    int_test(pawns_get_neighbors_nb(get_neighbors(33)),8);
}

void test_players_init()
{
    puts("\ttest_players_init:");
    struct players_t players[2];
    players_init(players, 2);
    int_test(players_get_nb_pawns(&players[0]), 0);
    int_test(players[0].index, 0);
    int_test(players[1].index, 1);
}

void test_game_winning_cond()
{
    puts("\ttest_game_winning_cond :");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 3, 0, 1, PAWN_SIMPLE, 0, 0);
    struct players_t* player0 = world_ext_get_player_nb(&world_ext, 0);
    struct players_t* player1 = world_ext_get_player_nb(&world_ext, 1);
    int_test(game_winning_cond(player1, &world_ext_get_initial_sets(&world_ext)[0], players_get_pawn_at_index(player1, 0), 3), 0);
    world_ext_pawn_moves(&world_ext, players_get_pawn_at_index(player0, 0), 1);
    world_ext_pawn_moves(&world_ext, players_get_pawn_at_index(player1, 0), 0);
    int_test(game_winning_cond(player1, &world_ext_get_initial_sets(&world_ext)[0], players_get_pawn_at_index(player1, 0), 3), 1);
}


void test_world_ext_get_current_sets()
{
    puts("\ttest_world_ext_get_current_sets :");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 1, PAWN_SIMPLE, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[0], 1), 1);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[0], 2), 2);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[0], 5), 5);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[0], 8), 8);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[1], 1), 51);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[1], 2), 52);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[1], 5), 55);
    int_test(sets_get_place_at(&world_ext_get_current_sets(&world_ext)[1], 8), 58);
}

void test_world_ext_get_all_moves_simple()
{
    init_neighbors(0);
    puts("\ttest_world_get_all_moves_simple:");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 2, PAWN_SIMPLE, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    int_test(sets_get_place_at(&set,0),11);
    int_test(sets_get_place_at(&set,3),20);
    int_test(sets_get_place_at(&set,6),91);
    int_test(sets_get_place_at(&set,11),88);
    int_test(sets_get_place_at(&set,12),100);
}

void test_world_ext_get_all_moves_tower()
{
    init_neighbors(0);
    puts("\ttest_world_get_all_moves_tower:");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 10, PAWN_TOWER, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    int_test(sets_get_place_at(&set,0),10);
    int_test(sets_get_place_at(&set,3),40);
    int_test(sets_get_place_at(&set,6),70);
    int_test(sets_get_place_at(&set,11),100);
}

void test_world_ext_get_all_moves_elefun()
{
    init_neighbors(0);
    puts("\ttest_world_get_all_moves_elefun:");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 2, PAWN_ELEFUN, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    int_test(sets_get_place_at(&set,0),20);
    int_test(sets_get_place_at(&set,1),80);
    int_test(sets_get_place_at(&set,8),100);
}

void test_world_ext_get_all_moves_king1st()
{
    init_neighbors(0);
    puts("\ttest_world_get_all_moves_king1st:");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 1, PAWN_KING1ST, 0, 0);
    struct sets_t set;
    sets_init(&set);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    world_ext_get_all_moves(&world_ext, &set, players_get_pawn_at_index(player, 0));
    int_test(sets_get_place_at(&set,0),11);
    int_test(sets_get_place_at(&set,3),19);
    int_test(sets_get_place_at(&set,6),31);
    int_test(sets_get_place_at(&set,11),61);
    int_test(sets_get_place_at(&set,19),100);
}

void test_world_ext_pawn_moves()
{
    init_neighbors(0);
    puts("\ttest_world_ext_pawn_moves :");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 1, 0, 1, PAWN_SIMPLE, 0, 0);
    struct world_t* world = world_ext_get_world(&world_ext);
    struct players_t* player = world_ext_get_player_nb(&world_ext, 0);
    struct pawns_t* pawn = players_get_pawn_at_index(player, 0);
    int_test(world_get_sort(world, 0), PAWN_SIMPLE);
    int_test(world_get(world, 0), BLACK);
    int_test(world_get_sort(world, 69), NO_SORT);
    int_test(world_get(world, 69), NO_COLOR);
    int_test(pawns_get_position(pawn), 0);
    world_ext_pawn_moves(&world_ext, pawn, 69);
    int_test(world_get_sort(world, 0), NO_SORT);
    int_test(world_get(world, 0), NO_COLOR);
    int_test(world_get_sort(world, 69), PAWN_SIMPLE);
    int_test(world_get(world, 69), BLACK);
    int_test(pawns_get_position(pawn), 69);
}

void test_world_ext_test_capture_1()
{
    init_neighbors(0);
    puts("\ttest_world_ext_test_capture :");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 1, PAWN_SIMPLE, 0, 0);
    struct players_t* player0 = world_ext_get_player_nb(&world_ext, 0);
    struct players_t* player1 = world_ext_get_player_nb(&world_ext, 1);
    struct pawns_t* pawn0 = players_get_pawn_at_index(player0, 0);
    struct pawns_t* pawn1 = players_get_pawn_at_index(player1, 0);
    world_ext_pawn_moves(&world_ext, pawn1, 10);
    struct sets_t set;
    sets_init(&set);
    world_ext_get_all_moves(&world_ext, &set, pawn0);
    int_test(sets_is_in_set(&set, 10), 1);
    int_test(sets_is_in_set(&set, 9), 0);
    int_test(sets_is_in_set(&set, 1), 0);
}

void test_world_ext_test_capture_2()
{
    puts("\ttest_world_ext_test_capture :");
    struct world_ext_t world_ext;
    world_ext_init(&world_ext, 2, 0, 1, PAWN_SIMPLE, 0, 0);
    struct players_t* player0 = world_ext_get_player_nb(&world_ext, 0);
    struct players_t* player1 = world_ext_get_player_nb(&world_ext, 1);
    struct pawns_t* pawn0 = players_get_pawn_at_index(player0, 0);
    struct pawns_t* pawn1 = players_get_pawn_at_index(player1, 0);
    struct pawns_t* pawn2 = players_get_pawn_at_index(player0, 1);
    world_ext_pawn_moves(&world_ext, pawn0, 10);
    world_ext_pawn_moves(&world_ext, pawn1, 0);
    struct sets_t set;
    sets_init(&set);
    world_ext_get_all_moves(&world_ext, &set, pawn2);
    int_test(sets_is_in_set(&set, 10), 0);
    int_test(sets_is_in_set(&set, 9), 0);
    int_test(sets_is_in_set(&set, 0), 0);
}

int main()
{
    srand((unsigned int) time(NULL));

    puts("test_geometry.c :");
    test_place_to_string();
    test_dir_to_string();
    
    puts("test_world.c :");
    test_world_set_get();

    puts("test_neighbors.c :");
    test_get_neighbor();
    test_get_neighbors0();
    test_get_neighbors1();
    test_get_neighbors2();

    puts("test_sets.c : ");
    test_sets();
    test_sets_set_initial_sets();
    test_sets_get_random();
    test_sets_add_remove();
    test_sets_is_in_set();

    puts("test_pawns.c :");
    test_pawns_get_neighbors_nb();

    puts("test_players.c");
    test_players_init();

    puts("test_game.c :");
    test_game_winning_cond();

    puts("test_world_ext.c :");
    test_world_ext_get_current_sets();
    test_world_ext_get_all_moves_simple();
    test_world_ext_get_all_moves_tower();
    test_world_ext_get_all_moves_elefun();
    test_world_ext_get_all_moves_king1st();
    test_world_ext_pawn_moves();
    test_world_ext_test_capture_1();
    test_world_ext_test_capture_2();


    //test_sets_get_good_places();

    return 0;
}
