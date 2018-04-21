#pragma once

#include "SingularPoints.h"
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define RED(text) ANSI_COLOR_RED text ANSI_COLOR_RESET
#define GREEN(text) ANSI_COLOR_GREEN text ANSI_COLOR_RESET
#define MAGENTA(text) ANSI_COLOR_MAGENTA text ANSI_COLOR_RESET
#define YELLOW(text) ANSI_COLOR_YELLOW text ANSI_COLOR_RESET
#define BLUE(text) ANSI_COLOR_BLUE text ANSI_COLOR_RESET
#define CYAN(text) ANSI_COLOR_CYAN text ANSI_COLOR_RESET

#define mu_assert(val1, val2) do { count_t++; if (val1 != val2) \
    {printf(RED("LINE: %d [ERROR], where your answer: "), __LINE__); print(val2); printf(RED(" and right one is ")); print(val1); printf("\n");} else correct_tests++; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
#define mu_begin() (printf(BLUE("[ %s ] - started \n"), __func__))
#define mu_end() (printf(BLUE("[ %s ] - ended\n\n"), __func__))

#define print(X)          \
    _Generic((X),       \
    int: print_int,       \
    double: print_double,     \
    default: print_int    \
)(X)

extern int tests_run;
extern int correct_tests;
extern int count_t;

void print_int(int value)
{
    printf(YELLOW("%d"), value);
}

void print_double(double value)
{
    printf(YELLOW("%lf"), value);
}