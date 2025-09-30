// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_triangle_matrix/triangle_matrix.h"

#define EPSILON 0.000001

TEST(TestTriangleMatrix, default_init) {
    TriangleMatrix<int> matrix;

    EXPECT_EQ(0, matrix.dim());
}

TEST(TestTriangleMatrix, size_init) {
    TriangleMatrix<int> matrix(3);

    EXPECT_EQ(3, matrix.dim());
}

TEST(TestTriangleMatrix, list_init) {
    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    EXPECT_EQ(3, matrix.dim());
}

TEST(TestTriangleMatrix, list_init_different_size) {
    ASSERT_ANY_THROW(TriangleMatrix<int> matrix({{1, 2, 3}, {4, 5}}));
    ASSERT_ANY_THROW(TriangleMatrix<int> matrix({{1, 2, 3}, {4, 5}, {6, 7}}));
}

TEST(TestTriangleMatrix, copy_init) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    TriangleMatrix<int> matrix_2(matrix_1);

    EXPECT_EQ(3, matrix_2.dim());
}

TEST(TestTriangleMatrix, equality_operator_equal) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2, 3}, {4, 5}, {6}};

    EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(TestTriangleMatrix, equality_operator_different_value) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2, 3}, {4, 5}, {7}};

    EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(TestTriangleMatrix, equality_operator_different_size) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2}, {3}};

    EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(TestTriangleMatrix, inequality_operator_equal) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2, 3}, {4, 5}, {6}};

    EXPECT_FALSE(matrix_1 != matrix_2);
}

TEST(TestTriangleMatrix, inequality_operator_different_value) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2, 3}, {4, 5}, {7}};

    EXPECT_TRUE(matrix_1 != matrix_2);
}

TEST(TestTriangleMatrix, inequality_operator_different_size) {
    TriangleMatrix<int> matrix_1 = {{1, 2, 3}, {4, 5}, {6}};
    TriangleMatrix<int> matrix_2 = {{1, 2}, {3}};

    EXPECT_TRUE(matrix_1 != matrix_2);
}
