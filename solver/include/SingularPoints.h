#pragma once

#include "Structures.h"

int num (Vector *vector, SingularPoints *sPoint);
int solve_cubic_equation(const double A, const double B, const double C, const double D, SingularPoints *sPoint);
int solve_square_equation( const double A, const double B, const double C, SingularPoints *sPoint);
int solve_linear_equation( const double A, const double B, SingularPoints *sPoint);