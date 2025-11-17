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

TEST(TestCalculateIslandsCount, MapWithTwoIslands) {
    Matrix<int> matrix = {
        {0, 1, 1, 0, 0, 1},
        {0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 1},
        {0, 0, 0, 0, 1, 0}
    };

    EXPECT_EQ(calculate_islands_count(matrix), 2);
}

TEST(TestCalculateIslandsCount, WrongMap) {
    Matrix<int> matrix = {
        {0, 1},
        {2, 3}
    };
    EXPECT_THROW(calculate_islands_count(matrix), std::invalid_argument);
}

TEST(TestCalculateIslandsCount, EmptyMap) {
    Matrix<int> matrix = {};
    EXPECT_EQ(calculate_islands_count(matrix), 0);
}

TEST(TestCalculateIslandsCount, SingleIsland) {
    Matrix<int> matrix = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 1);
}

TEST(TestCalculateIslandsCount, AllWater) {
    Matrix<int> matrix = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 0);
}

TEST(TestCalculateIslandsCount, ChessBoardPattern) {
    Matrix<int> matrix = {
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 8);
}

TEST(TestCalculateIslandsCount, SinglePixelIslands) {
    Matrix<int> matrix = {
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 5);
}

TEST(TestCalculateIslandsCount, SpiralIsland) {
    Matrix<int> matrix = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 1);
}

TEST(TestCalculateIslandsCount, DiagonalIslands) {
    Matrix<int> matrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 4);
}

TEST(TestCalculateIslandsCount, ComplexShape) {
    Matrix<int> matrix = {
        {1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {1, 0, 1, 0, 1}
    };
    EXPECT_EQ(calculate_islands_count(matrix), 6);
}
