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
    void* TreeDS;
    int Segments;
public:
    explicit  ImageTagger(int segments) {
        Segments=segments;
        TreeDS=Init_Tree();
        if(!TreeDS) throw;
    }

void* getTree () {
    return TreeDS;
    };
int getSegments () {
    return Segments;
}

    StatusType AddImage(int image_id) {
        void* node;
        void* img;
        Image *image = new Image(Segments);
        if(Find_Tree(TreeDS,image_id,&img)==SUCCESS)
            return FAILURE;
        return   Add_Tree(TreeDS,image_id,(void*)image,&node);

    }

    StatusType DeleteImage(int image_id) {
        void* image;
        if(Find_Tree(TreeDS,image_id,&image)!=SUCCESS)
            return FAILURE;
        ((Image*)image)->Delete_All_Labels();
        delete ((Image*)image);
        return Delete_Tree(TreeDS,image_id);
    }

    StatusType AddLabel (int imageID, int segmentID, int label) {
        if(segmentID>=Segments)
            return FAILURE;
        void* image;
        if(Find_Tree(TreeDS,imageID,&image)!=SUCCESS)
            return FAILURE;
        return  ((Image*)image)->AddLabel(segmentID,label);
    }


    StatusType getLabel  (int imageID, int segmentID, int* label) {
        if(segmentID>=Segments)
            return FAILURE;
        void *image;
        if (Find_Tree(TreeDS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->getLabel(segmentID, label);
    }

    StatusType DeleteLabel (int imageID, int segmentID) {
        if(segmentID>=Segments)
            return FAILURE;
        void *image;
        if (Find_Tree(TreeDS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->DeleteLabel(segmentID);
    }

    StatusType GetAllUnLabeledSegments ( int imageID, int **segments, int *numOfSegments) {

        void *image;
        if (Find_Tree(TreeDS, imageID, &image) != SUCCESS)
            return FAILURE;
        return ((Image *) image)->GetAllUnLabeledSegments(segments,numOfSegments);
    }

    //function for freeing the Data Structure
    void Quit_Tagger() {
        DeleteTree(TreeDS);
        Quit_Tree(&TreeDS);
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
        if(value!= nullptr) {
            ((Image *) value)->Delete_All_Labels(); // deleting the image->segments
            delete (Image *) value; // free image
        }
    }

    StatusType GetAllSegments(void *DS, int label, int **images, int **segments, int *numOfSegments){
        int segnum=0;
        auto root = static_cast<Tree<int>*>(TreeDS);
        root=root->getLeft();
        getnumOfSegments(root,label,&segnum);
        if(segnum==0) {
            *images= nullptr;
            *segments= nullptr;
            *numOfSegments=0;
            return SUCCESS;

        }
        int* imgs=(int*)malloc(sizeof(int)*(segnum));
        if(!imgs)
            return ALLOCATION_ERROR;
        int *seg=(int*)malloc(sizeof(int)*(segnum));
        if(!seg) {
            free(imgs);
            return ALLOCATION_ERROR;
        }
        int count=0;
        insertLabels(root,label,imgs,seg,&count);
        *numOfSegments=segnum;
        *images=imgs;
        *segments=seg;
        return SUCCESS;
    }


    void getnumOfSegments(void* DS ,int label ,int *numOfSegments) {
        //casting the DataStructure to Tree class
        auto root = static_cast<Tree<int>*>(DS);

        if ( root== nullptr) return ;

        if (root->getLeft()) {
            getnumOfSegments(root->getLeft(),label,numOfSegments);
        }
        auto image = static_cast<Image*>(root->getValue());
        int** ptr=(int**)image->getSegmentsPtr();
        for(int i =0 ; i < image->getSegments() ; i++ ) {
            if((ptr[i]) != nullptr ){
                if(*ptr[i]==label) (*(numOfSegments))++;
            }
        }


        if (root->getRight()) {
            getnumOfSegments(root->getRight(),label,numOfSegments);
        }
    }


    void insertLabels(void *DS, int label, int *images, int *segments, int* count) {
        //casting the DataStructure to Tree class
        auto root = static_cast<Tree<int>*>(DS);

        if ( root== nullptr) return ;

        if (root->getLeft()) {
            insertLabels(root->getLeft(),label,images,segments,count);
        }
        auto image = static_cast<Image*>((void*)root->getValue());
        int** ptr=(int**)image->getSegmentsPtr();
        for(int i =0 ; i < image->getSegments() ; i++ ) {
            if((ptr[i]) != nullptr ){
                if(*ptr[i]==label) {
                    (images[*count]) = root->getKey();
                    (segments[*count]) = i;
                    (*count)++;
                }
            }
        }


        if (root->getRight()) {
            insertLabels(root->getRight(),label,images,segments,count);
        }
    }

};


#endif //HW2_LIBRARY_IMAGETAGGER_H
