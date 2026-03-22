// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_BTREE_BTREE_H_
#define LIBS_LIB_BTREE_BTREE_H_

#include <iostream>

#include "libs/lib_queue/queue.h"

template<typename Key, typename Value>
class BTree {
 private:
    struct Node {
        Key key;
        Value value;
        Node *left, *right;

        Node(const Key& k, const Value& v,
            Node* l = nullptr, Node* r = nullptr);
    };

    Node* _root;
    size_t _size;

 public:
    BTree();
    ~BTree();

    void insert(const Key& key, const Value& value);
    Value* find(const Key& key) const;
    void erase(const Key& key);
    void clear();
    bool is_empty() const;

    void print_w() const;
    void print_dlcr() const;
    void print_dlrc() const;
    void print_dclr() const;
    void print_tree() const;

 private:
    void print_dlcr_rec(Node* node, bool& first) const;
    void print_dlrc_rec(Node* node, bool& first) const;
    void print_dclr_rec(Node* node, bool& first) const;
    void clear_rec(Node* node);
};

template<typename Key, typename Value>
BTree<Key, Value>::Node::Node(const Key& k, const Value& v, Node* l, Node* r)
    : key(k), value(v), left(l), right(r) {
}

template<typename Key, typename Value>
BTree<Key, Value>::BTree() : _root(nullptr), _size(0) {
}

template<typename Key, typename Value>
BTree<Key, Value>::~BTree() {
    clear();
}

template<typename Key, typename Value>
void BTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* node = new Node(key, value);

    if (is_empty()) {
        _root = node;
        _size++;
        return;
    }

    if (_root->key == key) {
        delete node;
        throw std::invalid_argument("BTree::insert: key already exist");
    }

    Node* current = nullptr;
    Queue<Node*> queue((_size + 1) / 2);
    queue.enqueue(_root);

    while (!queue.is_empty()) {
        current = queue.front();
        queue.dequeue();

        if ((current->left && current->left->key == key) ||
            (current->right && current->right->key == key)) {
            delete node;
            throw std::invalid_argument("BTree::insert: key already exist");
        }

        if (!current->left) {
            current->left = node;
            _size++;
            return;
        }

        if (!current->right) {
            current->right = node;
            _size++;
            return;
        }

        queue.enqueue(current->left);
        queue.enqueue(current->right);
    }
}

template<typename Key, typename Value>
Value* BTree<Key, Value>::find(const Key& key) const {
    if (is_empty()) {
        return nullptr;
    }

    Node* current = nullptr;
    Queue<Node*> queue((_size + 1) / 2);
    queue.enqueue(_root);

    while (!queue.is_empty()) {
        current = queue.front();
        queue.dequeue();

        if (current->key == key) {
            return &current->value;
        }

        if (current->left) {
            queue.enqueue(current->left);
        }

        if (current->right) {
            queue.enqueue(current->right);
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
void BTree<Key, Value>::erase(const Key& key) {
    if (is_empty()) {
        throw std::logic_error("BTree::erase: tree is empty");
    }

    if (_root->key == key && _size == 1) {
        delete _root;
        _root = nullptr;
        _size--;
        return;
    }

    Node *current = nullptr, *prev_node = nullptr;
    Node *to_erase = nullptr, *last_node = nullptr, *last_node_parent = nullptr;
    Queue<Node*> queue((_size + 1) / 2);
    queue.enqueue(_root);

    while (!queue.is_empty()) {
        prev_node = current;
        current = queue.front();
        queue.dequeue();

        if (current->key == key) {
            to_erase = current;
        }

        if (!current->left && last_node == nullptr) {
            last_node_parent = prev_node;
            last_node = prev_node->right;
        }

        if (!current->right && last_node == nullptr) {
            last_node_parent = current;
            last_node = current->left;
        }

        if (current->left) {
            queue.enqueue(current->left);
        }

        if (current->right) {
            queue.enqueue(current->right);
        }
    }

    if (to_erase == nullptr) {
        throw std::invalid_argument("BTree::erase: key not found");
    }

    to_erase->key = last_node->key;
    to_erase->value = last_node->value;
    if (last_node_parent->left == last_node) {
        last_node_parent->left = nullptr;
    } else {
        last_node_parent->right = nullptr;
    }
    delete last_node;
    _size--;
}

template<typename Key, typename Value>
void BTree<Key, Value>::clear() {
    clear_rec(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
bool BTree<Key, Value>::is_empty() const {
    return _root == nullptr;
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_w() const {
    if (is_empty()) {
        return;
    }

    Node* current = nullptr;
    Queue<Node*> queue((_size + 1) / 2);
    bool first = true;
    queue.enqueue(_root);

    while (!queue.is_empty()) {
        current = queue.front();

        if (!first) {
            std::cout << ", ";
        }

        first = false;
        std::cout << current->key << ":" << current->value;
        queue.dequeue();

        if (current->left) {
            queue.enqueue(current->left);
        }

        if (current->right) {
            queue.enqueue(current->right);
        }
    }
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dlcr() const {
    bool first = true;
    print_dlcr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dlrc() const {
    bool first = true;
    print_dlrc_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dclr() const {
    bool first = true;
    print_dclr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dlcr_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    print_dlcr_rec(node->left, first);

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value;
    first = false;
    print_dlcr_rec(node->right, first);
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dlrc_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    print_dlrc_rec(node->left, first);
    print_dlrc_rec(node->right, first);

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value;
    first = false;
}

template<typename Key, typename Value>
void BTree<Key, Value>::print_dclr_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value;
    first = false;
    print_dclr_rec(node->left, first);
    print_dclr_rec(node->right, first);
}

template<typename Key, typename Value>
void BTree<Key, Value>::clear_rec(Node *node) {
    if (node == nullptr) {
        return;
    }

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

#endif  // LIBS_LIB_BTREE_BTREE_H_
