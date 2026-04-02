// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_BSTREE_BSTREE_H_
#define LIBS_LIB_BSTREE_BSTREE_H_

#include <stdexcept>
#include <string>
#include <iostream>
#include "libs/lib_queue/queue.h"

template<typename Key, typename Value>
class BSTree {
 private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v,
           Node* l = nullptr, Node* r = nullptr);
    };

    Node* _root;
    size_t _size;

 public:
    BSTree();
    ~BSTree();

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
    Node* find_parent(const Key& key) const;
    void left_swap_and_erase(Node* node);
    void right_swap_and_erase(Node* node);
    void print_dlcr_rec(Node* node, bool& first) const;
    void print_dlrc_rec(Node* node, bool& first) const;
    void print_dclr_rec(Node* node, bool& first) const;
    void print_tree_rec(Node* node, int deep) const;
    void clear_rec(Node* node);
};

template<typename Key, typename Value>
BSTree<Key, Value>::Node::Node(const Key& k, const Value& v, Node* l, Node* r)
    : key(k), value(v), left(l), right(r){
}

template<typename Key, typename Value>
BSTree<Key, Value>::BSTree() : _root(nullptr), _size(0) {
}

template<typename Key, typename Value>
BSTree<Key, Value>::~BSTree() {
    clear();
}

template<typename Key, typename Value>
void BSTree<Key, Value>::insert(const Key &key, const Value &value) {
    Node* parent = find_parent(key);

    if (!parent) {
        _root = new Node(key, value);
        _size++;
        return;
    }

    if (parent->key < key && !parent->right) {
        parent->right = new Node(key, value);
        _size++;
        return;
    }

    if (parent->key > key && !parent->left) {
        parent->left = new Node(key, value);
        _size++;
        return;
    }

    throw std::invalid_argument("BSTree::insert: Key already exists");
}

template<typename Key, typename Value>
Value* BSTree<Key, Value>::find(const Key& key) const {
    if (is_empty()) {
        return nullptr;
    }

    Node* parent = find_parent(key);

    if (parent->left && parent->left->key == key) {
        return &parent->left->value;
    }

    if (parent->right && parent->right->key == key) {
        return &parent->right->value;
    }

    if (parent == _root) {
        return &_root->value;
    }

    return nullptr;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::erase(const Key& key) {
    if (is_empty()) {
        throw std::logic_error("BSTree::erase: tree is empty");
    }

    Node** slot;
    Node* to_erase_parent = find_parent(key);
    Node* to_erase = nullptr;

    if (to_erase_parent->left && to_erase_parent->left->key == key) {
        to_erase = to_erase_parent->left;
        slot = &to_erase_parent->left;
    } else if (to_erase_parent->right && to_erase_parent->right->key == key) {
        to_erase = to_erase_parent->right;
        slot = &to_erase_parent->right;
    } else if (to_erase_parent == _root) {
        to_erase = _root;
        slot = &_root;
    } else {
        throw std::invalid_argument("BSTree::erase: this key does not exist");
    }

    if (to_erase->left && to_erase->right) {
        Node* leaf = to_erase->left;
        Node* leaf_parent = to_erase;

        while (leaf->right) {
            leaf_parent = leaf;
            leaf = leaf->right;
        }

        if (leaf_parent != to_erase) {
            leaf_parent->right = leaf->left;
        } else {
            to_erase->left = leaf->left;
        }

        to_erase->key = leaf->key;
        to_erase->value = leaf->value;
        delete leaf;
    } else {
        *slot = to_erase->left ? to_erase->left : to_erase->right;
        delete to_erase;
    }
}

template<typename Key, typename Value>
void BSTree<Key, Value>::clear() {
    clear_rec(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
bool BSTree<Key, Value>::is_empty() const {
    return _root == nullptr;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_w() const {
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

    std::cout << std::endl;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_dlcr() const {
    bool first = true;
    print_dlcr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_dlrc() const {
    bool first = true;
    print_dlrc_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_dclr() const {
    bool first = true;
    print_dclr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_tree() const {
    print_tree_rec(_root, 1);
}

template<typename Key, typename Value>
void BSTree<Key, Value>::print_dlcr_rec(Node* node, bool& first) const {
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
void BSTree<Key, Value>::print_dlrc_rec(Node* node, bool& first) const {
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
void BSTree<Key, Value>::print_dclr_rec(Node* node, bool& first) const {
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
void BSTree<Key, Value>::print_tree_rec(Node* node, int deep) const {
    if (node == nullptr) {
        return;
    }

    print_tree_rec(node->right, deep + 1);
    std::cout << std::string(deep, ' ') << node->key << ":" << node->value << std::endl;
    print_tree_rec(node->left, deep + 1);
}

template<typename Key, typename Value>
void BSTree<Key, Value>::clear_rec(Node *node) {
    if (node == nullptr) {
        return;
    }

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template<typename Key, typename Value>
typename BSTree<Key, Value>::Node *BSTree<Key, Value>::find_parent(const Key& key) const {
    if (_root == nullptr) {
        return nullptr;
    }

    if (_root->key == key) {
        return _root;
    }

    Node *current = _root;

    while (current) {
        if (current->key > key) {
            if (!current->left || current->left->key == key) {
                return current;
            }

            current = current->left;
        }

        if (current->key < key) {
            if (!current->right || current->right->key == key) {
                return current;
            }

            current = current->right;
        }
    }

    return nullptr;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::left_swap_and_erase(Node* node) {
    Node* to_swap = node->left;
    Node* to_swap_parent = nullptr;

    while (to_swap->right) {
        to_swap_parent = to_swap;
        to_swap = to_swap->right;
    }

    node->key = to_swap->key;
    node->value = to_swap->value;
    delete to_swap;
    to_swap_parent->right = nullptr;
}

template<typename Key, typename Value>
void BSTree<Key, Value>::right_swap_and_erase(Node* node) {
    Node* to_swap = node->left;
    Node* to_swap_parent = nullptr;

    while (to_swap->right) {
        to_swap_parent = to_swap;
        to_swap = to_swap->right;
    }

    node->key = to_swap->key;
    node->value = to_swap->value;
    delete to_swap;
    to_swap_parent->right = nullptr;
}

#endif  // LIBS_LIB_BSTREE_BSTREE_H_
