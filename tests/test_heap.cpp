// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include "libs/lib_heap/heap.h"

TEST(TestHeap, HeapSort) {
    Heap<int> heap;
    std::stringstream ss;
    bool is_first = true;

    int array[15] = {10, 5, 3, 7, 8, 9, 3, 4, 1, 2, 3, 6, 5, 9, 7};

    for (int i = 0; i < 15; i++) {
        heap.insert(array[i]);
    }

    for (int i = 0; i < 15; i++) {
        if (!is_first) {
            ss << ", ";
        }

        is_first = false;
        ss << heap.pop();
    }

    EXPECT_EQ(ss.str(), "1, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7, 8, 9, 9, 10");
}

TEST(TestHeap, ClearAndThenIsEmpty) {
    Heap<int> heap;

    EXPECT_TRUE(heap.is_empty());

    int array[10] = {10, 3, 7, 8, 9, 4, 1, 2, 6, 5};

    for (int i = 0; i < 10; i++) {
        heap.insert(array[i]);
    }

    EXPECT_FALSE(heap.is_empty());
    heap.clear();
    EXPECT_TRUE(heap.is_empty());
}

TEST(TestHeap, TopReturnCorrect) {
    Heap<int> heap;

    heap.insert(3);
    EXPECT_EQ(heap.top(), 3);
    heap.insert(-1);
    EXPECT_EQ(heap.top(), -1);
}

TEST(TestHeap, SizeReturnCorrect) {
    Heap<int> heap;

    EXPECT_EQ(heap.size(), 0);
    heap.insert(3);
    EXPECT_EQ(heap.size(), 1);
    heap.insert(-1);
    EXPECT_EQ(heap.size(), 2);
}

TEST(TestHeap, EmptyHeapTopThrowExcept) {
    Heap<int> heap;

    EXPECT_THROW(heap.top(), std::logic_error);
}

TEST(TestHeap, EmptyHeapPopThrowExcept) {
    Heap<int> heap;

    EXPECT_THROW(heap.pop(), std::logic_error);
}
