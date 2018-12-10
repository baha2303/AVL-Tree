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
    void* Unlabeled;
    int segments;

public:

    explicit  Image(int Segments) {
        SegmentsPtr = new  void*[Segments];
        Unlabeled = Init_LL();
        for (int i = 0; i < Segments; i++) {
            Add(Unlabeled, i, nullptr, &(SegmentsPtr[i]));
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
        delete SegmentsPtr;
    }

    StatusType AddLabel( int segmentID, int label) {
        void *value;
        if (Find(Unlabeled, segmentID, &value) != SUCCESS)
            return FAILURE;
        *(int *) value = label;
        SegmentsPtr[segmentID]=value;
        Delete(Unlabeled,segmentID);
        return SUCCESS;
    }

    StatusType getLabel (int segmentID, int* label) {
        if(SegmentsPtr[segmentID]== nullptr)
            return FAILURE;
        *label=*(int*)SegmentsPtr[segmentID];
        return SUCCESS;
    }

    StatusType DeleteLabel(int segmentID) {

        if((int*)SegmentsPtr[segmentID] == nullptr)
            return FAILURE;

        return  Add(Unlabeled,segmentID, nullptr,&SegmentsPtr[segmentID]);


    }


    StatusType GetAllUnLabeledSegments (int **segments, int *numOfSegments) {

        Size(Unlabeled,numOfSegments) ;

        if(*numOfSegments==0)
            return FAILURE;
        int size=*numOfSegments;

        *segments = (int*)std::malloc(size * sizeof(int));
        if(!(*segments))
            return ALLOCATION_ERROR;

        int i=0;
        for(void* head=getHead<int>(Unlabeled) ; head != nullptr ; head=getNext<int>(head)  ) {
            *(segments[i])=*(int*)getnodeValue<int>(head);
            i++;
        }
        return SUCCESS;

    }


};

#endif //HW2_LIBRARY_IMAGE_H
