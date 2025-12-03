// Copyright 2025 Chernykh Valentin

#ifndef LIBS_LIB_MATH_MATH_H_
#define LIBS_LIB_MATH_MATH_H_

namespace Math {
const double PI = 3.14159265358979323846;
const double TWO_PI = 2 * PI;
const double LN2 = 0.693147180559945309417;

double fmod(double numer, double denom);
double normalize_angle(double x);
double abs(double x);

double sin(double x);
double cos(double x);
double tg(double x);
double sqrt(double x);
double ln(double x);
};  // namespace Math

#endif  // LIBS_LIB_MATH_MATH_H_
