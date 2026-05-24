// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_AVLTREE_AVLTREE_H_
#define LIBS_LIB_AVLTREE_AVLTREE_H_

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "libs/lib_queue/queue.h"
#include "libs/lib_tvector/tvector.h"

template<typename Key, typename Value>
class AVLTree {
 private:
    struct Node {
        Node *left, *right, *parent;
        Key key;
        Value value;
        size_t height;

        Node(const Key& a_key, const Value& a_value, Node* a_parent = nullptr,
            const size_t& a_height = 1, Node* a_left = nullptr,
            Node* a_right = nullptr);
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
    size_t size() const noexcept;
    TVector<Key> get_keys() const;

    void print_w() const;
    void print_dlcr() const;
    void print_dlrc() const;
    void print_dclr() const;
    void print_tree() const;

 private:
    Node* find_parent(const Key& key) const;
    void get_keys_rec(Node* node, TVector<Key>& result) const;
    void print_dlcr_rec(Node* node, bool& first) const;
    void print_dlrc_rec(Node* node, bool& first) const;
    void print_dclr_rec(Node* node, bool& first) const;
    void print_tree_rec(Node* node, int deep) const;
    void clear_rec(Node* node);

    void left_rotate(Node* node);
    void right_rotate(Node* node);
    // void case_rr(Node* node);
    // void case_ll(Node* node);
    // void case_lr(Node* node);
    // void case_rl(Node* node);
    void rebalance(Node* node);
    void recalculate_height(Node* node);
    int calculate_balance(Node* node);
};

template<typename Key, typename Value>
AVLTree<Key, Value>::Node::Node(const Key& a_key, const Value& a_value, Node* a_parent, const size_t& a_height,
    Node* a_left, Node* a_right) : key(a_key), value(a_value), parent(a_parent),
height(a_height), left(a_left), right(a_right){
}

template<typename Key, typename Value>
AVLTree<Key, Value>::AVLTree() : _root(nullptr), _size(0) {
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::print_tree() const {
    print_tree_rec(_root, 1);
}

template<typename Key, typename Value>
typename AVLTree<Key, Value>::Node* AVLTree<Key, Value>::find_parent(const Key& key) const {
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
void AVLTree<Key, Value>::print_tree_rec(Node *node, int deep) const {
    if (node == nullptr) {
        return;
    }

    print_tree_rec(node->right, deep + 1);
    std::cout << std::string(deep, ' ') << node->key << ":" << node->value << std::endl;
    print_tree_rec(node->left, deep + 1);
}

template<typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
    clear();
}

template<typename Key, typename Value>
size_t AVLTree<Key, Value>::size() const noexcept {
    return _size;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::get_keys_rec(Node* node, TVector<Key>& result) const {
    if (!node) return;
    get_keys_rec(node->left, result);
    result.push_back(node->key);
    get_keys_rec(node->right, result);
}

template<typename Key, typename Value>
TVector<Key> AVLTree<Key, Value>::get_keys() const {
    TVector<Key> result;
    get_keys_rec(_root, result);
    return result;
}

template<typename Key, typename Value>
Value* AVLTree<Key, Value>::find(const Key& key) const {
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

    if (parent->key == key) {
        return &parent->value;
    }

    return nullptr;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
    clear_rec(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::clear_rec(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::print_w() const {
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
void AVLTree<Key, Value>::print_dlcr() const {
    bool first = true;
    print_dlcr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::print_dlrc() const {
    bool first = true;
    print_dlrc_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::print_dclr() const {
    bool first = true;
    print_dclr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::print_dlcr_rec(Node* node, bool& first) const {
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
void AVLTree<Key, Value>::print_dlrc_rec(Node* node, bool& first) const {
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
void AVLTree<Key, Value>::print_dclr_rec(Node* node, bool& first) const {
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
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* parent = find_parent(key);
    Node* new_node = new Node(key, value, parent);

    if (!parent) {
        _root = new_node;
        _size++;
    } else if (parent->key < key && !parent->right) {
        parent->right = new_node;
        _size++;
    } else if (parent->key > key && !parent->left) {
        parent->left = new_node;
        _size++;
    } else {
        delete new_node;
        throw std::invalid_argument("AVLTree::insert: Key already exists");
    }

    if (new_node == _root)  {
        return;
    }

    Node* dad = new_node->parent;
    Node* grand = dad->parent;

    recalculate_height(dad);

    if (!grand) {
        return;
    }

    Node* current = grand;
    int prev_height, current_balance;

    while (current) {
        current_balance = calculate_balance(current);

        if (current_balance < -1 || current_balance > 1) {
            rebalance(current);
        }

        prev_height = current->height;
        recalculate_height(current);

        if (prev_height == current->height) {
            break;
        }

        current = current->parent;
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key) {
    if (is_empty()) {
        throw std::logic_error("AVLTree::erase: tree is empty");
    }

    Node** slot;
    Node* to_erase_parent = find_parent(key);
    Node* to_erase = nullptr;
    Node* real_parent;

    if (to_erase_parent->left && to_erase_parent->left->key == key) {
        to_erase = to_erase_parent->left;
        slot = &to_erase_parent->left;
    } else if (to_erase_parent->right && to_erase_parent->right->key == key) {
        to_erase = to_erase_parent->right;
        slot = &to_erase_parent->right;
    } else if (to_erase_parent == _root && to_erase_parent->key == key) {
        to_erase_parent = nullptr;
        to_erase = _root;
        slot = &_root;
    } else {
        throw std::invalid_argument("AVLTree::erase: this key does not exist");
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
            if (leaf->left) {
                leaf->left->parent = leaf_parent;
            }
        } else {
            to_erase->left = leaf->left;
            if (leaf->left) {
                leaf->left->parent = to_erase;
            }
        }

        real_parent = leaf_parent;

        to_erase->key = leaf->key;
        to_erase->value = leaf->value;
        delete leaf;
    } else {
        real_parent = to_erase_parent;
        if (to_erase->left) {
            to_erase->left->parent = to_erase_parent;
        }
        if (to_erase->right) {
            to_erase->right->parent = to_erase_parent;
        }
        *slot = to_erase->left ? to_erase->left : to_erase->right;
        delete to_erase;
    }

    _size--;

    while (real_parent) {
        int balance = calculate_balance(real_parent);

        if (balance < -1 || balance > 1) {
            size_t height_before_rebalance = real_parent->height;
            rebalance(real_parent);
            real_parent->parent->height = height_before_rebalance;
        }

        size_t old_height = real_parent->height;
        recalculate_height(real_parent);

        if (old_height == real_parent->height) {
            break;
        }

        real_parent = real_parent->parent;
    }
}

template<typename Key, typename Value>
bool AVLTree<Key, Value>::is_empty() const {
    return _root == nullptr;
}

// Before left_rotate(grand):    After:
//
//      great                       great
//        |                           |
//      grand                        dad
//      /   \          ->           /   \
//     A    dad                  grand    B
//          / \                  /   \
//       l_ch   B               A   l_ch
template<typename Key, typename Value>
void AVLTree<Key, Value>::left_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("AVLTree::left_rotate: node is nullptr");
    }

    Node* grand = node;
    Node* great = grand->parent;
    Node* dad = grand->right;
    Node* left_child = dad->left;

    dad->parent = grand->parent;
    grand->right = left_child;

    if (left_child) {
        left_child->parent = grand;
    }

    dad->left = grand;
    grand->parent = dad;

    if (great && great->right == node) {
        great->right = dad;
    } else if (great && great->left == node) {
        great->left = dad;
    }

    if (!great) {
        _root = dad;
    }
}

// Before right_rotate(grand):   After:
//
//      great                       great
//        |                           |
//      grand                        dad
//      /   \          ->           /   \
//    dad    B                     A   grand
//    / \                              /   \
//   A  r_ch                       r_ch    B
template<typename Key, typename Value>
void AVLTree<Key, Value>::right_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("AVLTree::right_rotate: node is nullptr");
    }

    Node* grand = node;
    Node* great = grand->parent;;
    Node* dad = grand->left;
    Node* right_child = dad->right;

    dad->parent = grand->parent;
    grand->left = right_child;

    if (right_child) {
        right_child->parent = grand;
    }

    dad->right = grand;
    grand->parent = dad;

    if (great && great->right == node) {
        great->right = dad;
    } else if (great && great->left == node) {
        great->left = dad;
    }

    if (!great) {
        _root = dad;
    }
}

// RR (grand>=2, dad>=0): left_rotate(grand)
//   grand          dad
//   /   \    ->   /   \
//  A    dad    grand    B
//       / \    /   \
//      C   B  A     C
//
// RL (grand>=2, dad<0): right_rotate(dad), then left_rotate(grand)
//   grand        grand           son
//   /   \   ->   /   \    ->    /   \
//  A    dad     A    son     grand   dad
//       / \          / \     /   \   / \
//     son   B       C   dad A     C D   B
//     / \               / \
//    C   D             D   B
//
// LL (grand<=-2, dad<=0): right_rotate(grand)
//     grand        dad
//     /   \  ->   /   \
//   dad    B     A   grand
//   / \               / \
//  A   C             C   B
//
// LR (grand<=-2, dad>0): left_rotate(dad), then right_rotate(grand)
//   grand        grand           son
//   /   \   ->   /   \    ->    /   \
// dad    B      son    B      dad   grand
// / \           / \            / \    / \
//A  son        dad  D         A   C  D   B
//   / \        / \
//  C   D      A   C
template<typename Key, typename Value>
void AVLTree<Key, Value>::rebalance(Node* node) {
    Node* grand = node;
    Node* dad = nullptr;

    int grand_balance = calculate_balance(grand);
    int dad_balance = 0;

    if (grand_balance >= 2) {
        dad = node->right;
        dad_balance = calculate_balance(dad);

        if (dad_balance >= 0) {
            left_rotate(grand);
        } else {
            right_rotate(dad);
            recalculate_height(dad);
            left_rotate(grand);
        }
    } else if (grand_balance <= -2) {
        dad = node->left;
        dad_balance = calculate_balance(dad);

        if (dad_balance <= 0) {
            right_rotate(grand);
        } else {
            left_rotate(dad);
            recalculate_height(dad);
            right_rotate(grand);
        }
    }
}

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
