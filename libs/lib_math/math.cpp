// Copyright 2025 Chernykh Valentin

#include <cmath>
#include <stdexcept>
#include "libs/lib_math/math.h"

double Math::fmod(double numer, double denom) {
    long long quotient = static_cast<long long>(numer / denom);
    return numer - (quotient * denom);
}

double Math::normalize_angle(double x) {
    x = fmod(x, TWO_PI);

    if (x > PI)
        x -= TWO_PI;

    if (x < -PI)
        x += TWO_PI;

    return x;
}

double Math::abs(double x) {
    return x < 0 ? -x : x;
}

double Math::sin(double x) {
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

double Math::cos(double x) {
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

double Math::tg(double x) {
    double cos_val = cos(x);

    if (abs(cos_val) < 1e-10) {
        throw std::runtime_error("Tangent is undefined (division by zero)");
    }

    return sin(x) / cos_val;
}

double Math::sqrt(double x) {
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

double Math::ln(double x) {
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
