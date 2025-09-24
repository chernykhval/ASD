// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_matrix/matrix.h"

#define EPSILON 0.000001

TEST(TestMatrix, default_init) {
    Matrix<int> matrix;

    EXPECT_EQ(0, matrix.rows());
    EXPECT_EQ(0, matrix.cols());
}

TEST(TestMatrix, size_init) {
    Matrix<int> matrix(2, 3);

    EXPECT_EQ(2, matrix.rows());
    EXPECT_EQ(3, matrix.cols());
}

TEST(TestMatrix, list_init) {
    Matrix<int> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    EXPECT_EQ(2, matrix.rows());
    EXPECT_EQ(3, matrix.cols());
}

TEST(TestMatrix, copy_init) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };

    Matrix<int> matrix_2(matrix_1);

    EXPECT_EQ(2, matrix_2.rows());
    EXPECT_EQ(3, matrix_2.cols());
}
