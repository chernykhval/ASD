// Copyright 2024 Chernykh Valentin

#include <gtest/gtest.h>
#include "circle.h"
#include "sphere.h"
#include "intersection_utils.h"
#include "point2.h"
#include "point3.h"

#define EPSILON 0.000001

TEST(TestCircleIntersection, no_intersection) {
    Circle first_circle(Point2(3, 4), 1);
    Circle second_circle(Point2(0, 0), 1);

    IntersectionType actual_result = intersection_betwen(
        first_circle,
        second_circle);
    IntersectionType expected_result = IntersectionType::No_Intersection;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleIntersection, one_inside_other) {
    Circle first_circle(Point2(1, 1), 2);
    Circle second_circle(Point2(0, 0), 5);

    IntersectionType actual_result = intersection_betwen(
        first_circle,
        second_circle);
    IntersectionType expected_result = IntersectionType::One_Inside_Other;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleIntersection, intersection) {
    Circle first_circle(Point2(3, 0), 2);
    Circle second_circle(Point2(0, 1), 4);

    IntersectionType actual_result = intersection_betwen(
        first_circle,
        second_circle);
    IntersectionType expected_result = IntersectionType::Intersection;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleIntersection, external_tangency) {
    Circle first_circle(Point2(2, 0), 1);
    Circle second_circle(Point2(0, 0), 1);

    IntersectionType actual_result = intersection_betwen(
        first_circle,
        second_circle);
    IntersectionType expected_result = IntersectionType::External_Tangency;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestCircleIntersection, internal_tangency) {
    Circle first_circle(Point2(1, 0), 2);
    Circle second_circle(Point2(0, 0), 3);

    IntersectionType actual_result = intersection_betwen(
        first_circle,
        second_circle);
    IntersectionType expected_result = IntersectionType::Internal_Tangency;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereIntersection, no_intersection) {
    Sphere first_sphere(Point3(0, 0, 10), 2);
    Sphere second_sphere(Point3(0, 0, 0), 3);

    IntersectionType actual_result = intersection_betwen(
        first_sphere,
        second_sphere);
    IntersectionType expected_result = IntersectionType::No_Intersection;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereIntersection, one_inside_other) {
    Sphere first_sphere(Point3(0, 0, 0), 5);
    Sphere second_sphere(Point3(1, 1, 1), 1);

    IntersectionType actual_result = intersection_betwen(
        first_sphere,
        second_sphere);
    IntersectionType expected_result = IntersectionType::One_Inside_Other;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereIntersection, intersection) {
    Sphere first_sphere(Point3(0, 0, 0), 4);
    Sphere second_sphere(Point3(0, 0, 5), 3);

    IntersectionType actual_result = intersection_betwen(
        first_sphere,
        second_sphere);
    IntersectionType expected_result = IntersectionType::Intersection;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereIntersection, external_tangency) {
    Sphere first_sphere(Point3(0, 0, 0), 4);
    Sphere second_sphere(Point3(0, 0, 7), 3);

    IntersectionType actual_result = intersection_betwen(
        first_sphere,
        second_sphere);
    IntersectionType expected_result = IntersectionType::External_Tangency;

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestSphereIntersection, internal_tangency) {
    Sphere first_sphere(Point3(0, 0, 0), 5);
    Sphere second_sphere(Point3(0, 0, 2), 3);

    IntersectionType actual_result = intersection_betwen(
        first_sphere,
        second_sphere);
    IntersectionType expected_result = IntersectionType::Internal_Tangency;

    EXPECT_EQ(expected_result, actual_result);
}
