//
// Created by admin on 04-06-2023.
//

#ifndef TAREA2_ABSTRACTTREE_H
#define TAREA2_ABSTRACTTREE_H

#include <iostream>
#include <string>

class AbstractTree {
public:
    virtual void insert(int valor) = 0;

    virtual bool search(int valor) = 0;

    virtual void clear() = 0;

    virtual size_t memoryUsage() = 0;

    virtual std::string typeTree() = 0;

    virtual void test() = 0;
};



#endif //TAREA2_ABSTRACTTREE_H
