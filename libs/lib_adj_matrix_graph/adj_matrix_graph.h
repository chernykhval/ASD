// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_
#define LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_

#include <climits>
#include <vector>
#include <tuple>

#include  "libs/lib_matrix/matrix.h"
#include "libs/lib_tvector/tvector.h"

#define NULL_EDGE INT_MAX

template<typename T>
class AdjMatrixGraph {
 private:
    bool _is_directed;
    bool _is_weighted;
    Matrix<int> _adj_matrix;
    TVector<T> _vertices;

 public:
    explicit AdjMatrixGraph(size_t vertex_count = 0, bool is_directed = false, bool is_weighted = true);
    explicit AdjMatrixGraph(std::vector<std::pair<T, T>> edges, bool is_directed = false, bool is_weighted = false);
    explicit AdjMatrixGraph(std::vector<std::tuple<T, T, int>> edges, bool is_directed = false, bool is_weighted = true);
    AdjMatrixGraph(const AdjMatrixGraph& other);

    void add_edge(const T& from_value, const T& to_value,  int weight = 0);
    void delete_edge(const T& from_value, const T& to_value);
    size_t size() const noexcept;
    bool has_edge(const T& from_value, const T& to_value) const;
    bool has_vertex(const T& value) const;
    int get_weight(const T& from_value, const T& to_value) const;
    TVector<T> get_vertices() const;
    TVector<T> get_neighbors(const T& value) const;
    bool is_weighted() const noexcept;
    bool is_directed() const noexcept;

 private:
    void add_vertex(const T& value);
    void delete_vertex(size_t index);
    bool is_vertex_used(size_t index) const;
    size_t get_vertex_index(const T& value) const;
};

template<typename T>
AdjMatrixGraph<T>::AdjMatrixGraph(size_t vertex_count, bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted),
    _adj_matrix(vertex_count, vertex_count), _vertices(vertex_count) {
    for (size_t i = 0; i < vertex_count; i++) {
        for (size_t j = 0; j < vertex_count; j++) {
            _adj_matrix[i][j] = NULL_EDGE;
        }
    }
}

template<typename T>
AdjMatrixGraph<T>::AdjMatrixGraph(std::vector<std::pair<T, T>> edges, bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted), _adj_matrix(), _vertices() {
    for (auto edge : edges) {
        add_edge(edge.first, edge.second);
    }
}

template<typename T>
AdjMatrixGraph<T>::AdjMatrixGraph(std::vector<std::tuple<T, T, int>> edges, bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted), _adj_matrix(), _vertices() {
    for (auto edge : edges) {
        add_edge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
    }
}

template<typename T>
AdjMatrixGraph<T>::AdjMatrixGraph(const AdjMatrixGraph& other)
    : _is_directed(other._is_directed), _is_weighted(other._is_weighted),
    _adj_matrix(other._adj_matrix), _vertices(other._vertices) {}

template<typename T>
void AdjMatrixGraph<T>::add_edge(const T& from_value, const T& to_value,  int weight) {
    if (weight == NULL_EDGE) {
        throw std::invalid_argument("AdjMatrixGraph::add_edge: MAX_INT weight is reserved");
    }

    if (!has_vertex(from_value)) {
        add_vertex(from_value);
    }

    if (!has_vertex(to_value)) {
        add_vertex(to_value);
    }

    size_t from_index = get_vertex_index(from_value);
    size_t to_index = get_vertex_index(to_value);

    _adj_matrix[from_index][to_index] = weight;

    if (!_is_directed && from_index != to_index) {
        _adj_matrix[to_index][from_index] = weight;
    }
}

template<typename T>
void AdjMatrixGraph<T>::delete_edge(const T& from_value, const T& to_value) {
    if (!has_vertex(from_value) || !has_vertex(to_value)) {
        throw std::invalid_argument("AdjMatrixGraph::delete_edge: vertex does not exist");
    }

    size_t from_index = get_vertex_index(from_value);
    size_t to_index = get_vertex_index(to_value);

    _adj_matrix[from_index][to_index] = NULL_EDGE;

    if (!_is_directed) {
        _adj_matrix[to_index][from_index] = NULL_EDGE;
    }

    size_t greater_index = from_index > to_index ? from_index : to_index;
    size_t least_index = from_index <= to_index ? from_index : to_index;

    if (!is_vertex_used(greater_index)) {
        delete_vertex(greater_index);
    }

    if (greater_index != least_index && !is_vertex_used(least_index)) {
        delete_vertex(least_index);
    }
}

template<typename T>
size_t AdjMatrixGraph<T>::size() const noexcept {
    return _vertices.size();
}

template<typename T>
bool AdjMatrixGraph<T>::has_edge(const T& from_value, const T& to_value) const {
    if (!has_vertex(from_value) || !has_vertex(to_value)) {
        return false;
    }

    size_t from_index = get_vertex_index(from_value);
    size_t to_index = get_vertex_index(to_value);

    return _adj_matrix[from_index][to_index] != NULL_EDGE;
}

template<typename T>
bool AdjMatrixGraph<T>::has_vertex(const T& value) const {
    for (size_t i = 0; i < _vertices.size(); i++) {
        if (_vertices[i] == value) {
            return true;
        }
    }

    return false;
}

template<typename T>
int AdjMatrixGraph<T>::get_weight(const T& from_value, const T& to_value) const {
    if (!_is_weighted) {
        return 1;
    }

    size_t from_index = get_vertex_index(from_value);
    size_t to_index = get_vertex_index(to_value);

    return _adj_matrix[from_index][to_index];
}

template<typename T>
TVector<T> AdjMatrixGraph<T>::get_vertices() const {
    return _vertices;
}

template<typename T>
TVector<T> AdjMatrixGraph<T>::get_neighbors(const T& value) const {
    size_t index = get_vertex_index(value);
    TVector<T> neighbors;

    for (size_t i = 0; i < _vertices.size(); i++) {
        if (_adj_matrix[index][i] != NULL_EDGE) {
            neighbors.push_back(_vertices[i]);
        }
    }

    return neighbors;
}

template<typename T>
bool AdjMatrixGraph<T>::is_weighted() const noexcept {
    return _is_weighted;
}

template<typename T>
bool AdjMatrixGraph<T>::is_directed() const noexcept {
    return _is_directed;
}

template<typename T>
void AdjMatrixGraph<T>::add_vertex(const T& value) {
    size_t old_size = _vertices.size();
    _vertices.push_back(value);
    Matrix<int> new_matrix(_vertices.size(), _vertices.size());

    for (size_t i = 0; i < _vertices.size(); i++) {
        for (size_t j = 0; j < _vertices.size(); j++) {
            if (i == old_size || j == old_size) {
                new_matrix[i][j] = NULL_EDGE;
            } else {
                new_matrix[i][j] = _adj_matrix[i][j];
            }
        }
    }

    _adj_matrix = new_matrix;
}

template<typename T>
void AdjMatrixGraph<T>::delete_vertex(size_t index) {
    _vertices.erase(_vertices.begin() + index);
    Matrix<int> new_matrix(_vertices.size(), _vertices.size());

    for (size_t i = 0; i < _vertices.size(); i++) {
        for (size_t j = 0; j < _vertices.size(); j++) {
            if (i < index && j < index) {
                new_matrix[i][j] = _adj_matrix[i][j];
            } else if (i < index && j >= index) {
                new_matrix[i][j] = _adj_matrix[i][j+1];
            } else if (i >= index && j < index) {
                new_matrix[i][j] = _adj_matrix[i+1][j];
            } else {
                new_matrix[i][j] = _adj_matrix[i+1][j+1];
            }
        }
    }

    _adj_matrix = new_matrix;
}

template<typename T>
bool AdjMatrixGraph<T>::is_vertex_used(size_t index) const {
    for (size_t i = 0; i < _vertices.size(); i++) {
        if (_adj_matrix[i][index] != NULL_EDGE
            || _adj_matrix[index][i] != NULL_EDGE) {
            return true;
        }
    }

    return false;
}

template<typename T>
size_t AdjMatrixGraph<T>::get_vertex_index(const T& value) const {
    for (size_t i = 0; i < _vertices.size(); i++) {
        if (_vertices[i] == value) {
            return i;
        }
    }

    throw std::out_of_range("AdjMatrixGraph::get_vertex_index: vertex does not exist");
}

#endif  // LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_
