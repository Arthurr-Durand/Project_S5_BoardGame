#include <stdio.h>
#include <stdlib.h>

#include "world.h"
#include "test_utilities.h"

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

int main()
{
	puts("test_world.c :");
	test_world_set_get();

	return 0;
}
