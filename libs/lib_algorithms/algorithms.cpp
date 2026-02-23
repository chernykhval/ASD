// Copyright 2025 Chernykh Valentin

#include <random>
#include <iostream>
#include "libs/lib_algorithms/algorithms.h"
#include "libs/lib_matrix/matrix.h"
#include "libs/lib_dsu/dsu.h"
#include "libs/lib_unordered_array_table/unordered_array_table.h"

size_t get_random_index(size_t n) noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> index(0, n - 1);

    return index(gen);
}

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

void validate_input(int start_cell, int end_cell, int rows, int cols) {
    if (start_cell < 0 || end_cell < 0 ||
        start_cell >= rows * cols || end_cell >= rows * cols) {
        throw std::invalid_argument("Error: invalid start_cell or end_cell");
        }
    if (start_cell == end_cell) {
        throw std::invalid_argument("Error: start_cell equal end_cell");
    }

    int start_cell_row = start_cell / cols;
    int start_cell_column = start_cell % cols;

    if (start_cell_row != 0 && start_cell_row != rows - 1 &&
       start_cell_column != 0 && start_cell_column != cols - 1) {
        throw std::invalid_argument("Error: start_cell not on the border");
    }

    int end_cell_row = end_cell / cols;
    int end_cell_column = end_cell % cols;

    if (end_cell_row != 0 && end_cell_row != rows - 1 &&
        end_cell_column != 0 && end_cell_column != cols - 1) {
        throw std::invalid_argument("Error: end_cell not on the border");
    }
}

Matrix<int> create_initial_matrix(int rows, int cols,
    int start_cell, int end_cell) {

    Matrix<int> walls(2 * rows + 1, 2 * cols + 1);

    for (int i = 0; i < 2 * rows + 1; i++) {
        for (int j = 0; j < 2 * cols + 1; j++) {
            if (i % 2 != 0 && j % 2 != 0) {
                int cell_row = (i - 1) / 2;
                int cell_col = (j - 1) / 2;
                int current_cell = cell_row  * cols + cell_col;

                if (current_cell == start_cell) {
                    walls[i][j] = 2;
                } else if (current_cell == end_cell) {
                    walls[i][j] = 3;
                } else {
                    walls[i][j] = 0;
                }
            } else {
                walls[i][j] = 1;
            }
        }
    }

    return walls;
}

UnorderedArrayTable<RoomConnection, WallSet> collect_wall_candidates(int rows,
    int cols, DSU& rooms) {
    UnorderedArrayTable<RoomConnection, WallSet> walls_to_destroy;

    for (int i = 0; i < rows * cols; i++) {
        int right = i + 1;
        int bottom = i + cols;

        if ((i % cols) + 1 < cols && rooms.find(i) != rooms.find(right)) {
            RoomConnection connection(rooms.find(i), rooms.find(right));

            if (walls_to_destroy.contains(connection) == false) {
                walls_to_destroy.insert(connection, WallSet());
            }

            walls_to_destroy.find(connection)->add(i, right);
        }

        if ((i / cols) + 1 < rows && rooms.find(i) != rooms.find(bottom)) {
            RoomConnection connection(rooms.find(i), rooms.find(bottom));

            if (walls_to_destroy.contains(connection) == false) {
                walls_to_destroy.insert(connection, WallSet());
            }

            walls_to_destroy.find(connection)->add(i, bottom);
        }
    }

    return walls_to_destroy;
}

void build_labyrinth(Matrix<int>& walls, DSU& rooms,
    UnorderedArrayTable<RoomConnection, WallSet>& table, int cols) {
    TVector<RoomConnection> keys = table.get_keys();
    shuffle(keys);

    for (auto key : keys) {
        WallSet* set = table.find(key);
        int wall_index = get_random_index(set->size());
        Wall wall_to_destroy = set->get_wall(wall_index);
        int room1 = wall_to_destroy.first();
        int room2 = wall_to_destroy.second();

        if (rooms.find(room1) == rooms.find(room2)) {
            continue;
        }

        rooms.unite(room1, room2);

        if (room2 == room1 + 1) {
            walls[2 * (room1 / cols) + 1][2 * (room1 % cols) + 2] = 0;
        } else {
            walls[2 * (room1 / cols) + 2][2 * (room1 % cols) + 1] = 0;
        }
    }
}

Matrix<int> generate(int start_cell, int end_cell, int rows, int cols) {
    validate_input(start_cell, end_cell, rows, cols);
    Matrix<int> walls = create_initial_matrix(rows, cols, start_cell, end_cell);

    DSU rooms(rows * cols);
    UnorderedArrayTable<RoomConnection, WallSet> walls_to_destroy =
        collect_wall_candidates(rows, cols, rooms);

    build_labyrinth(walls, rooms, walls_to_destroy, cols);

    return walls;
}

void print_labyrinth(const Matrix<int>& walls) {
    int rows = walls.rows();
    int cols = walls.cols();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (walls[i][j] == 2) {
                std::cout << "s";
                continue;
            }

            if (walls[i][j] == 3) {
                std::cout << "f";
                continue;
            }

            if (walls[i][j] != 1) {
                std::cout << " ";
                continue;
            }

            if (i % 2 == 0) {
                std::cout << "#";
            } else {
                std::cout << "#";
            }
        }

        std::cout << std::endl;
    }
}
