#include "../include/Structures.h"
#include "../include/SingularPoints.h"
#include <stdlib.h>


typedef struct Vector
{
	mydouble a;
	mydouble b;
	mydouble c;
	mydouble alpha;
	mydouble beta;

} Vector;

typedef struct Region
{
	mydouble a_from;
	mydouble a_to;
	mydouble a_step;

	mydouble b_from;
	mydouble b_to;
	mydouble b_step;

	mydouble c_from;
	mydouble c_to;
	mydouble c_step;

	mydouble alpha_from;
	mydouble alpha_to;
	mydouble alpha_step;

	mydouble beta_from;
	mydouble beta_to;
	mydouble beta_step;
} Region;

typedef struct Point
{
	mydouble x;
	mydouble y;
} Point;

typedef struct SingularPoints
{
	mydouble x0;
	mydouble y0;

	mydouble x1;
	mydouble y1;

	mydouble x2;
	mydouble y2;

	mydouble x3;
	mydouble y3;

	int numbers;
} SingularPoints;

Region *create_region(mydouble a_from
					, mydouble a_to
					, mydouble a_step
					, mydouble b_from
					, mydouble b_to
					, mydouble b_step
					, mydouble c_from
					, mydouble c_to
					, mydouble c_step
					, mydouble alpha_from
					, mydouble alpha_to
					, mydouble alpha_step
					, mydouble beta_from
					, mydouble beta_to
					, mydouble beta_step)
{
	Region *region = malloc(sizeof(Region));
	region->a_from = a_from;
	region->a_to = a_to;
	region->a_step = a_step;

	region->b_from = b_from;
	region->b_to = b_to;
	region->b_step = b_step;

	region->c_from = c_from;
	region->c_to = c_to;
	region->c_step = c_step;

	region->alpha_from = alpha_from;
	region->alpha_to = alpha_to;
	region->alpha_step = alpha_step;

	region->beta_from = beta_from;
	region->beta_to = beta_to;
	region->beta_step = beta_step;

	return region;
}

Vector *create_vector(const mydouble a
	, const mydouble b
	, const mydouble c
	, const mydouble alpha
	, const mydouble beta)
{
	Vector *vector = malloc(sizeof(Vector));

	vector->a = a;
	vector->b = b;
	vector->c = c;
	vector->alpha = alpha;
	vector->beta = beta;
	return vector;
}

SingularPoints *get_singular_points(Vector *vector)
{
	SingularPoints *sPoint = malloc(sizeof(SingularPoints));

	set_x0(sPoint, 0);
	set_y0(sPoint, 0);

	set_numbers(sPoint, num(vector, sPoint));
	return sPoint;
}

mydouble get_region_a_from(const Region *region)
{
	return region->a_from;
}

mydouble get_region_b_from(const Region *region)
{
	return region->b_from;
}

mydouble get_region_c_from(const Region *region)
{
	return region->c_from;
}

mydouble get_region_alpha_from(const Region *region)
{
	return region->alpha_from;
}

mydouble get_region_beta_from(const Region *region)
{
	return region->beta_from;
}

mydouble get_region_a_to(const Region *region)
{
	return region->a_to;
}

mydouble get_region_b_to(const Region *region)
{
	return region->b_to;
}

mydouble get_region_c_to(const Region *region)
{
	return region->c_to;
}

mydouble get_region_alpha_to(const Region *region)
{
	return region->alpha_to;
}

mydouble get_region_beta_to(const Region *region)
{
	return region->beta_to;
}

mydouble get_region_a_step(const Region *region)
{
	return region->a_step;
}

mydouble get_region_b_step(const Region *region)
{
	return region->b_step;
}

mydouble get_region_c_step(const Region *region)
{
	return region->c_step;
}

mydouble get_region_alpha_step(const Region *region)
{
	return region->alpha_step;
}

mydouble get_region_beta_step(const Region *region)
{
	return region->beta_step;
}

mydouble get_a(const Vector *vector)
{
	return vector->a;
}

mydouble get_b(const Vector *vector)
{
	return vector->b;
}

mydouble get_c(const Vector *vector)
{
	return vector->c;
}

mydouble get_alpha(const Vector *vector)
{
	return vector->alpha;
}

mydouble get_beta(const Vector *vector)
{
	return vector->beta;
}

void set_a(Vector *vector, const mydouble a)
{
	vector->a = a;
}

void set_b(Vector *vector, const mydouble b)
{
	vector->b = b;
}

void set_c(Vector *vector, const mydouble c)
{
	vector->c = c;
}

void set_alpha(Vector *vector, const mydouble alpha)
{
	vector->alpha = alpha;
}

void set_beta(Vector *vector, const mydouble beta)
{
	vector->beta = beta;
}

mydouble get_x0(SingularPoints *sPoint)
{
	return sPoint->x0;
}

mydouble get_x1(SingularPoints *sPoint)
{
	return sPoint->x1;
}

mydouble get_x2(SingularPoints *sPoint)
{
	return sPoint->x2;
}

mydouble get_x3(SingularPoints *sPoint)
{
	return sPoint->x3;
}

mydouble get_y0(SingularPoints *sPoint)
{
	return sPoint->y0;
}

mydouble get_y1(SingularPoints *sPoint)
{
	return sPoint->y1;
}

mydouble get_y2(SingularPoints *sPoint)
{
	return sPoint->y2;
}

mydouble get_y3(SingularPoints *sPoint)
{
	return sPoint->y3;
}

int  get_numbers(SingularPoints *sPoint)
{
	return sPoint->numbers;
}

void set_x0(SingularPoints *sPoint, mydouble x0)
{
	sPoint->x0 = x0;
}

void set_x1(SingularPoints *sPoint, mydouble x1)
{
	sPoint->x1 = x1;
}

void set_x2(SingularPoints *sPoint, mydouble x2)
{
	sPoint->x2 = x2;
}

void set_x3(SingularPoints *sPoint, mydouble x3)
{
	sPoint->x3 = x3;
}

void set_y0(SingularPoints *sPoint, mydouble y0)
{
	sPoint->y0 = y0;
}

void set_y1(SingularPoints *sPoint, mydouble y1)
{
	sPoint->y1 = y1;
}

void set_y2(SingularPoints *sPoint, mydouble y2)
{
	sPoint->y2 = y2;
}

void set_y3(SingularPoints *sPoint, mydouble y3)
{
	sPoint->y3 = y3;
}

void set_numbers(SingularPoints *sPoint, int numbers)
{
	sPoint->numbers = numbers;
}

void delete_vector(Vector *vector)
{
	free(vector);
}

void delete_region(Region *region)
{
	free(region);
}