#pragma once

typedef struct Vector Vector;
typedef struct Region Region;

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

const double get_region_a_from(const Region *region);
const double get_region_b_from(const Region *region);
const double get_region_c_from(const Region *region);
const double get_region_alpha_from(const Region *region);
const double get_region_beta_from(const Region *region);

const double get_region_a_to(const Region *region);
const double get_region_b_to(const Region *region);
const double get_region_c_to(const Region *region);
const double get_region_alpha_to(const Region *region);
const double get_region_beta_to(const Region *region);

const double get_region_a_step(const Region *region);
const double get_region_b_step(const Region *region);
const double get_region_c_step(const Region *region);
const double get_region_alpha_step(const Region *region);
const double get_region_beta_step(const Region *region);

const double get_a(const Vector *vector);
const double get_b(const Vector *vector);
const double get_c(const Vector *vector);
const double get_alpha(const Vector *vector);
const double get_beta(const Vector *vector);

void set_a(Vector *vector, double a);
void set_b(Vector *vector, double b);
void set_c(Vector *vector, double c);
void set_alpha(Vector *vector, double alpha);
void set_beta(Vector *vector, double beta);

void delete_vector(Vector *vector);
void delete_region(Region *region);