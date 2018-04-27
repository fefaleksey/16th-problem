#pragma once

#include "CustomDataTypes.h"

typedef struct Vector Vector;
typedef struct Region Region;
typedef struct Point Point;
typedef struct SingularPoints SingularPoints;


Vector *create_vector(mydouble a
	, mydouble b
	, mydouble c
	, mydouble alpha
	, mydouble beta);

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
	, mydouble beta_step);

SingularPoints *get_singular_points(Vector *vector);

mydouble get_region_a_from(const Region *region);
mydouble get_region_b_from(const Region *region);
mydouble get_region_c_from(const Region *region);
mydouble get_region_alpha_from(const Region *region);
mydouble get_region_beta_from(const Region *region);

mydouble get_region_a_to(const Region *region);
mydouble get_region_b_to(const Region *region);
mydouble get_region_c_to(const Region *region);
mydouble get_region_alpha_to(const Region *region);
mydouble get_region_beta_to(const Region *region);

mydouble get_region_a_step(const Region *region);
mydouble get_region_b_step(const Region *region);
mydouble get_region_c_step(const Region *region);
mydouble get_region_alpha_step(const Region *region);
mydouble get_region_beta_step(const Region *region);

mydouble get_a(const Vector *vector);
mydouble get_b(const Vector *vector);
mydouble get_c(const Vector *vector);
mydouble get_alpha(const Vector *vector);
mydouble get_beta(const Vector *vector);

void set_a(Vector *vector, mydouble a);
void set_b(Vector *vector, mydouble b);
void set_c(Vector *vector, mydouble c);
void set_alpha(Vector *vector, mydouble alpha);
void set_beta(Vector *vector, mydouble beta);

mydouble get_x0(SingularPoints *sPoint);
mydouble get_x1(SingularPoints *sPoint);
mydouble get_x2(SingularPoints *sPoint);
mydouble get_x3(SingularPoints *sPoint);
mydouble get_y0(SingularPoints *sPoint);
mydouble get_y1(SingularPoints *sPoint);
mydouble get_y2(SingularPoints *sPoint);
mydouble get_y3(SingularPoints *sPoint);
int get_numbers(SingularPoints *sPoint);

void set_x0(SingularPoints *sPoint, mydouble x0);
void set_x1(SingularPoints *sPoint, mydouble x1);
void set_x2(SingularPoints *sPoint, mydouble x2);
void set_x3(SingularPoints *sPoint, mydouble x3);
void set_y0(SingularPoints *sPoint, mydouble y0);
void set_y1(SingularPoints *sPoint, mydouble y1);
void set_y2(SingularPoints *sPoint, mydouble y2);
void set_y3(SingularPoints *sPoint, mydouble y3);
void set_numbers(SingularPoints *sPoint, int numbers);

void delete_vector(Vector *vector);
void delete_region(Region *region);