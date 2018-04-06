#pragma once

#include "Structures.h"

typedef struct Saver Saver;

Saver *create_saver(const char *output);
void save_vector(Saver *saver, const Vector *vector);
void delete_saver(Saver *saver);
