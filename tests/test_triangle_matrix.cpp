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

TEST(TestTriangleMatrix, add_with_matrix) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5, 4},
        {3, 2},
        {1}
    };
    TriangleMatrix<int> matrix_3 = matrix_1 + matrix_2;
    TriangleMatrix<int> result = {
        {7, 7, 7},
        {7, 7},
        {7}
    };

    EXPECT_TRUE(matrix_3 == result);
}

TEST(TestTriangleMatrix, add_with_matrix_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5},
        {3}
    };

    ASSERT_ANY_THROW(TriangleMatrix<int> matrix_3 = matrix_1 + matrix_2);
}

TEST(TestTriangleMatrix, sub_with_matrix) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5, 4},
        {3, 2},
        {1}
    };
    TriangleMatrix<int> matrix_3 = matrix_1 - matrix_2;
    TriangleMatrix<int> result = {
        {-5, -3, -1},
        {1, 3},
        {5}
    };

    EXPECT_TRUE(matrix_3 == result);
}

TEST(TestTriangleMatrix, sub_with_matrix_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5},
        {3}
    };

    ASSERT_ANY_THROW(TriangleMatrix<int> matrix_3 = matrix_1 - matrix_2);
}

TEST(TestTriangleMatrix, mult_with_matrix) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5, 4},
        {3, 2},
        {1}
    };
    TriangleMatrix<int> matrix_3 = matrix_1 * matrix_2;
    TriangleMatrix<int> result = {
        {6, 11, 11},
        {12, 13},
        {6}
    };

    EXPECT_TRUE(matrix_3 == result);
}

TEST(TestTriangleMatrix, mult_with_matrix_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {6, 5},
        {3}
    };

    ASSERT_ANY_THROW(TriangleMatrix<int> matrix_3 = matrix_1 * matrix_2);
}

TEST(TestTriangleMatrix, assignment_deep_copy) {
    TriangleMatrix<int> matrix_1 = {
        {10, 20},
        {30}
    };

    TriangleMatrix<int> matrix_2(2);

    matrix_2 = matrix_1;

    EXPECT_EQ(2, matrix_2.dim());
    EXPECT_TRUE(matrix_1 == matrix_2);
}

// Add two tests

TEST(TestTriangleMatrix, compound_add) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1},
        {1}
    };

    matrix_1 += matrix_2;

    TriangleMatrix<int> result = {
        {2, 3, 4},
        {5, 6},
        {7}
    };

    EXPECT_TRUE(matrix_1 == result);
}

TEST(TestTriangleMatrix, compound_add_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2},
        {3}
    };
    TriangleMatrix<int> matrix_2 = {
        {1, 0, 1},
        {1, 0},
        {1}
    };

    ASSERT_ANY_THROW(matrix_1 += matrix_2);
}

TEST(TestTriangleMatrix, compound_sub) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5},
        {6}
    };
    TriangleMatrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1},
        {1}
    };

    matrix_1 -= matrix_2;

    TriangleMatrix<int> result = {
        {0, 1, 2},
        {3, 4},
        {5}
    };

    EXPECT_TRUE(matrix_1 == result);
}

TEST(TestTriangleMatrix, compound_sub_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2},
        {3}
    };
    TriangleMatrix<int> matrix_2 = {
        {1, 0, 1},
        {1, 0},
        {1}
    };

    ASSERT_ANY_THROW(matrix_1 -= matrix_2);
}
