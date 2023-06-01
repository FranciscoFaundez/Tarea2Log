#ifndef SPLAYTREE_H
#define SPLAYTREE_H

struct SplayNode {
	int key; 
	SplayNode *left; // pointer to left child
	SplayNode *right; // pointer to right child
};

class SplayTree{

    public:
    SplayNode* root;

    SplayNode* rightRotate(SplayNode* k2);
    SplayNode* leftRotate(SplayNode *k2);
    SplayNode* Splay(int key, SplayNode* root);
    SplayNode* New_Node(int key);
    SplayNode* Insert(int key, SplayNode* root);
    SplayNode* Search(int key, SplayNode* root);
    void InOrder(SplayNode* root);

};

#endif