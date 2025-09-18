// Copyright 2024 Marina Usova

#include <iostream>

#define MATRIX

#ifdef EASY_EXAMPLE

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

#ifdef MATRIX

#include "cstdio"
#include "libs/lib_matrix/matrix.h"

template<typename T>
Matrix<T> fill_matrix(int m, int n) {
    Matrix<T> matrix(m, n);
    int a;

    for (int i = 0; i < m; i++) {
        std::cout << "Input " << i << " row of matrix (" << n << " values): ";

        for (int j = 0; j < n; j++) {
            // std::cout << "element (" << i << ", " << j << "): ";
            std::cin >> a;
        }
    }

    std::cout << "\n";

    return matrix;
}

void start_matrix_calculator() {
    size_t rows_A, columns_A, rows_B, columns_B;
    char operation;

    std::cout << "Set size of matrix A.\nRows count: ";
    std::cin >> rows_A;
    std::cout << "Columns count: ";
    std::cin >> columns_A;

    std::cout << "Choose operation (+, -, *):";
    std::cin >> operation;

    switch (operation) {
        case '+':
        case '-':
            rows_B = rows_A;
            columns_B = columns_A;
            std::cout << "Your choice: A(" << rows_A << "x" << columns_A << ") "
            << operation << " B(" << rows_B << "x" << columns_B << ")" << std::endl;
            break;

        case '*':
            rows_B = columns_A;
            std::cout << "Your choice: A(" << rows_A << "x" << columns_A << ") "
            << operation << " B(" << rows_B << "x<columns>)" << std::endl;
            std::cout << "Input B columns count: ";
            std::cin >> columns_B;
            std::cout << "Your choice: A(" << rows_A << "x" << columns_A << ") "
            << operation << " B(" << rows_B << "x" << columns_B << ")" << std::endl;
            break;

        default:
            std::cout << "Wrong operation!";
            break;
    }

    // std::cout << "Fill first matrix\n";
    // Matrix<int> first_matrix = fill_matrix<int>(m, n);
    // std::cout << "Fill second matrix\n";
    // Matrix<int> second_matrix = fill_matrix<int>(t, k);
}

void start_triangle_matrix_calculator() {
    std::cout << "To be developed...";
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
    }
    return 0;
}

#endif  // MATRIX
