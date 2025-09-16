// Copyright 2024 Chernykh Valentin

#ifndef LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_
#define LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_

#include <stdexcept>

enum class IntersectionType {
    No_Intersection,
    One_Inside_Other,
    Intersection,
    External_Tangency,
    Internal_Tangency
};

template <typename T>
IntersectionType intersection_betwen(T first, T second) {
    int big_r = first.get_radius();
    int small_r = second.get_radius();

    float distance = first.get_position().distance_to(second.get_position());

    if (big_r < small_r) {
        int temp = big_r;
        big_r = small_r;
        small_r = temp;
    }

    if (distance > big_r + small_r) {
        return IntersectionType::No_Intersection;
    } else if (distance == big_r + small_r) {
        return IntersectionType::External_Tangency;
    } else if (distance < big_r - small_r) {
        return IntersectionType::One_Inside_Other;
    } else if (distance == big_r - small_r) {
        return IntersectionType::Internal_Tangency;
    } else if (distance > big_r - small_r && distance < big_r + small_r) {
        return IntersectionType::Intersection;
    }

    throw std::runtime_error("Error type");
}

#endif  // LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_
