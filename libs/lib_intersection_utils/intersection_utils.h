// Copyright 2024 Chernykh Valentin

#ifndef LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_
#define LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_

enum class IntersectionType {
    No_Intersection,
    One_Inside_Other,
    Intersection,
    External_Tangency,
    Internal_Tangency
};

template <typename T>
IntersectionType intersection_betwen(T first, T second);

#endif  // LIBS_LIB_INTERSECTION_UTILS_INTERSECTION_UTILS_H_
