// Copyright 2024 Marina Usova

#define IOMATRIX_EXAMPLE
#include "libs/lib_matrix/matrix.h"

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
    Matrix<int> matrix(2, 3);
    std::cout << matrix << std::endl;
    std::cout << "Fill the matrix (2, 3): " << std::endl;
    std::cin >> matrix;
    std::cout << matrix << std::endl;
    return 0;
}

#endif  // IOMATRIX_EXAMPLE
