//
// Created by baha2 on 03-Dec-18.
//
#include <new>
#include "stdio.h"
#include "ImageTagger.h"
#include "library1LL.h"
#include "library1Tree.h"
#include "library2.h"



/* Required Interface for the Data Structure
 * -----------------------------------------*/

/* Description:   Initiates the data structure.
 * Input:         segments - The number of segments in each picture.
 * Output:        DS - A pointer to the data structure.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void *Init(int segments){
    try {
        ImageTagger *DS = new ImageTagger(segments);
        return (void*)DS;

    }catch (...) {
        return nullptr;
    }


}

/* Description:   Adds a new image to the data structure.
 * Input:         DS - A pointer to the data structure.
 *                image - The image to add.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or imageID <= 0.
 *                FAILURE - If the image is already in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType AddImage(void *DS, int imageID) {
    if(!DS || imageID <= 0 ) return INVALID_INPUT;
    return ((ImageTagger*)DS)->AddImage(imageID);
}

/* Description:   Deletes an image from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                image - The image to remove.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or imageID <= 0.
 *                FAILURE - If the image does not exist in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType DeleteImage(void *DS, int imageID) {
    if(!DS || imageID <= 0) return INVALID_INPUT;
    return   Delete(DS,imageID);

}

/* Description:   Tags the a segment in an image.
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to tag.
 * 				  segmentID - The segment to tag.
 * 				  label - The label of the segment.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL segmentID >= segments or segmentID < 0 or imageID < 0 or label < 0.
 *                FAILURE - If the image does not exist in the DS, or the segment is allready tagged.
 *                SUCCESS - Otherwise.
 */
StatusType AddLabel(void *DS, int imageID, int segmentID, int label) {
                if(!DS || imageID <0 || segmentID >=((ImageTagger*)DS)->getSegments() || segmentID <0 || label < 0 ) {
                    return INVALID_INPUT;
                }
    return ((ImageTagger*)DS)->AddLabel(imageID,segmentID,label);
}

/* Description:   Gets the a label of a segment in an image.
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to get the label from.
 * 				  segmentID - The segment to get the label from.
 * 				  label - A pointer to a variable which will hold the label.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL segmentID >= segments or segmentID < 0 or imageID < 0 or label == NULL.
 *                FAILURE - If the image does not exist in the DS, or the segment is not tagged.
 *                SUCCESS - Otherwise.
 */
StatusType GetLabel(void *DS, int imageID, int segmentID, int *label) {
    if(!DS || imageID <0 || segmentID >=((ImageTagger*)DS)->getSegments() || segmentID <0 || label == NULL ) {
        return INVALID_INPUT;
    }
    return ((ImageTagger*)DS)->getLabel(imageID,segmentID,label);
}

/* Description:   Deletes the a label of a segment in an image.
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to delete the label from.
 * 				  segmentID - The segment to delete the label from.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL segmentID >= segments or segmentID < 0 or imageID < 0.
 *                FAILURE - If the image does not exist in the DS, or the segment is not tagged.
 *                SUCCESS - Otherwise.
 */
StatusType DeleteLabel(void *DS, int imageID, int segmentID) {
    if(!DS || imageID <0 || segmentID >=((ImageTagger*)DS)->getSegments() || segmentID <0  ) {
        return INVALID_INPUT;
    }
    return ((ImageTagger*)DS)->DeleteLabel(imageID,segmentID);
}

/* Description:   Returns a list of all the unlabeled segments in an image.
 * Input:         DS - A pointer to the data structure.
 *                imageID - The image to get the segments from.
 * Output:        segments - A pointer to an array which will hold the unlabled segments. Note that you need to allocate the array inside the function.
 *  		      numOfSegments - A pointer to a variable which will hold the number of unlabled segments.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or imageID <= 0 or segments == NULL or numOfSegments == NULL.
 *                FAILURE - If the image does not exist in the DS, or the there is no unlabeled segment in the image.
 *                SUCCESS - Otherwise.
 */
StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments, int *numOfSegments) {
    if(!DS || imageID <= 0 || segments== nullptr || numOfSegments== nullptr ) {
        return INVALID_INPUT;
    }
    return ((ImageTagger*)DS)->GetAllUnLabeledSegments(imageID,segments,numOfSegments);
}

/* Description:   Returns a list of all the segments tagged with a certain label.
 * Input:         DS - A pointer to the data structure.
 *                label - The label to lookup for.
 * Output:        images - A pointer to an array which will hold the IDs of the images containing segments tagged with label. Note that you need to allocate the array inside the function.
 *                segments - A pointer to an array which will hold the segments of the images containing segments tagged with label. Note that you need to allocate the array inside the function.
 *  		      numOfSegments - A pointer to a variable which will hold the number of returned segments.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If one of the pointers is NULL or label < 0.
 *                SUCCESS - Otherwise.
 */
StatusType GetAllSegmentsByLabel(void *DS, int label, int **images, int **segments, int *numOfSegments) {
    if(!DS || ! images || !segments || !numOfSegments  || label<0) {
        return INVALID_INPUT;
    }
    return ((ImageTagger*)DS)->GetAllSegments(DS,label,images,segments,numOfSegments);
}

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit(void** DS) {
    ((ImageTagger*)DS)->Quit_Tagger();
}

