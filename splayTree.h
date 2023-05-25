#ifndef SPLAYTREE_H
#define SPLAYTREE_H

struct Node {
	int key; 
	Node *parent; 
	Node *left; // pointer to left child
	Node *right; // pointer to right child
};

class SplayTree{

    public:
    Node* Root;

    Node* rightRotate(Node* k2);
    Node* leftRotate(Node *k2);
    Node* Splay(int key, Node* root);
    Node * New_Node(int key);
    Node *Insert(int key, Node* root);
    Node* Search(int key, Node* root);
    void InOrder(Node* root);

};

#endif