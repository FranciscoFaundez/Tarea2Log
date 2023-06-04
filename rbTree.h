#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include "AbstractTree.h"

enum Color {RED, BLACK};

struct RBNode {
    int key;
    Color color;
    RBNode *left, *right, *parent;

    RBNode(int key) {
        this->key = key;
        color = RED;
        left = right = parent = nullptr;
    }
};

class RedBlackTree : public AbstractTree{
private:
    RBNode *root;

    void leftRotate(RBNode *x);
    void rightRotate(RBNode *x);
    void fixInsert(RBNode *z);
    RBNode* insert(RBNode *root, RBNode *z);
    void preOrder(RBNode *root);
    void clear(RBNode *root);
    int memoryUsage(RBNode *root);

public:
    RedBlackTree();
    void insert(int key) override;
    void print() override;
    void clear() override;
    int memoryUsage() override;
};

#endif // RBTREE_H_INCLUDED
