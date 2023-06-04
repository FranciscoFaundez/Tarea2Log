#include "RBTree.h"

void RedBlackTree::leftRotate(RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } 
    else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;

    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root = y;
    } 
    else if (x == x->parent->left) {
        x->parent->left = y;
    } 
    else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(RBNode *z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } 
        else {
            RBNode *y = z->parent->parent->left;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}

RBNode* RedBlackTree::insert(RBNode *root, RBNode *z) {
    RBNode *y = nullptr;
    RBNode *x = root;

    while (x != nullptr) {
        y = x;

        if (z->key < x->key) {
            x = x->left;
        } 
        else {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr) {
        root = z;
    } 
    else if (z->key < y->key) {
        y->left = z;
    } 
    else {
        y->right = z;
    }

    fixInsert(z);

    return root;
}

void RedBlackTree::preOrder(RBNode *root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void RedBlackTree::clear(RBNode *root) {
    if (root != nullptr) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

int RedBlackTree::memoryUsage(RBNode *root) {
    if (root == nullptr) {
        return 0;
    }
    int size = sizeof(*root);
    size += memoryUsage(root->left);
    size += memoryUsage(root->right);
    return size;
}


RedBlackTree::RedBlackTree() {
    root = nullptr;
}

/**
 * Inserta un nuevo nodo con la clave dada en el árbol.
 * @param key La clave del nuevo nodo.
 */
void RedBlackTree::insert(int key) {
    RBNode *z = new RBNode(key);
    root = insert(root, z);
}

/**
 * Imprime las claves de los nodos en orden preorden.
 */
void RedBlackTree::print() {
    preOrder(root);
    cout << endl;
}

/**
 * Elimina todos los nodos del árbol.
 */
void RedBlackTree::clear() {
    clear(root);
    root = nullptr;
}

/**
 * Mide el uso en memoria del árbol.
 * @return El tamaño en bytes del árbol.
 */
int RedBlackTree::memoryUsage() {
    return memoryUsage(root);
}

int main() {
    RedBlackTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    tree.print();
    std::cout << "Memory usage: " << tree.memoryUsage() << " bytes" << std::endl;

    tree.clear();

    return 0;
}
