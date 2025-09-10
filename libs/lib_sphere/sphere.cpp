// Copyright 2024 Chernykh Valentin

#include "../lib_sphere/sphere.h"
#include "../lib_point3/point3.h"

Sphere::Sphere() : _position(), _radius(1) {}
Sphere::Sphere(Point3 position, int radius) : _position(position), _radius(radius) {}

int Sphere::get_radius() {
	return _radius;
}

Point3 Sphere::get_position() {
	return _position;
}
