#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "players.h"
#include "test_utilities.h"


void test_players_init()
{
    puts("\ttest_players_init:");
    struct players_t players[2];
    players_init(players, 2);
    int_test(players_get_nb_pawns(&players[0]), 0);
    int_test(players[0].index, 0);
    int_test(players[1].index, 1);
}

int main()
{
    puts("test_players.c");
    test_players_init();

    return 0;
}
