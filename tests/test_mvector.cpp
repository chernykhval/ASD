// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_mvector/mvector.h"

#define EPSILON 0.000001

TEST(TestMVector, init) {
    MVector<int> vec;
    int expected_result = 0;
    int actual_result = vec.size();

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMVector, size_init) {
    MVector<int> vec(5);
    int expected_result = 5;
    int actual_result = vec.size();

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMVector, copy_init) {
    MVector<int> vec_1(5);
    MVector<int> vec_2(vec_1);
    int expected_result = vec_1.size();
    int actual_result = vec_2.size();

    EXPECT_EQ(expected_result, actual_result);
}