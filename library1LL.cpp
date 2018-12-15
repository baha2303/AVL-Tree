//
// Created by baha2 on 27-Nov-18.
//
// typedef class Node Node;
#include <new>
#include "library1LL.h"
#include "stdio.h"
#include "List.h"


/* Description:   Initiates the data structure.
 * Input:         None.
 * Output:        DS - A pointer to the data structure.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void *Init_LL() {
    try {
        Node<int> *DS = new Node<int>(0, nullptr, nullptr);
        DS->size = 0;
        return (void*)DS;
    }
    catch (std::bad_alloc &) {
        return nullptr;
    }


}

/* Description:   Adds a new item to the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The key to add.
 *                value - A pointer to the value to add.
 				  node - A pointer to a place which will hold a pointer to the new node in the DS.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType Add(void *DS, int key, void *value, void **node) {
    if (!DS || !node) {
        return INVALID_INPUT;
    }
    auto head = static_cast<Node<int> *>(DS);

    try {

        Node<int> *newNode = new Node<int>(key, value, head->getNext());
        head->setNext(newNode);
        *node = newNode;
        head->size++;
        return SUCCESS;
    } catch (std::bad_alloc &bad) {
        return ALLOCATION_ERROR;
    }

}


/* Description:   Finds an item in the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to find.
 * Output:        value - a pointer to a variable which will contain the value of the element.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - If the item is found in the DS.
 */
StatusType Find(void *DS, int key, void **value) {
    if (!value || !DS) {
        return INVALID_INPUT;
    }

    auto curr = static_cast<Node<int> *>(DS);
    curr = curr->getNext();
    while (curr) {
        if (curr->getKey() == key) {
            *value = (curr->getValue());
            return SUCCESS;
        }
        curr = curr->getNext();//go to the next node
    }
    return FAILURE;

}

StatusType Delete(void *DS, int key) {
    if (!DS) {
        return INVALID_INPUT;
    }

    auto prev = static_cast<Node<int> *>(DS);
    Node<int> *curr = prev->getNext();
    while (curr) {
        if (curr->getKey() == key) {
            prev->setNext(curr->getNext());
            delete curr;
            auto head = static_cast<Node<int> *>(DS);
            head->size--;
            return SUCCESS;
        }
        prev = curr;
        curr = curr->getNext();//go to the next node
    }
    return FAILURE;
}


/* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                p - A pointer to the node to delete.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType DeleteByPointer(void *DS, void *p) {

    auto node = static_cast<Node<int> *>(p);
    return Delete(DS, node->getKey());

}

/* Description:   Returns the current number of items in the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        n - A pointer to a variable that should be updated to the number of items in the data structure.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                SUCCESS - Otherwise.
 */
StatusType Size(void *DS, int *n) {
    if (!DS || !n)
        return INVALID_INPUT;


    auto head = static_cast<Node<int> *>(DS);
    *n = head->size;
    return SUCCESS;
}

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit_LL(void **DS) {

    auto head = static_cast<Node<int> *>(*DS);
    while (head->getNext()) {
        DeleteByPointer(head, head->getNext());

    }
    delete head;
    *DS = nullptr;
}
