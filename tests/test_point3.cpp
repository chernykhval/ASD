// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_point3/point3.h"

#define EPSILON 0.000001

TEST(TestPoint3, distance_to_another) {
    Point3 point_1 = Point3(3, 4, 12);
    Point3 point_2 = Point3(0, 0, 0);

    float actual_result = point_1.distance_to(point_2);
    float expected_result = 13;

    EXPECT_EQ(expected_result, actual_result);
}
