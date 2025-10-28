// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_list/list.h"

#define EPSILON 0.000001

TEST(TestList, DefaultConstructor_ShouldCreateEmptyList) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestList, CopyConstructor_ShouldCreateIndependentCopy) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy = original;

    auto orig_it = original.begin();
    auto copy_it = copy.begin();
    while (orig_it != original.end() && copy_it != copy.end()) {
        EXPECT_EQ(*orig_it, *copy_it);
        ++orig_it;
        ++copy_it;
    }

    *original.begin() = 100;
    EXPECT_EQ(*copy.begin(), 1);

    *copy.begin() = 200;
    EXPECT_EQ(*original.begin(), 100);
}

TEST(TestList, CopyConstructor_WithEmptyList_ShouldCreateEmptyList) {
    List<int> original;
    List<int> copy = original;

    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(copy.begin(), copy.end());
}

TEST(TestList, EmptyList_IteratorBegin_ShouldEqualEnd) {
    List<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestList, EmptyList_ConstIteratorBegin_ShouldEqualEnd) {
    const List<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestList, Iterator_ShouldTraverseElementsInOrder) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    int expected_value = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(TestList, Iterator_ShouldAllowElementModification) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = 11;
    }

    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, 11);
    }
}

TEST(TestList, ConstIterator_ShouldTraverseWithoutModification) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    const List<int>& const_list = list;
    int expected_value = 0;
    for (auto it = const_list.begin(); it != const_list.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(TestList, ConstIterator_OnCopiedList_ShouldPreserveOriginalData) {
    List<int> original;
    for (int i = 0; i < 3; i++) {
        original.push_back(i);
    }

    const List<int> copied = original;
    int expected_value = 0;
    for (auto it = copied.begin(); it != copied.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }

    expected_value = 0;
    for (auto it = original.begin(); it != original.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(TestList, IsEmpty_OnNewList_ShouldReturnTrue) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
}

TEST(TestList, IsEmpty_AfterPushBack_ShouldReturnFalse) {
    List<int> list;
    list.push_back(42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestList, IsEmpty_AfterPushFront_ShouldReturnFalse) {
    List<int> list;
    list.push_front(42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestList, IsEmpty_AfterClear_ShouldReturnTrue) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestList, IsEmpty_AfterPopLastElement_ShouldReturnTrue) {
    List<int> list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}


