// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_list/list.h"

#define EPSILON 0.000001

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
