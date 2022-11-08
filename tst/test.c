#include <stdio.h>

#include "../src/geometry.h"

/*
void test_place_to_string()
{
    printf("test_place_to_string :\n");
    printf("%d, %d > %s\n", 2, 1, place_to_string(2, 1));
    printf("%d, %d > %s\n", 0, 3, place_to_string(0, 3));
}
*/

void test_dir_to_string()
{
    printf("test_dir_to_string :\n");
    printf("%d > %s\n", -2, dir_to_string(-2));
    printf("%d > %s\n", 3, dir_to_string(3));
    printf("%d > %s\n", -5, dir_to_string(-5));
    printf("%d > %s\n", 12, dir_to_string(12));
}

int main()
{
    printf("test.c :\n");
    //test_place_to_string();
    test_dir_to_string();
    return 0;
}