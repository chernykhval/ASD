// Copyright 2024 Marina Usova

#define MATRIX_INTERFACE

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

    std::cout << "Fill matrix A\n";\
    std::cin >> matrix_A;
    std::cout << "Fill matrix B\n";
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

    std::cout << "Fill matrix A\n";\
    std::cin >> matrix_A;
    std::cout << "Fill matrix B\n";
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
