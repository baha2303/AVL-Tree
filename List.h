//
// Created by baha2 on 01-Dec-18.
//

#ifndef HW2_LIBRARY_HW2LIST_H
#define HW2_LIBRARY_HW2LIST_H
typedef void *data;

template<class T>
class Node {
    T key;
    data valuePtr;
    Node *next;
public:
    int size;

    explicit Node(const T &key, data value, Node *nextNode) : key(key), valuePtr(value), next(nextNode) {}

    T &getKey() {
        return key;
    }

    data getValue() {
        return valuePtr;
    }

    Node* getNext() {
        return next;
    }
    void setNext(Node* nextNode){
        next=nextNode;
    }



};

template <class T>
void* getNext( void *node ) {
    return ((Node<T>*)node)-> getNext();
}

template <class T>
void* getHead(void *DS) {
    return ((Node<T>*)DS)->getNext();
}

template <class T>
void* getnodeValue(void *node) {
    return ((Node<T>*)node)->getValue();
}

template <class T>
T& getnodeKey(void *node) {
    return ((Node<T>*)node)->getKey();
}
#endif //HW2_LIBRARY_HW2LIST_H
