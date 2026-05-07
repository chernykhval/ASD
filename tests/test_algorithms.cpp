// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_matrix/matrix.h"
#include "libs/lib_algorithms/algorithms.h"
#include "libs/lib_adj_matrix_graph/adj_matrix_graph.h"

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

TEST(TestLabyrinthGenerate, start_and_end_exception) {
    EXPECT_THROW(generate(-1, 8, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(0, -1, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(0, 15, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(15, 0, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(0, 0, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(0, 4, 3, 3), std::invalid_argument);
    EXPECT_THROW(generate(4, 0, 3, 3), std::invalid_argument);
}

TEST(TestLabyrinthGenerate, generate) {
    generate(0, 15, 4, 4);
}

// A --4-- B
// |       |
// 1       3
// |       |
// C --2-- D
//  \
//   1
//    \
//     E
TEST(TestDijkstra, basic_path) {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 4},
        {'A', 'C', 1},
        {'C', 'D', 2},
        {'C', 'E', 1},
        {'B', 'E', 3}
    });

    auto result = dijkstra<char>(graph, 'A', 'D');

    EXPECT_EQ(result.second, 3);
    EXPECT_EQ(result.first.size(), 3);
    EXPECT_EQ(result.first[0], 'A');
    EXPECT_EQ(result.first[1], 'C');
    EXPECT_EQ(result.first[2], 'D');
}

// Короткий прямой путь vs длинный дешёвый
// A --10-- B
//  \      /
//   5    1
//    \  /
//     C
TEST(TestDijkstra, short_path_not_always_cheapest) {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 10},
        {'A', 'C', 5},
        {'C', 'B', 1}
    });

    auto result = dijkstra<char>(graph, 'A', 'B');

    EXPECT_EQ(result.second, 6);
    EXPECT_EQ(result.first.size(), 3);
    EXPECT_EQ(result.first[0], 'A');
    EXPECT_EQ(result.first[1], 'C');
    EXPECT_EQ(result.first[2], 'B');
}

TEST(TestDijkstra, src_equals_dst) {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 1},
        {'B', 'C', 2}
    });

    auto result = dijkstra<char>(graph, 'A', 'A');

    EXPECT_EQ(result.second, 0);
    EXPECT_EQ(result.first.size(), 1);
    EXPECT_EQ(result.first[0], 'A');
}

TEST(TestDijkstra, no_path) {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 1},
        {'C', 'D', 1}
    }, true);

    auto result = dijkstra<char>(graph, 'A', 'D');

    EXPECT_EQ(result.second, -1);
    EXPECT_EQ(result.first.size(), 0);
}

TEST(TestDijkstra, directed_no_path_back) {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 1},
        {'B', 'C', 2}
    }, true);

    auto fwd = dijkstra<char>(graph, 'A', 'C');
    EXPECT_EQ(fwd.second, 3);

    auto back = dijkstra<char>(graph, 'C', 'A');
    EXPECT_EQ(back.second, -1);
    EXPECT_EQ(back.first.size(), 0);
}

// Невзвешенный: кратчайший путь по числу рёбер
// A - B - C
// |       |
// D - E --+
TEST(TestDijkstra, unweighted_shortest_by_hops) {
    AdjMatrixGraph<char> graph({
        {'A', 'B'},
        {'B', 'C'},
        {'A', 'D'},
        {'D', 'E'},
        {'E', 'C'}
    }, false, false);

    auto result = dijkstra<char>(graph, 'A', 'C');

    EXPECT_EQ(result.second, 2);
    EXPECT_EQ(result.first.size(), 3);
    EXPECT_EQ(result.first[0], 'A');
    EXPECT_EQ(result.first[1], 'B');
    EXPECT_EQ(result.first[2], 'C');
}
