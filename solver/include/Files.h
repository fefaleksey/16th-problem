#pragma once

#include "Structures.h"

struct Saver;

typedef struct Saver Saver;

Saver *create_saver(const char *output);
void save_results(Saver *saver, const Vector *vector, int quantity, double points[]);
void delete_saver(Saver *saver);
