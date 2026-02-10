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

// void generate(int start_cell, int end_cell, int n, int m) {
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> is_wall(0, 1);
//
//     Matrix<int> vertical_walls(n + 1, m);
//     Matrix<int> horizontal_walls(n, m + 1);
//     DSU rooms(n * m);
//
//     for (int i = 0; i < n + 1; i++) {
//         for (int j = 0; j < m; j++) {
//             vertical_walls[i][j] = 1;
//         }
//     }
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m + 1; j++) {
//             horizontal_walls[i][j] = 1;
//         }
//     }
//
//     for (int i = 0; i < n * m; i++) {
//         if ((i % m) + 1 == m && is_wall(gen) == 0) {
//             rooms.unite(i, i + 1);
//             vertical_walls[i / m][(i % m) + 1] = 0;
//         }
//
//         if ((i / m) + 1 == n && is_wall(gen) == 0) {
//             rooms.unite(i, i + m);
//             horizontal_walls[(i / m) + 1][i % m] = 0;
//         }
//     }
// }

void generate(int start_cell, int end_cell, int n, int m) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> is_wall(0, 99);

    Matrix<int> walls(2 * n + 1, 2 * m + 1);
    DSU rooms(n * m);

    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < 2 * m + 1; j++) {
            walls[i][j] = 1;
        }
    }

    if (start_cell < 0 || end_cell < 0 ||
        start_cell >= n * m || end_cell >= n * m) {
        throw std::invalid_argument("Error: invalid start_cell or end_cell");
    }
    if (start_cell == end_cell) {
        throw std::invalid_argument("Error: start_cell equal end_cell");
    }

    int start_cell_row = start_cell / m;
    int start_cell_column = start_cell % m;

    if (start_cell_row != 0 && start_cell_row != n - 1 &&
       start_cell_column != 0 && start_cell_column != m - 1) {
        throw std::invalid_argument("Error: start_cell not on the border");
    }

    int end_cell_row = end_cell / m;
    int end_cell_column = end_cell % m;

    if (end_cell_row != 0 && end_cell_row != n - 1 &&
        end_cell_column != 0 && end_cell_column != m - 1) {
        throw std::invalid_argument("Error: end_cell not on the border");
    }

    for (int i = 0; i < n * m; i++) {
        int void_cell_i = 2 * (i / m) + 1;
        int void_cell_j = 2 * (i % m) + 1;
        walls[void_cell_i][void_cell_j] = 0;

        if ((i % m) + 1 < m && is_wall(gen) < 50) {
            if (rooms.find(i) != rooms.find(i+1)) {
                rooms.unite(i, i + 1);
                walls[2 * (i / m) + 1][2 * (i % m) + 2] = 0;
            }
        }

        if ((i / m) + 1 < n && is_wall(gen) < 50) {
            if (rooms.find(i) != rooms.find(i + m)) {
                rooms.unite(i, i + m);
                walls[2 * (i / m) + 2][2 * (i % m) + 1] = 0;
            }
        }
    }

    print_labyrinth(walls);
    if (rooms.find(start_cell) != rooms.find(end_cell)) {
        std::cout << "there is no entrance\n count of sets: " << rooms.count() << std::endl;
    }
    for (int i = 0; i < n * m; i++) {
        std::cout << i << " parent(" << rooms.find(i) << ")" << std::endl;
    }
}

void print_labyrinth(const Matrix<int>& walls) {
    int rows = walls.rows();
    int cols = walls.cols();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (walls[i][j] != 1) {
                std::cout << " ";
                continue;
            }

            if (i % 2 == 0) {
                std::cout << "#";
            }
            else {
                std::cout << "#";
            }
        }

        std::cout << std::endl;
    }
}
