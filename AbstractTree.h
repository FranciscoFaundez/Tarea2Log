#ifndef ABSTRACT_TREE_H
#define ABSTRACT_TREE_H

class AbstractTree {
public:
    virtual void insert(int valor) = 0;
    virtual bool search(int valor) = 0;
    virtual void clear(int valor) = 0;
    virtual int memoryUsage() = 0;
};

#endif
