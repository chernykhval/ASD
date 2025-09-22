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

TEST(TestMVector, negative_size_init) {
    ASSERT_ANY_THROW(MVector<int> vec(-5););
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

TEST(TestMVector, assign_to_mvector) {
    MVector<int> vec_1(5);
    MVector<int> vec_2 = vec_1;
    int expected_result = vec_1.size();
    int actual_result = vec_2.size();

    EXPECT_EQ(expected_result, actual_result);
}

TEST(TestMVector, add_to_mvector) {
    MVector<int> vec_1(3);
    MVector<int> vec_2(3);

    for (int i = 0; i < vec_1.size(); i++) {
        vec_1[i] = i + 1;
    }

    for (int i = 0; i < vec_2.size(); i++) {
        vec_2[i] = i+4;
    }

    MVector<int> vec_3 = vec_1 + vec_2;

    EXPECT_EQ(vec_3[0], 5);
    EXPECT_EQ(vec_3[1], 7);
    EXPECT_EQ(vec_3[2], 9);
}

TEST(TestMVector, add_to_mvector_with_different_size) {
    MVector<int> vec_1(3);
    MVector<int> vec_2(4);

    ASSERT_ANY_THROW(MVector<int> vec_3 = vec_1 + vec_2;);
}
