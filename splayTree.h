#ifndef SPLAYTREE_H_INCLUDED
#define SPLAYTREE_H_INCLUDED

#include <iostream>
#include <vector>
#include "AbstractTree.h"

struct SplayNode {
    int key;
    int left, right;
};

class SplayTree : public AbstractTree{
public:
    /**
     * Constructor de la clase SplayTree.
     */
    SplayTree();

    /**
     * Inserta un nuevo nodo con la clave dada en el árbol.
     * @param key La clave del nuevo nodo.
     */
    void insert(int key) override;

    /**
     * Busca un nodo con la clave dada en el árbol.
     * @param key La clave del nodo a buscar.
     * @return true si se encuentra el nodo, false en caso contrario.
     */
    bool search(int key) override;

    /**
     * Elimina todos los nodos del árbol.
     */
    void clear() override;

    /**
     * Imprime las claves de los nodos en orden preorden.
     */
    void print();

    /**
     * Mide el uso en memoria del árbol.
     * @return El tamaño en bytes del árbol.
     */
    int memoryUsage() override;

private:
    int root, size;
    std::vector<SplayNode> nodes;

    /**
     * Realiza una rotación a la derecha en el nodo dado.
     * @param x El índice del nodo a rotar.
     * @return El índice del nuevo nodo raíz.
     */
    int rightRotate(int x);

    /**
     * Realiza una rotación a la izquierda en el nodo dado.
     * @param x El índice del nodo a rotar.
     * @return El índice del nuevo nodo raíz.
     */
    int leftRotate(int x);

    /**
     * Realiza la operación Splay en el árbol con la clave dada.
     * @param node El índice del nodo raíz del árbol.
     * @param key La clave del nodo a buscar.
     * @return El índice del nuevo nodo raíz.
     */
    int splay(int node, int key);

    /**
     * Imprime las claves de los nodos en orden preorden.
     * @param node El índice del nodo raíz del árbol.
     */
    void preOrder(int node);
};

#endif // SPLAYTREE_H_INCLUDED
