#include "../include/Logic.h"
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include "mpi/mpi.h"

#define QUANTITY_OF_HALF_TURN 2
#define EPS 0.000001
#define MAX_QUANTITY_OF_STEPS 10000000


const long double fi(long double x, long double y);
const long double psi(Vector *vector, long double x, long double y);
void set_next_point(Vector *vector, long double last_x, long double last_y, long double *next_x, long double *next_y, long double h);
int pass_few_semicircle(long double start_x, long double start_y, Vector *vector, int quantity, long double *rez_x, long double *rez_y);
int find_cycles_in_sp_environs(Vector *vector, long double x0, long double y0, long double to, unsigned int quantity_steps);

void swap(long double *a, long double *b)
{
	long double c = *a;
	*a = *b;
	*b = c;
}

int get_direction(long double from, long double to)
{
	if (from < to)
	{
		return 1;
	}

	return from > to ? -1 : 0;
}

int test(int argc, char **argv)
{
	int q[4] = {0};
	int myrank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	printf("%d %d\n", myrank, nprocs);
	Vector *vector;
	for (int i = 0; i < nprocs; ++i) {
		if (myrank == i) {
			vector = create_vector(-10.0 + 0.00001 * i, 2.7, 0.4, -437.5, 0.003);
			int quantity = find_cycles_in_sp_environs(vector, 0, 0, 10, 100);
			delete_vector(vector);
			q[i] = quantity;
		}
	}
	MPI_Finalize();
	printf("%d %d %d %d\n", q[0], q[1], q[2], q[3]);
	return q[0];
}

int find_cycles_in_region(Region *region, Saver *saver, int argc, char **argv)
{
	const long double a_from = get_region_a_from(region);
	const long double b_from = get_region_b_from(region);
	const long double c_from = get_region_c_from(region);
	const long double alpha_from = get_region_alpha_from(region);
	const long double beta_from = get_region_beta_from(region);

	const long double a_to = get_region_a_to(region);
	const long double b_to = get_region_b_to(region);
	const long double c_to = get_region_c_to(region);
	const long double alpha_to = get_region_alpha_to(region);
	const long double beta_to = get_region_beta_to(region);

	const long double a_step = get_region_a_step(region);
	const long double b_step = get_region_b_step(region);
	const long double c_step = get_region_c_step(region);
	const long double alpha_step = get_region_alpha_step(region);
	const long double beta_step = get_region_beta_step(region);


	MPI_Init(&argc, &argv);
	for (long double i = a_from; i <= a_to; i = i + a_step) {
		for (long double j = b_from; j <= b_to; j = j + b_step) {
			for (long double k = c_from; k <= c_to; k = k + c_step) {
				for (long double l = alpha_from; l <= alpha_to; l = l + alpha_step) {
					for (long double m = beta_from; m <= beta_to; m = m + beta_step) {
						Vector *vector = create_vector(i, j, k, l, m);
						int quantity = find_cycles_in_sp_environs(vector, 0, 0, 10, 20);
						if(quantity >= 3)
						{
							save_vector(saver, vector);
						}
						delete_vector(vector);
					}
				}
			}
		}
	}
	MPI_Finalize();
	return 0;
}

//(x0, y0) -- singular point
int find_cycles_in_sp_environs(Vector*vector, long double x0, long double y0, long double to, unsigned int quantity_steps)
{
	assert(quantity_steps);
	long double step = fabsl((to - x0)) / quantity_steps;
	long double coshi_x = x0;
	long double coshi_y = y0;
	long double last_x, last_y = coshi_y;
	long double next_x, next_y;
	int last_direction = 1, new_direction;
	int quantity = 0;
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("******%d******\n", myrank);
	for (int i = 0; i < quantity_steps; ++i) {
		coshi_x += step;
		last_x = coshi_x;
			if (pass_few_semicircle(last_x, last_y, vector, QUANTITY_OF_HALF_TURN, &next_x, &next_y)) {
			return -1; // ...
		}
		printf("%Lf %Lf || %Lf %Lf\n", last_x, last_y, next_x, next_y);
		new_direction = get_direction(last_x, next_x);
		if (last_direction != new_direction) {
			//printf("%.10lf %.10lf %d %d\n", last_x, next_x, last_direction, new_direction);
			long double right_x = coshi_x, left_x = coshi_x - step;
			while (right_x - left_x > EPS) {
				printf("***%Lf %Lf\n", left_x, right_x);
				long double new_x = left_x + (right_x - left_x) / 2;
				long double x, y;
				pass_few_semicircle(new_x, y0, vector, QUANTITY_OF_HALF_TURN, &x, &y);
				if (get_direction(new_x, x) == last_direction/*???*/) {
					left_x = new_x;
				}
				else {
					right_x = new_x;
				}
			}
			printf("%.10Lf %.10Lf %d %d\n", left_x, right_x, last_direction, new_direction);
			++quantity;
			last_direction = new_direction;
		}
	}
	/*
	for (int i = 0; i < quantity_steps; ++i) {
		coshi_x += step;
		last_x = coshi_x;
		if (pass_few_semicircle(last_x, last_y, vector, QUANTITY_OF_HALF_TURN, &next_x, &next_y)) {
			return -1; // ...
		}
		//printf("%lf %lf || %lf %lf\n", last_x, last_y, next_x, next_y);
		new_direction = get_direction(last_x, next_x);
		if (last_direction != new_direction) {
			if (step < EPS) {
				printf("%.10lf %.10lf %d %d\n", last_x, next_x, last_direction, new_direction);
				++quantity;
			}
			else {
				long double last_coshi = coshi_x - step; // * 1.1;
				quantity += find_cycles_in_sp_environs(vector, last_coshi, coshi_y, next_x, 100);
			}
			last_direction = new_direction;
		}
	}
	*/
	return quantity;
}

// TODO: пофиксить
int pass_few_semicircle(long double start_x, long double start_y, Vector *vector, int quantity, long double *rez_x, long double *rez_y)
{
	const long double h = 0.000001;
	long double y0 = start_y;
	long double last_x = start_x;
	long double last_y = start_y;
	long double next_x = 0;
	long double next_y = 0;
	int counter = -1;

	int quantitySteps = 0;
	while (counter < quantity && quantitySteps < MAX_QUANTITY_OF_STEPS) {
		quantitySteps++;
		set_next_point(vector, last_x, last_y, &next_x, &next_y, h);
		if (last_y >= y0 && next_y < y0 || last_y <= y0 && next_y > y0) {
			counter++;
		}
		last_x = next_x;
		last_y = next_y;
		if (quantitySteps == MAX_QUANTITY_OF_STEPS) {
			return 1;
		}
	}
	//printf("%lf %lf\n", next_x, next_y);
	*rez_x = next_x;
	*rez_y = next_y;
	return 0;
}


const long double fi(const long double x, const long double y)
{
	return x * x + x * y + y;
}

const long double psi(Vector *vector, const long double x, const long double y)
{
	const long double a = get_a(vector);
	const long double b = get_b(vector);
	const long double c = get_c(vector);
	const long double alpha = get_alpha(vector);
	const long double beta = get_beta(vector);

	return a * x * x + b * x * y + c * y * y + alpha * x + beta * y;
}

void set_next_point(Vector *vector, long double last_x, long double last_y, long double *next_x, long double *next_y, const long double h)
{
	const long double x = last_x;
	const long double y = last_y;

	const long double k11 = h * fi(x, y);
	const long double k21 = h * psi(vector, x, y);

	const long double k12 = h * fi(x + k11 / 2, y + k21 / 2);
	const long double k22 = h * psi(vector, x + k11 / 2, y + k21 / 2);

	const long double k13 = h * fi(x + k12 / 2, y + k22 / 2);
	const long double k23 = h * psi(vector, x + k12 / 2, y + k22 / 2);

	const long double k14 = h * fi(x + k13, y + k23);
	const long double k24 = h * psi(vector, x + k13, y + k23);

	*next_x = x + (k11 + k12 + k13 + k14) / 6;
	*next_y = y + (k21 + k22 + k23 + k24) / 6;
}

int FindCentre(long double start_x, long double start_y, Vector *vector, long double *rez_x, long double *rez_y)
{
	const long double error = 0.01;
	long double last_x = start_x;
	long double last_y = start_y;
	long double next_x;
	long double next_y;

	do {
		if (pass_few_semicircle(last_x, last_y, vector, 1, &next_x, &next_y)) {
			return 1;
		}

		if (last_x < next_x) {
			next_x -= (next_x - last_x) / 2;
		}
		else if (last_x > next_x) {
			swap(&last_x, &next_x);
			swap(&last_y, &next_y);
		}

	}
	while (next_x - start_x > error);
	*rez_x = next_x;
	*rez_y = next_y;
	return 0;
}
