// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_ALGORITHMS_ALGORITHMS_H_
#define LIBS_LIB_ALGORITHMS_ALGORITHMS_H_

#include "libs/lib_matrix/matrix.h"
#include "libs/lib_dsu/dsu.h"
#include "libs/lib_unordered_array_table/unordered_array_table.h"

struct RoomConnection {
    int room1;
    int room2;

    RoomConnection(int r1, int r2) {
        if (r1 < r2) {
            room1 = r1; room2 = r2;
        } else {
            room1 = r2; room2 = r1;
        }
    }

    RoomConnection() : room1(0), room2(0) {}

    int first() const { return room1; }
    int second() const { return room2; }

    bool operator==(const RoomConnection& other) const {
        return room1 == other.room1 && room2 == other.room2;
    }

    friend std::ostream& operator<<(std::ostream& os
        , const RoomConnection& rc) {
        os << "[" << rc.room1 << "<->" << rc.room2 << "]";
        return os;
    }
};

struct Wall {
    int cell1;
    int cell2;

    Wall(int c1, int c2) {
        if (c1 < c2) {
            cell1 = c1; cell2 = c2;
        } else {
            cell1 = c2; cell2 = c1;
        }
    }

    Wall() : cell1(0), cell2(0) {}

    int first() const { return cell1; }
    int second() const { return cell2; }

    friend std::ostream& operator<<(std::ostream& os, const Wall& w) {
        os << w.cell1 << "|" << w.cell2;
        return os;
    }
};

struct WallSet {
    TVector<Wall> walls;

    WallSet() = default;

    void add(int cell_1, int cell_2) {
        walls.push_back(Wall(cell_1, cell_2));
    }

    size_t size() const {
        return walls.size();
    }

    Wall get_wall(int index) const {
        return walls[index];
    }

    friend std::ostream& operator<<(std::ostream& os, const WallSet& ws) {
        os << "(";

        for (const auto& wall : ws.walls) {
             os << wall << " ";
        }

        os << "Count:" << ws.walls.size();
        os << ")";

        return os;
    }
};

size_t get_random_index(size_t n) noexcept;

int find_local_minimum_gradient_descent(const Matrix<int>& matrix);

int calculate_islands_count(const Matrix<int>& matrix);

Matrix<int> generate(int start_cell, int end_cell, int rows, int cols);
void print_labyrinth(const Matrix<int>& walls);
void validate_input(int start_cell, int end_cell, int rows, int cols);
Matrix<int> create_initial_matrix(int rows, int cols,
    int start_cell, int end_cell);
UnorderedArrayTable<RoomConnection, WallSet> collect_wall_candidates(int rows,
    int cols, DSU& rooms);
void build_labyrinth(Matrix<int>& walls, DSU& rooms,
    UnorderedArrayTable<RoomConnection, WallSet>& table, int cols);

#endif  // LIBS_LIB_ALGORITHMS_ALGORITHMS_H_
