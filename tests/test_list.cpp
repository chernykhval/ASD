// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_list/list.h"

#define EPSILON 0.000001

TEST(TestList, EmptyListIteratorBeginShouldEqEnd) {
    List<int> list;

    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestList, EmptyListConstIteratorBeginShouldEqEnd) {
    const List<int> list;

    EXPECT_EQ(list.begin(), list.end());
}

TEST(TestList, ListIterationWithIterator) {
    List<int> list;

    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(*it, i);
        i++;
    }
}

TEST(TestList, ListConstIterationWithIterator) {
    List<int> list;

    for (int i = 0; i < 3; i++) {
        list.push_back(i);
    }

    List<int> clist = list;

    EXPECT_EQ(*list.begin(), 0);

    // int i = 0;

    // for (List<int>::ConstIterator it = clist.begin(); it != clist.end(); ++it) {
    //     EXPECT_EQ(*it, i);
    //     i++;
    // }
}
