#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/geometry.h"
#include "../src/world.h"
#include "../src/neighbors.h"

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
    //init world
    struct world_t* world = world_init();
    //set index 0 to WHITE PAWN
    world_set(world, 0, WHITE);
    world_set_sort(world, 0, PAWN);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "WHITE PAWN");
    //set index 0 to NO_COLOR NO_SORT
    world_set(world, 0, NO_COLOR);
    world_set_sort(world, 0, NO_SORT);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "NO_COLOR NO_SORT");
}

void test_get_neighbor()
{
    puts("\ttest_get_neighbor :");
    int_test(get_neighbor(5, NORTH), 95);
    int_test(get_neighbor(33, WEST), 32);
    int_test(get_neighbor(89, EAST), 80);
    int_test(get_neighbor(99, SEAST), 0);
    int_test(get_neighbor(10, WEST), 19);
}
void test_get_neighbors()
{
    get_neighbors(0);
    get_neighbors(33);
    get_neighbors(19);
}

int main()
{
    puts("test_geometry.c :");
    test_place_to_string();
    test_dir_to_string();
    
    puts("test_world.c :");
    test_world_set_get();

    puts("test_neighbors.c :");
    test_get_neighbor();
    test_get_neighbors();

    return 0;
}
