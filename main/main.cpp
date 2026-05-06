// Copyright 2024 Marina Usova
// Copyright 2025 Chernykh Valentin
// Copyright 2026 Chernykh Valentin

#define LABYRINTH_TEST

#include "libs/lib_matrix/matrix.h"
#include "libs/lib_triangle_matrix/triangle_matrix.h"

#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "libs/lib_easy_example/easy_example.h"

int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}

#endif  // EASY_EXAMPLE

#ifdef IOMATRIX_EXAMPLE

int main() {
    // Matrix<int> matrix(2, 3);
    // std::cout << matrix << std::endl;
    // std::cout << "Fill the matrix (2, 3): " << std::endl;
    // std::cin >> matrix;
    // std::cout << matrix << std::endl;

    Matrix<int> matrix = {
        {1, 2, 3},
        {0, 4, 5},
        {0, 0, 6}
    };

    int size = 3;
    int layer = 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j >= size)
                continue;

            std::cout << "(" << j << ", " << i + j << "): " << layer << " = ";

            for (int k = 0; k < layer; k++) {
                std::cout << "(" << j << ", " << k + j <<
                    ") * (" << k + j << ", " << j + i << ") + ";
            }

            std::cout << std::endl;
        }

        layer++;
    }

    std::cout << std::endl;

    layer = 1;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i + j >= size)
                continue;

            std::cout << "(" << j << ", " << i << "): " << layer << " = ";

            if (j == 0 && i == 1) {
                std::cout << "";
            }
            for (int k = 0; k < layer; k++) {
                std::cout << "(" << j << ", " <<
                    k << ") * (" << k + j << ", " << i - k << ") + ";
            }

            std::cout << std::endl;
        }

        layer++;
    }
    return 0;
}

#endif  // IOMATRIX_EXAMPLE

#ifdef MATRIX_INTERFACE

#include <limits>
#include <string>

#include "cstdio"

int read_int(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            break;
        }

        std::cout << "Invalid input! Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return value;
}

size_t read_size(const std::string& prompt) {
    int value;

    while (true) {
        value = read_int(prompt);

        if (value >= 0) {
            break;
        }

        std::cout << "Invalid input! Please enter non-negative number.\n";
    }

    return static_cast<size_t>(value);
}

void read_matrix_size(const std::string& name,
    size_t& rows, size_t& columns) {
    std::cout << "Enter dimensions for matrix " << name << ":\n";
    rows = read_size("Rows: ");
    columns = read_size("Columns: ");

    while (rows == 0 || columns == 0) {
        std::cout << "Error: Dimensions must be positive!\n";
        rows = read_size("Rows: ");
        columns = read_size("Columns: ");
    }
}

void read_triangle_matrix_size(const std::string& name,
    size_t& dim) {
    std::cout << "Enter dimension for triangle matrix " << name << ":\n";
    dim = read_size("Dim: ");

    while (dim == 0) {
        std::cout << "Error: Dimensions must be positive!\n";
        dim = read_size("Dim: ");
    }
}

char raed_operation() {
    char operation;

    std::cout << "Enter operation(+, -, *): ";
    std::cin >> operation;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (operation != '+' && operation != '-' && operation != '*') {
        std::cout << "Invalid operation! Choose from +, -, *: ";
        std::cin >> operation;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return operation;
}

void start_matrix_calculator() {
    size_t rows_A = 0,
    columns_A = 0,
    rows_B = 0,
    columns_B = 0;
    char operation;

    read_matrix_size("A", rows_A, columns_A);
    operation = raed_operation();

    if (operation == '*') {
        rows_B = columns_A;
        std::cout << "For multiplication, matrix B must have "
        << rows_B << " rows\n";
        columns_B = read_size("Enter columns for matrix B: ");

        while (columns_B == 0) {
            std::cout << "Error: Dimensions must be positive!\n";
            columns_B = read_size("Enter columns for matrix B: ");
        }
    } else {
        rows_B = rows_A;
        columns_B = columns_A;
        std::cout << "For this operation, matrix B must be "
        << rows_B << "x" << columns_B << "\n";
    }

    Matrix<float> matrix_A(rows_A, columns_A);
    Matrix<float> matrix_B(rows_B, columns_B);

    std::cout << "Fill matrix A(" << rows_A << "x" << columns_A << ")\n";
    std::cin >> matrix_A;
    std::cout << "Fill matrix B(" << rows_B << "x" << columns_B << ")\n";
    std::cin >> matrix_B;

    Matrix<float> result;

    switch (operation) {
        case '+':
            result = matrix_A + matrix_B;
            break;
        case '-':
            result = matrix_A - matrix_B;
            break;
        case '*':
            result = matrix_A * matrix_B;
            break;
    }

    std::cout << "Result Matrix:\n" << result << std::endl;
}

void start_triangle_matrix_calculator() {
    size_t dim;
    char operation;

    read_triangle_matrix_size("A", dim);
    operation = raed_operation();

    std::cout << "For this operation, matrix B must be "
        << dim << "x" << dim << "\n";


    TriangleMatrix<float> matrix_A(dim);
    TriangleMatrix<float> matrix_B(dim);

    std::cout << "Fill matrix A(" << dim << "x" << dim << ")\n";
    std::cin >> matrix_A;
    std::cout << "Fill matrix B(" << dim << "x" << dim << ")\n";
    std::cin >> matrix_B;

    TriangleMatrix<float> result;

    switch (operation) {
        case '+':
            result = matrix_A + matrix_B;
            break;
        case '-':
            result = matrix_A - matrix_B;
            break;
        case '*':
            result = matrix_A * matrix_B;
            break;
    }

    std::cout << "Result Matrix:\n" << result << std::endl;
}

int main() {
    char user_input;
    bool is_exit = false;

    while (true) {
        if (is_exit) {
            break;
        }

        std::cout << "Choose calculator:\n"
                     "1. Matrix\n"
                     "2. TriangleMatrix\n"
                     "0. Exit\n"
                     "Input: ";
        std::cin >> user_input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (user_input) {
            case '1':
                start_matrix_calculator();
                break;

            case '2':
                start_triangle_matrix_calculator();
                break;

            case '0':
                is_exit = true;
                break;

            default:
                std::cout << "Wrong input!\n";
                break;
        }

        if (!is_exit) {
            std::cout << "Press any key to continue...\n";
            std::cin.get();
            std::cin.get();
        }
    }

    return 0;
}

#endif  // MATRIX_INTERFACE

#ifdef LIST_TEST

#include "libs/lib_list/list.h"

int main() {
    try {
        List<int> list;
        std::cout << "Create emoty list. empty: " << list.is_empty()
        << std::endl;

        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        std::cout << "After push_back(1,2,3): ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        list.push_front(0);
        list.push_front(-1);
        std::cout << "After push_front(0,-1): ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        list.insert(2, 999);
        std::cout << "After insert(2, 999): ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        list.pop_front();
        list.pop_back();
        std::cout << "After pop_front() and pop_back(): ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        list.erase(1);
        std::cout << "After erase(1): ";
        for (auto it = list.begin(); it != list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        const List<int>& const_list = list;
        std::cout << "Const Iterator: ";
        for (auto it = const_list.begin(); it != const_list.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        list.clear();
        std::cout << "After clear(): empty: " << list.is_empty() << std::endl;

        std::cout << "All tests complete!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    List<int> simple_;

    return 0;
}

#endif  // LIST_TEST

#ifdef LABYRINTH_TEST

#include <iostream>
#include "libs/lib_algorithms/algorithms.h"

int main() {
    auto labyrinth = generate(0, 899, 30, 30);
    print_labyrinth(labyrinth);
    print_labyrinth(labyrinth, true);
    system("pause");
    return 0;
}
#endif  // LABYRINTH_TEST

#ifdef HEAP_TEST

#include <iostream>
#include "libs/lib_heap/heap.h"
#include "libs/lib_priority_queue/priority_queue.h"
#include "random"

int main() {
    PriorityQueue<int> priority_queue;
    int K = 30;
    int k = K;
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_int_distribution<> dist_1(0, 3);
    std::uniform_int_distribution<> dist_2(0, 99);

    while (k > 0) {
        int n = dist_1(gen);
        int rand_priority = dist_2(gen);

        for (int i = 0; i < n; i++) {
            priority_queue.push(rand_priority, k);
            k--;
        }
    }

    for (int i = 0; i < 15; i++) {
        std::cout << priority_queue.pop_info() << std::endl;
        priority_queue.pop();
    }

    system("pause");

    return 0;
}
#endif  // HEAP_TEST

#ifdef HASH_TABLE_TEST

#include <iostream>
#include <cstdlib>
#include "libs/lib_hash_table_c/hash_table_c.h"
#include "libs/lib_hash_table_oa/hash_table_oa.h"
#include "libs/lib_tvector/tvector.h"

int main() {
    TVector<std::pair<std::string, int>> dict1;
    TVector<std::pair<std::string, int>> dict2;

    dict1.push_back(std::pair<std::string, int>("table", 1349));
    dict1.push_back(std::pair<std::string, int>("hash", 1985));
    dict1.push_back(std::pair<std::string, int>("list", 4372));
    dict2.push_back(std::pair<std::string, int>("array", 4312));
    dict2.push_back(std::pair<std::string, int>("list", 5863));
    dict2.push_back(std::pair<std::string, int>("hash", 4372));
    dict2.push_back(std::pair<std::string, int>("vector", 2586));

    HashTableOA<int> hash_table;

    for (std::pair<std::string, int> pair : dict1) {
        hash_table.insert(pair.first, pair.second);
    }

    for (std::pair<std::string, int> pair : dict2) {
        try {
            hash_table.insert(pair.first, pair.second);
        }
        catch (const std::exception& e) {
        }
    }

    std::cout << hash_table.to_string();

    system("pause");

    return 0;
}

#endif  // HASH_TABLE_TEST

#ifdef DIJKSTRA_TEST

#include <iostream>
#include <cstdlib>
#include "libs/lib_algorithms/algorithms.h"
#include "libs/lib_adj_matrix_graph/adj_matrix_graph.h"
#include "libs/lib_tvector/tvector.h"

int main() {
    AdjMatrixGraph<char> graph({
        {'A', 'B', 4},
        {'A', 'C', 1},
        {'C', 'D', 2},
        {'C', 'E', 1},
        {'B', 'E', 3}
    });

    std::pair<TVector<char>, int> result = dijkstra<char>(graph, 'A', 'D');
    std::cout << result.first << "\n" << result.second << std::endl;

    system("pause");

    return 0;
}

#endif  // DIJKSTRA_TEST
