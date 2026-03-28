// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_AVLTREE_AVLTREE_H_
#define LIBS_LIB_AVLTREE_AVLTREE_H_

#include <cstdlib>

template<typename Key, typename Value>
class AVLTree {
 private:
    struct Node {
        Node *left, *right, *parent;
        Key key;
        Value value;
        size_t height;
    };

    Node* _root;
    size_t _size;

 public:
    AVLTree();
    ~AVLTree();

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
    void print_dlcr_rec(Node* node, bool& first) const;
    void print_dlrc_rec(Node* node, bool& first) const;
    void print_dclr_rec(Node* node, bool& first) const;
    void print_tree_rec(Node* node, int deep) const;
    void clear_rec(Node* node);

    void left_rotate(Node* node);
    void right_rotate(Node* node);
    void case_rr(Node* node);
    void case_ll(Node* node);
    void case_lr(Node* node);
    void case_rl(Node* node);
    void rebalance(Node* node);
    void recalculate_height(Node* node);
    int calculate_balance(Node* node);
};

template<typename Key, typename Value>
void AVLTree<Key, Value>::recalculate_height(Node* node) {
    size_t left_height = 0;
    size_t right_height = 0;

    if (node->left) {
        left_height = node->left->height;
    }

    if (node->right) {
        right_height = node->right->height;
    }

    node->height = ++(left_height > right_height ? left_height : right_height);
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::calculate_balance(Node* node) {
    int left_height = 0;
    int right_height = 0;

    if (node->left) {
        left_height = node->left->height;
    }

    if (node->right) {
        right_height = node->right->height;
    }

    return right_height - left_height;
}

#endif  // LIBS_LIB_AVLTREE_AVLTREE_H_
