// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_point2/point2.h"

#define EPSILON 0.000001

TEST(TestPoint2, distance_to_another) {
    Point2 pos_1 = Point2(3, 4);
    Point2 pos_2 = Point2(0, 0);

    float actual_result = pos_1.distance_to(pos_2);
    float expected_result = 5;

    EXPECT_EQ(expected_result, actual_result);
}
