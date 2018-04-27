#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <mpi/mpi.h>
#include "../include/Logic.h"

static const int QUANTITY_OF_HALF_TURN = 2;
static const mydouble K = 1;
#define EPS 0.000000001
#define MAX_QUANTITY_OF_STEPS 100000000


mydouble fi(mydouble x, mydouble y);
mydouble psi(Vector *vector, mydouble x, mydouble y);
void set_next_point(Vector *vector, mydouble x, mydouble y, mydouble *next_x, mydouble *next_y, mydouble h);
int pass_few_semicircle(mydouble start_x, mydouble start_y, Vector *vector, int quantity, mydouble *rez_x, mydouble *rez_y);
int find_cycles_in_sp_environs(Vector *vector, mydouble x0, mydouble y0, mydouble to, unsigned int quantity_steps);

int get_direction(mydouble from, mydouble to)
{
	if (from < to)
	{
		return 1;
	}

	return from > to ? -1 : 0;
}

int test(int argc, char **argv)
{
	int q[8] = {0};
	int myrank, nprocs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	printf("%d %d\n", myrank, nprocs);
	Vector *vector;
	for (int i = 0; i < nprocs; ++i) {
		if (myrank == i) {
			//vector = create_vector(-10.0 + 0.00001 * i, 2.7, 0.4, -440, 0.003);
			//vector = create_vector(-0.2, 1, 0.5, -15, 0.13);
			vector = create_vector(-10, 2.2, 0.7, -72.7778, 0.0015);
			//vector = create_vector(-10.5, 1.925 + 0.002 * i, 0.4, -2012, 0.2);
			//int quantity = find_cycles_in_sp_environs(vector, 0, 0, 20, 200);
			int quantity = find_cycles_in_sp_environs(vector, 0, 0, 20, 1000);
			delete_vector(vector);
			q[i] = quantity;
		}
	}
	MPI_Finalize();
	printf("%d %d %d %d %d %d %d %d\n", q[0], q[1], q[2], q[3], q[4], q[5], q[6], q[7]);
	return q[0];
}

int find_cycles_in_region(Region *region, Saver *saver, int argc, char **argv)
{
	const mydouble a_from = get_region_a_from(region);
	const mydouble b_from = get_region_b_from(region);
	const mydouble c_from = get_region_c_from(region);
	const mydouble alpha_from = get_region_alpha_from(region);
	const mydouble beta_from = get_region_beta_from(region);

	const mydouble a_to = get_region_a_to(region);
	const mydouble b_to = get_region_b_to(region);
	const mydouble c_to = get_region_c_to(region);
	const mydouble alpha_to = get_region_alpha_to(region);
	const mydouble beta_to = get_region_beta_to(region);

	const mydouble a_step = get_region_a_step(region);
	const mydouble b_step = get_region_b_step(region);
	const mydouble c_step = get_region_c_step(region);
	const mydouble alpha_step = get_region_alpha_step(region);
	const mydouble beta_step = get_region_beta_step(region);


	MPI_Init(&argc, &argv);
	for (mydouble i = a_from; i <= a_to; i = i + a_step) {
		for (mydouble j = b_from; j <= b_to; j = j + b_step) {
			for (mydouble k = c_from; k <= c_to; k = k + c_step) {
				for (mydouble l = alpha_from; l <= alpha_to; l = l + alpha_step) {
					for (mydouble m = beta_from; m <= beta_to; m = m + beta_step) {
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
int find_cycles_in_sp_environs(Vector*vector, mydouble x0, mydouble y0, mydouble to, unsigned int quantity_steps)
{
	assert(quantity_steps);
	mydouble step = fabs((to - x0)) / quantity_steps;
	mydouble coshi_x = x0;
	mydouble coshi_y = y0;
	mydouble last_x, last_y = coshi_y;
	mydouble next_x, next_y;
	int last_direction = 1, new_direction;
	int quantity = 0;
	int myrank;
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	printf("******%d******\n", myrank);
	unsigned int i;
	for (i = 0; i < quantity_steps; ++i) {
		coshi_x += step;
		last_x = coshi_x;
			if (pass_few_semicircle(last_x, last_y, vector, QUANTITY_OF_HALF_TURN, &next_x, &next_y)) {
				return -1; // ...
		}
		printf("%lf %lf || %lf %lf\n", last_x, last_y, next_x, next_y);
		new_direction = get_direction(last_x, next_x);
		if (last_direction != new_direction) {
			//printf("%.10lf %.10lf %d %d\n", last_x, next_x, last_direction, new_direction);
			mydouble right_x = coshi_x, left_x = coshi_x - step;
			while (right_x - left_x > EPS) {
//				printf("***%lf %lf\n", left_x, right_x);
				mydouble new_x = left_x + (right_x - left_x) / 2;
				mydouble x, y;
				pass_few_semicircle(new_x, y0, vector, QUANTITY_OF_HALF_TURN, &x, &y);
				if (get_direction(new_x, x) == last_direction/*???*/) {
					left_x = new_x;
				}
				else {
					right_x = new_x;
				}
			}
			printf("%.10lf %.10lf %d %d\n", left_x, right_x, last_direction, new_direction);
			++quantity;
			last_direction = new_direction;
		}
	}
	return quantity;
}

int pass_few_semicircle(mydouble start_x, mydouble start_y, Vector *vector, int quantity, mydouble *rez_x, mydouble *rez_y)
{
	const mydouble h = 0.000001;
	mydouble y0 = start_y;
	mydouble last_x = start_x;
	mydouble last_y = start_y;
	mydouble next_x = 0;
	mydouble next_y = 0;
	int counter = -1;

	int quantitySteps = 0;
	while (counter < quantity && quantitySteps < MAX_QUANTITY_OF_STEPS) {
		quantitySteps++;
		set_next_point(vector, last_x, last_y, &next_x, &next_y, h);
		if ( (last_y >= y0 && next_y < y0) || (last_y <= y0 && next_y > y0) ) { //parentheses ???
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


mydouble fi(const mydouble x, const mydouble y)
{
	return K * x * x + K * x * y + y;
}

mydouble psi(Vector *vector, const mydouble x, const mydouble y)
{
	const mydouble a = get_a(vector);
	const mydouble b = get_b(vector);
	const mydouble c = get_c(vector);
	const mydouble alpha = get_alpha(vector);
	const mydouble beta = get_beta(vector);
	return K * a * x * x + K * b * x * y + K * c * y * y + alpha * x + beta * y;
}

void set_next_point(Vector *vector, mydouble x, mydouble y, mydouble *next_x, mydouble *next_y, const mydouble h)
{
	const mydouble k11 = h * fi(x, y);
	const mydouble k21 = h * psi(vector, x, y);

	const mydouble k12 = h * fi(x + k11 / 2, y + k21 / 2);
	const mydouble k22 = h * psi(vector, x + k11 / 2, y + k21 / 2);

	const mydouble k13 = h * fi(x + k12 / 2, y + k22 / 2);
	const mydouble k23 = h * psi(vector, x + k12 / 2, y + k22 / 2);

	const mydouble k14 = h * fi(x + k13, y + k23);
	const mydouble k24 = h * psi(vector, x + k13, y + k23);

	*next_x = x + (k11 + 2 * k12 + 2 * k13 + k14) / 6;
	*next_y = y + (k21 + 2 * k22 + 2 * k23 + k24) / 6;
}