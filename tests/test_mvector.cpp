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

TEST(TestMVector, list_init) {
    MVector<int> vec = {1, 2, 3, 4, 5};
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
    MVector<int> vec_1 = {1, 2, 3};
    MVector<int> vec_2 = {4, 5, 6};

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

TEST(TestMVector, sub_to_mvector) {
    MVector<int> vec_1 = {1, 2, 3};
    MVector<int> vec_2 = {4, 5, 6};

    MVector<int> vec_3 = vec_1 - vec_2;

    EXPECT_EQ(vec_3[0], -3);
    EXPECT_EQ(vec_3[1], -3);
    EXPECT_EQ(vec_3[2], -3);
}

TEST(TestMVector, sub_to_mvector_with_different_size) {
    MVector<int> vec_1(3);
    MVector<int> vec_2(4);

    ASSERT_ANY_THROW(MVector<int> vec_3 = vec_1 - vec_2;);
}

TEST(TestMVector, mult_to_mvector) {
    MVector<int> vec_1 = {1, 2, 3};
    MVector<int> vec_2 = {4, 5, 6};

    int result = vec_1 * vec_2;

    EXPECT_EQ(32, result);
}

TEST(TestMVector, mult_to_scalar) {
    MVector<int> vec = {1, 2, 3};
    MVector<int> result = vec * 2;

    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
}

TEST(TestMVector, div_to_scalar) {
    MVector<int> vec = {2, 4, 6};
    MVector<int> result = vec / 2;

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(TestMVector, div_by_zero) {
    MVector<int> vec = {1, 2, 3};

    ASSERT_ANY_THROW(MVector<int> result = vec / 0;);
}

TEST(TestMVector, length) {
    MVector<int> vec = {3, 4};

    EXPECT_EQ(5, vec.length());
}

TEST(TestMVector, normalized) {
    MVector<float> vec = {3.0, 4.0};
    MVector<float> result = vec.normalized();

    EXPECT_EQ(1, result.length());
}

TEST(TestMVector, zero_normalized) {
    MVector<int> vec = {0, 0, 0};

    ASSERT_ANY_THROW(vec.normalized());
}

TEST(TestMVector, compound_addition) {
    MVector<int> vec_1 = {1, 2, 3};
    MVector<int> vec_2 = {4, 5, 6};
    vec_1 += vec_2;

    EXPECT_EQ(vec_1[0], 5);
    EXPECT_EQ(vec_1[1], 7);
    EXPECT_EQ(vec_1[2], 9);
}
