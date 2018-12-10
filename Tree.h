//
// Created by baha2 on 03-Dec-18.
//

#include "stdio.h"
#include <iostream>     // std::cout
#include <new>          // std::bad_alloc

#ifndef HW2_TREE_TREE_H
#define HW2_TREE_TREE_H


typedef void* Data;

template <class T>
T& max(T a, T b) {
    return a > b ? a : b ;
}

template<class T>
class Tree {
    int height;
    T key;
    Data valuePtr= nullptr;
    Tree *father= nullptr;
    Tree *leftSon= nullptr;
    Tree *rightSon= nullptr;
public:
    explicit Tree(const T &key, Data value, Tree *father) : height(0), key(key), valuePtr(value),
                                                            father(father) {}

    T &getKey() {
        return key;
    }

    Data getValue() {
        return valuePtr;
    }

    Tree *getLeft() {
        return leftSon;
    }

    Tree *getRight() {
        return rightSon;
    }

    Tree *getFather() {
        return father;
    }

    void setLeft(Tree *left) {
        leftSon = left;
    }

    void setRight(Tree *right) {
        rightSon = right;
    }

    void setFather(Tree *father) {
        this->father = father;
    }

    int getHeight() {
        if (!this) {
            return -1;//because tree is empty
        }
        return height;
    }

    void setHeight(int newHeight) {
        height = newHeight;
    }

    int size;

};

#endif //HW2_TREE_TREE_H
