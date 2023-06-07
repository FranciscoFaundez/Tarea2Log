#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;
using uint = long long;

// key structure that represents a node in the tree
struct Node {
	uint key;
	Node *parent; 
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	bool color; // 1 -> Red, 0 -> Black
};

typedef Node *NodePtr;

// class RBTree implements the operations in Red Black Tree
class RBTree {

public:
	NodePtr root;
	NodePtr TNULL;

	// initializes the nodes with appropirate values
	// all the pointers are set to point to the null pointer

	NodePtr searchTreeHelper(NodePtr node, uint key) {
		if (node == TNULL || key == node->key) {

			if (node->key == key) {
        		return node;
    		}else{
			return nullptr;
			}
		}

		if (key < node->key) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	
	// fix the red-black tree
	void fixInsert(NodePtr k){
		NodePtr u;
		while (k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 3.1
					u->color = false;
					k->parent->color = false;
					k->parent->parent->color = true;
					k = k->parent->parent;
				} else {
					if (k == k->parent->left) {
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = false;
					k->parent->parent->color = true;
					leftRotate(k->parent->parent);
				}
			} else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {
					// mirror case 3.1
					u->color = false;
					k->parent->color = false;
					k->parent->parent->color = true;
					k = k->parent->parent;	
				} else {
					if (k == k->parent->right) {
						// mirror case 3.2.2
						k = k->parent;
						leftRotate(k);
					}
					// mirror case 3.2.1
					k->parent->color = false;
					k->parent->parent->color = true;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = false;
	}

	
	RBTree() {
		TNULL = new Node;
		TNULL->color = false;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
	}


	// search the tree for the key k
	// and return the corresponding node
	NodePtr search(uint k) {
		return searchTreeHelper(this->root, k);
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// insert the key to the tree in its appropriate position
	// and fix the tree
	void insert(uint key) {
		// Ordinary Binary Search Insertion
		NodePtr node = new Node;
		node->parent = nullptr;
		node->key = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = true; // new node must be red

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) {
			y = x;
			if (node->key < x->key) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->key < y->key) {
			y->left = node;
		} else {
			y->right = node;
		}

		// if new node is a root node, simply return
		if (node->parent == nullptr){
			node->color = false;
			return;
		}

		// if the grandparent is null, return
		if (node->parent->parent == nullptr) {
			return;
		}

		// Fix the tree
		fixInsert(node);
	}
	//-----------------------------------------------------//

	//Now we create functions to delete the Tree
	void deleteTree(Node* raiz) {
		if (raiz == nullptr) {
			return;
		}
		deleteTree(root->left);
		deleteTree(root->right);
		delete raiz;
	}

	void deleteCompleteTree() {
        deleteTree(root);
        root = nullptr;
    }


	//---------------------------------------------------//
	//Now we create functions to help check if the trees are being created correctly

	void prettyPrint() {
	    if (root) {
    		printHelper(this->root, "", true);
	    }
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != TNULL) {
		   cout<<indent;
		   if (last) {
		      cout<<"R----";
		      indent += "     ";
		   } else {
		      cout<<"L----";
		      indent += "|    ";
		   }
            
           string sColor = root->color?"RED":"BLACK";
		   cout<<root->key<<"("<<sColor<<")"<<endl;
		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

    void fillRB(uint N0, uint N) {
        for (uint i = N0; i < N; ++i) {
            this->insert(i+1);
        }
    }

    static size_t memoryUsage(Node* node){
        if(!node){
            return 0;
        }
        return sizeof(&node) + memoryUsage(node->left) + memoryUsage(node->right);
    }

};
/*
int main() {
	RBTree bst;

	Node* test = NULL;
	bst.insert(8);
	bst.insert(18);
	bst.insert(5);
	bst.insert(15);
	bst.insert(17);
	bst.insert(25);
	bst.insert(40);
	bst.insert(80);
	test = bst.search(18);
	cout << "Nodo buscado (deberia ser 18): " << test->key << endl;

	//Buscar nodo que no está en el árbool
	test = bst.search(50);
	if (test == NULL){
		cout << "Nodo no encontrado " << endl;
	}
	else{
		cout << "Nodo buscado : " << test->key << endl;
	}


	bst.prettyPrint();

	//Test to check if the tree is being deleted correctly
	bst.deleteCompleteTree();
	bst.prettyPrint();
	
	return 0;
}

*/