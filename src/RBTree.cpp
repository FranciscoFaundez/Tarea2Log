//
// Created by admin on 04-06-2023.
//

#include <cassert>
#include "headers/RBTree.h"


RBNode RBTree::searchTreeHelper(RBNode node, int key) {
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

void RBTree::fixInsert(RBNode k) {
    RBNode u;
    while (k->parent->color == 1) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == 1) {
                // case 3.1
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    rightRotate(k);
                }
                // case 3.2.1
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if (u->color == 1) {
                // mirror case 3.1
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    leftRotate(k);
                }
                // mirror case 3.2.1
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = BLACK;
}

RBTree::RBTree() {
    TNULL = new Node;
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

bool RBTree::search(int k) {
    return searchTreeHelper(this->root, k);
}

void RBTree::leftRotate(RBNode x) {
    RBNode y = x->right;
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

void RBTree::rightRotate(RBNode x) {
    RBNode y = x->left;
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

void RBTree::insert(int key) {
    // Ordinary Binary Search Insertion
    auto node = new Node;
    node->parent = nullptr;
    node->key = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED; // new node must be red

    RBNode y = nullptr;
    RBNode x = this->root;

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
        node->color = BLACK;
        return;
    }

    // if the grandparent is null, return
    if (node->parent->parent == nullptr) {
        return;
    }

    // Fix the tree
    fixInsert(node);
}

void RBTree::prettyPrint() {
    if (root) {
        printHelper(this->root, "", true);
    }
}

void RBTree::preOrderHelper(RBNode node) {
    if (node != TNULL) {
        std::cout<<node->key<<" ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }
}

void RBTree::inOrderHelper(RBNode node) {
    if (node != TNULL) {
        inOrderHelper(node->left);
        std::cout<<node->key<<" ";
        inOrderHelper(node->right);
    }
}


void RBTree::postOrderHelper(RBNode node) {
    if (node != TNULL) {
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        std::cout<<node->key<<" ";
    }
}

void RBTree::printHelper(RBNode ptrRoot, std::string indent, bool last) {
    // print the tree structure on the screen
    if (ptrRoot != TNULL) {
        std::cout<<indent;
        if (last) {
            std::cout<<"R----";
            indent += "     ";
        } else {
            std::cout<<"L----";
            indent += "|    ";
        }

        std::string sColor = ptrRoot->color?"RED":"BLACK";
        std::cout<<ptrRoot->key<<"("<<sColor<<")"<<std::endl;
        printHelper(ptrRoot->left, indent, false);
        printHelper(ptrRoot->right, indent, true);
    }
}

void RBTree::preorder() {
    preOrderHelper(this->root);
}

void RBTree::inorder() {
    inOrderHelper(this->root);
}

void RBTree::postorder() {
    postOrderHelper(this->root);
}

size_t RBTree::memoryUsage() {
    return sizeof(RBTree) + memoryUsageHelper(root);
}

size_t RBTree::memoryUsageHelper(RBNode node) {
    if (node == TNULL) {
        return 0;
    }
    return sizeof(Node) + memoryUsageHelper(node->left) + memoryUsageHelper(node->right);
}

std::string RBTree::typeTree() {
    return "RBTree";
}

void RBTree::clearHelper(RBNode node) {
    if (node != RBTree::TNULL) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

void RBTree::clear() {
    clearHelper(root);
    root = TNULL;
}

void RBTree::test() {
    std::cout <<"############## TEST REDBLACKTREE ###############" << std::endl;
    RBTree rbt;

    std::cout << "Prueba de insertar elementos 1" << std::endl;
    std::cout << "8 18 5 15 17 " << std::endl;

    rbt.insert(8);
    rbt.insert(18);
    rbt.insert(5);
    rbt.insert(15);
    rbt.insert(17);

    rbt.prettyPrint();

    std::cout << "Prueba de insertar elementos 2" << std::endl;
    std::cout << "25 40 80" << std::endl;

    rbt.insert(25);
    rbt.insert(40);
    rbt.insert(80);

    rbt.prettyPrint();

    std::cout << "Buscando el valor 18" << std::endl;
    assert(rbt.search(18) && "Error: No se encontró el valor 18");
    std::cout << "Pasa\n" << std::endl;

    std::cout <<"Buscar valor que no esta en el arbol (50)" << std::endl;
    assert(!rbt.search(50) && "Error: dice que el valor se encuentra en el arbol.");
    std::cout << "Pasa\n" << std::endl;

    //Test to check if the tree is being deleted correctly
    std::cout << "Limpiamos el arbol" << std::endl;
    rbt.clear();
    rbt.prettyPrint();
    std::cout <<"################ END TEST #################" << std::endl;
}



