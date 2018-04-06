#include "../include/Structures.h"
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

const double get_region_a_from(const Region *region)
{
	return region->a_from;
}

const double get_region_b_from(const Region *region)
{
	return region->b_from;
}

const double get_region_c_from(const Region *region)
{
	return region->c_from;
}

const double get_region_alpha_from(const Region *region)
{
	return region->alpha_from;
}

const double get_region_beta_from(const Region *region)
{
	return region->beta_from;
}

const double get_region_a_to(const Region *region)
{
	return region->a_to;
}

const double get_region_b_to(const Region *region)
{
	return region->b_to;
}

const double get_region_c_to(const Region *region)
{
	return region->c_to;
}

const double get_region_alpha_to(const Region *region)
{
	return region->alpha_to;
}

const double get_region_beta_to(const Region *region)
{
	return region->beta_to;
}

const double get_region_a_step(const Region *region)
{
	return region->a_step;
}

const double get_region_b_step(const Region *region)
{
	return region->b_step;
}

const double get_region_c_step(const Region *region)
{
	return region->c_step;
}

const double get_region_alpha_step(const Region *region)
{
	return region->alpha_step;
}

const double get_region_beta_step(const Region *region)
{
	return region->beta_step;
}

const double get_a(const Vector *vector)
{
	return vector->a;
}

const double get_b(const Vector *vector)
{
	return vector->b;
}

const double get_c(const Vector *vector)
{
	return vector->c;
}

const double get_alpha(const Vector *vector)
{
	return vector->alpha;
}

const double get_beta(const Vector *vector)
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

void delete_vector(Vector *vector)
{
	free(vector);
}

void delete_region(Region *region)
{
	free(region);
}