// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <sstream>
#include <gtest/gtest.h>
#include "libs/lib_btree/btree.h"

class BTreeTest : public ::testing::Test {
protected:
    BTree<int, int> tree;

    void SetUp() override {
        for (int i = 0; i < 5; i++) {
            tree.insert(i, i + 1);
        }
    }
};

TEST_F(BTreeTest, BTreePrintW) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "0:1, 1:2, 2:3, 3:4, 4:5\n");
}

TEST_F(BTreeTest, BTreePrintDLCR) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "3:4, 1:2, 4:5, 0:1, 2:3\n");
}

TEST_F(BTreeTest, BTreePrintDLRC) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlrc();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "3:4, 4:5, 1:2, 2:3, 0:1\n");
}

TEST_F(BTreeTest, BTreePrintDCLR) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dclr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "0:1, 1:2, 3:4, 4:5, 2:3\n");
}

TEST_F(BTreeTest, BTreePrintTree) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "  2:3\n"
                        " 0:1\n"
                        "   4:5\n"
                        "  1:2\n"
                        "   3:4\n");
}

TEST(TestBTree, EraseFromEmptyTreeThrowException) {
    BTree<int, int> tree;

    EXPECT_THROW(tree.erase(2), std::logic_error);
}

TEST(TestBTree, EraseNonexistantRootThrowException) {
    BTree<int, int> tree;
    tree.insert(1, 100);

    EXPECT_THROW(tree.erase(2), std::invalid_argument);
}

TEST(TestBTree, EraseNonexistantThrowException) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);
    tree.insert(4, 400);
    tree.insert(5, 500);

    EXPECT_THROW(tree.erase(6), std::invalid_argument);
}

TEST(TestBTree, EraseNode) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);
    tree.insert(4, 400);
    tree.insert(5, 500);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:100, 2:200, 3:300, 4:400, 5:500\n");

    tree.erase(2);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:100, 5:500, 3:300, 4:400\n");
}

TEST(TestBTree, EraseRoot) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);
    tree.insert(4, 400);
    tree.insert(5, 500);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:100, 2:200, 3:300, 4:400, 5:500\n");

    tree.erase(1);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "5:500, 2:200, 3:300, 4:400\n");
}

TEST(TestBTree, EraseSingleRoot) {
    BTree<int, int> tree;
    tree.insert(1, 100);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:100\n");

    tree.erase(1);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "");
}

TEST(TestBTree, ClearAndEmpty) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);
    tree.insert(4, 400);
    tree.insert(5, 500);

    EXPECT_FALSE(tree.is_empty());
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBTree, InsertRootKeyThrowsException) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);

    EXPECT_THROW(tree.insert(1, 100), std::invalid_argument);
}

TEST(TestBTree, InsertExistKeyThrowsException) {
    BTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);

    EXPECT_THROW(tree.insert(3, 100), std::invalid_argument);
}
