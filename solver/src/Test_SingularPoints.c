#include "../include/Test_SingularPoints.h"
#include "../include/Tests.h"

int tests_run = 0;
int correct_tests = 0;
int count_t = 0;

static char * test_solve_linear_eqation()
{
    mu_begin();
    Vector * vector = create_vector(0.0, 0.0, 0.0, 0.0, 0.0);
    SingularPoints * sPoint = get_singular_points(vector);
    mu_assert(2, solve_linear_equation(2.0, 6.0, sPoint));
    mu_assert(1, solve_linear_equation(2.0, 0.0, sPoint));
    mu_assert(1, solve_linear_equation(-2.0, 0.0, sPoint));
    mu_assert(2, solve_linear_equation(2.0, 6.0, sPoint));
    mu_assert(2, solve_linear_equation(2.0, 6.0, sPoint));
    mu_assert(1, solve_linear_equation(1.0, 1.0, sPoint));
    mu_end();
    return 0;
}

static char * test_solve_square_eqation()
{
    mu_begin();
    Vector * vector = create_vector(0.0, 0.0, 0.0, 0.0, 0.0);
    SingularPoints * sPoint = get_singular_points(vector);
    mu_assert(1,solve_square_equation(1.0, 0.0, 0.0001, sPoint));
    mu_assert(3,solve_square_equation(1.0, 0.0, -0.0001, sPoint));
    mu_assert(1,solve_square_equation(1.0, 0.0, 0.000000, sPoint));
    mu_assert(1,solve_square_equation(1.0, 0.0, 0.000, sPoint));
    mu_assert(1,solve_square_equation(1.0, 0.0, 0.0, sPoint));
    mu_assert(1,solve_square_equation(1.0, 0.0, 999999.0, sPoint));
    mu_assert(3,solve_square_equation(1.0, 0.0, -999999.0, sPoint));
    mu_assert(1,solve_square_equation(1.0, 2.0, 1.0, sPoint));
    mu_assert(2,solve_square_equation(1.0, -2.0, 1.0, sPoint));
    mu_assert(1,solve_square_equation(-1.0, -2.0, -1.0, sPoint));
    mu_assert(2,solve_square_equation(-1.0, 2.0, -1.0, sPoint));
    mu_assert(2,solve_square_equation(1.0, 198.0, 9801.0, sPoint));
    mu_assert(1,solve_square_equation(1.0, 198.0, 9802.0, sPoint));
    mu_end();
    return 0;
}

static char * test_solve_cubic_eqation()
{
    mu_begin();
    Vector * vector = create_vector(0.0, 0.0, 0.0, 0.0, 0.0);
    SingularPoints * sPoint = get_singular_points(vector);
    mu_assert(2,solve_cubic_equation(8.0, 7.0, -4.0, 1.0, sPoint));// корень олоко -1 и 0 по стандарту.
    printf(" \n %lf %lf %lf %lf \n", get_x0(sPoint), get_x1(sPoint),get_x2(sPoint),get_x3(sPoint));
    mu_assert(2,solve_cubic_equation(1.0, -2.0, 1.0, 0.0, sPoint));// 0, 1 - корни ур-ия.
    printf(" \n %lf %lf %lf %lf \n", get_x0(sPoint), get_x1(sPoint),get_x2(sPoint),get_x3(sPoint));
    mu_assert(2,solve_cubic_equation(1.0, 100.0, 99.0, 0.0, sPoint));
    printf(" \n %lf %lf %lf %lf \n", get_x0(sPoint), get_x1(sPoint),get_x2(sPoint),get_x3(sPoint));
    mu_end();
    return 0;
}

static char * all_tests()
{
    mu_run_test(test_solve_linear_eqation);
    mu_run_test(test_solve_square_eqation);
    mu_run_test(test_solve_cubic_eqation);
    return 0;
}

void Test_SingularPoints( void )
{
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        if(correct_tests == count_t)
            printf(GREEN("ALL TESTS PASSED\n"));
    }
    printf(CYAN("Tests run: %d\n"), tests_run);
    return;
}