#include <iostream>
#include <new>
#include <assert.h>
#include <stdio.h>
#include "library1Tree.h"
#include <string.h>
#include "Tree.h"
using std::string;
using std::cout;


int main() {
    std::string name1 = "muhannad";
    std::string name2 = "muhanna";
    std::string name3 = "muhann";
    std::string name4 = "muhan";
    std::string name5 = "muha";
    std::string name6 = "muh";
    std::string name7 = "mu";
    std::string name8 = "m";
    void* node1;
    void* node2;
    void* node3;
    void* node4;
    void* node5;
    void* node6;
    void* node7;
    void* node8;
    void* DS = Init_Tree();

    Add_Tree(DS,4,&name4,&node4);
    Add_Tree(DS,1,&name1,&node1);
    //  Add_Tree(DS,2,&name2,&node2);
    Add_Tree(DS,3,&name3,&node3);
    //   Add_Tree(DS,5,&name5,&node5);
//    Add_Tree(DS,6,&name6,&node6);
//    Add_Tree(DS,7,&name7,&node7);
//    Add_Tree(DS,8,&name8,&node8);
    auto head = static_cast<Tree<int> *>(node4);
    cout<<"*"<< head->getKey()<< "*"<<std::endl;
    cout<<"*"<< head->getHeight()<< "*"<<std::endl;
    //  Delete_Tree(DS,5);
    // Delete_Tree(DS,8);
    // Delete_Tree(DS,2);
    // Delete_Tree(DS,1);
    //Delete_Tree(DS,5);
    PrintTree(DS);

    return 0;
}
Hello
