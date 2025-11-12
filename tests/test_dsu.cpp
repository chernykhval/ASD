// Copyright 2025 Chernykh Valentin

#include <gtest/gtest.h>
#include "libs/lib_dsu/dsu.h"

#define EPSILON 0.000001

TEST(TestDSU, ConstructorInitialization) {
    DSU dsu(5);

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(TestDSU, FindOutOfRange) {
    DSU dsu(3);

    EXPECT_THROW(dsu.find(-1), std::out_of_range);
    EXPECT_THROW(dsu.find(3), std::out_of_range);
    EXPECT_THROW(dsu.find(100), std::out_of_range);
}

TEST(TestDSU, BasicUnion) {
    DSU dsu(5);

    dsu.unite(0, 1);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_NE(dsu.find(0), dsu.find(2));
}

TEST(TestDSU, UnionOutOfRange) {
    DSU dsu(3);

    EXPECT_THROW(dsu.unite(-1, 0), std::out_of_range);
    EXPECT_THROW(dsu.unite(0, 3), std::out_of_range);
    EXPECT_THROW(dsu.unite(2, 5), std::out_of_range);
}

TEST(TestDSU, MultipleUnions) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    dsu.unite(4, 5);

    int set1 = dsu.find(0);
    int set2 = dsu.find(3);

    EXPECT_EQ(set1, dsu.find(1));
    EXPECT_EQ(set1, dsu.find(2));
    EXPECT_EQ(set2, dsu.find(4));
    EXPECT_EQ(set2, dsu.find(5));
    EXPECT_NE(set1, set2);

    dsu.unite(2, 3);
    EXPECT_EQ(dsu.find(0), dsu.find(5));
}

TEST(TestDSU, UnionSameElement) {
    DSU dsu(3);

    dsu.unite(1, 1);
    EXPECT_EQ(dsu.find(1), 1);
}

TEST(TestDSU, RepeatedUnion) {
    DSU dsu(4);

    dsu.unite(0, 1);
    int original_parent = dsu.find(0);
    
    dsu.unite(0, 1);
    dsu.unite(1, 0);

    EXPECT_EQ(dsu.find(0), original_parent);
    EXPECT_EQ(dsu.find(1), original_parent);
}

TEST(TestDSU, UnionByRank) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(2, 3);

    dsu.unite(0, 2);

    int root1 = dsu.find(0);
    int root2 = dsu.find(1);
    int root3 = dsu.find(2);
    int root4 = dsu.find(3);

    EXPECT_EQ(root1, root2);
    EXPECT_EQ(root1, root3);
    EXPECT_EQ(root1, root4);
}

TEST(TestDSU, RankBehavior) {
    DSU dsu(4);

    dsu.unite(0, 1);

    dsu.unite(2, 3);

    dsu.unite(0, 2);

    int representative = dsu.find(0);
    EXPECT_EQ(representative, dsu.find(1));
    EXPECT_EQ(representative, dsu.find(2));
    EXPECT_EQ(representative, dsu.find(3));
}

TEST(TestDSU, LargeSequenceOfOperations) {
    const int SIZE = 100;
    DSU dsu(SIZE);

    for (int i = 2; i < SIZE; i += 2) {
        dsu.unite(0, i);
    }

    for (int i = 3; i < SIZE; i += 2) {
        dsu.unite(1, i);
    }

    int even_rep = dsu.find(0);
    int odd_rep = dsu.find(1);
    EXPECT_NE(even_rep, odd_rep);

    for (int i = 0; i < SIZE; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(dsu.find(i), even_rep);
        } else {
            EXPECT_EQ(dsu.find(i), odd_rep);
        }
    }

    dsu.unite(0, 1);

    int final_rep = dsu.find(0);
    for (int i = 0; i < SIZE; i++) {
        EXPECT_EQ(dsu.find(i), final_rep);
    }
}

TEST(TestDSU, SingleElement) {
    DSU dsu(1);

    EXPECT_EQ(dsu.find(0), 0);
    dsu.unite(0, 0);
    EXPECT_EQ(dsu.find(0), 0);
}

TEST(TestDSU, TwoElements) {
    DSU dsu(2);

    EXPECT_NE(dsu.find(0), dsu.find(1));
    dsu.unite(0, 1);
    EXPECT_EQ(dsu.find(0), dsu.find(1));
}
