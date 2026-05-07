// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_bstree_table/bstree_table.h"
#include "libs/lib_tvector/tvector.h"

TEST(TestBSTreeTable, insert) {
    BSTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestBSTreeTable, insert_exception) {
    BSTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestBSTreeTable, erase_true) {
    BSTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestBSTreeTable, erase_false) {
    BSTreeTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_FALSE(table.erase(2));
}

TEST(TestBSTreeTable, find) {
    BSTreeTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestBSTreeTable, is_empty_and_clear) {
    BSTreeTable<int, std::string> table;

    EXPECT_TRUE(table.is_empty());
    table.insert(1, "hello");
    EXPECT_FALSE(table.is_empty());
    table.clear();
    EXPECT_TRUE(table.is_empty());
}

TEST(TestBSTreeTable, multiple_elements_scenario) {
    BSTreeTable<int, std::string> table;

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

TEST(TestBSTreeTable, to_string) {
    BSTreeTable<int, std::string> table;

    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{2} : {two}\n"
                       "{1} : {one}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}

TEST(TestBSTreeTable, ToStringForEmptyTable) {
    BSTreeTable<int, std::string> table;

    EXPECT_EQ("Table is empty\n", table.to_string());
}

TEST(TestBSTreeTable, contains) {
    BSTreeTable<int, std::string> table;

    table.insert(1, "one");

    EXPECT_TRUE(table.contains(1));

    table.erase(1);

    EXPECT_FALSE(table.contains(1));
}

TEST(TestBSTreeTable, get_keys) {
    BSTreeTable<int, std::string> table;

    table.insert(2, "two");
    table.insert(1, "one");
    table.insert(3, "three");

    TVector<int> keys = table.get_keys();

    EXPECT_EQ(3, keys.size());
    EXPECT_EQ(2, keys[0]);
    EXPECT_EQ(1, keys[1]);
    EXPECT_EQ(3, keys[2]);
}
