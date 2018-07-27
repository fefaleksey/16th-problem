#include <stdio.h>
#include <stdlib.h>
#include "include/Logic.h"

int main(int argc, char **argv)
{
	Region *region = create_region(  2, 2, 1,
									 2, 2, 1,
									 2, 2, 1,
									 2, 2, 1,
									 2, 2, 1);
	find_cycles_in_region(region, argc, argv);
	return 0;
}
