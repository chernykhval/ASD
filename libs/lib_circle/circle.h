// Copyright 2024 Chernykh Valentin

#ifndef LIB_CIRCLE_CIRCLE_H_
#define LIB_CIRCLE_CIRCLE_H_

#include "../lib_point2/point2.h"

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

#endif  // LIB_CIRCLE_CIRCLE_H_
