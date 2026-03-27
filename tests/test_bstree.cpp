// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <gtest/gtest.h>
#include "libs/lib_bstree/bstree.h"

class PrintBSTreeTest : public ::testing::Test {
protected:
    BSTree<int, int> tree;

    void SetUp() override {
        int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

        for (int i = 0; i < 11; i++) {
            tree.insert(array[i], i);
        }
    }
};

TEST_F(PrintBSTreeTest, PrintW) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "6:0, 4:1, 7:2, 1:3, 5:4, 11:5, 2:6, 9:7, 3:8, 8:9, 10:10\n");
}

TEST_F(PrintBSTreeTest, PrintDLCR) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:3, 2:6, 3:8, 4:1, 5:4, 6:0, 7:2, 8:9, 9:7, 10:10, 11:5\n");
}

TEST_F(PrintBSTreeTest, PrintDLRC) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlrc();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "3:8, 2:6, 1:3, 5:4, 4:1, 8:9, 10:10, 9:7, 11:5, 7:2, 6:0\n");
}

TEST_F(PrintBSTreeTest, PrintDCLR) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dclr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "6:0, 4:1, 1:3, 2:6, 3:8, 5:4, 7:2, 11:5, 9:7, 8:9, 10:10\n");
}

TEST_F(PrintBSTreeTest, PrintTree) {
    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, InsertSortArray) {
    BSTree<int, int> tree;

    int array[10] = {10, 3, 7, 8, 9, 4, 1, 2, 6, 5};

    for (int i = 0; i < 10; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "1:6, 2:7, 3:1, 4:5, 5:9, 6:8, 7:2, 8:3, 9:4, 10:0\n");
}

TEST(TestBSTree, InsertAlreadyExistElemThrowsException) {
    BSTree<int, int> tree;

    int array[10] = {10, 3, 7, 8, 9, 4, 1, 2, 6, 5};

    for (int i = 0; i < 10; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_THROW(tree.insert(10, 10), std::invalid_argument);
}

TEST(TestBSTree, ClearAndEmpty) {
    BSTree<int, int> tree;
    tree.insert(1, 100);
    tree.insert(2, 200);
    tree.insert(3, 300);
    tree.insert(4, 400);
    tree.insert(5, 500);

    EXPECT_FALSE(tree.is_empty());
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBSTree, Erase) {
    BSTree<int, int> tree;

    int array[10] = {5, 3, 1, 2, 4, 7, 9, 10, 8, 6};

    for (int i = 0; i < 10; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    10:7\n"
                        "   9:6\n"
                        "    8:8\n"
                        "  7:5\n"
                        "   6:9\n"
                        " 5:0\n"
                        "   4:4\n"
                        "  3:1\n"
                        "    2:3\n"
                        "   1:2\n");

    tree.erase(3);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    10:7\n"
                        "   9:6\n"
                        "    8:8\n"
                        "  7:5\n"
                        "   6:9\n"
                        " 5:0\n"
                        "   4:4\n"
                        "  2:3\n"
                        "   1:2\n");
}

TEST(TestBSTree, EraseLeaf) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(3);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, EraseNodeWithOneLeftChild) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(11);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, EraseNodeWithOneRightChild) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(7);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "  8:9\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, EraseRootNode) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(6);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, EraseNodeWithTwoChields) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    9:7\n"
                        "     8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");

    tree.erase(9);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   11:5\n"
                        "     10:10\n"
                        "    8:9\n"
                        "  7:2\n"
                        " 6:0\n"
                        "   5:4\n"
                        "  4:1\n"
                        "     3:8\n"
                        "    2:6\n"
                        "   1:3\n");
}

TEST(TestBSTree, EraseKeyNotExistThrow) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_THROW(tree.erase(25), std::invalid_argument);
}

TEST(TestBSTree, EraseEmptyTreeThrow) {
    BSTree<int, int> tree;

    EXPECT_THROW(tree.erase(25), std::logic_error);
}

TEST(TestBSTree, EraseTreeWithOneNode) {
    BSTree<int, int> tree;

    tree.insert(1, 1);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), " 1:1\n");

    tree.erase(1);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "");
}

TEST(TestBSTree, FindInEmptyTreeReturnNullptr) {
    BSTree<int, int> tree;

    EXPECT_EQ(tree.find(1), nullptr);
}

TEST(TestBSTree, FindNonExistKeyreturnNullptr) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_EQ(tree.find(25), nullptr);
}

TEST(TestBSTree, FindLeafReturnPtr) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_EQ(*tree.find(10), 10);
}

TEST(TestBSTree, FindNodeReturnPtr) {
    BSTree<int, int> tree;

    int array[11] = {6, 4, 7, 1, 5, 11, 2, 9, 3, 8, 10};

    for (int i = 0; i < 11; i++) {
        tree.insert(array[i], i);
    }

    EXPECT_EQ(*tree.find(2), 6);
}

TEST(TestBSTree, FindRootInTreeWithSingleElementReturnPtr) {
    BSTree<int, int> tree;

    tree.insert(6, 24);

    EXPECT_EQ(*tree.find(6), 24);
}
