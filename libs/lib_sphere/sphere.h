// Copyright 2024 Chernykh Valentin

#ifndef LIBS_LIB_SPHERE_SPHERE_H_
#define LIBS_LIB_SPHERE_SPHERE_H_

#include "../lib_point3/point3.h"

class Sphere {
 private:
    Point3 _position;
    int _radius;
 public:
    Sphere();
    Sphere(Point3 position, int radius);

    int get_radius();
    Point3 get_position();
};

#endif  // LIBS_LIB_SPHERE_SPHERE_H_
