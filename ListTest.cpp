#include <iostream>
#include <new>
#include "library1LL.h"
#include "stdio.h"
#include "assert.h"
int main() {
    std::cout << "Testing..." << std::endl;
    void* DS = Init();
    if(!DS) {
        std::cout << "Init Failed" << std::endl;
    }
    std::cout << "Init Success" << std::endl;
    int sum[10];

    void* node[10];
    for(int i = 1 ; i<10 ; i++) {
        sum[i]=i;
        if (Add(DS, i , sum+i, node+i) == SUCCESS) {
            std::cout << "Add key&value of -" << i << "-  Success";
            std::cout << " Pointer to node " << i << " = " << node[i] <<  std::endl;
        } else {
            std::cout << "Init Failed !!!" << std::endl;
            return FAILURE;
        }
    }
    void* value;
    if(Find(DS,5,&value)==SUCCESS && *(int*)value == 5 ) {
        std::cout << "Find 5  Success" << std::endl;
    } else {
        std::cout << "Find 5 Failed" << std::endl;
    }

    if(Find(DS,8,&value)==SUCCESS && *(int*)value == 8 ) {
        std::cout << "Find 8 Success" << std::endl;
    } else {
        std::cout << "Find 8 Failed" << std::endl;
    }

    if(Delete(DS,8) != SUCCESS) {
        std::cout << "Delete 8 Failed" << std::endl;
        return FAILURE;
    } else {
        std::cout << "Delete 8 Success" << std::endl;

    }
    if(Find(DS,8,&value)==SUCCESS && *(int*)value == 8 ) {
        std::cout << "Find 8 Success" << std::endl;
    } else {
        std::cout << "8 Not found " << std::endl;
    }

    if(DeleteByPointer(DS,node[4]) != SUCCESS) {
        std::cout << "Delete 4 Failed" << std::endl;
        return FAILURE;
    } else {
        std::cout << "Delete 4 Success" << std::endl;

    }
    if(Find(DS,4,&value)==SUCCESS && *(int*)value == 4 ) {
        std::cout << "Find 4 Success" << std::endl;
    } else {
        std::cout << "4 Not found " << std::endl;
    }

    int * size;
    if(Size(DS,size) == SUCCESS ) {
        std::cout << "size is  " << *size << std::endl;
    }
    else
        std::cout << "Size function failed!! " << std::endl;

    Quit(&DS);
    if(DS) {
        return -1;
    }
    else
        return 0;

}