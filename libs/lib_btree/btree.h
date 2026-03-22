// Copyright 2026 Chernykh Valentin

#ifndef LIBS_LIB_BTREE_BTREE_H_
#define LIBS_LIB_BTREE_BTREE_H_

template<typename Key, typename Value>
class BTree {
 private:
    struct Node {
        Key key;
        Value value;
        Node *left, *right;

        Node(const Key& k, const Value&, Node* l = nullptr, Node* r = nullptr);
    };

    Node* _root;

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

 private:
    void print_dlcr_reс(Node* node) const;
    void print_dlrc_reс(Node* node) const;
    void print_dclr_reс(Node* node) const;
    void clear_rec(Node* node);
};

#endif  // LIBS_LIB_BTREE_BTREE_H_
