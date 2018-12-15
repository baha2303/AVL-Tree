//
// Created by baha2 on 04-Dec-18.
//

#ifndef HW2_LIBRARY_IMAGE_H
#define HW2_LIBRARY_IMAGE_H

#include "library1LL.h"
#include "List.h"    // for the segments unlabbeled linked list
#include <iostream>
#include <new>
class Image {
    void** SegmentsPtr;
    int* segmentsvalues;
    void* Unlabeled;
    int segments;

public:
    explicit  Image(int Segments) {
        SegmentsPtr = new void*[Segments];
        segmentsvalues=new int[Segments];
        for(int i=0;i<Segments;i++) {
            SegmentsPtr[i]= nullptr;
        }
        Unlabeled = Init_LL();
        void* node;
        for (int i = 0; i < Segments; i++) {
            Add(Unlabeled, i, nullptr, &node);
        }
        segments=Segments;
    }
    int getSegments () {
        return segments;
    }
    void **getSegmentsPtr () {
        return SegmentsPtr;
    }

    void Delete_All_Labels () {
        Quit_LL(&Unlabeled);
        delete[] SegmentsPtr;
        delete[] segmentsvalues;
    }

    StatusType AddLabel( int segmentID, int label) {
        void *value;

        if (Find(Unlabeled, segmentID, &value) != SUCCESS)
            return FAILURE;
        SegmentsPtr[segmentID]=&segmentsvalues[segmentID];
        segmentsvalues[segmentID]=label;
        Delete(Unlabeled,segmentID);
        return SUCCESS;
    }

    StatusType getLabel (int segmentID, int* label) {
        if(SegmentsPtr[segmentID]== nullptr)
            return FAILURE;
        *label=segmentsvalues[segmentID];
        return SUCCESS;
    }

    StatusType DeleteLabel(int segmentID) {

        if(SegmentsPtr[segmentID]== nullptr)
            return FAILURE;

       SegmentsPtr[segmentID]= nullptr;
       void *node;
        return  Add(Unlabeled,segmentID, nullptr,&node);

    }


    StatusType GetAllUnLabeledSegments (int **segments, int *numOfSegments) {

        Size(Unlabeled,numOfSegments) ;

        if(*numOfSegments==0) {
            *segments= nullptr;
            return FAILURE;
        }

        int size=*numOfSegments;

        int  *seg = (int*)std::malloc(size * sizeof(int));
        if(!(seg))
            return ALLOCATION_ERROR;

        int i=0;
        int key;
        for(void* head=getHead<int>(Unlabeled) ; head != nullptr ; head=getNext<int>(head)  ) {


            key=getnodeKey<int>(head);
            (seg[i])=key;
            i++;
        }
        *segments=seg;
        return SUCCESS;

    }


};

#endif //HW2_LIBRARY_IMAGE_H
