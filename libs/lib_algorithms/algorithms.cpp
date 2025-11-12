// Copyright 2025 Chernykh Valentin

#include <random>
#include "libs/lib_algorithms/algorithms.h"
#include "libs/lib_matrix/matrix.h"
#include "libs/lib_dsu/dsu.h"

int find_local_minimum_gradient_descent(const Matrix<int>& matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist_rows(0, matrix.rows() - 1);
    std::uniform_int_distribution<> dist_cols(0, matrix.cols() - 1);

    int current_row = dist_rows(gen);
    int current_col = dist_cols(gen);
    int next_row = current_row;
    int next_col = current_col;
    int min;

    int matrix_rows = matrix.rows();
    int matrix_cols = matrix.cols();

    MVector<MVector<int>> directions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1}
    };

    while (true) {
        bool found_min = false;

        min = matrix[current_row][current_col];

        for (int i = 0; i < directions.size(); i++) {
            int new_row = current_row + directions[i][0];
            int new_col = current_col + directions[i][1];

            if (new_row >= 0 && new_row < matrix_rows &&
                new_col >= 0 && new_col < matrix_cols) {
                if (matrix[new_row][new_col] < min) {
                    min = matrix[new_row][new_col];
                    next_row = new_row;
                    next_col = new_col;
                    found_min = true;
                }
            }
        }

        if (found_min == false) {
            break;
        }

        current_row = next_row;
        current_col = next_col;
    }

    return min;
}

int calculate_islands_count(const Matrix<int>& matrix) {
    size_t rows = matrix.rows();
    size_t cols = matrix.cols();
    DSU islands(rows * cols);
    int water_count = 0;

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                water_count++;
                continue;
            }

            if (matrix[i][j] != 1) {
                throw std::invalid_argument("Matrix contains wrong elements");
            }

            int current_index = i * cols + j;

            if (j + 1 < cols && matrix[i][j + 1] == 1) {
                islands.unite(current_index, i * cols + (j + 1));
            }

            if (i + 1 < rows && matrix[i + 1][j] == 1) {
                islands.unite(current_index, (i + 1) * cols + j);
            }
        }
    }

    return islands.count() - water_count;
}
