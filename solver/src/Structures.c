#include "../include/Structures.h"
#include "../include/SingularPoints.h"
#include <stdlib.h>


typedef struct Vector
{
	double a;
	double b;
	double c;
	double alpha;
	double beta;

} Vector;

typedef struct Region
{
	double a_from;
	double a_to;
	double a_step;

	double b_from;
	double b_to;
	double b_step;

	double c_from;
	double c_to;
	double c_step;

	double alpha_from;
	double alpha_to;
	double alpha_step;

	double beta_from;
	double beta_to;
	double beta_step;
} Region;

typedef struct Point
{
	double x;
	double y;
} Point;

typedef struct SingularPoints
{
	double x0;
	double y0;

	double x1;
	double y1;

	double x2;
	double y2;

	double x3;
	double y3;

	int numbers;
} SingularPoints;

Region *create_region(double a_from
					, double a_to
					, double a_step
					, double b_from
					, double b_to
					, double b_step
					, double c_from
					, double c_to
					, double c_step
					, double alpha_from
					, double alpha_to
					, double alpha_step
					, double beta_from
					, double beta_to
					, double beta_step)
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

Vector *create_vector(const double a
	, const double b
	, const double c
	, const double alpha
	, const double beta)
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

double get_region_a_from(const Region *region)
{
	return region->a_from;
}

double get_region_b_from(const Region *region)
{
	return region->b_from;
}

double get_region_c_from(const Region *region)
{
	return region->c_from;
}

double get_region_alpha_from(const Region *region)
{
	return region->alpha_from;
}

double get_region_beta_from(const Region *region)
{
	return region->beta_from;
}

double get_region_a_to(const Region *region)
{
	return region->a_to;
}

double get_region_b_to(const Region *region)
{
	return region->b_to;
}

double get_region_c_to(const Region *region)
{
	return region->c_to;
}

double get_region_alpha_to(const Region *region)
{
	return region->alpha_to;
}

double get_region_beta_to(const Region *region)
{
	return region->beta_to;
}

double get_region_a_step(const Region *region)
{
	return region->a_step;
}

double get_region_b_step(const Region *region)
{
	return region->b_step;
}

double get_region_c_step(const Region *region)
{
	return region->c_step;
}

double get_region_alpha_step(const Region *region)
{
	return region->alpha_step;
}

double get_region_beta_step(const Region *region)
{
	return region->beta_step;
}

double get_a(const Vector *vector)
{
	return vector->a;
}

double get_b(const Vector *vector)
{
	return vector->b;
}

double get_c(const Vector *vector)
{
	return vector->c;
}

double get_alpha(const Vector *vector)
{
	return vector->alpha;
}

double get_beta(const Vector *vector)
{
	return vector->beta;
}

void set_a(Vector *vector, const double a)
{
	vector->a = a;
}

void set_b(Vector *vector, const double b)
{
	vector->b = b;
}

void set_c(Vector *vector, const double c)
{
	vector->c = c;
}

void set_alpha(Vector *vector, const double alpha)
{
	vector->alpha = alpha;
}

void set_beta(Vector *vector, const double beta)
{
	vector->beta = beta;
}

double get_x0(SingularPoints *sPoint)
{
	return sPoint->x0;
}

double get_x1(SingularPoints *sPoint)
{
	return sPoint->x1;
}

double get_x2(SingularPoints *sPoint)
{
	return sPoint->x2;
}

double get_x3(SingularPoints *sPoint)
{
	return sPoint->x3;
}

double get_y0(SingularPoints *sPoint)
{
	return sPoint->y0;
}

double get_y1(SingularPoints *sPoint)
{
	return sPoint->y1;
}

double get_y2(SingularPoints *sPoint)
{
	return sPoint->y2;
}

double get_y3(SingularPoints *sPoint)
{
	return sPoint->y3;
}

int  get_numbers(SingularPoints *sPoint)
{
	return sPoint->numbers;
}

void set_x0(SingularPoints *sPoint, double x0)
{
	sPoint->x0 = x0;
}

void set_x1(SingularPoints *sPoint, double x1)
{
	sPoint->x1 = x1;
}

void set_x2(SingularPoints *sPoint, double x2)
{
	sPoint->x2 = x2;
}

void set_x3(SingularPoints *sPoint, double x3)
{
	sPoint->x3 = x3;
}

void set_y0(SingularPoints *sPoint, double y0)
{
	sPoint->y0 = y0;
}

void set_y1(SingularPoints *sPoint, double y1)
{
	sPoint->y1 = y1;
}

void set_y2(SingularPoints *sPoint, double y2)
{
	sPoint->y2 = y2;
}

void set_y3(SingularPoints *sPoint, double y3)
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
