#ifndef RBTREE_H
#define RBTREE_H

using namespace std;

struct Node {
	int key; 
	Node *parent; 
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	int color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

class RBTree {

public:
	NodePtr root;
	NodePtr TNULL;

    NodePtr searchTreeHelper(NodePtr node, int key);
    void rbTransplant(NodePtr u, NodePtr v);
    void fixInsert(NodePtr k);
    RBTree();
    NodePtr search(int k);
    NodePtr minimum(NodePtr node);
    NodePtr maximum(NodePtr node);
    NodePtr successor(NodePtr x);
    NodePtr predecessor(NodePtr x);
    void leftRotate(NodePtr x);
    void rightRotate(NodePtr x);
    void insert(int key);
    void prettyPrint();
    void printHelper(NodePtr root, string indent, bool last);
    void deleteTree(Node* raiz);
    void deleteCompleteTree();

};
#endif