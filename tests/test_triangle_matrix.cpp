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


TEST(TriangleMatrixMultiplicationTest, BasicMultiplication) {
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

TEST(TriangleMatrixMultiplicationTest, MultiplicationWithIdentity) {
    TriangleMatrix<int> identity = {
        {1, 0, 0},
        {1, 0},
        {1}
    };

    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    TriangleMatrix<int> result1 = matrix * identity;
    TriangleMatrix<int> result2 = identity * matrix;

    EXPECT_TRUE(result1 == matrix);
    EXPECT_TRUE(result2 == matrix);
}

TEST(TriangleMatrixMultiplicationTest, MultiplicationWithZero) {
    TriangleMatrix<int> zero = {
        {0, 0, 0},
        {0, 0},
        {0}
    };

    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    TriangleMatrix<int> result = matrix * zero;
    EXPECT_TRUE(result == zero);
}

TEST(TriangleMatrixMultiplicationTest, NonCommutative) {
    TriangleMatrix<int> A = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    TriangleMatrix<int> B = {
        {2, 1, 1},
        {3, 2},
        {1}
    };

    TriangleMatrix<int> AB = A * B;
    TriangleMatrix<int> BA = B * A;

    EXPECT_FALSE(AB == BA);

    TriangleMatrix<int> expected_AB = {
        {2, 7, 8},
        {12, 13},
        {6}
    };

    TriangleMatrix<int> expected_BA = {
        {2, 8, 17},
        {12, 27},
        {6}
    };

    EXPECT_TRUE(AB == expected_AB);
    EXPECT_TRUE(BA == expected_BA);
}

TEST(TriangleMatrixMultiplicationTest, SingleElement) {
    TriangleMatrix<int> A = {{5}};
    TriangleMatrix<int> B = {{3}};

    TriangleMatrix<int> result = A * B;
    TriangleMatrix<int> expected = {{15}};

    EXPECT_TRUE(result == expected);
}

TEST(TriangleMatrixMultiplicationTest, TwoByTwo) {
    TriangleMatrix<int> A = {
        {2, 3},
        {4}
    };

    TriangleMatrix<int> B = {
        {1, 2},
        {3}
    };

    TriangleMatrix<int> result = A * B;
    TriangleMatrix<int> expected = {
        {2, 13},
        {12}
    };

    EXPECT_TRUE(result == expected);
}

TEST(TriangleMatrixMultiplicationTest, SizeMismatch) {
    TriangleMatrix<int> A = {
        {1, 2},
        {3}
    };

    TriangleMatrix<int> B = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    EXPECT_THROW(A * B, std::invalid_argument);
}

TEST(TriangleMatrixMultiplicationTest, Associative) {
    TriangleMatrix<int> A = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    TriangleMatrix<int> B = {
        {2, 1, 1},
        {3, 2},
        {1}
    };

    TriangleMatrix<int> C = {
        {1, 0, 2},
        {2, 1},
        {3}
    };

    TriangleMatrix<int> AB_times_C = (A * B) * C;
    TriangleMatrix<int> A_times_BC = A * (B * C);

    EXPECT_TRUE(AB_times_C == A_times_BC);
}

TEST(TriangleMatrixMultiplicationTest, DoublePrecision) {
    TriangleMatrix<double> A = {
        {1.5, 2.5},
        {3.5}
    };

    TriangleMatrix<double> B = {
        {2.0, 1.0},
        {2.0}
    };

    TriangleMatrix<double> result = A * B;
    TriangleMatrix<double> expected = {
        {3.0, 6.5},
        {7.0}
    };

    EXPECT_TRUE(result == expected);
}

TEST(TriangleMatrixMultiplicationTest, ChainMultiplication) {
    TriangleMatrix<int> A = {{2}};

    TriangleMatrix<int> A2 = A * A;
    TriangleMatrix<int> A4 = A2 * A2;
    TriangleMatrix<int> expected = {{16}};

    EXPECT_TRUE(A4 == expected);
}
