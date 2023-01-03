#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "test_utilities.h"


void test_world_ext_get_current_sets()
{
    puts("\ttest_world_ext_get_current_sets :");
    struct world_ext_t world_ext;
    init_neighbors(2);
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
    puts("test_world_ext.c :");
    test_world_ext_get_current_sets();
    test_world_ext_get_all_moves_simple();
    test_world_ext_get_all_moves_tower();
    test_world_ext_get_all_moves_elefun();
    test_world_ext_get_all_moves_king1st();
    test_world_ext_pawn_moves();
    test_world_ext_test_capture_1();
    test_world_ext_test_capture_2();

    return 0;
}
