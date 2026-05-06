// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_ADJ_LIST_GRAPH_ADJ_LIST_GRAPH_H_
#define LIBS_LIB_ADJ_LIST_GRAPH_ADJ_LIST_GRAPH_H_

#include <vector>
#include <tuple>

#include "libs/lib_list/list.h"
#include "libs/lib_tvector/tvector.h"

template<typename T>
class AdjListGraph {
 private:
    struct Neighbor {
        T data;
        int weight;

        explicit Neighbor(const T& data, int weight = 0) : data(data), weight(weight) {}
    };

    struct AdjList {
        T vertex;
        List<Neighbor> neighbors;
    };

    bool _is_directed;
    bool _is_weighted;
    TVector<AdjList> _vertices;

 public:
    explicit AdjListGraph(bool is_directed = false, bool is_weighted = true);
    explicit AdjListGraph(std::vector<std::pair<T, T>> edges, bool is_directed = false, bool is_weighted = false);
    explicit AdjListGraph(std::vector<std::tuple<T, T, int>> edges, bool is_directed = false, bool is_weighted = true);
    AdjListGraph(const AdjListGraph& other);

    void add_edge(const T& from_value, const T& to_value, int weight = 0);
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
    void delete_vertex(const T& value);
    bool is_vertex_used(const T& value) const;
    AdjList* get_adj(const T& value);
    const AdjList* get_adj(const T& value) const;
    Neighbor* get_neighbor(List<Neighbor>& neighbors, const T& value);
    const Neighbor* get_neighbor(const List<Neighbor>& neighbors, const T& value) const;
};

template<typename T>
AdjListGraph<T>::AdjListGraph(bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted) {}

template<typename T>
AdjListGraph<T>::AdjListGraph(std::vector<std::pair<T, T>> edges, bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted) {
    for (auto edge : edges) {
        add_edge(edge.first, edge.second);
    }
}

template<typename T>
AdjListGraph<T>::AdjListGraph(std::vector<std::tuple<T, T, int>> edges, bool is_directed, bool is_weighted)
    : _is_directed(is_directed), _is_weighted(is_weighted) {
    for (auto edge : edges) {
        add_edge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
    }
}

template<typename T>
AdjListGraph<T>::AdjListGraph(const AdjListGraph& other)
    : _is_directed(other._is_directed), _is_weighted(other._is_weighted),
    _vertices(other._vertices) {}

template<typename T>
void AdjListGraph<T>::add_edge(const T& from_value, const T& to_value, int weight) {
    if (!has_vertex(from_value)) {
        add_vertex(from_value);
    }

    if (!has_vertex(to_value)) {
        add_vertex(to_value);
    }

    for (auto& adj : _vertices) {
        if (adj.vertex == from_value) {
            Neighbor* existing = get_neighbor(adj.neighbors, to_value);
            if (existing) {
                existing->weight = weight;
            } else {
                adj.neighbors.push_back(Neighbor(to_value, weight));
            }
        }

        if (!_is_directed && from_value != to_value && adj.vertex == to_value) {
            Neighbor* existing = get_neighbor(adj.neighbors, from_value);
            if (existing) {
                existing->weight = weight;
            } else {
                adj.neighbors.push_back(Neighbor(from_value, weight));
            }
        }
    }
}

template<typename T>
void AdjListGraph<T>::delete_edge(const T& from_value, const T& to_value) {
    if (!has_vertex(from_value) || !has_vertex(to_value)) {
        throw std::invalid_argument("AdjListGraph::delete_edge: vertex does not exist");
    }

    AdjList* from_adj = get_adj(from_value);
    for (auto it = from_adj->neighbors.begin(); it != from_adj->neighbors.end(); ++it) {
        if (it->data == to_value) {
            from_adj->neighbors.erase(it);
            break;
        }
    }

    if (!_is_directed && from_value != to_value) {
        AdjList* to_adj = get_adj(to_value);
        for (auto it = to_adj->neighbors.begin(); it != to_adj->neighbors.end(); ++it) {
            if (it->data == from_value) {
                to_adj->neighbors.erase(it);
                break;
            }
        }
    }

    if (!is_vertex_used(to_value)) {
        delete_vertex(to_value);
    }

    if (from_value != to_value && !is_vertex_used(from_value)) {
        delete_vertex(from_value);
    }
}

template<typename T>
size_t AdjListGraph<T>::size() const noexcept {
    return _vertices.size();
}

template<typename T>
bool AdjListGraph<T>::has_edge(const T& from_value, const T& to_value) const {
    const AdjList* adj = get_adj(from_value);
    return adj && get_neighbor(adj->neighbors, to_value) != nullptr;
}

template<typename T>
bool AdjListGraph<T>::has_vertex(const T& value) const {
    return get_adj(value) != nullptr;
}

template<typename T>
int AdjListGraph<T>::get_weight(const T& from_value, const T& to_value) const {
    if (!_is_weighted) {
        return 1;
    }

    const AdjList* adj = get_adj(from_value);
    if (adj) {
        const Neighbor* neighbor = get_neighbor(adj->neighbors, to_value);
        if (neighbor) {
            return neighbor->weight;
        }
    }

    throw std::out_of_range("AdjListGraph::get_weight: edge does not exist");
}

template<typename T>
TVector<T> AdjListGraph<T>::get_vertices() const {
    TVector<T> result;

    for (const auto& adj : _vertices) {
        result.push_back(adj.vertex);
    }

    return result;
}

template<typename T>
TVector<T> AdjListGraph<T>::get_neighbors(const T& value) const {
    const AdjList* adj = get_adj(value);

    if (!adj) {
        throw std::out_of_range("AdjListGraph::get_neighbors: vertex does not exist");
    }

    TVector<T> neighbors;
    for (auto it = adj->neighbors.begin(); it != adj->neighbors.end(); ++it) {
        neighbors.push_back(it->data);
    }

    return neighbors;
}

template<typename T>
bool AdjListGraph<T>::is_weighted() const noexcept {
    return _is_weighted;
}

template<typename T>
bool AdjListGraph<T>::is_directed() const noexcept {
    return _is_directed;
}

template<typename T>
void AdjListGraph<T>::add_vertex(const T& value) {
    AdjList adj;
    adj.vertex = value;
    _vertices.push_back(adj);
}

template<typename T>
void AdjListGraph<T>::delete_vertex(const T& value) {
    for (auto it = _vertices.begin(); it != _vertices.end(); ++it) {
        if (it->vertex == value) {
            _vertices.erase(it);
            return;
        }
    }
}

template<typename T>
bool AdjListGraph<T>::is_vertex_used(const T& value) const {
    for (const auto& adj : _vertices) {
        if (adj.vertex == value) {
            if (!adj.neighbors.is_empty()) {
                return true;
            }
        } else if (_is_directed) {
            for (auto it = adj.neighbors.begin(); it != adj.neighbors.end(); ++it) {
                if (it->data == value) {
                    return true;
                }
            }
        }
    }

    return false;
}

template<typename T>
typename AdjListGraph<T>::AdjList* AdjListGraph<T>::get_adj(const T& value) {
    for (auto& adj : _vertices) {
        if (adj.vertex == value) {
            return &adj;
        }
    }

    return nullptr;
}

template<typename T>
const typename AdjListGraph<T>::AdjList* AdjListGraph<T>::get_adj(const T& value) const {
    for (const auto& adj : _vertices) {
        if (adj.vertex == value) {
            return &adj;
        }
    }

    return nullptr;
}

template<typename T>
typename AdjListGraph<T>::Neighbor* AdjListGraph<T>::get_neighbor(List<Neighbor>& neighbors, const T& value) {
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        if (it->data == value) {
            return &(*it);
        }
    }

    return nullptr;
}

template<typename T>
const typename AdjListGraph<T>::Neighbor* AdjListGraph<T>::get_neighbor(const List<Neighbor>& neighbors, const T& value) const {
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        if (it->data == value) {
            return &(*it);
        }
    }

    return nullptr;
}

#endif  // LIBS_LIB_ADJ_LIST_GRAPH_ADJ_LIST_GRAPH_H_
