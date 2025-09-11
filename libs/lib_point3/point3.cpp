// Copyright 2024 Chernykh Valentin

#include <cmath>

#include "libs/lib_point3/point3.h"

Point3::Point3() : _x(0), _y(0), _z(0) {}
Point3::Point3(int x, int y, int z) : _x(x), _y(y), _z(z) {}
Point3::Point3(const Point3& other) {
    _x = other._x;
    _y = other._y;
    _z = other._z;
}

float Point3::distance_to(const Point3& other) {
    int dx = _x - other._x;
    int dy = _y - other._y;
    int dz = _z - other._z;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance;
}
