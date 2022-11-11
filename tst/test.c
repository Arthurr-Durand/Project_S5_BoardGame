#include <stdio.h>

#include "../src/geometry.h"
#include "../src/world.h"

void test_place_to_string()
{
    printf("\ttest_place_to_string :\n");
    printf("\t\t%d, %d > %s\n", 2, 1, place_to_string(2, 1));
    printf("\t\t%d, %d > %s\n", 3, 0, place_to_string(3, 0));
    printf("\t\t%d, %d > %s\n", 0, 3, place_to_string(0, 3));
    printf("\t\t%d, %d > %s\n", -5, 3, place_to_string(-5, 3));
}

void test_dir_to_string()
{
    printf("\ttest_dir_to_string :\n");
    printf("\t\t%d > %s\n", -2, dir_to_string(-2));
    printf("\t\t%d > %s\n", 3, dir_to_string(3));
    printf("\t\t%d > %s\n", -5, dir_to_string(-5));
    printf("\t\t%d > %s\n", 12, dir_to_string(12));
}

void test_world_set_get(struct world_t* world)
{
    printf("\ttest_world_set_get :\n");
    printf("\t\tset index 0 to WHITE PAWN\n");
    world_set(world, 0, WHITE);
    world_set_sort(world, 0, PAWN);
    printf("\t\t%d > %s\n", 0, place_to_string(world_get(world, 0), world_get_sort(world, 0)));
    printf("\t\tset index 0 to NO_COLOR NO_SORT\n");
    world_set(world, 0, NO_COLOR);
    world_set_sort(world, 0, NO_SORT);
    printf("\t\t%d > %s\n", 0, place_to_string(world_get(world, 0), world_get_sort(world, 0)));
}

int main()
{
    printf("test_geometry.c :\n");
    test_place_to_string();
    test_dir_to_string();
    
    printf("\ttest_world_get :\n");
    struct world_t* world = world_init();

    printf("test_world.c :\n");
    test_world_set_get(world);

    return 0;
}
