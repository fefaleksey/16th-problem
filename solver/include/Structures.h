#pragma once

typedef struct Vector Vector;
typedef struct Region Region;
typedef struct Point Point;
typedef struct SingularPoints SingularPoints;


Vector *create_vector(double a
	, double b
	, double c
	, double alpha
	, double beta);

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
	, double beta_step);

SingularPoints *get_singular_points(Vector *vector);

double get_region_a_from(const Region *region);
double get_region_b_from(const Region *region);
double get_region_c_from(const Region *region);
double get_region_alpha_from(const Region *region);
double get_region_beta_from(const Region *region);

double get_region_a_to(const Region *region);
double get_region_b_to(const Region *region);
double get_region_c_to(const Region *region);
double get_region_alpha_to(const Region *region);
double get_region_beta_to(const Region *region);

double get_region_a_step(const Region *region);
double get_region_b_step(const Region *region);
double get_region_c_step(const Region *region);
double get_region_alpha_step(const Region *region);
double get_region_beta_step(const Region *region);

double get_a(const Vector *vector);
double get_b(const Vector *vector);
double get_c(const Vector *vector);
double get_alpha(const Vector *vector);
double get_beta(const Vector *vector);

void set_a(Vector *vector, double a);
void set_b(Vector *vector, double b);
void set_c(Vector *vector, double c);
void set_alpha(Vector *vector, double alpha);
void set_beta(Vector *vector, double beta);

double get_x0(SingularPoints *sPoint);
double get_x1(SingularPoints *sPoint);
double get_x2(SingularPoints *sPoint);
double get_x3(SingularPoints *sPoint);
double get_y0(SingularPoints *sPoint);
double get_y1(SingularPoints *sPoint);
double get_y2(SingularPoints *sPoint);
double get_y3(SingularPoints *sPoint);
int get_numbers(SingularPoints *sPoint);

void set_x0(SingularPoints *sPoint, double x0);
void set_x1(SingularPoints *sPoint, double x1);
void set_x2(SingularPoints *sPoint, double x2);
void set_x3(SingularPoints *sPoint, double x3);
void set_y0(SingularPoints *sPoint, double y0);
void set_y1(SingularPoints *sPoint, double y1);
void set_y2(SingularPoints *sPoint, double y2);
void set_y3(SingularPoints *sPoint, double y3);
void set_numbers(SingularPoints *sPoint, int numbers);

void delete_vector(Vector *vector);
void delete_region(Region *region);