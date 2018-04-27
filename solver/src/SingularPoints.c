#include "../include/SingularPoints.h"
#include <math.h>

#define EPS 0.0000000001

int three_solution(mydouble x1, mydouble x2, mydouble x3, SingularPoints *sPoint)
{
	int i = 1;
	if (fabs(x1 + 1) > EPS && fabs(x1) > EPS)
	{
		set_x1(sPoint, x1);
		set_y1(sPoint, -(x1 * x1) / (x1 + 1));
		i++;

		if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
		{
			set_x2(sPoint, x2);
			set_y2(sPoint, -(x2 * x2) / (x2 + 1));
			i++;

			if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
			{
				set_x3(sPoint, x3);
				set_y3(sPoint, -(x3 * x3) / (x3 + 1));
				i++;
			}

		}
		else if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
		{
			set_x2(sPoint, x3);
			set_y2(sPoint, -(x3 * x3) / (x3 + 1));
			i++;
		}
	}
	else if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
	{
		set_x1(sPoint, x2);
		set_y1(sPoint, -(x2 * x2) / (x2 + 1));
		i++;

		if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
		{
			set_x2(sPoint, x3);
			set_y2(sPoint, -(x3 * x3) / (x3 + 1));
			i++;
		}
	}
	else if (fabs(x3 + 1) > EPS && fabs(x3) > EPS)
	{
		set_x1(sPoint, x3);
		set_y1(sPoint, -(x3 * x3) / (x3 + 1));
		i++;
	}

	return i;
}

int two_solution(mydouble x1, mydouble x2, SingularPoints *sPoint) {
	int i = 1;
	if (fabs(x1 + 1) > EPS && fabs(x1) > EPS)
	{
		set_x1(sPoint, x1);
		set_y1(sPoint, -(x1 * x1) / (x1 + 1));
		i++;

		if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
		{
			set_x2(sPoint, x2);
			set_y2(sPoint, -(x2 * x2) / (x2 + 1));
			i++;
		}
	} else if (fabs(x2 + 1) > EPS && fabs(x2) > EPS)
	{
		set_x1(sPoint, x2);
		set_y1(sPoint, -(x2 * x2) / (x2 + 1));
		i++;
	}

	return i;
}

int  solve_cubic_equation(const mydouble A, const mydouble B, const mydouble C, const mydouble D, SingularPoints *sPoint)
{
	const mydouble p = C / A - (B * B) / (3 * A * A);
	const mydouble q = 2 * B * B * B / (27 * A * A * A) - (B * C) / (3 * A * A) + D / A;
	const mydouble Q1 = (p * p * p / 27) + (q * q / 4);

	if (fabs(Q1) < EPS)
	{
		const mydouble alpha = cbrt(-q / 2);
		const mydouble x1 = 2 * alpha - B / (3 * A);
		const mydouble x2 = -alpha - B / (3 * A);

		return two_solution(x1, x2, sPoint);
	}
	else if (Q1 > 0)
	{
		const mydouble alpha = cbrt(-q / 2 + sqrt(Q1));
		const mydouble beta = cbrt(-q / 2 - sqrt(Q1));
		const mydouble x = alpha + beta - B / (3 * A);

		if (fabs(x + 1) > EPS && fabs(x) > EPS)
		{
			set_x1(sPoint, x);
			set_y1(sPoint, -(x * x) / (x + 1));

			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		const mydouble r = sqrt(-p * p * p / 27);
		const mydouble fi = acos(-q / (2 * p)) / 3;

		const mydouble x1 = 2 * cbrt(r) * cos(fi) - B / (3 * A);
		const mydouble x2 = 2 * cbrt(r) * cos(fi + 2 * M_PI / 3) - B / (3 * A);
		const mydouble x3 = 2 * cbrt(r) * cos(fi + 4 * M_PI / 3) - B / (3 * A);

		return three_solution(x1, x2, x3, sPoint);
	}
}

int solve_square_equation( const mydouble A, const mydouble B, const mydouble C, SingularPoints *sPoint)
{
	const mydouble Dis = B * B - 4 * A * C;
	if (fabs(Dis) < EPS)
	{
		const mydouble x = -B / (2 * A);
		if (fabs(x + 1) > EPS && fabs(x) > EPS)
		{
			set_x1(sPoint, x);
			set_y1(sPoint, -(x * x) / (x + 1));

			return 2;
		}
		else
		{
			return 1;
		}
	}
	if (Dis > 0)
	{
		const mydouble x1 = (-B + sqrt(Dis)) / (2 * A);
		const mydouble x2 = (-B - sqrt(Dis)) / (2 * A);

		return two_solution(x1, x2, sPoint);
	}
	else
	{
		return 1;
	}
}

int solve_linear_equation( const mydouble A, const mydouble B, SingularPoints *sPoint)
{
	const mydouble x = -B / A;
	if (fabs(x - 1) > EPS && fabs(x) > EPS)
	{
		set_x1(sPoint, x);
		set_x1(sPoint, -(x * x) / (x + 1));
		return 2;
	}
	else
	{
		return 1;
	}
}

int num ( Vector *vector, SingularPoints *sPoint)
{
	const mydouble a = get_a(vector);
	const mydouble b = get_b(vector);
	const mydouble c = get_c(vector);
	const mydouble alpha = get_alpha(vector);
	const mydouble beta = get_beta(vector);

	const mydouble A1 = a - b + c;
	const mydouble B1 = 2 * a - b + alpha - beta;
	const mydouble C1 = a - beta + 2 * alpha;
	const mydouble D1 = alpha;

	if (A1 != 0)
	{
		return solve_cubic_equation(A1, B1, C1, D1, sPoint);
	}

	if (B1 != 0)
	{
		return solve_square_equation(B1, C1, D1, sPoint);
	}

	if (C1 != 0)
	{
		return solve_linear_equation(C1, D1, sPoint);
	}
	if (D1 != 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}