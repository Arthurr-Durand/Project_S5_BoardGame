#include <stdio.h>

#include "../src/geometry.h"

void test_place_to_string()
{
    printf("test_place_to_string :\n");
    printf("%d, %d > %s\n", 2, 1, place_to_string(2, 1));
    printf("%d, %d > %s\n", 0, 3, place_to_string(0, 3));
}

void dir_to_string()
{
    printf("test_place_to_string :\n");
    printf("%d, %d > %s\n", -2, 1, dir_to_string(-2, 1));
    printf("%d, %d > %s\n", 0, 3, dir_to_string(0, 3));
    printf("%d, %d > %s\n", -5, 12, dir_to_string(-5, 12));
}

int main()
{
    printf("test.c :\n");
    test_place_to_string();
    return 0;
}