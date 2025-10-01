// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
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

TEST(TestMatrix, list_init_different_size) {
    ASSERT_ANY_THROW(Matrix<int> matrix({{1, 2, 3}, {4, 5}}));
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

TEST(TestMatrix, const_access_operator) {
    const Matrix<int> matrix = {
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

TEST(TestMatrix, access_operator_write) {
    Matrix<int> matrix = {
        {1, 2, 3},
        {4, 5, 6}
    };

    matrix[0][0] = 123;

    EXPECT_EQ(123, matrix[0][0]);
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

TEST(TestMatrix, mult_with_matrix_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2, 7},
        {3, 4, 8},
        {5, 6, 9}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };

    ASSERT_ANY_THROW(Matrix<int> matrix_3 = matrix_1 * matrix_2;);
}

TEST(TestMatrix, assignment_deep_copy) {
    Matrix<int> matrix_1 = {
        {10, 20},
        {30, 40}
    };

    Matrix<int> matrix_2(1, 1);

    matrix_2 = matrix_1;

    EXPECT_EQ(2, matrix_2.rows());
    EXPECT_EQ(2, matrix_2.cols());
    EXPECT_EQ(10, matrix_2[0][0]);
    EXPECT_EQ(40, matrix_2[1][1]);

    matrix_1[0][0] = 99;

    EXPECT_EQ(10, matrix_2[0][0]);
    EXPECT_EQ(99, matrix_1[0][0]);
}

TEST(TestMatrix, assignment_self_assignment) {
    Matrix<int> matrix = {
        {1, 2},
        {3, 4}
    };

    const int expected_row = matrix.rows();
    const int expected_val = matrix[1][0];

    matrix = matrix;

    EXPECT_EQ(expected_row, matrix.rows());
    EXPECT_EQ(expected_val, matrix[1][0]);
    EXPECT_EQ(4, matrix[1][1]);

    Matrix<int>& assigned_ref = (matrix = matrix);
    EXPECT_EQ(&matrix, &assigned_ref);
}

TEST(TestMatrix, assignment_chained) {
    Matrix<int> matrix_A(1, 1);
    Matrix<int> matrix_B(1, 1);
    Matrix<int> matrix_C = {{5, 6}};

    matrix_A = matrix_B = matrix_C;

    EXPECT_EQ(5, matrix_A[0][0]);
    EXPECT_EQ(6, matrix_A[0][1]);

    EXPECT_EQ(5, matrix_B[0][0]);
    EXPECT_EQ(6, matrix_B[0][1]);

    matrix_C[0][0] = 99;
    EXPECT_EQ(5, matrix_A[0][0]);
}

TEST(TestMatrix, compound_add) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1, 1}
    };

    matrix_1 += matrix_2;

    EXPECT_EQ(2, matrix_1[0][0]);
    EXPECT_EQ(3, matrix_1[0][1]);
    EXPECT_EQ(4, matrix_1[0][2]);
    EXPECT_EQ(5, matrix_1[1][0]);
    EXPECT_EQ(6, matrix_1[1][1]);
    EXPECT_EQ(7, matrix_1[1][2]);
}

TEST(TestMatrix, compound_add_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };

    ASSERT_ANY_THROW(matrix_1 += matrix_2);
}

TEST(TestMatrix, compound_sub) {
    Matrix<int> matrix_1 = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 1, 1},
        {1, 1, 1}
    };

    matrix_1 -= matrix_2;

    EXPECT_EQ(0, matrix_1[0][0]);
    EXPECT_EQ(1, matrix_1[0][1]);
    EXPECT_EQ(2, matrix_1[0][2]);
    EXPECT_EQ(3, matrix_1[1][0]);
    EXPECT_EQ(4, matrix_1[1][1]);
    EXPECT_EQ(5, matrix_1[1][2]);
}

TEST(TestMatrix, compound_sub_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };

    ASSERT_ANY_THROW(matrix_1 -= matrix_2);
}

TEST(TestMatrix, compound_mult) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };

    matrix_1 *= matrix_2;

    EXPECT_EQ(3, matrix_1.rows());
    EXPECT_EQ(3, matrix_1.cols());
    EXPECT_EQ(1, matrix_1[0][0]);
    EXPECT_EQ(2, matrix_1[0][1]);
    EXPECT_EQ(1, matrix_1[0][2]);
    EXPECT_EQ(3, matrix_1[1][0]);
    EXPECT_EQ(4, matrix_1[1][1]);
    EXPECT_EQ(3, matrix_1[1][2]);
    EXPECT_EQ(5, matrix_1[2][0]);
    EXPECT_EQ(6, matrix_1[2][1]);
    EXPECT_EQ(5, matrix_1[2][2]);
}

TEST(TestMatrix, compound_mult_different_size) {
    Matrix<int> matrix_1 = {
        {1, 2, 7},
        {3, 4, 8},
        {5, 6, 9}
    };
    Matrix<int> matrix_2 = {
        {1, 0, 1},
        {0, 1, 0}
    };

    ASSERT_ANY_THROW(matrix_1 *= matrix_2);
}

TEST(TestMatrix, mult_by_scalar) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    Matrix<int> matrix_2 = matrix_1 * 2;

    EXPECT_EQ(2, matrix_2[0][0]);
    EXPECT_EQ(4, matrix_2[0][1]);
    EXPECT_EQ(6, matrix_2[1][0]);
    EXPECT_EQ(8, matrix_2[1][1]);
    EXPECT_EQ(10, matrix_2[2][0]);
    EXPECT_EQ(12, matrix_2[2][1]);
}

TEST(TestMatrix, div_by_scalar) {
    Matrix<int> matrix_1 = {
        {2, 4},
        {6, 8},
        {10, 12}
    };
    Matrix<int> matrix_2 = matrix_1 / 2;

    EXPECT_EQ(1, matrix_2[0][0]);
    EXPECT_EQ(2, matrix_2[0][1]);
    EXPECT_EQ(3, matrix_2[1][0]);
    EXPECT_EQ(4, matrix_2[1][1]);
    EXPECT_EQ(5, matrix_2[2][0]);
    EXPECT_EQ(6, matrix_2[2][1]);
}

TEST(TestMatrix, div_by_zero) {
    Matrix<int> matrix_1 = {
        {2, 4},
        {6, 8},
        {10, 12}
    };

    ASSERT_ANY_THROW(Matrix<int> matrix_2 = matrix_1 / 0);
}

TEST(TestMatrix, compound_mult_by_scalar) {
    Matrix<int> matrix_1 = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    matrix_1 *= 2;

    EXPECT_EQ(2, matrix_1[0][0]);
    EXPECT_EQ(4, matrix_1[0][1]);
    EXPECT_EQ(6, matrix_1[1][0]);
    EXPECT_EQ(8, matrix_1[1][1]);
    EXPECT_EQ(10, matrix_1[2][0]);
    EXPECT_EQ(12, matrix_1[2][1]);
}

TEST(TestMatrix, compound_div_by_scalar) {
    Matrix<int> matrix_1 = {
        {2, 4},
        {6, 8},
        {10, 12}
    };
    matrix_1 /= 2;

    EXPECT_EQ(1, matrix_1[0][0]);
    EXPECT_EQ(2, matrix_1[0][1]);
    EXPECT_EQ(3, matrix_1[1][0]);
    EXPECT_EQ(4, matrix_1[1][1]);
    EXPECT_EQ(5, matrix_1[2][0]);
    EXPECT_EQ(6, matrix_1[2][1]);
}

TEST(TestMatrix, compound_div_by_zero) {
    Matrix<int> matrix_1 = {
        {2, 4},
        {6, 8},
        {10, 12}
    };

    ASSERT_ANY_THROW(matrix_1 /= 0);
}

TEST(TestMatrix, mult_by_mvector) {
    Matrix<int> matrix = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    MVector<int> mvector = {1, 2};
    MVector<int> result = matrix * mvector;

    EXPECT_EQ(5, result[0]);
    EXPECT_EQ(11, result[1]);
    EXPECT_EQ(17, result[2]);
}

TEST(TestMatrix, mult_by_mvector_different_size) {
    Matrix<int> matrix = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    MVector<int> mvector = {1, 2, 3};

    EXPECT_ANY_THROW(MVector<int> result = matrix * mvector);
}

TEST(TestMatrix, equality_operator_equal) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2}, {3, 4}};

    EXPECT_TRUE(matrix_1 == matrix_2);
}

TEST(TestMatrix, equality_operator_different_value) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2}, {3, 99}};

    EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(TestMatrix, equality_operator_different_size) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_FALSE(matrix_1 == matrix_2);
}

TEST(TestMatrix, inequality_operator_equal) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2}, {3, 4}};

    EXPECT_FALSE(matrix_1 != matrix_2);
}

TEST(TestMatrix, inequality_operator_different_value) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2}, {3, 99}};

    EXPECT_TRUE(matrix_1 != matrix_2);
}

TEST(TestMatrix, inequality_operator_different_size) {
    Matrix<int> matrix_1 = {{1, 2}, {3, 4}};
    Matrix<int> matrix_2 = {{1, 2, 3}, {4, 5, 6}};

    EXPECT_TRUE(matrix_1 != matrix_2);
}

TEST(TestMatrix, basic_integer_output) {
    Matrix<int> matrix = {
        {10, 200},
        {3, 40}
    };

    const std::string expected =
        "| 10 200 |\n"
        "|  3  40 |\n";

    std::stringstream ss;

    ss << matrix;

    EXPECT_EQ(expected, ss.str());
}

TEST(TestMatrix, floating_point_output) {
    Matrix<double> matrix = {
        {1.23, 10.0},
        {100.12345, 0.5}
    };

    const std::string expected =
        "|    1.23  10 |\n"
        "| 100.123 0.5 |\n";

    std::stringstream ss;

    ss << matrix;

    EXPECT_EQ(expected, ss.str());
}

TEST(TestMatrix, empty_matrix_output) {
    Matrix<int> matrix(0, 0);

    const std::string expected = "";

    std::stringstream ss;
    ss << matrix;

    EXPECT_EQ(expected, ss.str());
}

TEST(TestMatrixOutput, ColumnarWidthAlignment) {
    Matrix<int> matrix = {
        {1000, 20, 3},
        {1, 5, 300},
        {10, 2, 30},
    };

    const std::string expected =
        "| 1000 20   3 |\n"
        "|    1  5 300 |\n"
        "|   10  2  30 |\n";

    std::stringstream ss;
    ss << matrix;

    EXPECT_EQ(expected, ss.str());
}

TEST(TestMatrix, basic_correct_input) {
    Matrix<int> matrix(2, 3);

    const std::string input_data = "1 2 3 \n 4 5 6";

    std::stringstream ss(input_data);

    ss >> matrix;

    EXPECT_FALSE(ss.fail());

    EXPECT_EQ(2, matrix.rows());
    EXPECT_EQ(3, matrix.cols());
    EXPECT_EQ(1, matrix[0][0]);
    EXPECT_EQ(3, matrix[0][2]);
    EXPECT_EQ(4, matrix[1][0]);
    EXPECT_EQ(6, matrix[1][2]);
}

TEST(TestMatrix, format_error_handling_input) {
    Matrix<double> matrix(3, 3);

    const std::string input_data = "1.1 2.2 3.3 \n 4.4 X 5.5 6.6";

    std::stringstream ss(input_data);

    ss >> matrix;

    EXPECT_TRUE(ss.fail());

    EXPECT_EQ(1.1, matrix[0][0]);
    EXPECT_EQ(4.4, matrix[1][0]);
    EXPECT_EQ(0.0, matrix[1][1]);
}

TEST(TestMatrix, end_of_file_handling_input) {
    Matrix<int> matrix(3, 3);

    const std::string input_data = "1 2 3 4 5";

    std::stringstream ss(input_data);

    ss >> matrix;

    EXPECT_TRUE(ss.eof());
    EXPECT_TRUE(ss.fail());

    EXPECT_EQ(5, matrix[1][1]);
    EXPECT_EQ(0, matrix[2][2]);
}
