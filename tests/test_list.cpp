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

TEST(TestList, PushBack_ShouldAddElementToEnd) {
    List<int> list;
    list.push_back(1);
    EXPECT_EQ(*list.begin(), 1);

    list.push_back(2);
    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(TestList, PushFront_ShouldAddElementToBeginning) {
    List<int> list;
    list.push_back(2);

    list.push_front(1);
    EXPECT_EQ(*list.begin(), 1);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(TestList, PushFront_OnEmptyList_ShouldAddSingleElement) {
    List<int> list;
    list.push_front(42);
    EXPECT_EQ(*list.begin(), 42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestList, InsertByPosition_AtBeginning_ShouldWorkLikePushFront) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    size_t pos = 0;

    list.insert(pos, 1);
    EXPECT_EQ(*list.begin(), 1);
}

TEST(TestList, InsertByPosition_AtEnd_ShouldWorkLikePushBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.insert(2, 3);
    auto it = list.begin();
    ++it; ++it;
    EXPECT_EQ(*it, 3);
}

TEST(TestList, InsertByPosition_InMiddle_ShouldMaintainOrder) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(1, 2);
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(TestList, InsertByPosition_OutOfRange_ShouldThrowException) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(5, 2), std::out_of_range);
}

TEST(TestList, InsertByIterator_ShouldAddElementAfterIterator) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    auto it = list.begin();
    list.insert(it, 2);

    auto result_it = list.begin();
    EXPECT_EQ(*result_it, 1);
    ++result_it;
    EXPECT_EQ(*result_it, 2);
    ++result_it;
    EXPECT_EQ(*result_it, 3);
}

TEST(TestList, InsertByIterator_AtTail_ShouldUpdateTail) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it = list.begin();
    ++it;
    list.insert(it, 3);

    // Verify new element is at the end
    auto last_it = list.begin();
    ++last_it; ++last_it;
    EXPECT_EQ(*last_it, 3);
}

TEST(TestList, InsertByIterator_WithNullIterator_ShouldThrowException) {
    List<int> list;
    list.push_back(1);

    List<int>::Iterator null_iterator(nullptr);
    EXPECT_THROW(list.insert(null_iterator, 2), std::runtime_error);
}

TEST(TestList, InsertByIterator_OnEmptyList_ShouldThrowException) {
    List<int> list;
    auto it = list.begin();

    EXPECT_THROW(list.insert(it, 1), std::runtime_error);
}

