#include "SplayTree.h"

/**
* Constructor de la clase SplayTree.
*/
SplayTree::SplayTree() {
    root = -1;
    size = 0;
}
/**
 * Inserta un nuevo nodo con la clave dada en el árbol.
 * @param key La clave del nuevo nodo.
 */
void SplayTree::insert(int key) {
    if (root == -1) {
        nodes.push_back({key, -1, -1});
        root = 0;
        size++;
        return;
    }
    root = splay(root, key);
    if (nodes[root].key == key) {
        return;
    }
    int new_node = nodes.size();
    nodes.push_back({key, -1, -1});
    if (nodes[root].key > key) {
        nodes[new_node].left = nodes[root].left;
        nodes[new_node].right = root;
        nodes[root].left = -1;
    } else {
        nodes[new_node].right = nodes[root].right;
        nodes[new_node].left = root;
        nodes[root].right = -1;
    }
    root = new_node;
    size++;
}
/**
 * Busca un nodo con la clave dada en el árbol.
 * @param key La clave del nodo a buscar.
 * @return true si se encuentra el nodo, false en caso contrario.
 */
bool SplayTree::search(int key) {
    if (root == -1) {
        return false;
    }
    root = splay(root, key);
    return nodes[root].key == key;
}
/**
 * Elimina todos los nodos del árbol.
 */
void SplayTree::clear() {
    nodes.clear();
    root = -1;
    size = 0;
}
/**
 * Imprime las claves de los nodos en orden preorden.
 */
void SplayTree::print() {
    preOrder(root);
    std::cout << std::endl;
}
/**
 * Mide el uso en memoria del árbol.
 * @return El tamaño en bytes del árbol.
 */
int SplayTree::memoryUsage() {
    int total_size = 0;
    total_size += sizeof(root);
    total_size += sizeof(size);
    for (int i = 0; i < nodes.size(); i++) {
        total_size += sizeof(nodes[i].key);
        total_size += sizeof(nodes[i].left);
        total_size += sizeof(nodes[i].right);
    }
    total_size += sizeof(nodes);
    return total_size;
}
/**
 * Realiza una rotación a la derecha en el nodo dado.
 * @param x El índice del nodo a rotar.
 * @return El índice del nuevo nodo raíz.
 */
int SplayTree::rightRotate(int x) {
    int y = nodes[x].left;
    nodes[x].left = nodes[y].right;
    nodes[y].right = x;
    return y;
}
/**
 * Realiza una rotación a la izquierda en el nodo dado.
 * @param x El índice del nodo a rotar.
 * @return El índice del nuevo nodo raíz.
 */
int SplayTree::leftRotate(int x) {
    int y = nodes[x].right;
    nodes[x].right = nodes[y].left;
    nodes[y].left = x;
    return y;
}
/**
 * Realiza la operación Splay en el árbol con la clave dada.
 * @param node El índice del nodo raíz del árbol.
 * @param key La clave del nodo a buscar.
 * @return El índice del nuevo nodo raíz.
 */
int  SplayTree::splay(int node, int key) {
    if (node == -1 || nodes[node].key == key) {
        return node;
    }
    if (nodes[node].key > key) {
        if (nodes[node].left == -1) {
            return node;
        }
        if (nodes[nodes[node].left].key > key) {
            nodes[node].left = splay(nodes[node].left, key);
            node = rightRotate(node);
        } else if (nodes[nodes[node].left].key < key) {
            nodes[nodes[node].left].right = splay(nodes[nodes[node].left].right, key);
            if (nodes[nodes[node].left].right != -1) {
                nodes[node].left = leftRotate(nodes[node].left);
            }
        }
        return (nodes[node].left == -1) ? node : rightRotate(node);
    } else {
        if (nodes[node].right == -1) {
            return node;
        }
        if (nodes[nodes[node].right].key > key) {
            nodes[nodes[node].right].left = splay(nodes[nodes[node].right].left, key);
            if (nodes[nodes[node].right].left != -1) {
                nodes[node].right = rightRotate(nodes[node].right);
            }
        } else if (nodes[nodes[node].right].key < key) {
            nodes[node].right = splay(nodes[node].right, key);
            node = leftRotate(node);
        }
        return (nodes[node].right == -1) ? node : leftRotate(node);
    }
}
/**
 * Imprime las claves de los nodos en orden preorden.
 * @param node El índice del nodo raíz del árbol.
 */
void SplayTree::preOrder(int node) {
    if (node != -1) {
        std::cout << nodes[node].key << " ";
        preOrder(nodes[node].left);
        preOrder(nodes[node].right);
    }
}

int main() {
    SplayTree tree;

    tree.insert(100);
    tree.insert(50);
    tree.insert(200);
    tree.insert(40);
    tree.insert(30);
    tree.insert(60);
    tree.insert(55);
    tree.insert(150);
    tree.insert(300);

    tree.print();

    std::cout << tree.search(55) << std::endl;
    std::cout << tree.search(175) << std::endl;

    std::cout << "Memory usage: " << tree.memoryUsage() << " bytes" << std::endl;

    tree.clear();

    return 0;
}
