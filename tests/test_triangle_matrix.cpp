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

TEST(TestTriangleMatrix, compound_mult) {
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

    matrix_1 *= matrix_2;

    TriangleMatrix<int> result = {
        {1, 3, 6},
        {4, 9},
        {6}
    };

    EXPECT_TRUE(matrix_1 == result);
}

TEST(TestTriangleMatrix, compound_mult_different_size) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2},
        {3}
    };
    TriangleMatrix<int> matrix_2 = {
        {1, 0, 1},
        {1, 0},
        {1}
    };

    ASSERT_ANY_THROW(matrix_1 *= matrix_2);
}

TEST(TestTriangleMatrix, mult_by_scalar) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2},
        {3}
    };
    TriangleMatrix<int> matrix_2 = matrix_1 * 2;
    TriangleMatrix<int> result = {
        {2, 4},
        {6}
    };

    EXPECT_TRUE(matrix_2 == result);
}

TEST(TestTriangleMatrix, div_by_scalar) {
    TriangleMatrix<int> matrix_1 = {
        {2, 4},
        {6}
    };
    TriangleMatrix<int> matrix_2 = matrix_1 / 2;
    TriangleMatrix<int> result = {
        {1, 2},
        {3}
    };

    EXPECT_TRUE(matrix_2 == result);
}

TEST(TestTriangleMatrix, div_by_zero) {
    TriangleMatrix<int> matrix_1 = {
        {2, 4},
        {6}
    };

    ASSERT_ANY_THROW(TriangleMatrix<int> matrix_2 = matrix_1 / 0);
}

TEST(TestTriangleMatrix, compound_mult_by_scalar) {
    TriangleMatrix<int> matrix_1 = {
        {1, 2},
        {3}
    };
    matrix_1 *= 2;

    TriangleMatrix<int> result = {
        {2, 4},
        {6}
    };

    EXPECT_TRUE(result == matrix_1);
}

TEST(TestTriangleMatrix, compound_div_by_scalar) {
    TriangleMatrix<int> matrix_1 = {
        {2, 4},
        {6}
    };
    matrix_1 /= 2;

    TriangleMatrix<int> result = {
        {1, 2},
        {3}
    };

    EXPECT_TRUE(result == matrix_1);
}

TEST(TestTriangleMatrix, compound_div_by_zero) {
    TriangleMatrix<int> matrix_1 = {
        {2, 4},
        {6}
    };

    ASSERT_ANY_THROW(matrix_1 /= 0);
}

TEST(TestTriangleMatrix, mult_by_mvector) {
    TriangleMatrix<int> matrix = {
        {1, 2},
        {3}
    };
    MVector<int> mvector = {1, 2};
    MVector<int> result = matrix * mvector;

    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(6, result[1]);
}

TEST(TestTriangleMatrix, mult_by_mvector_different_size) {
    TriangleMatrix<int> matrix = {
        {1, 2},
        {3}
    };
    MVector<int> mvector = {1, 2, 3};

    EXPECT_ANY_THROW(MVector<int> result = matrix * mvector);
}

TEST(TestTriangleMatrix, at_method_basic_usage) {
    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    EXPECT_EQ(1, matrix.at(0, 0));
    EXPECT_EQ(2, matrix.at(0, 1));
    EXPECT_EQ(3, matrix.at(0, 2));
    EXPECT_EQ(4, matrix.at(1, 1));
    EXPECT_EQ(5, matrix.at(1, 2));
    EXPECT_EQ(6, matrix.at(2, 2));

    EXPECT_EQ(0, matrix.at(1, 0));
    EXPECT_EQ(0, matrix.at(2, 0));
    EXPECT_EQ(0, matrix.at(2, 1));
}

TEST(TestTriangleMatrix, at_method_out_of_range) {
    TriangleMatrix<int> matrix = {
        {1, 2},
        {3}
    };

    EXPECT_THROW(matrix.at(2, 0), std::out_of_range);
    EXPECT_THROW(matrix.at(0, 2), std::out_of_range);
    EXPECT_THROW(matrix.at(2, 2), std::out_of_range);
    EXPECT_THROW(matrix.at(100, 100), std::out_of_range);
}

TEST(TestTriangleMatrix, set_method_basic_usage) {
    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    matrix.set(0, 1, 10);
    EXPECT_EQ(10, matrix.at(0, 1));

    matrix.set(1, 2, 20);
    EXPECT_EQ(20, matrix.at(1, 2));

    matrix.set(2, 2, 30);
    EXPECT_EQ(30, matrix.at(2, 2));

    EXPECT_EQ(1, matrix.at(0, 0));
    EXPECT_EQ(4, matrix.at(1, 1));
}

TEST(TestTriangleMatrix, set_method_lower_triangle_exception) {
    TriangleMatrix<int> matrix = {
        {1, 2, 3},
        {4, 5},
        {6}
    };

    EXPECT_THROW(matrix.set(1, 0, 10), std::invalid_argument);
    EXPECT_THROW(matrix.set(2, 0, 20), std::invalid_argument);
    EXPECT_THROW(matrix.set(2, 1, 30), std::invalid_argument);

    EXPECT_EQ(1, matrix.at(0, 0));
    EXPECT_EQ(2, matrix.at(0, 1));
    EXPECT_EQ(4, matrix.at(1, 1));
    EXPECT_EQ(0, matrix.at(1, 0));
}

TEST(TestTriangleMatrix, set_method_out_of_range) {
    TriangleMatrix<int> matrix = {
        {1, 2},
        {3}
    };

    EXPECT_THROW(matrix.set(2, 0, 10), std::out_of_range);
    EXPECT_THROW(matrix.set(0, 2, 20), std::out_of_range);
    EXPECT_THROW(matrix.set(2, 2, 30), std::out_of_range);
}
