// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_SKIP_LIST_SKIP_LIST_H
#define LIBS_LIB_SKIP_LIST_SKIP_LIST_H

#include <utility>
#include <random>
#include <cstdio>
#include <iostream>

#include "libs/lib_list/list.h"

template<typename Key, typename Value>
class SkipList {
 private:
    struct Node {
        std::pair<Key, Value> _pair;
        Node** _next;
        size_t _size;

        explicit Node(const Key&, const Value&,
            Node** next = nullptr, size_t size = 0) noexcept;
        ~Node() noexcept;

        Value& get_value() noexcept;
        Key& get_key() const noexcept;
    };

    List<Node*> _heads;
    size_t _level;
    size_t _size;
    size_t _max_level;

 public:
    explicit  SkipList();
    explicit  SkipList(size_t max_level);
    void insert(const Key&, const Value&);
    void print() const noexcept;

private:
    bool flip_coin() const noexcept;
    size_t calculate_level() const noexcept;
};

template<typename Key, typename Value>
SkipList<Key, Value>::Node::Node(const Key& key, const Value& value,
            Node** next, size_t size)noexcept : _pair(key, value),
            _next(next), _size(size) {
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
Key& SkipList<Key, Value>::Node::get_key() const noexcept {
    return _pair.first;
}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList() : _heads(), _level(0), _max_level(5), _size(0) {
}

template<typename Key, typename Value>
SkipList<Key, Value>::SkipList(size_t max_level) :
_heads(), _level(0), _max_level(max_level), _size(0) {
}

template<typename Key, typename Value>
void SkipList<Key, Value>::insert(const Key& key, const Value& value) {
    size_t level = calculate_level();

    if (level > _level) {
        size_t offset = level - _level;

        for (int i = 0; i < offset; ++i) {
            _heads.push_front(nullptr);
            ++_level;
        }
    }

    Node** next_nodes = new Node*[level];
    Node* new_node = new Node(key, value, next_nodes, level);

    auto head = _heads.begin();

    for (size_t i = 0; i < _level; ++i) {
        Node* current_node = *head;
        Node* prev_node = nullptr;
        size_t current_index = _level - i - 1;

        if (current_node == nullptr) {
            if (current_index < level) {
                new_node->_next[current_index] = nullptr;
                *head = new_node;
            }

            ++head;
            continue;
        }

        if (current_node->get_value() > value) {
            if (current_index < level) {
                new_node->_next[current_index] = *head;
                *head = new_node;
            }

            ++head;
            continue;
        }

       while (true) {
           if (current_node->_next[current_index] != nullptr &&
               current_node->_next[current_index]->get_value() <= value) {
               current_node = current_node->_next[current_index];
               continue;
           }

           if (current_index < level) {
               new_node->_next[current_index] = current_node->_next[current_index];
               current_node->_next[current_index] = new_node;
           }

           if (current_index > 0) {
               --current_index;
               continue;
           }

           break;
       }

        break;
    }

    ++_size;
}

template<typename Key, typename Value>
void SkipList<Key, Value>::print() const noexcept {
    int current_level = _level - 1;

    for (auto head : _heads) {

        std::cout << "[h] ";
        Node* node = head;

        for (int i = 0; i < _size; ++i) {
            if (node == nullptr) {
                std::cout << "[n] ";
            }
            else {
                std::cout << "[" << node->_pair.second << "] ";
                node = node->_next[current_level];
            }
        }

        current_level--;

        std::cout << '\n';
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

#endif  // LIBS_LIB_SKIP_LIST_SKIP_LIST_H
