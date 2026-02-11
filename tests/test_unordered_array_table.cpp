// Copyright 2026 Chernykh Valentin

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_unordered_array_table/unordered_array_table.h"

#define EPSILON 0.000001

TEST(TestUnorderedArrayTable, insert) {
    UnorderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_EQ(1, table.size());
}

TEST(TestUnorderedArrayTable, insert_exception) {
    UnorderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.insert(1, "hello"), std::invalid_argument);
}

TEST(TestUnorderedArrayTable, erase) {
    UnorderedArrayTable<int, std::string> table;

    table.insert(1, "hello");
    table.erase(1);

    EXPECT_EQ(0, table.size());
}

TEST(TestUnorderedArrayTable, erase_exception) {
    UnorderedArrayTable<int, std::string> table;

    table.insert(1, "hello");

    EXPECT_THROW(table.erase(2), std::invalid_argument);
}

TEST(TestUnorderedArrayTable, find) {
    UnorderedArrayTable<int, std::string> table;

    EXPECT_EQ(nullptr, table.find(1));
    table.insert(1, "hello");
    EXPECT_EQ("hello", *table.find(1));
}

TEST(TestUnorderedArrayTable, is_empty_and_clear) {
    UnorderedArrayTable<int, std::string> table;

    EXPECT_EQ(true, table.is_empty());
    table.insert(1, "hello");
    EXPECT_EQ(false, table.is_empty());
    table.clear();
    EXPECT_EQ(true, table.is_empty());
}

TEST(TestUnorderedArrayTable, multiple_elements_scenario) {
    UnorderedArrayTable<int, std::string> table;

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

TEST(TestUnorderedArrayTable, to_string) {
    UnorderedArrayTable<int, std::string> table;

    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    std::string text = "{key} : {value}\n"
                       "{1} : {one}\n"
                       "{2} : {two}\n"
                       "{3} : {three}\n";

    EXPECT_EQ(text, table.to_string());
}