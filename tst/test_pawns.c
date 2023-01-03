#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "test_utilities.h"


void test_pawns_get_neighbors_nb()
{
    puts("\ttest_pawns_get_neighbors_nb:");
    int_test(pawns_get_neighbors_nb(get_neighbors(33)),8);
}

int main()
{
    puts("test_pawns.c :");
    test_pawns_get_neighbors_nb();

    return 0;
}
