// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_matrix/matrix.h"
#include "libs/lib_algorithms/algorithms.h"

#define EPSILON 0.000001

TEST(TestMatrixLocMin, matrix_loc_min) {
    int iterations = 100;
    Matrix<int> matrix = {
        {3, 1, 2},
        {5, 8, 4},
        {7, 6, 9}
    };

    for (int i = 0; i < iterations; i++) {
        int result = find_local_minimum_gradient_descent(matrix);

        EXPECT_TRUE(result == 6 || result == 1);
    }
}

TEST(TestMatrixLocMin, matrix_one_loc_min) {
    int iterations = 100;
    Matrix<int> matrix = {
        {9, 8, 7},
        {6, 4, 3},
        {5, 2, 1}
    };

    for (int i = 0; i < iterations; i++) {
        int result = find_local_minimum_gradient_descent(matrix);

        EXPECT_EQ(result, 1);
    }
}
