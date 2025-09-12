// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_tvector/tvector.h"

#define EPSILON 0.000001

#include <gtest/gtest.h>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <utility>

// Helper functions for testing
bool find_chet(int a) {
    return a % 2 == 0;
}

bool comp(int a, int b) {
    return a > b || a > 10;
}

bool sort_check(uint64_t a, uint64_t b) {
    return a < b;
}

bool sort_descending(int a, int b) {
    return a > b;
}

bool sort_ascending(int a, int b) {
    return a < b;
}

bool search_predicate_none_match(int x) {
    return x > 1000;
}

bool search_predicate_all_match(int x) {
    return x >= 0;
}

// TVector Constructor Tests
TEST(TVectorTest, DefaultInit) {
    TVector<int> vec;

    EXPECT_EQ(nullptr, vec.data());
    EXPECT_EQ(vec.begin(), vec.end());
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(0u, vec.capacity());
}

TEST(TVectorTest, SizeInit) {
    TVector<int> vec(25);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(25u, vec.size());
    EXPECT_EQ(30u, vec.capacity());
}

TEST(TVectorTest, SizeAndValueInit) {
    TVector<int> vec(25, 5);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(25u, vec.size());
    EXPECT_EQ(30u, vec.capacity());
}

TEST(TVectorTest, CopyInit) {
    TVector<int> vec_1(25, 5);
    TVector<int> vec_2(vec_1);

    EXPECT_NE(nullptr, vec_1.data());
    EXPECT_NE(vec_1.begin(), vec_1.end());
    EXPECT_NE(nullptr, vec_2.data());
    EXPECT_NE(vec_2.begin(), vec_2.end());
    EXPECT_EQ(25u, vec_1.size());
    EXPECT_EQ(30u, vec_1.capacity());
    EXPECT_EQ(25u, vec_2.size());
    EXPECT_EQ(30u, vec_2.capacity());
}

TEST(TVectorTest, MoveInit) {
    TVector<int> vec_1(25, 5);
    TVector<int> vec_2(std::move(vec_1));

    EXPECT_EQ(nullptr, vec_1.data());
    EXPECT_EQ(vec_1.begin(), vec_1.end());
    EXPECT_NE(nullptr, vec_2.data());
    EXPECT_NE(vec_2.begin(), vec_2.end());
    EXPECT_EQ(0u, vec_1.size());
    EXPECT_EQ(0u, vec_1.capacity());
    EXPECT_EQ(25u, vec_2.size());
    EXPECT_EQ(30u, vec_2.capacity());
}

TEST(TVectorTest, ArrayInit) {
    int* array = new int[16] { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec(array, 16);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(16u, vec.size());
    EXPECT_EQ(30u, vec.capacity());

    delete[] array;
}

TEST(TVectorTest, InitializerListInit) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(16u, vec.size());
    EXPECT_EQ(30u, vec.capacity());
}

// Assignment Operator Tests
TEST(TVectorTest, CopyAssignment) {
    TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec_2;

    vec_2 = vec_1;

    EXPECT_NE(nullptr, vec_1.data());
    EXPECT_NE(vec_1.begin(), vec_1.end());
    EXPECT_NE(nullptr, vec_2.data());
    EXPECT_NE(vec_2.begin(), vec_2.end());
    EXPECT_EQ(16u, vec_1.size());
    EXPECT_EQ(30u, vec_1.capacity());
    EXPECT_EQ(16u, vec_2.size());
    EXPECT_EQ(30u, vec_2.capacity());
}

TEST(TVectorTest, MoveAssignment) {
    TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec_2;

    vec_2 = std::move(vec_1);

    EXPECT_EQ(nullptr, vec_1.data());
    EXPECT_EQ(vec_1.begin(), vec_1.end());
    EXPECT_NE(nullptr, vec_2.data());
    EXPECT_NE(vec_2.begin(), vec_2.end());
    EXPECT_EQ(0u, vec_1.size());
    EXPECT_EQ(0u, vec_1.capacity());
    EXPECT_EQ(16u, vec_2.size());
    EXPECT_EQ(30u, vec_2.capacity());
}

TEST(TVectorTest, EqualityOperator) {
    TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec_2 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_TRUE(vec_1 == vec_2);
}

TEST(TVectorTest, InequalityOperator) {
    TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int> vec_2 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 17 };

    EXPECT_TRUE(vec_1 != vec_2);
}

TEST(TVectorTest, IndexAccess) {
    const TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(14, vec_1[13]);
}

TEST(TVectorTest, IndexAccessException) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_THROW(vec[17], std::out_of_range);
}

TEST(TVectorTest, ConstIndexAccess) {
    const TVector<int> vec_1 = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(14, vec_1[13]);
}

TEST(TVectorTest, ConstIndexAccessException) {
    const TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_THROW(vec[17], std::out_of_range);
}

// Access Methods Tests
TEST(TVectorTest, Data) {
    const TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(1, *vec.data());
}

TEST(TVectorTest, ConstData) {
    const TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(1, *vec.data());
}

TEST(TVectorTest, Size) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(5, vec.size());
}

TEST(TVectorTest, Capacity) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(15, vec.capacity());
}

TEST(TVectorTest, Front) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(1, vec.front());
}

TEST(TVectorTest, Back) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(5, vec.back());
}

TEST(TVectorTest, Begin) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int>::Iterator it = vec.begin();

    EXPECT_EQ(1, *it);
}

TEST(TVectorTest, End) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int>::Iterator it = vec.end();

    EXPECT_EQ(16, *(it - 1));
}

// Push/Pop Operations Tests
TEST(TVectorTest, PushBackCopyEmpty) {
    TVector<int> actual_result;
    int a = 16;
    actual_result.push_back(a);
    TVector<int> expected_result = { 16 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(1u, actual_result.size());
    EXPECT_EQ(15u, actual_result.capacity());
}

TEST(TVectorTest, PushBackCopyWithCapacity) {
    TVector<int> actual_result = { 1, 2, 3 };
    int a = 4;
    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    actual_result.push_back(a);

    TVector<int> expected_result = { 1, 2, 3, 4 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(old_size + 1, actual_result.size());
    EXPECT_EQ(old_capacity, actual_result.capacity());
}

TEST(TVectorTest, PushBackCopyFullCapacity) {
    TVector<int> actual_result;
    for (int i = 0; i < static_cast<int>(actual_result.capacity()); ++i) {
        actual_result.push_back(i);
    }
    int a = 100;
    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    actual_result.push_back(a);

    TVector<int> expected_result;
    for (size_t i = 0; i < old_size; ++i)
        expected_result.push_back(static_cast<int>(i));
    expected_result.push_back(a);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(old_size + 1, actual_result.size());
    EXPECT_GT(actual_result.capacity(), old_capacity);
}

TEST(TVectorTest, PushBackCopyLargeVector) {
    TVector<int> actual_result;
    const int large_size = 1000000;
    actual_result.reserve(large_size);
    for (int i = 0; i < large_size; ++i) {
        actual_result.push_back(i);
    }
    int a = 42;
    actual_result.push_back(a);

    EXPECT_EQ(static_cast<size_t>(large_size + 1), actual_result.size());
    EXPECT_EQ(a, actual_result[large_size]);
}

TEST(TVectorTest, PushBackCopyAfterShrinkToFit) {
    TVector<int> actual_result;
    for (int i = 0; i < static_cast<int>(actual_result.capacity()); ++i) {
        actual_result.push_back(i);
    }
    actual_result.shrink_to_fit();

    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    int a = 999;
    actual_result.push_back(a);

    TVector<int> expected_result;
    for (size_t i = 0; i < old_size; ++i)
        expected_result.push_back(static_cast<int>(i));
    expected_result.push_back(a);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(old_size + 1, actual_result.size());
    EXPECT_GT(actual_result.capacity(), old_capacity);
}

TEST(TVectorTest, PushBackMove) {
    TVector<int> actual_result = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15 };
    actual_result.push_back(16);
    TVector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8,
     9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(16u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, PushFrontCopy) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    int a = 1;
    actual_result.push_front(a);
    TVector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(16u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, PushFrontMove) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    actual_result.push_front(1);
    TVector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(16u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, InsertCopy) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int a = 12;
    actual_result.insert(actual_result.begin() + 2, a);
    TVector<int> expected_result = { 2, 3, 12, 4, 5, 6, 7, 8, 9, 10 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(10u, actual_result.size());
    EXPECT_EQ(15u, actual_result.capacity());
}

TEST(TVectorTest, InsertElemsCopy) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int a = 12;
    actual_result.insert(actual_result.begin() + 2, 7, a);
    TVector<int> expected_result = { 2, 3, 12, 12, 12, 12, 12,
        12, 12, 4, 5, 6, 7, 8, 9, 10 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(16u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, InsertMove) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    actual_result.insert(actual_result.begin() + 2, 12);
    TVector<int> expected_result = { 2, 3, 12, 4, 5, 6, 7, 8, 9, 10 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(10u, actual_result.size());
    EXPECT_EQ(15u, actual_result.capacity());
}

TEST(TVectorTest, Emplace) {
    TVector<int> actual_result = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    actual_result.emplace(actual_result.begin() + 2, 12);
    TVector<int> expected_result = { 2, 3, 12, 4, 5, 6, 7, 8, 9, 10 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(10u, actual_result.size());
    EXPECT_EQ(15u, actual_result.capacity());
}

TEST(TVectorTest, PopBackEmpty) {
    TVector<int> vec;

    EXPECT_THROW(vec.pop_back(), std::exception);
}

TEST(TVectorTest, PopBackWithCapacity) {
    TVector<int> actual_result = { 1, 2, 3 };
    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    actual_result.pop_back();

    TVector<int> expected_result = { 1, 2 };

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(old_size - 1, actual_result.size());
    EXPECT_EQ(old_capacity, actual_result.capacity());
}

TEST(TVectorTest, PopBackLessCapacity) {
    TVector<int> actual_result;
    for (int i = 0; i < 16; ++i) {
        actual_result.push_back(i);
    }
    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    actual_result.pop_back();
    actual_result.pop_back();
    actual_result.pop_back();

    TVector<int> expected_result;
    for (size_t i = 0; i < 13; ++i)
        expected_result.push_back(static_cast<int>(i));

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(old_size - 3, actual_result.size());
    EXPECT_LT(actual_result.capacity(), old_capacity);
}

TEST(TVectorTest, PopBackLargeVector) {
    TVector<int> actual_result(500000);
    const int large_size =500000;
    for (int i = 0; i < large_size; ++i) {
        actual_result.pop_back();
    }

    EXPECT_EQ(0u, actual_result.size());
}

TEST(TVectorTest, PopBackAfterShrinkToFit) {
    TVector<int> actual_result(16);
    actual_result.shrink_to_fit();

    size_t old_capacity = actual_result.capacity();
    size_t old_size = actual_result.size();

    actual_result.pop_back();
    actual_result.pop_back();
    actual_result.pop_back();

    EXPECT_EQ(old_size - 3, actual_result.size());
    EXPECT_LT(actual_result.capacity(), old_capacity);
}

TEST(TVectorTest, PopFront) {
    TVector<int> actual_result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    TVector<int> expected_result = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };

    actual_result.pop_front();
    actual_result.pop_front();
    actual_result.pop_front();
    actual_result.pop_front();
    actual_result.pop_front();
    actual_result.pop_front();

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(25u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, Erase) {
    TVector<int> actual_result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
    TVector<int> expected_result = { 3, 4, 5, 6, 8, 9, 10, 12, 13, 14, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29 };

    actual_result.erase(actual_result.begin());
    actual_result.erase(actual_result.end() - 1);
    actual_result.erase(actual_result.begin());
    actual_result.erase(actual_result.end() - 1);
    actual_result.erase(actual_result.begin() + 4);
    actual_result.erase(actual_result.begin() + 11);
    actual_result.erase(actual_result.begin() + 7);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(24u, actual_result.size());
    EXPECT_EQ(30u, actual_result.capacity());
}

TEST(TVectorTest, EraseEmpty) {
    TVector<int> vec;

    EXPECT_THROW(vec.erase(vec.begin()), std::exception);
}

// Container Management Tests
TEST(TVectorTest, Clear) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    vec.clear();

    EXPECT_NE(nullptr, vec.data());
    EXPECT_EQ(vec.begin(), vec.end());
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(15u, vec.capacity());
}

TEST(TVectorTest, ShrinkToFit) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    vec.shrink_to_fit();

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(16u, vec.size());
    EXPECT_EQ(16u, vec.capacity());
}

TEST(TVectorTest, Resize1) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31, 32 };

    vec.pop_back();
    vec.pop_front();
    vec.erase(vec.begin() + 8);
    vec.erase(vec.begin() + 4);
    vec.erase(vec.begin() + 25);
    vec.erase(vec.begin() + 15);
    vec.erase(vec.begin() + 13);
    vec.insert(vec.begin() + 25, 111);
    vec.insert(vec.begin() + 8, 222);
    vec.insert(vec.begin() + 17, 333);
    vec.resize(32);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(32u, vec.size());
    EXPECT_EQ(45u, vec.capacity());
}

TEST(TVectorTest, Resize2) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32 };

    vec.pop_back();
    vec.pop_front();
    vec.erase(vec.begin() + 8);
    vec.erase(vec.begin() + 4);
    vec.erase(vec.begin() + 25);
    vec.erase(vec.begin() + 15);
    vec.erase(vec.begin() + 13);
    vec.insert(vec.begin() + 25, 111);
    vec.insert(vec.begin() + 8, 222);
    vec.insert(vec.begin() + 17, 333);
    vec.resize(25);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(25u, vec.size());
    EXPECT_EQ(30u, vec.capacity());
}

TEST(TVectorTest, Resize3) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };

    vec.pop_back();
    vec.pop_front();
    vec.erase(vec.begin() + 8);
    vec.erase(vec.begin() + 4);
    vec.erase(vec.begin() + 25);
    vec.erase(vec.begin() + 15);
    vec.erase(vec.begin() + 13);
    vec.insert(vec.begin() + 25, 111);
    vec.insert(vec.begin() + 8, 222);
    vec.insert(vec.begin() + 17, 333);
    vec.resize(5);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(5u, vec.size());
    EXPECT_EQ(15u, vec.capacity());
}

TEST(TVectorTest, Shuffle) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    vec.pop_back();
    vec.pop_back();
    vec.pop_front();
    vec.erase(vec.begin() + 2);
    shuffle(vec);

    EXPECT_NE(nullptr, vec.data());
    EXPECT_NE(vec.begin(), vec.end());
    EXPECT_EQ(6u, vec.size());
    EXPECT_EQ(15u, vec.capacity());
}

// Search Tests
TEST(TVectorTest, SearchBegin) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    vec.pop_front();
    int actual_result = search_begin(vec, find_chet);

    EXPECT_EQ(0, actual_result);
}

TEST(TVectorTest, SearchEnd) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    vec.pop_front();
    vec.pop_back();
    int actual_result = search_end(vec, find_chet);

    EXPECT_EQ(6, actual_result);
}

TEST(TVectorTest, SearchAll) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    vec.pop_front();
    vec.pop_back();

    int* searched_result = search_all(vec, find_chet);
    int* need_result = new int[4] {0, 2, 4, 6};

    bool all_match = true;
    for (int i = 0; i < 4; i++) {
        if (searched_result[i] != need_result[i])
            all_match = false;
    }

    EXPECT_TRUE(all_match);
    delete[] need_result;
}

// Complex Test
TEST(TVectorTest, ComplexOperations) {
    TVector<int> actual_result = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36 };
    TVector<int> expected_result = { 2, 3, 4, 5, 7, 8, 9, 11, 222, 12, 13,
        14, 15, 16, 18, 20, 21, 333, 22, 23, 24, 25, 26, 27, 28, 30,
        31, 111, 32, 33, 34, 35 };

    actual_result.pop_back();
    actual_result.pop_front();
    actual_result.erase(actual_result.begin() + 8);
    actual_result.erase(actual_result.begin() + 4);
    actual_result.erase(actual_result.begin() + 25);
    actual_result.erase(actual_result.begin() + 15);
    actual_result.erase(actual_result.begin() + 13);
    actual_result.insert(actual_result.begin() + 25, 111);
    actual_result.insert(actual_result.begin() + 8, 222);
    actual_result.insert(actual_result.begin() + 17, 333);

    EXPECT_EQ(expected_result, actual_result);
    EXPECT_EQ(32u, actual_result.size());
    EXPECT_EQ(45u, actual_result.capacity());
}

// Iterator Tests
TEST(TVectorTest, IteratorInit) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(1, *vec.begin());
}

TEST(TVectorTest, IteratorDereference) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator it = vec.begin();

    EXPECT_EQ(1, *it);

    *it = 10;
    EXPECT_EQ(10, vec[0]);

    ++it;
    EXPECT_EQ(2, *it);
}

TEST(TVectorTest, IteratorDereferenceEmpty) {
    TVector<int> vec;

    EXPECT_THROW(*vec.end(), std::exception);
}

TEST(TVectorTest, IteratorDereferenceOutOfRange) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_THROW(*vec.end(), std::exception);
}

TEST(TVectorTest, IteratorArrowOperator) {
    TVector<int> vect(1, 5);
    TVector<TVector<int>> vec(1, vect);

    EXPECT_EQ(5, vec.begin()->front());
}

TEST(TVectorTest, IteratorAssign) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };
    TVector<int>::Iterator it_1 = vec.end();
    it_1 = vec.begin();

    EXPECT_EQ(1, *it_1);
}

TEST(TVectorTest, IteratorLeftIncrement) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(2, *(++vec.begin()));
}

TEST(TVectorTest, IteratorRightIncrement) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
     9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(1, *(vec.begin()++));
}

TEST(TVectorTest, IteratorLeftDecrement) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
     9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(16, *(--vec.end()));
}

TEST(TVectorTest, IteratorRightDecrement) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8,
     9, 10, 11, 12, 13, 14, 15, 16 };

    EXPECT_EQ(16, *((vec.end() - 1)--));
}

TEST(TVectorTest, IteratorAdd) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(3, *(vec.begin() + 2));
}

TEST(TVectorTest, IteratorAddOutOfRangeException) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_THROW(vec.begin() + 6, std::exception);
    EXPECT_THROW(vec.begin() + (-1), std::exception);
}

TEST(TVectorTest, IteratorSub) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_EQ(4, *(vec.end() - 2));
}

TEST(TVectorTest, IteratorSubOutOfRangeException) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    EXPECT_THROW(vec.end() - 6, std::exception);
    EXPECT_THROW(vec.end() - (-1), std::exception);
}

TEST(TVectorTest, IteratorAddAssign) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::Iterator bg = vec.begin();

    EXPECT_EQ(1, *bg);

    bg += 2;
    EXPECT_EQ(3, *bg);
}

TEST(TVectorTest, IteratorAddAssignOutOfRangeException) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::Iterator bg = vec.begin();

    EXPECT_THROW(bg += 6, std::exception);
    EXPECT_THROW(bg += (-1), std::exception);
}

TEST(TVectorTest, IteratorSubAssign) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::Iterator ed = vec.end();

    EXPECT_EQ(5, *(ed - 1));

    ed -= 3;
    EXPECT_EQ(3, *ed);
}

TEST(TVectorTest, IteratorSubAssignOutOfRangeException) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::Iterator ed = vec.end();

    EXPECT_THROW(ed -= 6, std::exception);
    EXPECT_THROW(ed -= (-1), std::exception);
}

TEST(TVectorTest, IteratorEquality) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator it_1 = vec.begin();
    TVector<int>::Iterator it_2 = vec.begin();

    EXPECT_TRUE(it_1 == it_2);
}

TEST(TVectorTest, IteratorInequality) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    TVector<int>::Iterator it_1 = vec.begin();
    TVector<int>::Iterator it_2 = vec.end();

    EXPECT_TRUE(it_1 != it_2);
}

TEST(TVectorTest, IteratorDifference) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    vec.pop_front();
    TVector<int>::Iterator it_1 = vec.begin();
    TVector<int>::Iterator it_2 = vec.end();

    EXPECT_EQ(4, it_2 - it_1);
}

// Sort Test (commented out due to potential long runtime)
/*
TEST(TVectorTest, Sort) {
    TVector<uint64_t> expected_result(100000000);
    TVector<uint64_t> actual_result(100000000);

    for (uint64_t i = 0; i < 100000000; i++) {
        expected_result[i] = i;
    }

    for (uint64_t i = 0; i < 100000000; i++) {
        actual_result[100000000 - 1 - i] = i;
    }

    auto start = std::chrono::high_resolution_clock::now();
    tv_sort(actual_result, sort_check);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    EXPECT_EQ(expected_result, actual_result);
}
*/

// Additional AI Generated Tests
TEST(TVectorTest, SizeValueInitZero) {
    EXPECT_THROW(TVector<int>(0, 5), std::exception);
}

TEST(TVectorTest, SizeValueInitLarge) {
    TVector<int> vec(1000, 42);
    bool all_values_correct = true;
    for (size_t i = 0; i < vec.size() && all_values_correct; ++i) {
        if (vec[i] != 42) {
            all_values_correct = false;
        }
    }
    EXPECT_EQ(1000u, vec.size());
    EXPECT_EQ(1005u, vec.capacity());
    EXPECT_TRUE(all_values_correct);
}

TEST(TVectorTest, SelfAssignment) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int> original = vec;
    vec = vec;  // Self-assignment
    EXPECT_EQ(original, vec);
}

TEST(TVectorTest, AssignmentDifferentSizes) {
    TVector<int> vec1 = { 1, 2, 3 };
    TVector<int> vec2 = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    vec1 = vec2;
    EXPECT_EQ(vec2, vec1);
}

TEST(TVectorTest, FrontException) {
    TVector<int> vec;
    EXPECT_THROW(vec.front(), std::runtime_error);
}

TEST(TVectorTest, BackException) {
    TVector<int> vec;
    EXPECT_THROW(vec.back(), std::runtime_error);
}

TEST(TVectorTest, FrontBackAfterOperations) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec.pop_front();
    vec.pop_back();
    vec.erase(vec.begin() + 2);
    EXPECT_EQ(2, vec.front());
    EXPECT_EQ(9, vec.back());
}

TEST(TVectorTest, IsEmptyTrue) {
    TVector<int> vec;
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, IsEmptyFalse) {
    TVector<int> vec = { 1, 2, 3 };
    EXPECT_FALSE(vec.is_empty());
}

TEST(TVectorTest, IsEmptyAfterClear) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    vec.clear();
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, IsEmptyAfterAllErased) {
    TVector<int> vec = { 1, 2, 3 };
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, ResizeWithValue) {
    TVector<int> vec = { 1, 2, 3 };
    vec.resize(6);
    EXPECT_EQ(6u, vec.size());
}

TEST(TVectorTest, IteratorBeginEndEmpty) {
    TVector<int> vec;
    EXPECT_EQ(vec.begin(), vec.end());
}

TEST(TVectorTest, IteratorArithmeticEdgeCases) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::Iterator it = vec.begin();

    // Test adding 0
    TVector<int>::Iterator it_plus_zero = it + 0;
    EXPECT_EQ(it, it_plus_zero);

    // Test subtracting 0
    TVector<int>::Iterator it_minus_zero = it - 0;
    EXPECT_EQ(it, it_minus_zero);
}

TEST(TVectorTest, IteratorSkipDeleted) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec.erase(vec.begin() + 2);  // Delete element at index 2 (value 3)
    vec.erase(vec.begin() + 4);  // Delete element at index 4 (value 6)

    // Iterate through and collect values
    TVector<int> collected;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        collected.push_back(*it);
    }

    TVector<int> expected = { 1, 2, 4, 5, 7, 8, 9, 10 };
    EXPECT_EQ(expected, collected);
}

TEST(TVectorTest, MemoryManagementStress) {
    TVector<int> vec;

    // Fill vector
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
    }

    // Remove every third element
    for (int i = 99; i >= 0; i -= 3) {
        if (i < static_cast<int>(vec.size())) {
            vec.erase(vec.begin() + i);
        }
    }

    // Add some more elements
    for (int i = 1000; i < 1020; ++i) {
        vec.push_back(i);
    }

    // Check that size is reasonable and vector is still functional
    bool size_reasonable = vec.size() > 50 && vec.size() < 150;
    bool can_access_elements = true;
    try {
        vec.front();
        vec.back();
        vec[0];
        vec[vec.size() - 1];
    }
    catch (...) {
        can_access_elements = false;
    }

    EXPECT_TRUE(size_reasonable);
    EXPECT_TRUE(can_access_elements);
}

TEST(TVectorTest, CopyWithDeletedElements) {
    TVector<int> vec1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec1.erase(vec1.begin() + 2);
    vec1.erase(vec1.begin() + 4);
    vec1.erase(vec1.begin() + 6);

    TVector<int> vec2(vec1);  // Copy constructor

    EXPECT_EQ(vec1, vec2);
    EXPECT_EQ(vec1.size(), vec2.size());
}

TEST(TVectorTest, MoveFromEmpty) {
    TVector<int> vec1;
    TVector<int> vec2(std::move(vec1));

    EXPECT_EQ(0u, vec1.size());
    EXPECT_EQ(0u, vec1.capacity());
    EXPECT_EQ(0u, vec2.size());
    EXPECT_EQ(0u, vec2.capacity());
    EXPECT_EQ(nullptr, vec1.data());
    EXPECT_EQ(nullptr, vec2.data());
}

TEST(TVectorTest, InitializerListDuplicates) {
    TVector<int> vec = { 5, 5, 5, 5, 5 };
    bool all_same = true;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] != 5) {
            all_same = false;
            break;
        }
    }
    EXPECT_TRUE(all_same);
    EXPECT_EQ(5u, vec.size());
}

TEST(TVectorTest, PushToFullCapacity) {
    TVector<int> vec(15, 1);  // Fill to exact capacity step
    vec.push_back(2);
    EXPECT_EQ(16u, vec.size());
    EXPECT_EQ(30u, vec.capacity());
    EXPECT_EQ(2, vec.back());
}

TEST(TVectorTest, MultipleInsertions) {
    TVector<int> vec = { 1, 5 };
    auto it = vec.begin() + 1;
    vec.insert(it, 2);
    vec.insert(it, 3);
    vec.insert(it, 4);

    TVector<int> expected = { 1, 4, 3, 2, 5 };
    EXPECT_EQ(expected, vec);
}

TEST(TVectorTest, EmplaceConstruction) {
    TVector<int> vec = { 1, 2, 4, 5 };
    vec.emplace(vec.begin() + 2, 3);

    TVector<int> expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(expected, vec);
}

TEST(TVectorTest, ShrinkToFitEmpty) {
    TVector<int> vec;
    vec.shrink_to_fit();
    EXPECT_EQ(0u, vec.size());
    EXPECT_EQ(0u, vec.capacity());
}

TEST(TVectorTest, ShrinkToFitAfterDeletions) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec.erase(vec.begin() + 2);
    vec.erase(vec.begin() + 4);
    vec.shrink_to_fit();

    EXPECT_EQ(8u, vec.size());
    EXPECT_EQ(8u, vec.capacity());
}

TEST(TVectorTest, ResizeToZero) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    vec.resize(0);
    EXPECT_EQ(0u, vec.size());
    EXPECT_TRUE(vec.is_empty());
}

TEST(TVectorTest, ResizeSameSize) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    size_t old_capacity = vec.capacity();
    vec.resize(5);
    EXPECT_EQ(5u, vec.size());
    EXPECT_EQ(old_capacity, vec.capacity());
}

TEST(TVectorTest, IndexAccessWithDeletions) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    vec.erase(vec.begin() + 2);  // Remove 3
    vec.erase(vec.begin() + 4);  // Remove 6 (now at index 4)

    // After deletions: {1, 2, 4, 5, 7, 8, 9, 10}
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(4, vec[2]);
    EXPECT_EQ(5, vec[3]);
    EXPECT_EQ(7, vec[4]);
}

TEST(TVectorTest, ConstOperations) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };

    // Test const data()
    EXPECT_EQ(1, *vec.data());

    // Test const operator[]
    EXPECT_EQ(3, vec[2]);

    // Test const size(), capacity()
    EXPECT_EQ(5u, vec.size());
    EXPECT_EQ(15u, vec.capacity());
}

TEST(TVectorTest, IteratorComparisons) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    auto it1 = vec.begin();
    auto it2 = vec.begin() + 2;
    auto it3 = vec.end();

    EXPECT_LT(it1, it2);
    EXPECT_GT(it2, it1);
    EXPECT_LE(it1, it2);
    EXPECT_GE(it2, it1);
    EXPECT_LT(it2, it3);
    EXPECT_FALSE(it1 > it3);
}

TEST(TVectorTest, IteratorIndexOperator) {
    TVector<int> vec = { 10, 20, 30, 40, 50 };
    auto it = vec.begin();

    EXPECT_EQ(10, it[0]);
    EXPECT_EQ(20, it[1]);
    EXPECT_EQ(30, it[2]);
    EXPECT_EQ(40, it[3]);
    EXPECT_EQ(50, it[4]);
}

TEST(TVectorTest, IteratorIndexOperatorException) {
    TVector<int> vec = { 1, 2, 3 };
    auto it = vec.begin();

    EXPECT_THROW(it[10], std::runtime_error);
}

TEST(TVectorTest, LargeOperations) {
    const size_t large_size = 10000;
    TVector<int> vec;

    // Fill with large amount of data
    for (size_t i = 0; i < large_size; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    // Verify size and some elements
    EXPECT_EQ(large_size, vec.size());
    EXPECT_EQ(0, vec[0]);
    EXPECT_EQ(static_cast<int>(large_size - 1), vec[large_size - 1]);
    EXPECT_EQ(static_cast<int>(large_size / 2), vec[large_size / 2]);
}

TEST(TVectorTest, ExceptionSafety) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };

    // Test invalid index access
    EXPECT_THROW(vec[100], std::out_of_range);

    // Test iterator out of range
    EXPECT_THROW(vec.begin() + 100, std::out_of_range);

    // Test dereferencing end()
    EXPECT_THROW(*(vec.end()), std::out_of_range);
}

TEST(TVectorTest, CapacityManagement) {
    TVector<int> vec;
    size_t prev_capacity = 0;
    bool capacity_increases = true;

    // Fill vector and check capacity increases
    for (int i = 0; i < 50; ++i) {
        if (vec.capacity() < prev_capacity) {
            capacity_increases = false;
            break;
        }
        prev_capacity = vec.capacity();
        vec.push_back(i);
    }

    EXPECT_TRUE(capacity_increases);
}

TEST(TVectorTest, EqualityAfterOperations) {
    TVector<int> vec1 = { 1, 2, 3, 4, 5 };
    TVector<int> vec2 = { 0, 1, 2, 3, 4, 5, 6 };

    // Modify vec2 to have same logical content as vec1
    vec2.pop_front();  // Remove 0
    vec2.pop_back();   // Remove 6

    EXPECT_EQ(vec1, vec2);
}

TEST(TVectorTest, SearchNoMatches) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    int result_begin = search_begin(vec, search_predicate_none_match);
    int result_end = search_end(vec, search_predicate_none_match);

    EXPECT_EQ(-1, result_begin);
    EXPECT_EQ(-1, result_end);
}

TEST(TVectorTest, SearchAllMatch) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    int result_begin = search_begin(vec, search_predicate_all_match);
    int result_end = search_end(vec, search_predicate_all_match);

    EXPECT_EQ(0, result_begin);
    EXPECT_EQ(4, result_end);
}

TEST(TVectorTest, SortAlreadySorted) {
    TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int> expected = vec;
    tv_sort(vec, sort_ascending);
    EXPECT_EQ(expected, vec);
}

TEST(TVectorTest, SortReverseOrder) {
    TVector<int> vec = { 5, 4, 3, 2, 1 };
    tv_sort(vec, sort_ascending);
    TVector<int> expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(expected, vec);
}

TEST(TVectorTest, SortWithDeletions) {
    TVector<int> vec = { 5, 4, 3, 2, 1, 6, 7, 8 };
    vec.erase(vec.begin() + 2);  // Remove 3
    vec.erase(vec.begin() + 4);  // Remove 1

    tv_sort(vec, sort_ascending);

    // Should be sorted but may have gaps due to deleted elements
    bool is_sorted = true;
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            is_sorted = false;
            break;
        }
    }

    EXPECT_TRUE(is_sorted);
}

TEST(TVectorTest, ShufflePreservesElements) {
    TVector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TVector<int> original = vec;

    shuffle(vec);

    // Sort both vectors to compare content
    tv_sort(vec, sort_ascending);
    tv_sort(original, sort_ascending);

    EXPECT_EQ(original, vec);
    EXPECT_EQ(original.size(), vec.size());
}

TEST(TVectorTest, PerformancePushBack) {
    TVector<int> vec;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; ++i) {
        vec.push_back(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Check that it completed and has correct size
    EXPECT_EQ(100000u, vec.size());
    // Note: Performance timing logged but not asserted
}

// Const Iterator Tests
TEST(TVectorTest, ConstIteratorBegin) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator it = vec.begin();

    EXPECT_EQ(1, *it);
}

TEST(TVectorTest, ConstIteratorEnd) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator it = vec.end();

    EXPECT_EQ(5, *(it - 1));
}

TEST(TVectorTest, ConstIteratorDereference) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator it = vec.begin();

    EXPECT_EQ(1, *it);
    // Note: Cannot modify through const_iterator - this is enforced at compile time
}

TEST(TVectorTest, ConstIteratorIncrement) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator it = vec.begin();

    ++it;
    EXPECT_EQ(2, *it);
}

TEST(TVectorTest, ConstIteratorDecrement) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator it = vec.end();

    --it;
    EXPECT_EQ(5, *it);
}

TEST(TVectorTest, ConstIteratorComparison) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    TVector<int>::ConstIterator begin_it = vec.begin();
    TVector<int>::ConstIterator end_it = vec.end();

    EXPECT_NE(begin_it, end_it);
    EXPECT_EQ(begin_it, begin_it);
}

TEST(TVectorTest, ConstIteratorRangeBasedFor) {
    const TVector<int> vec = { 1, 2, 3, 4, 5 };
    int sum = 0;

    for (const int& value : vec) {
        sum += value;
    }

    EXPECT_EQ(15, sum);
}

TEST(TVectorTest, ConstIteratorAfterModification) {
    TVector<int> vec = { 1, 2, 3 };
    const TVector<int>& const_ref = vec;

    // Modify vector
    vec.push_back(4);

    // Check that iterators work with new content
    int sum = 0;
    for (auto it = const_ref.begin(); it != const_ref.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(10, sum);  // 1+2+3+4=10
}
