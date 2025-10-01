// Copyright 2025 Chernykh Valentin

#include "libs/lib_circle/circle.h"
#include "libs/lib_point2/point2.h"

Circle::Circle() : _position(), _radius(1) {}
Circle::Circle(Point2 position, int radius) :
    _position(position), _radius(radius) {}

int Circle::get_radius() {
    return _radius;
}

Point2 Circle::get_position() {
    return _position;
}
