#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "geometry.h"
#include "world.h"
#include "neighbors.h"
#include "sets.h"
#include "pawns.h"
#include "players.h"
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
    str_test(place_to_string(0, 3), "ERROR");
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
    world_set_sort(world, 0, PAWN);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "WHITE PAWN");
    // set index 0 to NO_COLOR NO_SORT
    world_set(world, 0, NO_COLOR);
    world_set_sort(world, 0, NO_SORT);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "NO_COLOR NO_SORT");
}

void test_get_neighbor()
{
    puts("\ttest_get_neighbor :");
    int_test(get_neighbor(90, NEAST), 81);
    int_test(get_neighbor(6, EAST), 7);
    int_test(get_neighbor(28, SEAST), 39);
    int_test(get_neighbor(46, NWEST), 35);
    int_test(get_neighbor(99, SWEST), 8);
}

void test_get_neighbors()
{
    puts("\ttest_get_neighbors :");
    int_test(get_neighbors(0).n[0].i, 11);
    int_test(get_neighbors(0).n[4].d, EAST);
    int_test(get_neighbors(33).n[8].i, WORLD_SIZE);
    int_test(get_neighbors(33).n[8].d, NO_DIR);
    int_test(get_neighbors(19).n[7].i, 8);
    int_test(get_neighbors(19).n[2].d, SWEST);
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
    sets_set_sorts(&set, world, PAWN);
    int_test(world_get_sort(world, 0), PAWN);

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
    // set_initials_sets
    sets_set_initial_sets(3, sets);
    int_test(sets_get_nb(&sets[0]), 10);
    int_test(sets_get_nb(&sets[2]), 10);
}

void test_sets_get_random(){

    puts("\ttest_sets_get_random :");
    // world init
    struct world_t* world = world_init();
    // pawns init
    struct pawns_t pawn;
    pawns_init(&pawn, 2, WHITE, SIMPLE, 0);
    struct sets_t set;
    sets_init(&set);
    pawns_get_all_moves(&set, &pawn, world);
    for (int i = 0; i < 10; ++i)
        printf("\t\t> %d\n", sets_get_random_place(&set));
}

void test_set_appartient_sets(){
    puts("\ttest_set_appartient_sets");
    struct sets_t set;
    sets_init(&set);
    for(int i=0; i<10;i++)
        sets_add(&set,i);
    int_test(set_appartient_sets(&set,9),1);
    int_test(set_appartient_sets(&set,100),0);
    int_test(set_appartient_sets(&set,-15),0);
    int_test(set_appartient_sets(&set,6),1);
    int_test(set_appartient_sets(&set,200),0);
    int_test(set_appartient_sets(&set,4),1);
    int_test(set_appartient_sets(&set,1),1);
}

void test_pawns_get_neighbors_nb()
{
    puts("\ttest_pawns_get_neighbors_nb:");
    int_test(pawns_get_neighbors_nb(get_neighbors(33)),8);
}

void test_pawns_all_moves()
{
    puts("\ttest_pawns_all_moves:");
    // world init
    struct world_t* world = world_init();
    // pawns init
    struct pawns_t pawn;
    pawns_init(&pawn, 2, WHITE, SIMPLE, 0);
    struct sets_t set;
    sets_init(&set);
    pawns_get_all_moves(&set, &pawn, world);
    int_test(sets_get_place_at(&set,2),10);
    int_test(sets_get_place_at(&set,14),99);
    int_test(sets_get_place_at(&set,8),1);
}

void test_pawns_move()
{
    puts("\ttest_pawns_move:");
    // init world and pawn
    struct world_t* world = world_init();
    struct pawns_t pawn;
    pawns_init(&pawn, 1, WHITE, SIMPLE, 0);
    world_set_sort(world, 0, PAWN);
    world_set(world, 0, pawn.color);
    int_test(world_get_sort(world, 0), PAWN);
    int_test(world_get(world, 0), WHITE);
    int_test(world_get_sort(world, 69), NO_SORT);
    int_test(world_get(world, 69), NO_COLOR);
    // move the pawn from 0 to 69
    pawns_moves(world, &pawn, 69);
    int_test(world_get_sort(world, 0), NO_SORT);
    int_test(world_get(world, 0), NO_COLOR);
    int_test(world_get_sort(world, 69), PAWN);
    int_test(world_get(world, 69), WHITE);
    int_test(pawns_get_position(&pawn), 69);
}

void test_pawns_get_all_tower_moves()
{
    puts("\ttest_pawns_all_moves:");
    // world init
    struct world_t* world = world_init();
    // pawns init
    struct pawns_t tower;
    pawns_init(&tower, 10, WHITE, TOWER, 0);
    struct sets_t set;
    sets_init(&set);
    pawns_get_all_moves(&set, &tower, world);
    // for (int i =0;i<sets_get_nb(&set);i++)
    //     printf("%d\n",sets_get_place_at(&set,i));
    int_test(sets_get_place_at(&set,2),30);
    int_test(sets_get_place_at(&set,14),5);
    int_test(sets_get_place_at(&set,8),90);
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

void test_print_game(){
    puts("\ttest_print_game :");
    struct world_t* world = world_init();
    print_game(world);
}

void test_game_winning_cond()
{
    puts("\ttest_game_winning_cond :");
    struct world_t* world = world_init();
    struct players_t players[3];
    players_init(players, 3);
    struct sets_t sets[3];
    sets_list_init(sets, 3);
    sets_set_initial_sets(3, sets);
    players_set_initial_pawns(world, players, 3, sets, 1);
    int_test(game_winning_cond(&players[1], sets, &players[1].pawns[0],3), 0);
    pawns_moves(world,&players[1].pawns[0],1);
    pawns_moves(world,&players[0].pawns[1],15);
    int_test(game_winning_cond(&players[1], sets, &players[1].pawns[0],2), 1);
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
    test_get_neighbors();

    puts("test_sets.c : ");
    test_sets();
    test_sets_set_initial_sets();
    test_sets_get_random();
    test_set_appartient_sets();

    puts("test_pawns.c :");
    test_pawns_get_neighbors_nb();
    test_pawns_all_moves();
    test_pawns_move();
    test_pawns_get_all_tower_moves();

    puts("test_players.c");
    test_players_init();

    puts("test_game.c :");
    test_print_game();
    test_game_winning_cond();

    return 0;
}
