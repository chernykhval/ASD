// Copyright 2024 Chernykh Valentin

#ifndef LIBS_LIB_CIRCLE_CIRCLE_H_
#define LIBS_LIB_CIRCLE_CIRCLE_H_

#include "point2.h"

class Circle {
 private:
    Point2 _position;
    int _radius;
 public:
    Circle();
    Circle(Point2 position, int radius);

    int get_radius();
    Point2 get_position();
};

#endif  // LIBS_LIB_CIRCLE_CIRCLE_H_
