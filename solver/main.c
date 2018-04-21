#include <stdio.h>
#include <stdlib.h>
#include "include/Logic.h"
#include "include/SingularPoints.h"

int main(int argc, char **argv)
{
    Test_SingularPoints();
	int a = test(argc, argv);
	printf("%d\n", a);
	return 0;
}
