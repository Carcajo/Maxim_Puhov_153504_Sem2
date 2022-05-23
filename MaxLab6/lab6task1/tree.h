#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>

#include <vector>
#include <QString>
template <typename T, typename K>
struct Node {

    T data = T();
    K key = K();

    Node* left = nullptr, * right = nullptr;

    Node(T data_, K key_) : data(data_), key(key_) {}

    Node(K key_) : key(key_) {}


    Node(std::pair<T, K> pr) : data(pr.first), key(pr.second) {}
};

template <typename T, typename K>
class Tree {

    typedef T value_type;
    typedef Node<T, K> node;
    typedef T& data;
    typedef K key;

private:

    std::vector<std::pair<value_type, key>> keys;

    std::string tr, PreOrder, PostOrder, IncreaseOrder;

protected:
    node* root = nullptr;

private:

    size_t sz = 0;

    std::allocator<node> NewNode;

    void recursive_show(node* cur, unsigned level = 1) {

        if (cur) {

            recursive_show(cur->left, level + 1);

            for (int i = 0; i < level; ++i) {
               // std::cout << '\t';
                tr.push_back('\t');
            }

            //std::cout << cur->key << '\n' << '\n';
            tr += std::to_string(cur->key); tr.push_back('\n'); tr.push_back('\n');

            recursive_show(cur->right, level + 1);
        }

    }


    void recursive_clear(node* cur) {

        if (cur) {

            recursive_clear(cur->left);

            recursive_clear(cur->right);

            //delete cur;

            NewNode.destroy(cur);

            NewNode.deallocate(cur, 1);
        }

    }

    void fill_keys(node* cur) {

        if (cur) {

            fill_keys(cur->left);

            fill_keys(cur->right);

            std::pair<value_type, key> pr(cur->data, cur->key);
            keys.push_back(std::move(pr));

        }
    }

    void make_balanced(node** cur, unsigned n, unsigned size) {
        if (n == size) {
            *cur = nullptr;
            return;
        }
        else {
            unsigned m = (n + size) / 2;

            *cur = NewNode.allocate(1);
            NewNode.construct((*cur), Node<T, K>(keys[m]));

            make_balanced(&(*cur)->left, n, m);

            make_balanced(&(*cur)->right, m + 1, size);
        }
    }


    void traversePreOrder(node* cur) {
        if (cur) {
            //std::cout << ' ' << cur->key;

            PreOrder.push_back(' ');
            PreOrder += std::to_string(cur->key);

            traversePreOrder(cur->right);

            traversePreOrder(cur->left);
        }
    }

    void traversePostOrder(node* cur) {
        if (cur) {
            traversePostOrder(cur->right);
            traversePostOrder(cur->left);

            PostOrder.push_back(' ');
            PostOrder += std::to_string(cur->key);
            //std::cout << ' ' << cur->key;
        }
    }

    void traverseIncreaseKey(node* cur) {
        if (cur) {
            traverseIncreaseKey(cur->right);

            IncreaseOrder.push_back(' ');
            IncreaseOrder += std::to_string(cur->key);

            //std::cout << ' ' << cur->key;

            traverseIncreaseKey(cur->left);
        }
    }

public:

    Tree() = default;

    Tree(T data_, K key_) {

        root = NewNode.allocate(1);
        NewNode.construct(root, data_, key_);
        //root = new Node<T, K>;

       // root->data = data_;
       // root->key = key_;

        sz = 1;

    }

    ~Tree() {
        recursive_clear(root);
    }

    bool empty() {
        return !root;
    }

    void clear() {

        sz = 0;

        recursive_clear(root);

    }

    std::string show() {

        tr.clear();

        tr.push_back('\n');

        recursive_show(root);

        return tr;

    }

    void make_balanced() {

        keys.clear();

        fill_keys(root);

        make_balanced(&root, 0, keys.size());

    }

    bool exist(K key_) {

        node* cur = root;

        while (cur && cur->data != key_) {

            if (cur->key > key_)
                cur = cur->left;
            else
                cur = cur->right;
        }

        return cur;

    }

    data find(K key_) {

        node* cur = root;

        while (cur && cur->key != key_) {

            if (cur->key < key_)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (cur)
            return cur->data;
        else
            exit(-138);
    }

    bool insert(T data_, K key_) {

        if (empty()) {

            //root = new node(data_, key_);

            root = NewNode.allocate(1);

            NewNode.construct(root, data_, key_);

            sz = 1;

            return true;
        }

        node* cur = root;

        while (cur && cur->key != key_) {

            if (cur->key < key_ && !cur->left) {

                cur->left = NewNode.allocate(1);
                NewNode.construct(cur->left, data_, key_);

                //cur->left = new node(data_, key_);

                ++sz;

                return true;
            }

            if (cur->key > key_ && !cur->right) {

                                cur->right = NewNode.allocate(1);
                                NewNode.construct(cur->right, data_, key_);

               // cur->right = new node(data_, key_);

                ++sz;

                return true;

            }

            if (cur->key > key_)
                cur = cur->right;

            else
                cur = cur->left;
        }

        return false;

    }

    bool erase(K key) {

        if (empty())
            return false;

        node* cur, * parent, * R, * Prev_R;

        cur = root;

        parent = nullptr;

        while (cur && cur->key != key) {
            parent = cur;
            if (cur->key < key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        if (!cur) {
            return false;
        }

        if (!cur->right)
            R = cur->left;
        else
            if (!cur->left)
                R = cur->right;
            else {

                Prev_R = cur;
                R = cur->left;

                while (R->right) {
                    Prev_R = R;
                    R = R->right;
                }

                if (Prev_R == cur)
                    R->right = cur->right;

                else {
                    R->right = cur->right;
                    Prev_R->right = R->left;
                    R->left = Prev_R;
                }
            }
        if (cur == root)
            root = R;
        else
            if (cur->key > parent->key)
                parent->left = R;
            else
                parent->right = R;

        //delete cur;
        NewNode.destroy(cur);
        NewNode.deallocate(cur, 1);

        return true;
    }

    const size_t size() noexcept {
        return sz;
    }

    std::string traversePreOrder() {

        PreOrder.clear();

        traversePreOrder(root);

        return PreOrder;
    }

    std::string traversePostOrder() {

        PostOrder.clear();

        traversePostOrder(root);

        return PostOrder;
    }

    std::string traverseIncreaseKey() {

        IncreaseOrder.clear();

        traverseIncreaseKey(root);

        return IncreaseOrder;
    }

};

template< typename T, typename K>
class taskTree : public Tree<T, K> {

    typedef Node<T, K> node;

private:

    size_t counter;

    void count(node* cur) {

        if (cur) {

            count(cur->left);
            count(cur->right);

            counter += cur->data.size();
        }

    }

public:

    taskTree() : counter(0) {}

    size_t count_symbols() {

        counter = 0;

        count(Tree<T, K>::root);

        return counter;
    }

};

#endif // TREE_H
к
