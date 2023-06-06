//
// Created by admin on 04-06-2023.
//

#ifndef TAREA2_RBTREE_H
#define TAREA2_RBTREE_H

#include "AbstractTree.h"

enum Color {RED, BLACK};

// key structure that represents a node in the tree
struct Node {
    int key;
    Node *parent;
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    Color color;
};

typedef Node *RBNode;

// class RBTree implements the operations in Red Black Tree
class RBTree : public AbstractTree{

public:
    RBNode root;
    RBNode TNULL;

    RBTree();

    // search the tree for the key k
    // and return the corresponding node
    bool search(int k) override;

    // rotate left at node x
    void leftRotate(RBNode x);

    // rotate right at node x
    void rightRotate(RBNode x);

    // insert the key to the tree in its appropriate position
    // and fix the tree
    void insert(int key) override;
    //-----------------------------------------------------//

    //Now we create functions to clear the Tree
    void clear() override;

    void clearHelper(RBNode node);

    //---------------------------------------------------//

    // initializes the nodes with appropirate values
    // all the pointers are set to point to the null pointer

    RBNode searchTreeHelper(RBNode node, int key);

    // fix the red-black tree
    void fixInsert(RBNode k);


    //Now we create functions to help check if the trees are being created correctly

    void prettyPrint();

    void preOrderHelper(RBNode node);

    void inOrderHelper(RBNode node);

    void postOrderHelper(RBNode node);

    void printHelper(RBNode root, std::string indent, bool last);

    // Pre-Order traversal
    // Node->Left Subtree->Right Subtree
    void preorder();

    // In-Order traversal
    // Left Subtree -> Node -> Right Subtree
    void inorder();

    // Post-Order traversal
    // Left Subtree -> Right Subtree -> Node
    void postorder();

    //---------------------------------------------------//
    std::string typeTree() override;

    size_t memoryUsage() override;

    size_t memoryUsageHelper(RBNode node);

    void test() override;

};
#endif //TAREA2_RBTREE_H
