// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_RBTREE_RBTREE_H_
#define LIBS_LIB_RBTREE_RBTREE_H_

#include <stdexcept>
#include <string>
#include <iostream>
#include "libs/lib_queue/queue.h"
#include "libs/lib_tvector/tvector.h"

template<typename Key, typename Value>
class RBTree {
 private:
    enum Color {
        RED,
        BLACK
    };

    struct Node {
        Key key;
        Value value;
        Node *left, *right, *parent;
        Color color;

        Node(const Key& a_key, const Value& a_value, Color a_color,
            Node* a_parent = nullptr,
            Node* a_left = nullptr, Node* a_right = nullptr);
    };

    Node* _root;
    size_t _size;

 public:
    RBTree();
    ~RBTree();

    void insert(const Key& key, const Value& value);
    Value* find(const Key& key) const;
    void erase(const Key& key);
    void clear();
    bool is_empty() const noexcept;
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
    void rebalance(Node* node);

    void recolor(Node* node);
    void swap_color(Node* n1, Node* n2);
    void fix_double_black(Node* parent, bool db_is_left_child);
    Color color_of(Node* node);
    const char* color_str(Node* node) const;
};

template<typename Key, typename Value>
RBTree<Key, Value>::Node::Node(const Key& a_key, const Value& a_value,
    Color a_color, Node* a_parent,
    Node* a_left, Node* a_right) : key(a_key), value(a_value), parent(a_parent),
    color(a_color), left(a_left), right(a_right) {
}

template<typename Key, typename Value>
RBTree<Key, Value>::RBTree() : _root(nullptr), _size(0) {
}

template<typename Key, typename Value>
RBTree<Key, Value>::~RBTree() {
    clear();
}

template<typename Key, typename Value>
bool RBTree<Key, Value>::is_empty() const noexcept {
    return _root == nullptr;
}

template<typename Key, typename Value>
size_t RBTree<Key, Value>::size() const noexcept {
    return _size;
}

template<typename Key, typename Value>
typename RBTree<Key, Value>::Node* RBTree<Key, Value>::find_parent(const Key& key) const {
    if (_root == nullptr) {
        return nullptr;
    }

    if (_root->key == key) {
        return _root;
    }

    Node* current = _root;

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
Value* RBTree<Key, Value>::find(const Key& key) const {
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

// Deletion cases. [DB] = double black, appears when BLACK node is removed without replacement.
// r = in-order predecessor (rightmost of d's left subtree). Only the COLOR OF r determines fix.
//
//
// ── Case 0: leaf ──────────────────────────────────────────────────────────────
//
//  0a: d(R) leaf — delete, done
//
//       p                         p
//      / \           ->          / \
//    d(R)  B                  NULL   B
//
//
//  0b: d(B) leaf — delete, [DB] appears -> fix_double_black
//
//       p                         p
//      / \           ->          / \
//    d(B)  B                  [DB]   B
//
//
// ── Case 1: one child ─────────────────────────────────────────────────────────
//
//  d(B), child(R) — only possible combination — reattach child, child->BLACK, done
//
//       p                         p
//      /             ->           /
//    d(B)                      child(B)
//        \
//       child(R)
//
//
// ── Case 2: two children — copy r.key/value into d, delete r from its position ─
//
//  2a: d(B), r(R) — r is always a leaf (RED can't have 1 child)
//      copy r->d, delete r(R leaf), done
//
//         d(B)                    d(B, key=r)
//         / \          ->         / \
//       ...   ...               ...   ...
//       r(R)                  NULL               no fix
//      (leaf)
//
//
//  2b1: d(R), r(B) not leaf — r has exactly one RED child
//       copy r->d, reattach child, child->BLACK, done
//
//         d(R)                    d(R, key=r)
//         / \          ->         / \
//       ...   ...               ...   ...
//       r(B)                  child(B)           no fix
//       /
//     child(R)
//
//
//  2b2: d(R), r(B) leaf — copy r->d, [DB] appears -> fix_double_black
//
//         d(R)                    d(R, key=r)
//         / \          ->         / \
//       ...   ...               ...   ...
//       r(B)                  [DB]               fix!
//      (leaf)
//
//
//  2c1: d(B), r(B) not leaf — r has exactly one RED child
//       copy r->d, reattach child, child->BLACK, done
//
//         d(B)                    d(B, key=r)
//         / \          ->         / \
//       ...   ...               ...   ...
//       r(B)                  child(B)           no fix
//       /
//     child(R)
//
//
//  2c2: d(B), r(B) leaf — copy r->d, [DB] appears -> fix_double_black
//
//         d(B)                    d(B, key=r)
//         / \          ->         / \
//       ...   ...               ...   ...
//       r(B)                  [DB]               fix!
//      (leaf)
template<typename Key, typename Value>
void RBTree<Key, Value>::erase(const Key& key) {
    if (is_empty()) {
        throw std::logic_error("RBTree::erase: tree is empty");
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
    } else if (to_erase_parent == _root && to_erase_parent->key == key) {
        to_erase_parent = nullptr;
        to_erase = _root;
        slot = &_root;
    } else {
        throw std::invalid_argument("RBTree::erase: this key does not exist");
    }

    if (to_erase->left && to_erase->right) {
        Node* to_replace = to_erase->left;
        Node* replace_parent = to_erase;

        while (to_replace->right) {
            replace_parent = to_replace;
            to_replace = to_replace->right;
        }

        if (replace_parent != to_erase) {
            replace_parent->right = to_replace->left;

            if (to_replace->left) {
                to_replace->left->parent = replace_parent;
                to_replace->left->color = BLACK;
            } else if (to_replace->color == BLACK) {
                fix_double_black(replace_parent, false);
            }
        } else {
            to_erase->left = to_replace->left;

            if (to_replace->left) {
                to_replace->left->parent = to_erase;
                to_replace->left->color = BLACK;
            } else if (to_replace->color == BLACK) {
                fix_double_black(replace_parent, true);
            }
        }

        to_erase->key = to_replace->key;
        to_erase->value = to_replace->value;

        delete to_replace;
    } else {
        if (to_erase->left) {
            to_erase->left->parent = to_erase_parent;
            to_erase->left->color = BLACK;
        }

        if (to_erase->right) {
            to_erase->right->parent = to_erase_parent;
            to_erase->right->color = BLACK;
        }

        bool is_left = to_erase_parent && (slot == &to_erase_parent->left);
        *slot = to_erase->left ? to_erase->left : to_erase->right;

        if (to_erase_parent && !*slot && to_erase->color == BLACK) {
            fix_double_black(to_erase_parent, is_left);
        }

        delete to_erase;
    }

    _size--;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::clear() {
    clear_rec(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::clear_rec(Node* node) {
    if (node == nullptr) {
        return;
    }

    clear_rec(node->left);
    clear_rec(node->right);
    delete node;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::get_keys_rec(Node* node, TVector<Key>& result) const {
    if (!node) return;
    get_keys_rec(node->left, result);
    result.push_back(node->key);
    get_keys_rec(node->right, result);
}

template<typename Key, typename Value>
TVector<Key> RBTree<Key, Value>::get_keys() const {
    TVector<Key> result;
    get_keys_rec(_root, result);
    return result;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::insert(const Key& key, const Value& value) {
    Node* parent = find_parent(key);
    Node* new_node = new Node(key, value, RED, parent);

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
        throw std::invalid_argument("RBTree::insert: Key already exists");
    }

    if (new_node == _root) {
        recolor(new_node);
        return;
    }

    if (new_node->parent->color == RED) {
        rebalance(new_node);
    }
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_w() const {
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
        std::cout << current->key << ":" << current->value << color_str(current);
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
void RBTree<Key, Value>::print_dlcr() const {
    bool first = true;
    print_dlcr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_dlrc() const {
    bool first = true;
    print_dlrc_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_dclr() const {
    bool first = true;
    print_dclr_rec(_root, first);
    std::cout << std::endl;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_tree() const {
    print_tree_rec(_root, 1);
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_dlcr_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    print_dlcr_rec(node->left, first);

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value << color_str(node);
    first = false;
    print_dlcr_rec(node->right, first);
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_dlrc_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    print_dlrc_rec(node->left, first);
    print_dlrc_rec(node->right, first);

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value << color_str(node);
    first = false;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_dclr_rec(Node* node, bool& first) const {
    if (node == nullptr) {
        return;
    }

    if (!first) {
        std::cout << ", ";
    }

    std::cout << node->key << ":" << node->value << color_str(node);
    first = false;
    print_dclr_rec(node->left, first);
    print_dclr_rec(node->right, first);
}

template<typename Key, typename Value>
void RBTree<Key, Value>::print_tree_rec(Node* node, int deep) const {
    if (node == nullptr) {
        return;
    }

    print_tree_rec(node->right, deep + 1);
    std::cout << std::string(deep, ' ') << node->key << ":" << node->value << color_str(node) << std::endl;
    print_tree_rec(node->left, deep + 1);
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
void RBTree<Key, Value>::left_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("RBTree::left_rotate: node is nullptr");
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
void RBTree<Key, Value>::right_rotate(Node* node) {
    if (!node) {
        throw std::invalid_argument("RBTree::right_rotate: node is nullptr");
    }

    Node* grand = node;
    Node* great = grand->parent;
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

// Case 1: uncle(R) — recolor, move up
//
//  Initial:                  Recolor dad + uncle:      Recolor grand, child = grand:
//
//       grand(B)                  grand(B)                  grand(R)  <- child
//       /       \                 /       \                 /       \
//    dad(R)   uncle(R)         dad(B)   uncle(B)         dad(B)   uncle(B)
//    /                         /                         /
//  child(R)                  child(R)                  child(R)
//
//
// Case 2/3: uncle(B) — rotation + swap_color
//
//  RR (dad = grand->right, child = dad->right):
//  left_rotate(grand) + swap_color(dad, grand)
//
//       grand(B)                   dad(B)
//       /       \        ->       /       \
//    uncle(B)  dad(R)         grand(R)  child(R)
//                  \           /
//               child(R)   uncle(B)
//
//
//  LL (dad = grand->left, child = dad->left):
//  right_rotate(grand) + swap_color(dad, grand)
//
//         grand(B)                  dad(B)
//         /       \       ->       /       \
//       dad(R)  uncle(B)       child(R)  grand(R)
//       /                                    \
//     child(R)                            uncle(B)
//
//
//  RL (dad = grand->right, child = dad->left):
//  step 1: right_rotate(dad)
//
//       grand(B)                grand(B)
//       /       \       ->      /       \
//    uncle(B)  dad(R)       uncle(B)  child(R)
//              /                           \
//           child(R)                      dad(R)
//
//  step 2: left_rotate(grand) + swap_color(child, grand)
//
//       grand(B)                  child(B)
//       /       \       ->        /       \
//    uncle(B)  child(R)       grand(R)   dad(R)
//                   \          /
//                  dad(R)   uncle(B)
//
//
//  LR (dad = grand->left, child = dad->right):
//  step 1: left_rotate(dad)
//
//         grand(B)                grand(B)
//         /       \      ->       /       \
//       dad(R)  uncle(B)      child(R)  uncle(B)
//           \                   /
//          child(R)           dad(R)
//
//  step 2: right_rotate(grand) + swap_color(child, grand)
//
//         grand(B)                  child(B)
//         /       \       ->        /       \
//      child(R)  uncle(B)        dad(R)   grand(R)
//       /                                      \
//     dad(R)                                uncle(B)
template<typename Key, typename Value>
void RBTree<Key, Value>::rebalance(Node* node) {
    Node* child = node;

    while (child != _root && child->parent->color == RED) {
        Node* dad = child->parent;
        Node* grand = dad->parent;
        Node* uncle = (dad == grand->left) ? grand->right : grand->left;

        if (uncle != nullptr && uncle->color == RED) {
            dad->color = BLACK;
            uncle->color = BLACK;
            grand->color = RED;
            child = grand;
        } else {
            break;
        }
    }

    if (child != _root && child->parent->color == RED) {
        Node* dad = child->parent;
        Node* grand = dad->parent;

        if (dad == grand->right) {
            if (child == dad->left) {
                right_rotate(dad);
                child = dad;
                dad = child->parent;
            }
            left_rotate(grand);
            swap_color(dad, grand);
        } else {
            if (child == dad->right) {
                left_rotate(dad);
                child = dad;
                dad = child->parent;
            }
            right_rotate(grand);
            swap_color(dad, grand);
        }
    }

    _root->color = BLACK;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::recolor(Node* node) {
    if (!node) {
        return;
    }

    if (node->color == RED) {
        node->color = BLACK;
    } else if (node->color == BLACK) {
        node->color = RED;
    }
}

template<typename Key, typename Value>
void RBTree<Key, Value>::swap_color(Node* n1, Node* n2) {
    Color temp = n1->color;
    n1->color = n2->color;
    n2->color = temp;
}

// Fix double black — [DB] is left child of parent in all diagrams (right side is symmetric).
//
// Case A: s(R) — left_rotate(p) + swap_color(p, s), get new BLACK sibling, then B/C/D:
//
//       p(B)                          s(B)
//      /    \              ->        /    \
//    [DB]   s(R)                  p(R)    sr
//           / \                  /    \
//          sl  sr              [DB]   sl    <- new BLACK sibling
//
//
// Case B: s(B), sl(B), sr(B) — s->RED, resolve or propagate [DB] up:
//
//  p(R):
//       p(R)                          p(B)
//      /    \              ->        /    \
//    [DB]   s(B)                 BLACK   s(R)    done
//           / \                          / \
//          sl  sr                       sl  sr
//
//  p(B):
//       p(B)                         p[DB]
//      /    \              ->        /    \
//    [DB]   s(B)                 BLACK   s(R)    propagate [DB] up to p
//           / \                          / \
//          sl  sr                       sl  sr
//
//
// Case D: s(B), near(R)=sl, far(B)=sr — right_rotate(s) + swap_color(near, s) -> Case C:
//
//       p(?)                          p(?)
//      /    \              ->        /    \
//    [DB]   s(B)                  [DB]  near(B)    <- new sibling
//           / \                            \
//          sl   sr                          s(R)
//          (R)  (B)                            \
//                                              sr(B)
//
//
// Case C: s(B), far(R)=sr — left_rotate(p) + swap_color(p, s) + far->BLACK, done:
//
//       p(C)                          s(C)
//      /    \              ->        /    \
//    [DB]   s(B)                 p(B)   sr(B)
//           / \                 /    \
//          sl  sr(R)          [DB]   sl       done, [DB] resolved
template<typename Key, typename Value>
void RBTree<Key, Value>::fix_double_black(Node* parent, bool db_is_left_child) {
    while (parent) {
        Node* sibling = db_is_left_child ? parent->right : parent->left;

        if (color_of(sibling) == RED) {
            if (db_is_left_child) {
                left_rotate(parent);
                swap_color(parent, sibling);
                sibling = parent->right;
            } else {
                right_rotate(parent);
                swap_color(parent, sibling);
                sibling = parent->left;
            }
        }

        Node *near, *far;

        if (db_is_left_child) {
            near = sibling->left;

            if (color_of(near) == RED) {
                right_rotate(sibling);
                swap_color(near, sibling);
                sibling = near;
            }

            far = sibling->right;

            if (color_of(far) == RED) {
                left_rotate(parent);
                swap_color(parent, sibling);
                far->color = BLACK;
                return;
            }
        } else {
            near = sibling->right;

            if (color_of(near) == RED) {
                left_rotate(sibling);
                swap_color(near, sibling);
                sibling = near;
            }

            far = sibling->left;

            if (color_of(far) == RED) {
                right_rotate(parent);
                swap_color(parent, sibling);
                far->color = BLACK;
                return;
            }
        }

        if (color_of(sibling->right) == BLACK && color_of(sibling->left) == BLACK) {
            sibling->color = RED;

            if (color_of(parent) == RED) {
                parent->color = BLACK;
                return;
            } else {
                Node* temp = parent;
                parent = parent->parent;

                if (parent) {
                    db_is_left_child = parent->left == temp;
                }
            }
        }
    }
}

template<typename Key, typename Value>
typename RBTree<Key, Value>::Color RBTree<Key, Value>::color_of(Node* node) {
    if (node) {
        return node->color;
    }

    return BLACK;
}

template<typename Key, typename Value>
const char* RBTree<Key, Value>::color_str(Node* node) const {
    return node->color == RED ? "(R)" : "(B)";
}

#endif  // LIBS_LIB_RBTREE_RBTREE_H_
