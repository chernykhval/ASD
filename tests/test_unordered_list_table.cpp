// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_unordered_list_table/unordered_list_table.h"

#define EPSILON 0.000001

TEST(TestUnorderedListTable, insert) {
    UnorderedListTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestUnorderedListTable, insert_exception) {
    UnorderedListTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestUnorderedListTable, erase_true) {
    UnorderedListTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_TRUE(table.erase(1));
    EXPECT_FALSE(table.erase(1));
    EXPECT_EQ(0, table.size());
}

TEST(TestUnorderedListTable, erase_false) {
    UnorderedListTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_FALSE(table.erase(2));
}

TEST(TestUnorderedListTable, find) {
    UnorderedListTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestUnorderedListTable, is_empty_and_clear) {
    UnorderedListTable<int, std::string> table;

    EXPECT_EQ(true, table.is_empty());
    table.insert(1, "hello");
    EXPECT_EQ(false, table.is_empty());
    table.clear();
    EXPECT_EQ(true, table.is_empty());
}

TEST(TestUnorderedListTable, multiple_elements_scenario) {
    UnorderedListTable<int, std::string> table;

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

TEST(TestUnorderedListTable, to_string) {
    UnorderedListTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{1} : {one}\n"
                       "{2} : {two}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}
