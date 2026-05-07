// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <sstream>
#include <gtest/gtest.h>
#include "libs/lib_avltree/avltree.h"

TEST(TestAVLTree, IsEmptyOnNewTree) {
    AVLTree<int, int> tree;
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, IsEmptyAfterInsert) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    EXPECT_FALSE(tree.is_empty());
}

TEST(TestAVLTree, InsertDuplicateThrows) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    EXPECT_THROW(tree.insert(1, 2), std::invalid_argument);
}

TEST(TestAVLTree, FindInEmptyTreeReturnsNullptr) {
    AVLTree<int, int> tree;
    EXPECT_EQ(nullptr, tree.find(1));
}

TEST(TestAVLTree, FindNonExistentReturnsNullptr) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    EXPECT_EQ(nullptr, tree.find(4));
}

TEST(TestAVLTree, FindNonExistentWouldBeChildOfRoot) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_EQ(nullptr, tree.find(7));
}

TEST(TestAVLTree, FindRootReturnsValue) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    EXPECT_EQ(50, *tree.find(5));
}

TEST(TestAVLTree, FindLeafReturnsValue) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    EXPECT_EQ(30, *tree.find(3));
    EXPECT_EQ(70, *tree.find(7));
}

TEST(TestAVLTree, FindAllowsModify) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    *tree.find(5) = 99;
    EXPECT_EQ(99, *tree.find(5));
}

TEST(TestAVLTree, ClearEmptiesTree) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(1));
}

TEST(TestAVLTree, EraseEmptyTreeThrows) {
    AVLTree<int, int> tree;
    EXPECT_THROW(tree.erase(1), std::logic_error);
}

TEST(TestAVLTree, EraseNonExistentThrows) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    EXPECT_THROW(tree.erase(99), std::invalid_argument);
}

TEST(TestAVLTree, EraseSingleNode) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    tree.erase(1);
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(1));
}

TEST(TestAVLTree, EraseLeaf) {
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.erase(3);
    EXPECT_EQ(nullptr, tree.find(3));
    EXPECT_EQ(50, *tree.find(5));
    EXPECT_EQ(70, *tree.find(7));
}

TEST(TestAVLTree, PrintDLCR) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlcr();
    std::cout.rdbuf(old);

    EXPECT_EQ("1:1, 3:3, 4:4, 5:5, 7:7\n", ss.str());
}

TEST(TestAVLTree, PrintDLRC) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dlrc();
    std::cout.rdbuf(old);

    EXPECT_EQ("1:1, 4:4, 3:3, 7:7, 5:5\n", ss.str());
}

TEST(TestAVLTree, PrintDCLR) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_dclr();
    std::cout.rdbuf(old);

    EXPECT_EQ("5:5, 3:3, 1:1, 4:4, 7:7\n", ss.str());
}

TEST(TestAVLTree, PrintW) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_w();
    std::cout.rdbuf(old);

    EXPECT_EQ("5:5, 3:3, 7:7, 1:1, 4:4\n", ss.str());
}

TEST(TestAVLTree, SizeAfterInserts) {
    AVLTree<int, int> tree;
    EXPECT_EQ(0, tree.size());
    tree.insert(1, 1);
    EXPECT_EQ(1, tree.size());
    tree.insert(2, 2);
    tree.insert(3, 3);
    EXPECT_EQ(3, tree.size());
}

TEST(TestAVLTree, SizeAfterErase) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.erase(2);
    EXPECT_EQ(2, tree.size());
}

TEST(TestAVLTree, SizeAfterClear) {
    AVLTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.clear();
    EXPECT_EQ(0, tree.size());
}

TEST(TestAVLTree, GetKeysEmpty) {
    AVLTree<int, int> tree;
    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(0, keys.size());
}

TEST(TestAVLTree, GetKeysReturnsBFS) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    TVector<int> keys = tree.get_keys();
    EXPECT_EQ(5, keys.size());
    EXPECT_EQ(5, keys[0]);
    EXPECT_EQ(3, keys[1]);
    EXPECT_EQ(7, keys[2]);
    EXPECT_EQ(1, keys[3]);
    EXPECT_EQ(4, keys[4]);
}

TEST(TestAVLTree, EraseRoot) {
    AVLTree<int, int> tree;
    tree.insert(5, 5);
    tree.insert(3, 3);
    tree.insert(7, 7);
    tree.insert(1, 1);
    tree.insert(4, 4);

    tree.erase(5);

    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_EQ(3, *tree.find(3));
    EXPECT_EQ(7, *tree.find(7));
    EXPECT_EQ(4, tree.size());
}

TEST(TestAVLTree, InsertRRCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 70, 100, 120, 10, 50, 80, 130, 40, 60};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "     60:12\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.insert(140, 13);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    140:13\n"
                        "   130:10\n"
                        "    120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "     60:12\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");
}

TEST(TestAVLTree, InsertLLCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 70, 100, 120, 10, 50, 80, 130, 40, 60};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "     60:12\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.insert(39, 13);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "     80:9\n"
                        "    70:4\n"
                        "     60:12\n"
                        "   50:8\n"
                        "    40:11\n"
                        "     39:13\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");
}

TEST(TestAVLTree, InsertLRCase1) {
    AVLTree<int, int> tree;

    int array[9] = {70, 20, 90, 10, 40, 80, 100, 30, 50};

    for (int i = 0; i < 9; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   100:6\n"
                        "  90:2\n"
                        "   80:5\n"
                        " 70:0\n"
                        "    50:8\n"
                        "   40:4\n"
                        "    30:7\n"
                        "  20:1\n"
                        "   10:3\n");

    tree.insert(60, 9);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   100:6\n"
                        "  90:2\n"
                        "   80:5\n"
                        " 70:0\n"
                        "    60:9\n"
                        "   50:8\n"
                        "  40:4\n"
                        "    30:7\n"
                        "   20:1\n"
                        "    10:3\n");

    tree.insert(61, 10);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "   100:6\n"
                        "  90:2\n"
                        "   80:5\n"
                        " 70:0\n"
                        "    61:10\n"
                        "   60:9\n"
                        "    50:8\n"
                        "  40:4\n"
                        "    30:7\n"
                        "   20:1\n"
                        "    10:3\n");

    tree.insert(62, 11);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    100:6\n"
                        "   90:2\n"
                        "    80:5\n"
                        "  70:0\n"
                        "    62:11\n"
                        "   61:10\n"
                        " 60:9\n"
                        "   50:8\n"
                        "  40:4\n"
                        "    30:7\n"
                        "   20:1\n"
                        "    10:3\n");
}

TEST(TestAVLTree, InsertLRCase2) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 70, 100, 120, 10, 50, 80, 130, 40, 60};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "     60:12\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.insert(59, 13);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "     80:9\n"
                        "    70:4\n"
                        "   60:12\n"
                        "     59:13\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");
}

TEST(TestAVLTree, InsertRLCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 50, 100, 120, 10, 40, 70, 130, 60, 80};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "     80:12\n"
                        "    70:9\n"
                        "     60:11\n"
                        "   50:4\n"
                        "    40:8\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.insert(61, 13);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "     80:12\n"
                        "    70:9\n"
                        "     61:13\n"
                        "   60:11\n"
                        "    50:4\n"
                        "     40:8\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");
}

TEST(TestAVLTree, EraseRRCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 50, 100, 120, 10, 40, 70, 130, 60, 80};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "     80:12\n"
                        "    70:9\n"
                        "     60:11\n"
                        "   50:4\n"
                        "    40:8\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.erase(20);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:12\n"
                        "   70:9\n"
                        "    60:11\n"
                        "  50:4\n"
                        "    40:8\n"
                        "   30:1\n"
                        "    10:7\n");
}

TEST(TestAVLTree, EraseRLCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 30, 110, 20, 70, 100, 120, 10, 50, 80, 130, 40, 60};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "     60:12\n"
                        "    50:8\n"
                        "     40:11\n"
                        "  30:1\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.erase(20);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "    60:12\n"
                        "  50:8\n"
                        "    40:11\n"
                        "   30:1\n"
                        "    10:7\n");
}

TEST(TestAVLTree, EraseLLCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 60, 110, 40, 70, 100, 120, 20, 50, 80, 130, 10, 30};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "  60:1\n"
                        "    50:8\n"
                        "   40:3\n"
                        "     30:12\n"
                        "    20:7\n"
                        "     10:11\n");

    tree.erase(70);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   60:1\n"
                        "    50:8\n"
                        "  40:3\n"
                        "    30:12\n"
                        "   20:7\n"
                        "    10:11\n");
}

TEST(TestAVLTree, EraseLRCase) {
    AVLTree<int, int> tree;

    int array[13] = {90, 60, 110, 20, 70, 100, 120, 10, 40, 80, 130, 30, 50};

    for (int i = 0; i < 13; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   70:4\n"
                        "  60:1\n"
                        "     50:12\n"
                        "    40:8\n"
                        "     30:11\n"
                        "   20:3\n"
                        "    10:7\n");

    tree.erase(70);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    130:10\n"
                        "   120:6\n"
                        "  110:2\n"
                        "   100:5\n"
                        " 90:0\n"
                        "    80:9\n"
                        "   60:1\n"
                        "    50:12\n"
                        "  40:8\n"
                        "    30:11\n"
                        "   20:3\n"
                        "    10:7\n");
}

TEST(TestAVLTree, EraseRRAndLLCase) {
    AVLTree<int, int> tree;

    int array[12] = {80, 50, 100, 30, 60, 90, 110, 20, 40, 70, 120, 10};

    for (int i = 0; i < 12; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    120:10\n"
                        "   110:6\n"
                        "  100:2\n"
                        "   90:5\n"
                        " 80:0\n"
                        "    70:9\n"
                        "   60:4\n"
                        "  50:1\n"
                        "    40:8\n"
                        "   30:3\n"
                        "    20:7\n"
                        "     10:11\n");

    tree.erase(90);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "    120:10\n"
                        "   110:6\n"
                        "    100:2\n"
                        "  80:0\n"
                        "    70:9\n"
                        "   60:4\n"
                        " 50:1\n"
                        "   40:8\n"
                        "  30:3\n"
                        "   20:7\n"
                        "    10:11\n");
}

TEST(TestAVLTree, EraseThreeRebalanceCase) {
    AVLTree<int, int> tree;

    int array[33] = {130, 80, 260, 50, 100, 210, 290, 30, 60, 90, 110, 180, 230, 270, 310, 20, 40, 70, 120, 160, 190, 220, 240, 280, 300, 320, 10, 140, 170, 200, 250, 330, 150};

    for (int i = 0; i < 33; i++) {
        tree.insert(array[i], i);
    }

    std::stringstream ss;
    std::streambuf* old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "      330:31\n"
                        "     320:25\n"
                        "    310:14\n"
                        "     300:24\n"
                        "   290:6\n"
                        "     280:23\n"
                        "    270:13\n"
                        "  260:2\n"
                        "      250:30\n"
                        "     240:22\n"
                        "    230:12\n"
                        "     220:21\n"
                        "   210:5\n"
                        "      200:29\n"
                        "     190:20\n"
                        "    180:11\n"
                        "      170:28\n"
                        "     160:19\n"
                        "       150:32\n"
                        "      140:27\n"
                        " 130:0\n"
                        "     120:18\n"
                        "    110:10\n"
                        "   100:4\n"
                        "    90:9\n"
                        "  80:1\n"
                        "     70:17\n"
                        "    60:8\n"
                        "   50:3\n"
                        "     40:16\n"
                        "    30:7\n"
                        "     20:15\n"
                        "      10:26\n");

    tree.erase(90);

    ss.str("");
    old = std::cout.rdbuf(ss.rdbuf());
    tree.print_tree();
    std::cout.rdbuf(old);

    EXPECT_EQ(ss.str(), "      330:31\n"
                        "     320:25\n"
                        "    310:14\n"
                        "     300:24\n"
                        "   290:6\n"
                        "     280:23\n"
                        "    270:13\n"
                        "  260:2\n"
                        "     250:30\n"
                        "    240:22\n"
                        "   230:12\n"
                        "    220:21\n"
                        " 210:5\n"
                        "     200:29\n"
                        "    190:20\n"
                        "   180:11\n"
                        "     170:28\n"
                        "    160:19\n"
                        "      150:32\n"
                        "     140:27\n"
                        "  130:0\n"
                        "      120:18\n"
                        "     110:10\n"
                        "      100:4\n"
                        "    80:1\n"
                        "      70:17\n"
                        "     60:8\n"
                        "   50:3\n"
                        "     40:16\n"
                        "    30:7\n"
                        "     20:15\n"
                        "      10:26\n");
}
