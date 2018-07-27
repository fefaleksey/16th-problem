#include "../include/Files.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Saver
{
	FILE *output;
} Saver;

Saver *create_saver(const char *output)
{
	Saver *saver = malloc(sizeof(Saver));
	saver->output = fopen(output, "w");
	return saver;
}

//y always == 0, is saved only x
void save_vector(Saver *saver, const Vector *vector)
{
	fprintf(saver->output
		, "%lf %lf %lf %lf %lf\n"
		, get_a(vector)
		, get_b(vector)
		, get_c(vector)
		, get_alpha(vector)
		, get_beta(vector));
}

void save_results(Saver *saver, const Vector *vector, int quantity, double points[])
{
	save_vector(saver, vector);
	fprintf(saver->output, "%d\n", quantity);
	for (int i = 0; i < quantity; ++i) {
		fprintf(saver->output, "%.9lf\n", points[i]);
	}
}

void delete_saver(Saver *saver)
{
	fclose(saver->output);
	free(saver);
}
