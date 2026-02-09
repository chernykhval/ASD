// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_ALGORITHMS_ALGORITHMS_H_
#define LIBS_LIB_ALGORITHMS_ALGORITHMS_H_

#include "libs/lib_matrix/matrix.h"

int find_local_minimum_gradient_descent(const Matrix<int>& matrix);

int calculate_islands_count(const Matrix<int>& matrix);

void generate(int start_cell, int end_cell, int n, int m);
void print_labyrinth(const Matrix<int>& walls);

#endif  // LIBS_LIB_ALGORITHMS_ALGORITHMS_H_
