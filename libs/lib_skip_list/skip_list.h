// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_SKIP_LIST_SKIP_LIST_H_
#define LIBS_LIB_SKIP_LIST_SKIP_LIST_H_

#include <utility>
#include <random>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "libs/lib_list/list.h"
#include "libs/lib_matrix/matrix.h"

template<typename Key, typename Value>
class SkipList {
 private:
    struct Node {
        std::pair<Key, Value> _pair;
        Node** _next;
        size_t _size;

        Node(const Key&, const Value&,
            Node** next = nullptr, size_t size = 0) noexcept;
        Node(const Key&, const Value&, size_t size = 0) noexcept;
        ~Node() noexcept;

        Value& get_value() noexcept;
        const Key& get_key() const noexcept;
    };

    List<Node*> _heads;
    size_t _level;
    size_t _size;
    size_t _max_level;

 public:
    SkipList();
    explicit SkipList(size_t max_level);
    void insert(const Key&, const Value&);
    bool contains(const Key& key) const;
    void print() const noexcept;

 private:
    bool flip_coin() const noexcept;
    size_t calculate_level() const noexcept;
};

template<typename Key, typename Value>
SkipList<Key, Value>::Node::Node(const Key& key, const Value& value,
            Node** next, size_t size) noexcept : _pair(key, value),
            _next(next), _size(size) {
}

template<typename Key, typename Value>
SkipList<Key, Value>::Node::Node(const Key& key, const Value& value,
size_t size) noexcept : _pair(key, value), _size(size) {
    if (size == 0) {
        _next = nullptr;
    } else {
        _next = new Node*[size];
    }
}

template<typename Key, typename Value>
SkipList<Key, Value>::Node::~Node() noexcept {
    delete[] _next;
}

template<typename Key, typename Value>
Value& SkipList<Key, Value>::Node::get_value() noexcept {
    return _pair.second;
}

template<typename Key, typename Value>
const Key& SkipList<Key, Value>::Node::get_key() const noexcept {
    return _pair.first;
}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList() : _heads(), _level(0),
_max_level(5), _size(0) {
}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList(size_t max_level) :
_heads(), _level(0), _max_level(max_level), _size(0) {
}

template<typename Key, typename Value>
void SkipList<Key, Value>::insert(const Key& key, const Value& value) {
    if (contains(key)) {
        throw std::invalid_argument("Key already exists");
    }

    size_t level = calculate_level();

    if (level > _level) {
        size_t offset = level - _level;

        for (int i = 0; i < offset; ++i) {
            _heads.push_front(nullptr);
            ++_level;
        }
    }

    Node* new_node = new Node(key, value, level);

    auto head_it = _heads.begin();
    Node* current_node = nullptr;

    for (int current_index = _level - 1; current_index >= 0;
        --current_index, ++head_it) {
        if (current_node == nullptr) {
            if (*head_it == nullptr || (*head_it)->get_key() > key) {
                if (current_index < level) {
                    new_node->_next[current_index] = *head_it;
                    *head_it = new_node;
                }

                continue;
            }

            current_node = *head_it;
        }

        while (current_node->_next[current_index] != nullptr &&
            current_node->_next[current_index]->get_key() <= key) {
            current_node = current_node->_next[current_index];
        }

        if (current_index < level) {
            new_node->_next[current_index] = current_node->_next[current_index];
            current_node->_next[current_index] = new_node;
        }
    }

    ++_size;
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::contains(const Key& key) const {
    auto head_it = _heads.begin();
    Node* current_node = nullptr;

    for (int current_index = _level - 1; current_index >= 0;
        --current_index, ++head_it) {
        if (current_node == nullptr) {
            if (*head_it == nullptr || (*head_it)->get_key() > key) {
                continue;
            }

            if ((*head_it)->get_key() == key) {
                return true;
            }

            current_node = *head_it;
        }

        while (current_node->_next[current_index] != nullptr &&
            current_node->_next[current_index]->get_key() <= key) {
            current_node = current_node->_next[current_index];

            if (current_node->get_key() == key) {
                return true;
            }
        }
    }

    return false;
}

template<typename Key, typename Value>
void SkipList<Key, Value>::print() const noexcept {
    TVector<Node*> nodes;
    int index = 0;

    for (auto head : _heads) {
        nodes.push_back(head);
        ++index;
    }

    for (int i = 0; i < _level; ++i) {
        size_t current_index = _level - i - 1;
        std::stringstream ss;
        std::stringstream buffer;
        ss << "[head_" << current_index + 1 << "]";
        Node* last_row_element = nodes[_level - 1];
        Node* current_row_element = nodes[i];

        for (int j = 0; j < _size; ++j) {
            if (last_row_element == current_row_element) {
                ss << "->[" << current_row_element->get_key() << ":"
                << current_row_element->get_value() << "]";
                current_row_element = current_row_element->_next[current_index];
            } else {
                buffer << "->[" << last_row_element->get_key() << ":"
                << last_row_element->get_value() << "]";
                ss << std::string(buffer.str().length(), '-');
                buffer.str("");
                buffer.clear();
            }

            last_row_element = last_row_element->_next[0];
        }

        ss << "->[null]" << std::endl;
        std::cout << ss.str();
    }
}

template<typename Key, typename Value>
bool SkipList<Key, Value>::flip_coin() const noexcept {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::bernoulli_distribution d(0.5);

    return d(gen);
}

template<typename Key, typename Value>
size_t SkipList<Key, Value>::calculate_level() const noexcept {
    size_t level = 1;

    while ((_max_level == 0 || level < _max_level) && flip_coin()) {
        ++level;
    }

    return level;
}

#endif  // LIBS_LIB_SKIP_LIST_SKIP_LIST_H_
