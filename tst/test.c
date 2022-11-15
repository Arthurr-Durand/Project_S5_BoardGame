#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/geometry.h"
#include "../src/world.h"

void str_test(const char str1[], const char str2[]) {
    (!strcmp(str1, str2)) ? printf("\t\tPASSED\n") : printf("\t\tRecieve %s instead of %s.\n", str1, str2);
}

void test_place_to_string()
{
    printf("\ttest_place_to_string :\n");
    str_test(place_to_string(2, 1), "WHITE PAWN");
    str_test(place_to_string(3, 0), "MAX_COLOR NO_SORT");
    str_test(place_to_string(0, 3), "ERROR");
    str_test(place_to_string(-5, 3), "ERROR");
}

void test_dir_to_string()
{
    printf("\ttest_dir_to_string :\n");
    str_test(dir_to_string(-2), "SWEST");
    str_test(dir_to_string(3), "NORTH");
    str_test(dir_to_string(-5), "ERROR");
    str_test(dir_to_string(12), "ERROR");
}

void test_world_set_get(struct world_t* world)
{
    printf("\ttest_world_set_get :\n");
    //set index 0 to WHITE PAWN
    world_set(world, 0, WHITE);
    world_set_sort(world, 0, PAWN);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "WHITE PAWN");
    //set index 0 to NO_COLOR NO_SORT
    world_set(world, 0, NO_COLOR);
    world_set_sort(world, 0, NO_SORT);
    str_test(place_to_string(world_get(world, 0), world_get_sort(world, 0)), "NO_COLOR NO_SORT");
}

int main()
{
    printf("test_geometry.c :\n");
    test_place_to_string();
    test_dir_to_string();
    
    struct world_t* world = world_init();
    printf("test_world.c :\n");
    test_world_set_get(world);

    return 0;
}
