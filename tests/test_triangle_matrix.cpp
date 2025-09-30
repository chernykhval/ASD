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
