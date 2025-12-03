// Copyright 2025 Chernykh Valentin

#include <cmath>
#include <stdexcept>
#include <cstdint>
#include "libs/lib_my_math/my_math.h"

double MyMath::fmod(double numer, double denom) {
    int64_t quotient = static_cast<int64_t>(numer / denom);
    return numer - (quotient * denom);
}

double MyMath::normalize_angle(double x) {
    x = fmod(x, TWO_PI);

    if (x > PI)
        x -= TWO_PI;

    if (x < -PI)
        x += TWO_PI;

    return x;
}

double MyMath::abs(double x) {
    return x < 0 ? -x : x;
}

double MyMath::sin(double x) {
    x = normalize_angle(x);

    double term = x;
    double sum = term;
    int n = 1;
    double eps = 1e-9;

    while (abs(term) > eps) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }

    return sum;
}

double MyMath::cos(double x) {
    x = normalize_angle(x);

    double term = 1.0;
    double sum = term;
    int n = 1;
    double eps = 1e-9;

    while (abs(term) > eps) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    }

    return sum;
}

double MyMath::tg(double x) {
    double cos_val = cos(x);

    if (abs(cos_val) < 1e-10) {
        throw std::runtime_error("Tangent is undefined (division by zero)");
    }

    return sin(x) / cos_val;
}

double MyMath::sqrt(double x) {
    if (x < 0) {
        throw std::runtime_error("Square root of negative number");
    }

    if (x == 0) {
        return 0;
    }

    double guess = x;

    for (int i = 0; i < 100; ++i) {
        double next_guess = 0.5 * (guess + x / guess);

        if (abs(next_guess - guess) < 1e-10) {
            return next_guess;
        }

        guess = next_guess;
    }

    return guess;
}

double MyMath::ln(double x) {
    if (x <= 0) {
        throw std::runtime_error("Logarithm of non-positive number");
    }

    int k = 0;

    while (x > 1.5) {
        x /= 2.0;
        k++;
    }

    while (x < 0.5) {
        x *= 2.0;
        k--;
    }

    double y = (x - 1.0) / (x + 1.0);
    double y_sq = y * y;

    double term = y;
    double sum = 0.0;
    double eps = 1e-12;
    int n = 1;

    for (int i = 0; i < 1000; ++i) {
        double current_val = term / n;
        sum += current_val;

        if (abs(current_val) < eps) break;

        term *= y_sq;
        n += 2;
    }

    return 2.0 * sum + k * LN2;
}
