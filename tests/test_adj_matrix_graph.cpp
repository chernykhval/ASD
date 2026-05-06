// Copyright 2026 Chernykh Valentin

#define EPSILON 0.000001

#include <gtest/gtest.h>
#include <string>
#include "libs/lib_adj_matrix_graph/adj_matrix_graph.h"

TEST(TestAdjMatrixGraph, init) {
    AdjMatrixGraph<std::string> graph(0, false);

    graph.add_edge("first", "second");

    EXPECT_TRUE(graph.is_weighted());
    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_edge("first", "second"));
    EXPECT_TRUE(graph.has_edge("second", "first"));
    EXPECT_EQ(graph.get_weight("first", "second"), 0);
}

TEST(TestAdjMatrixGraph, pairs_init) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}, {"first", "third"}}, false);

    EXPECT_FALSE(graph.is_weighted());
    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_vertex("third"));
    EXPECT_TRUE(graph.has_edge("first", "second"));
    EXPECT_TRUE(graph.has_edge("second", "first"));
    EXPECT_TRUE(graph.has_edge("first", "third"));
    EXPECT_TRUE(graph.has_edge("third", "first"));
    EXPECT_EQ(graph.get_weight("first", "second"), 1);
    EXPECT_EQ(graph.get_weight("first", "third"), 1);
}

TEST(TestAdjMatrixGraph, pairs_init_directed) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}, {"first", "third"}}, true);

    EXPECT_FALSE(graph.is_weighted());
    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_vertex("third"));
    EXPECT_TRUE(graph.has_edge("first", "second"));
    EXPECT_FALSE(graph.has_edge("second", "first"));
    EXPECT_TRUE(graph.has_edge("first", "third"));
    EXPECT_FALSE(graph.has_edge("third", "first"));
    EXPECT_EQ(graph.get_weight("first", "second"), 1);
    EXPECT_EQ(graph.get_weight("first", "third"), 1);
}

TEST(TestAdjMatrixGraph, tuples_init) {
    AdjMatrixGraph<std::string> graph({{"first", "second", 12}, {"first", "third", 22}}, false);

    EXPECT_TRUE(graph.is_weighted());

    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_vertex("third"));
    EXPECT_TRUE(graph.has_edge("first", "second"));
    EXPECT_TRUE(graph.has_edge("second", "first"));
    EXPECT_TRUE(graph.has_edge("first", "third"));
    EXPECT_TRUE(graph.has_edge("third", "first"));
    EXPECT_EQ(graph.get_weight("first", "second"), 12);
    EXPECT_EQ(graph.get_weight("second", "first"), 12);
    EXPECT_EQ(graph.get_weight("first", "third"), 22);
    EXPECT_EQ(graph.get_weight("third", "first"), 22);
}

TEST(TestAdjMatrixGraph, size) {
    AdjMatrixGraph<std::string> graph(0, false);
    EXPECT_EQ(graph.size(), 0);

    graph.add_edge("a", "b");
    EXPECT_EQ(graph.size(), 2);

    graph.add_edge("a", "c");
    EXPECT_EQ(graph.size(), 3);

    graph.delete_edge("a", "b");
    EXPECT_EQ(graph.size(), 2);
}

TEST(TestAdjMatrixGraph, has_edge_missing_vertex) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}}, false);

    EXPECT_FALSE(graph.has_edge("first", "nonexistent"));
    EXPECT_FALSE(graph.has_edge("nonexistent", "first"));
    EXPECT_FALSE(graph.has_edge("nonexistent", "other"));
}

TEST(TestAdjMatrixGraph, delete_edge) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}, {"first", "third"}}, false);

    graph.delete_edge("first", "second");

    EXPECT_FALSE(graph.has_edge("first", "second"));
    EXPECT_FALSE(graph.has_edge("second", "first"));
    EXPECT_FALSE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_edge("first", "third"));
}

TEST(TestAdjMatrixGraph, delete_edge_directed) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}, {"third", "second"}}, true);

    graph.delete_edge("first", "second");

    EXPECT_FALSE(graph.has_edge("first", "second"));
    EXPECT_FALSE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_edge("third", "second"));
}

TEST(TestAdjMatrixGraph, delete_edge_removes_both_vertices) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}}, false);

    graph.delete_edge("first", "second");

    EXPECT_FALSE(graph.has_vertex("first"));
    EXPECT_FALSE(graph.has_vertex("second"));
    EXPECT_EQ(graph.size(), 0);
}

TEST(TestAdjMatrixGraph, delete_edge_reversed_index_order) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("a", "b");

    graph.delete_edge("b", "a");

    EXPECT_FALSE(graph.has_vertex("a"));
    EXPECT_FALSE(graph.has_vertex("b"));
    EXPECT_EQ(graph.size(), 0);
}

TEST(TestAdjMatrixGraph, delete_edge_throws_on_missing_vertex) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}}, false);

    EXPECT_THROW(graph.delete_edge("first", "nonexistent"), std::invalid_argument);
    EXPECT_THROW(graph.delete_edge("nonexistent", "first"), std::invalid_argument);
}

TEST(TestAdjMatrixGraph, get_neighbors_undirected) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("a", "b");
    graph.add_edge("a", "c");

    TVector<std::string> neighbors = graph.get_neighbors("a");
    EXPECT_EQ(neighbors.size(), 2);
    EXPECT_EQ(neighbors[0], "b");
    EXPECT_EQ(neighbors[1], "c");

    TVector<std::string> b_neighbors = graph.get_neighbors("b");
    EXPECT_EQ(b_neighbors.size(), 1);
    EXPECT_EQ(b_neighbors[0], "a");
}

TEST(TestAdjMatrixGraph, get_neighbors_directed) {
    AdjMatrixGraph<std::string> graph({{"a", "b"}, {"a", "c"}}, true);

    TVector<std::string> a_neighbors = graph.get_neighbors("a");
    EXPECT_EQ(a_neighbors.size(), 2);

    TVector<std::string> b_neighbors = graph.get_neighbors("b");
    EXPECT_EQ(b_neighbors.size(), 0);
}

TEST(TestAdjMatrixGraph, is_directed) {
    AdjMatrixGraph<std::string> undirected({{"a", "b"}}, false);
    AdjMatrixGraph<std::string> directed({{"a", "b"}}, true);

    EXPECT_FALSE(undirected.is_directed());
    EXPECT_TRUE(directed.is_directed());
}

TEST(TestAdjMatrixGraph, get_vertices) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("a", "b");
    graph.add_edge("a", "c");

    TVector<std::string> vertices = graph.get_vertices();
    EXPECT_EQ(vertices.size(), 3);
}

TEST(TestAdjMatrixGraph, self_loop) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("first", "first");

    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_edge("first", "first"));
    EXPECT_EQ(graph.size(), 1);
}

TEST(TestAdjMatrixGraph, self_loops_isolated_vertices) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("first", "first");
    graph.add_edge("second", "second");

    EXPECT_EQ(graph.size(), 2);
    EXPECT_TRUE(graph.has_vertex("first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_TRUE(graph.has_edge("first", "first"));
    EXPECT_TRUE(graph.has_edge("second", "second"));
    EXPECT_FALSE(graph.has_edge("first", "second"));
    EXPECT_FALSE(graph.has_edge("second", "first"));
}

TEST(TestAdjMatrixGraph, delete_self_loop) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("first", "first");
    graph.add_edge("second", "second");

    graph.delete_edge("first", "first");

    EXPECT_FALSE(graph.has_vertex("first"));
    EXPECT_FALSE(graph.has_edge("first", "first"));
    EXPECT_TRUE(graph.has_vertex("second"));
    EXPECT_EQ(graph.size(), 1);
}

TEST(TestAdjMatrixGraph, add_edge_overwrites_weight) {
    AdjMatrixGraph<std::string> graph(0, false);
    graph.add_edge("a", "b", 5);
    graph.add_edge("a", "b", 10);

    EXPECT_EQ(graph.get_weight("a", "b"), 10);
    EXPECT_EQ(graph.get_weight("b", "a"), 10);
    EXPECT_EQ(graph.size(), 2);
}

TEST(TestAdjMatrixGraph, add_edge_reserved_weight_throws) {
    AdjMatrixGraph<std::string> graph(0, false);

    EXPECT_THROW(graph.add_edge("a", "b", INT_MAX), std::invalid_argument);
}

TEST(TestAdjMatrixGraph, vertex_count_constructor) {
    AdjMatrixGraph<int> graph(3, false);

    EXPECT_EQ(graph.size(), 3);
    EXPECT_FALSE(graph.is_directed());
    EXPECT_TRUE(graph.is_weighted());
}

TEST(TestAdjMatrixGraph, delete_edge_no_edge_is_noop) {
    AdjMatrixGraph<std::string> graph({{"a", "b"}, {"a", "c"}}, false);

    graph.delete_edge("b", "c");

    EXPECT_TRUE(graph.has_vertex("b"));
    EXPECT_TRUE(graph.has_vertex("c"));
    EXPECT_TRUE(graph.has_edge("a", "b"));
    EXPECT_TRUE(graph.has_edge("a", "c"));
}

TEST(TestAdjMatrixGraph, get_weight_no_edge_returns_null_edge) {
    AdjMatrixGraph<std::string> graph({{"a", "b", 5}, {"a", "c", 3}}, false);

    EXPECT_EQ(graph.get_weight("b", "c"), NULL_EDGE);
}

TEST(TestAdjMatrixGraph, get_weight_missing_vertex_throws) {
    AdjMatrixGraph<std::string> graph({{"first", "second", 5}}, false);

    EXPECT_THROW(graph.get_weight("first", "nonexistent"), std::out_of_range);
    EXPECT_THROW(graph.get_weight("nonexistent", "first"), std::out_of_range);
}

TEST(TestAdjMatrixGraph, get_neighbors_missing_vertex_throws) {
    AdjMatrixGraph<std::string> graph({{"first", "second"}}, false);

    EXPECT_THROW(graph.get_neighbors("nonexistent"), std::out_of_range);
}

TEST(TestAdjMatrixGraph, copy_constructor) {
    AdjMatrixGraph<std::string> graph({{"first", "second", 5}}, false);
    AdjMatrixGraph<std::string> copy(graph);

    EXPECT_EQ(copy.is_weighted(), graph.is_weighted());
    EXPECT_TRUE(copy.has_vertex("first"));
    EXPECT_TRUE(copy.has_vertex("second"));
    EXPECT_TRUE(copy.has_edge("first", "second"));
    EXPECT_EQ(copy.get_weight("first", "second"), 5);

    copy.add_edge("first", "third");
    EXPECT_FALSE(graph.has_vertex("third"));
}
