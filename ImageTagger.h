//
// Created by baha2 on 03-Dec-18.
//

#ifndef HW2_LIBRARY_IMAGETAGGER_H
#define HW2_LIBRARY_IMAGETAGGER_H

#include <iostream>     // std::cout
#include <new>          // std::bad_alloc
#include "Image.h"
#include "library1Tree.h"
#include "Tree.h"



// class containing a ptr array for every segment's data and a linked list for unlabbeled segments.
class ImageTagger {
    void* DS;
    int Segments;

public:
    explicit  ImageTagger(int segments) {
        Segments=segments;
        DS=Init_Tree();
        if(!DS) throw;
    }
int getSegments () {
    return Segments;
}

    StatusType AddImage(int image_id) {
        void* node;
        Image *image = new Image(Segments);

        return   Add_Tree(DS,image_id,(void*)image,&node);

    }

    StatusType DeleteImage(int image_id) {
        void* image;
        Find_Tree(DS,image_id,&image);
        ((Image*)image)->Delete_All_Labels();
        delete ((Image*)image);
        return Delete_Tree(DS,image_id);
    }

    StatusType AddLabel (int imageID, int segmentID, int label) {
        void* image;
        if(Find_Tree(DS,imageID,&image)!=SUCCESS)
            return FAILURE;
        return  ((Image*)image)->AddLabel(segmentID,label);
    }


    StatusType getLabel  (int imageID, int segmentID, int* label) {
        void *image;
        if (Find_Tree(DS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->getLabel(segmentID, label);
    }

    StatusType DeleteLabel (int imageID, int segmentID) {
        void *image;
        if (Find_Tree(DS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->DeleteLabel(segmentID);
    }

    StatusType GetAllUnLabeledSegments ( int imageID, int **segments, int *numOfSegments) {

        void *image;
        if (Find_Tree(DS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->GetAllUnLabeledSegments(segments,numOfSegments);
    }

    //function for freeing the Data Structure
    void Quit_Tagger() {
        DeleteTree(DS);
        Quit_Tree(&DS);
    }

    // recursive function iterating preorder on tree and freeing every value in it's route.
    void DeleteTree(void* DS) {
        //casting the DataStructure to Tree class
        auto root = static_cast<Tree<int>*>(DS);

        if ( root== nullptr) return ;

        if (root->getLeft()) {
            DeleteTree(root->getLeft());
        }
        if (root->getRight()) {
            DeleteTree(root->getRight());
        }

        void* value = root->getValue(); // getting a pointer to each node's value (Image class)
        ((Image*)value)->Delete_All_Labels(); // deleting the image->segments
        delete (Image*)value; // free image
    }

    StatusType GetAllSegments(void *DS, int label, int **images, int **segments, int *numOfSegments){
        getnumOfSegments(DS,label,numOfSegments);
        *images=(int*)malloc(sizeof(int)*(*numOfSegments));
        if(!*images)
            return ALLOCATION_ERROR;
        *segments=(int*)malloc(sizeof(int)*(*numOfSegments));
        if(!*segments) {
            free(*images);
            return ALLOCATION_ERROR;
        }
        insertLabels(DS,label,images,segments,0);
        return SUCCESS;
    }


    void getnumOfSegments(void* DS ,int label ,int *numOfSegments) {
        //casting the DataStructure to Tree class
        auto root = static_cast<Tree<int>*>(DS);

        if ( root== nullptr) return ;

        if (root->getLeft()) {
            getnumOfSegments(root->getLeft(),label,numOfSegments);
        }
        auto image = static_cast<Image*>((void*)root);
        int** ptr=(int**)image->getSegmentsPtr();
        for(int i =0 ; i < image->getSegments() ; i++ ) {
            if(*(ptr[i]) == label ){
                (*(numOfSegments))++;
            }
        }


        if (root->getRight()) {
            getnumOfSegments(root->getRight(),label,numOfSegments);
        }
    }


    void insertLabels(void *DS, int label, int **images, int **segments, int count) {
        //casting the DataStructure to Tree class
        auto root = static_cast<Tree<int>*>(DS);

        if ( root== nullptr) return ;

        if (root->getLeft()) {
            insertLabels(root->getLeft(),label,images,segments,count);
        }
        auto image = static_cast<Image*>((void*)root);
        int** ptr=(int**)image->getSegmentsPtr();
        for(int i =0 ; i < image->getSegments() ; i++ ) {
            if(*(ptr[i]) == label ){
                *(images[count])=root->getKey();
                *(segments[count])=i;
                count++;
            }
        }


        if (root->getRight()) {
            insertLabels(root->getRight(),label,images,segments,count);
        }
    }

};


#endif //HW2_LIBRARY_IMAGETAGGER_H
