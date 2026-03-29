// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_AVLTREE_AVLTREE_H_
#define LIBS_LIB_AVLTREE_AVLTREE_H_

#include <cstdlib>
#include <stdexcept>

template<typename Key, typename Value>
class AVLTree {
 private:
    struct Node {
        Node *left, *right, *parent;
        Key key;
        Value value;
        size_t height;

        Node(const Key& a_key, const Value& a_value, Node* a_parent = nullptr,
            const size_t& a_height = 0, Node* a_left = nullptr,
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
    int grand_balance;

    recalculate_height(dad);

    if (!grand) {
        return;
    }

    grand_balance = calculate_balance(grand);

    if (grand_balance < -1 || grand_balance > 1) {
        rebalance(grand);
    }

    Node* current = grand;
    int prev_height;

    while (current) {
        prev_height = current->height;
        recalculate_height(current);

        if (prev_height == current->height) {
            break;
        }

        current = current->parent;
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::left_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("AVLTree::left_rotate: node is nullptr");
    }

    Node* grand = node;
    Node* great = grand->parent;;
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

template<typename Key, typename Value>
void AVLTree<Key, Value>::right_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("AVLTree::left_rotate: node is nullptr");
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
