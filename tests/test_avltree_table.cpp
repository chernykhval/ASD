// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_avltree_table/avltree_table.h"
#include "libs/lib_tvector/tvector.h"

TEST(TestAVLTreeTable, insert) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestAVLTreeTable, insert_exception) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestAVLTreeTable, erase_true) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestAVLTreeTable, erase_false) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_FALSE(table.erase(2));
}

TEST(TestAVLTreeTable, find) {
    AVLTreeTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestAVLTreeTable, is_empty_and_clear) {
    AVLTreeTable<int, std::string> table;

    EXPECT_TRUE(table.is_empty());
    table.insert(1, "hello");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestAVLTreeTable, multiple_elements_scenario) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(3, table.size());

    EXPECT_EQ("one", *table.find(1));
    EXPECT_EQ("two", *table.find(2));
    EXPECT_EQ("three", *table.find(3));

    table.erase(2);

    EXPECT_EQ(2, table.size());
    EXPECT_EQ(nullptr, table.find(2));
    EXPECT_EQ("one", *table.find(1));
    EXPECT_EQ("three", *table.find(3));
}

TEST(TestAVLTreeTable, to_string) {
    AVLTreeTable<int, std::string> table;

    // вставка 2,1,3 — корень 2, дети 1 и 3, ротаций нет
    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{2} : {two}\n"
                       "{1} : {one}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}

TEST(TestAVLTreeTable, ToStringForEmptyTable) {
    AVLTreeTable<int, std::string> table;

    EXPECT_EQ("Table is empty\n", table.to_string());
}

TEST(TestAVLTreeTable, contains) {
    AVLTreeTable<int, std::string> table;

    table.insert(1, "one");

    EXPECT_TRUE(table.contains(1));

    table.erase(1);

    EXPECT_FALSE(table.contains(1));
}

TEST(TestAVLTreeTable, get_keys) {
    AVLTreeTable<int, std::string> table;

    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");

    TVector<int> keys = table.get_keys();

    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(2, keys[0]);
    EXPECT_EQ(1, keys[1]);
    EXPECT_EQ(3, keys[2]);
}

// AVL-специфичный: вставка в отсортированном порядке вызывает ротации,
// но find должен находить все элементы
TEST(TestAVLTreeTable, FindAfterRotations) {
    AVLTreeTable<int, std::string> table;

    // вставка 1,2,3 вызывает RR-ротацию, 2 становится корнем
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ("one",   *table.find(1));
    EXPECT_EQ("two",   *table.find(2));
    EXPECT_EQ("three", *table.find(3));
}

// AVL-специфичный: get_keys после ротации возвращает BFS-порядок
// сбалансированного дерева, не порядок вставки
TEST(TestAVLTreeTable, GetKeysAfterRotation) {
    AVLTreeTable<int, std::string> table;

    // вставка 1,2,3 → RR-ротация → корень=2, левый=1, правый=3
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    TVector<int> keys = table.get_keys();

    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(2, keys[0]);
    EXPECT_EQ(1, keys[1]);
    EXPECT_EQ(3, keys[2]);
}
