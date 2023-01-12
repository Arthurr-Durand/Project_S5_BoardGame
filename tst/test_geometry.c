#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "test_utilities.h"

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

int main()
{
	puts("test_geometry.c :");
	test_place_to_string();
	test_dir_to_string();

	return 0;
}
