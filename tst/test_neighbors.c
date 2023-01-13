#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "neighbors.h"
#include "test_utilities.h"

void test_get_neighbor()
{
	puts("\ttest_get_neighbor :");
	int_test(get_neighbor(90, NEAST), 81);
	int_test(get_neighbor(6, EAST), 7);
	int_test(get_neighbor(28, SEAST), 39);
	int_test(get_neighbor(46, NWEST), 35);
	int_test(get_neighbor(99, SWEST), 8);
}

void test_get_neighbors0()
{
	puts("\ttest_get_neighbors 0 :");
	init_neighbors(0);
	int_test(get_neighbors2(0).n[0].i, 11);
	int_test(get_neighbors2(0).n[0].d, SEAST);
	int_test(get_neighbors2(33).n[0].i, 44);
	int_test(get_neighbors2(33).n[1].d, SOUTH);
	int_test(get_neighbors2(19).n[0].i, 20);
	int_test(get_neighbors2(19).n[3].d, WEST);
}

void test_get_neighbors1()
{
	puts("\ttest_get_neighbors 1 :");
	init_neighbors(1);
	int_test(get_neighbors2(33).n[0].i, 42);
	int_test(get_neighbors2(33).n[0].d, SWEST);
	int_test(get_neighbors2(33).n[1].i, 23);
	int_test(get_neighbors2(33).n[1].d, NORTH);
	int_test(get_neighbors2(33).n[2].i, 44);
	int_test(get_neighbors2(33).n[2].d, SEAST);
}

void test_get_neighbors2()
{
	puts("\ttest_get_neighbors 2 :");
	init_neighbors(2);
	int_test(get_neighbors2(33).n[0].i, 43);
	int_test(get_neighbors2(33).n[0].d, SOUTH);
	int_test(get_neighbors2(33).n[1].i, 32);
	int_test(get_neighbors2(33).n[1].d, WEST);
	int_test(get_neighbors2(33).n[2].i, 34);
	int_test(get_neighbors2(33).n[2].d, EAST);
}

int main()
{
	puts("test_neighbors.c :");
	test_get_neighbor();
	test_get_neighbors0();
	test_get_neighbors1();
	test_get_neighbors2();

	return 0;
}
