// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_
#define LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_

#include <climits>

#include  "libs/lib_matrix/matrix.h"

#define NULL_EDGE INT_MAX

template<typename T>
class AdjMatrixGraph {
 private:
    struct Vertex {
        T data;
        size_t index;
    };

    bool _is_directed;
    bool _is_weighted;
    Matrix<int> _adj_matrix;
    TVector<T> _vertices;

 public:
    explicit AdjMatrixGraph(bool is_directed = false,
        bool is_weighted = false, size_t vertex_count = 0);

    void add_edge(const T& from_value, const T& to_value,  int weight);
    void delete_edge(const T& from_value, const T& to_value);

 private:
    void add_vertex(const T& value);
    void delete_vertex(size_t index);
    bool is_vertex_used(size_t index);
};

template<typename T>
AdjMatrixGraph<T>::AdjMatrixGraph(bool is_directed, bool is_weighted,
    size_t vertex_count) : _is_directed(is_directed), _is_weighted(is_weighted),
_adj_matrix(vertex_count, vertex_count), _vertices(vertex_count) {
    for (size_t i = 0; i < vertex_count; i++) {
        for (size_t j = 0; j < vertex_count; j++) {
            _adj_matrix[i][j] = NULL_EDGE;
        }
    }
}

template<typename T>
void AdjMatrixGraph<T>::add_edge(const T& from_value, const T& to_value,  int weight) {
    size_t old_size = _vertices.size();
    size_t from_index = old_size, to_index = old_size;

    for (size_t i = 0; i < old_size; i++) {
        if (_vertices[i] == from_value) {
            from_index = i;
        }
        if (_vertices[i] == to_value) {
            to_index = i;
        }
    }

    if (from_index == old_size) {
        add_vertex(from_value);
        from_index = _vertices.size() - 1;
    }

    if (to_index == old_size) {
        add_vertex(to_value);
        to_index = _vertices.size() - 1;
    }

    _adj_matrix[from_index][to_index] = weight;
}

template<typename T>
void AdjMatrixGraph<T>::delete_edge(const T& from_value, const T& to_value) {
    size_t old_size = _vertices.size();
    size_t from_index = old_size, to_index = old_size;

    for (size_t i = 0; i < old_size; i++) {
        if (_vertices[i] == from_value) {
            from_index = i;
        }
        if (_vertices[i] == to_value) {
            to_index = i;
        }
    }

    if (from_index == old_size || to_index == old_size) {
        throw std::out_of_range("AdjMatrixGraph::delete_edge : Invalid edge, vertex does not exist");
    }

    _adj_matrix[from_index][to_index] = NULL_EDGE;

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
void AdjMatrixGraph<T>::add_vertex(const T& value) {
    size_t old_size = _vertices.size();
    _vertices.push_back(value);
    Matrix<int> new_matrix(_vertices.size(), _vertices.size());

    for (int i = 0; i < _vertices.size(); i++) {
        for (int j = 0; j < _vertices.size(); j++) {
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
    size_t old_size = _vertices.size();
    _vertices.erase(_vertices.begin() + index);
    Matrix<int> new_matrix(_vertices.size(), _vertices.size());

    for (int i = 0; i < _vertices.size(); i++) {
        for (int j = 0; j < _vertices.size(); j++) {
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
bool AdjMatrixGraph<T>::is_vertex_used(size_t index) {
    for (size_t i = 0; i < _vertices.size(); i++) {
        if (_adj_matrix[i][index] != NULL_EDGE
            || _adj_matrix[index][i] != NULL_EDGE) {
            return true;
        }
    }

    return false;
}

#endif  // LIBS_LIB_ADJ_MATRIX_GRAPH_ADJ_MATRIX_GRAPH_H_
