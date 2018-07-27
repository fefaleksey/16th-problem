#include "../include/SingularPoints.h"
#include <math.h>

int three_solution(double x1, double x2, double x3, SingularPoints *sPoint)
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

int two_solution(double x1, double x2, SingularPoints *sPoint) {
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

int  solve_cubic_equation(const double A, const double B, const double C, const double D, SingularPoints *sPoint)
{
	const double p = C / A - (B * B) / (3 * A * A);
	const double q = 2 * B * B * B / (27 * A * A * A) - (B * C) / (3 * A * A) + D / A;
	const double Q1 = (p * p * p / 27) + (q * q / 4);

	if (fabs(Q1) < EPS)
	{
		const double alpha = cbrt(-q / 2);
		const double x1 = 2 * alpha - B / (3 * A);
		const double x2 = -alpha - B / (3 * A);

		return two_solution(x1, x2, sPoint);
	}
	else if (Q1 > 0)
	{
		const double alpha = cbrt(-q / 2 + sqrt(Q1));
		const double beta = cbrt(-q / 2 - sqrt(Q1));
		const double x = alpha + beta - B / (3 * A);

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
		const double r = sqrt(-p * p * p / 27);
		const double fi = acos(-q / (2 * p)) / 3;

		const double x1 = 2 * cbrt(r) * cos(fi) - B / (3 * A);
		const double x2 = 2 * cbrt(r) * cos(fi + 2 * M_PI / 3) - B / (3 * A);
		const double x3 = 2 * cbrt(r) * cos(fi + 4 * M_PI / 3) - B / (3 * A);

		return three_solution(x1, x2, x3, sPoint);
	}
}

int solve_square_equation( const double A, const double B, const double C, SingularPoints *sPoint)
{
	const double Dis = B * B - 4 * A * C;
	if (fabs(Dis) < EPS)
	{
		const double x = -B / (2 * A);
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
		const double x1 = (-B + sqrt(Dis)) / (2 * A);
		const double x2 = (-B - sqrt(Dis)) / (2 * A);

		return two_solution(x1, x2, sPoint);
	}
	else
	{
		return 1;
	}
}

int solve_linear_equation( const double A, const double B, SingularPoints *sPoint)
{
	const double x = -B / A;
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
	const double a = get_a(vector);
	const double b = get_b(vector);
	const double c = get_c(vector);
	const double alpha = get_alpha(vector);
	const double beta = get_beta(vector);

	const double A1 = a - b + c;
	const double B1 = 2 * a - b + alpha - beta;
	const double C1 = a - beta + 2 * alpha;
	const double D1 = alpha;

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
