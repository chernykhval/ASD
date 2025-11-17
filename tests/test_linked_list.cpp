// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_linked_list/linked_list.h"

#define EPSILON 0.000001

TEST(TestLinkedList, DefaultConstructor_ShouldCreateEmptyList) {
    LinkedList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestLinkedList, CopyConstructor_ShouldCreateIndependentCopy) {
    LinkedList<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    LinkedList<int> copy = original;

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

TEST(TestLinkedList, CopyConstructor_WithEmptyList_ShouldCreateEmptyList) {
    LinkedList<int> original;
    LinkedList<int> copy = original;

    EXPECT_TRUE(copy.is_empty());
    EXPECT_EQ(copy.begin(), copy.end());
}

TEST(TestLinkedList, EmptyList_IteratorBegin_ShouldEqualEnd) {
    LinkedList<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestLinkedList, EmptyList_ConstIteratorBegin_ShouldEqualEnd) {
    const LinkedList<int> list;
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestLinkedList, Iterator_ShouldTraverseElementsInOrder) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    int expected_value = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(TestLinkedList, Iterator_ShouldAllowElementModification) {
    LinkedList<int> list;
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

TEST(TestLinkedList, ConstIterator_ShouldTraverseWithoutModification) {
    LinkedList<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    const LinkedList<int>& const_list = list;
    int expected_value = 0;
    for (auto it = const_list.begin(); it != const_list.end(); ++it) {
        EXPECT_EQ(*it, expected_value);
        expected_value++;
    }
}

TEST(TestLinkedList, ConstIterator_OnCopiedList_ShouldPreserveOriginalData) {
    LinkedList<int> original;
    for (int i = 0; i < 3; i++) {
        original.push_back(i);
    }

    const LinkedList<int> copied = original;
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

TEST(TestLinkedList, IsEmpty_OnNewList_ShouldReturnTrue) {
    LinkedList<int> list;
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, IsEmpty_AfterPushBack_ShouldReturnFalse) {
    LinkedList<int> list;
    list.push_back(42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestLinkedList, IsEmpty_AfterPushFront_ShouldReturnFalse) {
    LinkedList<int> list;
    list.push_front(42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestLinkedList, IsEmpty_AfterClear_ShouldReturnTrue) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, IsEmpty_AfterPopLastElement_ShouldReturnTrue) {
    LinkedList<int> list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, PushBack_ShouldAddElementToEnd) {
    LinkedList<int> list;
    list.push_back(1);
    EXPECT_EQ(*list.begin(), 1);

    list.push_back(2);
    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(TestLinkedList, PushFront_ShouldAddElementToBeginning) {
    LinkedList<int> list;
    list.push_back(2);

    list.push_front(1);
    EXPECT_EQ(*list.begin(), 1);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(TestLinkedList, PushFront_OnEmptyList_ShouldAddSingleElement) {
    LinkedList<int> list;
    list.push_front(42);
    EXPECT_EQ(*list.begin(), 42);
    EXPECT_FALSE(list.is_empty());
}

TEST(TestLinkedList, InsertByPosition_AtBeginning_ShouldWorkLikePushFront) {
    LinkedList<int> list;
    list.push_back(2);
    list.push_back(3);

    size_t pos = 0;

    list.insert(pos, 1);
    EXPECT_EQ(*list.begin(), 1);
}

TEST(TestLinkedList, InsertByPosition_AtEnd_ShouldWorkLikePushBack) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.insert(2, 3);
    auto it = list.begin();
    ++it; ++it;
    EXPECT_EQ(*it, 3);
}

TEST(TestLinkedList, InsertByPosition_InMiddle_ShouldMaintainOrder) {
    LinkedList<int> list;
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

TEST(TestLinkedList, InsertByPosition_OutOfRange_ShouldThrowException) {
    LinkedList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(5, 2), std::out_of_range);
}

TEST(TestLinkedList, InsertByIterator_ShouldAddElementAfterIterator) {
    LinkedList<int> list;
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

TEST(TestLinkedList, InsertByIterator_AtTail_ShouldUpdateTail) {
    LinkedList<int> list;
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

TEST(TestLinkedList, InsertByIterator_WithNullIterator_ShouldThrowException) {
    LinkedList<int> list;
    list.push_back(1);

    LinkedList<int>::Iterator null_iterator(nullptr);
    EXPECT_THROW(list.insert(null_iterator, 2), std::runtime_error);
}

TEST(TestLinkedList, InsertByIterator_OnEmptyList_ShouldThrowException) {
    LinkedList<int> list;
    auto it = list.begin();

    EXPECT_THROW(list.insert(it, 1), std::runtime_error);
}

TEST(TestLinkedList, PopBack_OnEmptyList_ShouldThrowException) {
    LinkedList<int> list;
    EXPECT_THROW(list.pop_back(), std::runtime_error);
}

TEST(TestLinkedList, PopFront_OnEmptyList_ShouldThrowException) {
    LinkedList<int> list;
    EXPECT_THROW(list.pop_front(), std::runtime_error);
}

TEST(TestLinkedList, PopBack_OnSingleElement_ShouldMakeListEmpty) {
    LinkedList<int> list;
    list.push_back(42);
    list.pop_back();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, PopFront_OnSingleElement_ShouldMakeListEmpty) {
    LinkedList<int> list;
    list.push_back(42);
    list.pop_front();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, PopBack_OnMultipleElements_ShouldRemoveLastElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(TestLinkedList, PopFront_OnMultipleElements_ShouldRemoveFirstElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(*list.begin(), 2);
}

TEST(TestLinkedList, EraseByPosition_AtBeginning_ShouldRemoveFirstElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(0);
    EXPECT_EQ(*list.begin(), 2);
}

TEST(TestLinkedList, EraseByPosition_AtEnd_ShouldRemoveLastElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(2);

    auto it = list.begin();
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(TestLinkedList, EraseByPosition_InMiddle_ShouldRemoveCorrectElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.erase(1);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(TestLinkedList, EraseByPosition_OutOfRange_ShouldThrowException) {
    LinkedList<int> list;
    list.push_back(1);

    EXPECT_THROW(list.erase(5), std::out_of_range);
}

TEST(TestLinkedList, EraseByIterator_ShouldRemoveTargetElement) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it;
    list.erase(it);

    auto result_it = list.begin();
    EXPECT_EQ(*result_it, 1);
    ++result_it;
    EXPECT_EQ(*result_it, 3);
}

TEST(TestLinkedList, EraseByIterator_AtBeginning_ShouldUpdateHead) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);

    list.erase(list.begin());
    EXPECT_EQ(*list.begin(), 2);
}

TEST(TestLinkedList, EraseByIterator_AtEnd_ShouldUpdateTail) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    ++it; ++it;
    list.erase(it);

    auto last_it = list.begin();
    ++last_it;
    EXPECT_EQ(*last_it, 2);
    ++last_it;
    EXPECT_EQ(last_it, list.end());
}

TEST(TestLinkedList, EraseByIterator_WithNullIterator_ShouldThrowException) {
    LinkedList<int> list;
    list.push_back(1);

    LinkedList<int>::Iterator null_it(nullptr);
    EXPECT_THROW(list.erase(null_it), std::runtime_error);
}

TEST(TestLinkedList, Clear_OnEmptyList_ShouldDoNothing) {
    LinkedList<int> list;
    list.clear();
    EXPECT_TRUE(list.is_empty());
}

TEST(TestLinkedList, Clear_OnNonEmptyList_ShouldRemoveAllElements) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestLinkedList, Clear_ShouldAllowReuseOfList) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();

    list.push_back(3);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(*list.begin(), 3);
}



TEST(TestLinkedList, AssignmentOperator_ShouldCreateIndependentCopy) {
    LinkedList<int> original;
    original.push_back(1);
    original.push_back(2);

    LinkedList<int> copy;
    copy = original;

    auto orig_it = original.begin();
    auto copy_it = copy.begin();
    while (orig_it != original.end() && copy_it != copy.end()) {
        EXPECT_EQ(*orig_it, *copy_it);
        ++orig_it;
        ++copy_it;
    }

    *original.begin() = 100;
    EXPECT_EQ(*copy.begin(), 1);
}

TEST(TestLinkedList, AssignmentOperator_ToNonEmptyList_ShouldClearOldData) {
    LinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);

    LinkedList<int> list2;
    list2.push_back(30);
    list2.push_back(40);
    list2.push_back(50);

    list1 = list2;

    auto it = list1.begin();
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(*it, 40);
    ++it;
    EXPECT_EQ(*it, 50);
}

TEST(TestLinkedList, AssignmentOperator_FromEmptyList_ShouldMakeTargetEmpty) {
    LinkedList<int> non_empty;
    non_empty.push_back(1);
    non_empty.push_back(2);

    LinkedList<int> empty;
    non_empty = empty;

    EXPECT_TRUE(non_empty.is_empty());
}

TEST(TestLinkedList, AssignmentOperator_ChainedAssignment_ShouldWork) {
    LinkedList<int> a, b, c;
    c.push_back(1);
    c.push_back(2);

    a = b = c;

    EXPECT_EQ(*a.begin(), 1);
    EXPECT_EQ(*b.begin(), 1);
    EXPECT_EQ(*c.begin(), 1);
}

TEST(TestLinkedList, AssignmentOperator_ShouldReturnReference) {
    LinkedList<int> a, b, c;
    c.push_back(42);

    (a = b) = c;
    EXPECT_EQ(*a.begin(), 42);
}
