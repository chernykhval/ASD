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

TEST(TestMatrix, access_operator) {
    Matrix<int> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    EXPECT_EQ(1, matrix[0][0]);
    EXPECT_EQ(2, matrix[0][1]);
    EXPECT_EQ(3, matrix[0][2]);
    EXPECT_EQ(4, matrix[1][0]);
    EXPECT_EQ(5, matrix[1][1]);
    EXPECT_EQ(6, matrix[1][2]);
}

TEST(TestMatrix, add_with_matrix) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1, 1}
    };
    Matrix<int> matrix_3 = matrix_1 + matrix_2;

    EXPECT_EQ(2, matrix_3[0][0]);
    EXPECT_EQ(3, matrix_3[0][1]);
    EXPECT_EQ(4, matrix_3[0][2]);
    EXPECT_EQ(5, matrix_3[1][0]);
    EXPECT_EQ(6, matrix_3[1][1]);
    EXPECT_EQ(7, matrix_3[1][2]);
}

TEST(TestMatrix, add_with_matrix_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1},
        {1, 1},
        {1, 1}
    };

    ASSERT_ANY_THROW(Matrix<int> matrix_3 = matrix_1 + matrix_2);
}

TEST(TestMatrix, sub_with_matrix) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1, 1}
    };
    Matrix<int> matrix_3 = matrix_1 - matrix_2;

    EXPECT_EQ(0, matrix_3[0][0]);
    EXPECT_EQ(1, matrix_3[0][1]);
    EXPECT_EQ(2, matrix_3[0][2]);
    EXPECT_EQ(3, matrix_3[1][0]);
    EXPECT_EQ(4, matrix_3[1][1]);
    EXPECT_EQ(5, matrix_3[1][2]);
}

TEST(TestMatrix, sub_with_matrix_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1},
        {1, 1},
        {1, 1}
    };

    ASSERT_ANY_THROW(Matrix<int> matrix_3 = matrix_1 - matrix_2);
}

TEST(TestMatrix, transpose) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = matrix_1.transpose();

    EXPECT_EQ(1, matrix_2[0][0]);
    EXPECT_EQ(4, matrix_2[0][1]);
    EXPECT_EQ(2, matrix_2[1][0]);
    EXPECT_EQ(5, matrix_2[1][1]);
    EXPECT_EQ(3, matrix_2[2][0]);
    EXPECT_EQ(6, matrix_2[2][1]);
}

TEST(TestMatrix, mult_with_matrix) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };
    Matrix<int> matrix_3 = matrix_1 * matrix_2;

    EXPECT_EQ(3, matrix_3.rows());
    EXPECT_EQ(3, matrix_3.cols());
    EXPECT_EQ(1, matrix_3[0][0]);
    EXPECT_EQ(2, matrix_3[0][1]);
    EXPECT_EQ(1, matrix_3[0][2]);
    EXPECT_EQ(3, matrix_3[1][0]);
    EXPECT_EQ(4, matrix_3[1][1]);
    EXPECT_EQ(3, matrix_3[1][2]);
    EXPECT_EQ(5, matrix_3[2][0]);
    EXPECT_EQ(6, matrix_3[2][1]);
    EXPECT_EQ(5, matrix_3[2][2]);
}
