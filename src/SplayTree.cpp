//
// Created by admin on 04-06-2023.
//

#include <cassert>
#include "headers/SplayTree.h"


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
size_t SplayTree::memoryUsage() {
    int total_size = 0; // Inicializa la variable total_size a cero.
    total_size += sizeof(root); // Agrega el tamaño en bytes del atributo root al total.
    total_size += sizeof(size); // Agrega el tamaño en bytes del atributo size al total.
    for (auto & node : nodes) { // Recorre el vector de nodos nodes.
        total_size += sizeof(node.key); // Agrega el tamaño en bytes del atributo key de cada nodo al total.
        total_size += sizeof(node.left); // Agrega el tamaño en bytes del atributo left de cada nodo al total.
        total_size += sizeof(node.right); // Agrega el tamaño en bytes del atributo right de cada nodo al total.
    }
    total_size += sizeof(nodes); // Agrega el tamaño en bytes del vector nodes al total.
    return total_size; // Retorna el tamaño total en bytes del árbol.
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

std::string SplayTree::typeTree() {
    return "SplayTree";
}

void SplayTree::test() {
    std::cout <<"############## TEST SPLAYTREE ###############" << std::endl;
    SplayTree st;

    std::cout << "Prueba de insertar elementos 1" << std::endl;
    std::cout << "4 5 1 2 8" << std::endl;
    st.insert(4);
    st.insert(5);
    st.insert(1);
    st.insert(2);
    st.insert(8);

    st.print(); // print
    std::cout << "Prueba de insertar elementos 2" << std::endl;
    std::cout << "10 11 3" << std::endl;
    st.insert(10);
    st.insert(11);
    st.insert(3);

    st.print(); // print

    std::cout << "Buscando el valor 10" << std::endl;
    assert(st.search(10) && "Error: No se encontró el valor 10");
    std::cout << "Pasa\n" << std::endl;

    //Search for non-existing node
    std::cout <<"Buscar valor que no esta en el arbol (50)" << std::endl;
    assert(!st.search(50) && "Error: dice que el valor se encuentra en el arbol.");
    std::cout << "Pasa\n" << std::endl;

    //Clear the tree
    std::cout << "Limpiamos el arbol" << std::endl;
    st.clear();
    st.print(); //print
    std::cout <<"################ END TEST #################" << std::endl;
}


