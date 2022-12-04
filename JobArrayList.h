#ifndef CS203_PROJECT1_JOBARRAYLIST_H
#define CS203_PROJECT1_JOBARRAYLIST_H

#include "Job.h"

typedef struct JobArrayList_struct {
    Job** arr;
    int length;
    int arrSize;
} JobArrayList;

/**
 * Creates a new JobArrayList
 * @return A pointer to the new JobArrayList
 */
JobArrayList* createJobArrayList();

/**
 * Deletes a JobArrayList
 * @param arr The JobArrayList
 */
void deleteJobArrayList(JobArrayList *arr);

/**
 * Inserts an element to the end of the ArrayList
 * @param arr The list
 * @param data The element to add
 */
void insertJAL(JobArrayList *arr, Job* data);

/**
 * Inserts an element at the given index of the ArrayList
 * @param arr The list
 * @param data The element to add
 * @param index The index to put it at
 */
void insertAtIndexJAL(JobArrayList *arr, Job* data, int index);

/**
 * Gets the element from the given index
 * @param arr The list
 * @param index The index
 * @return The element at the index, NULL if out of bounds
 */
Job* getJAL(JobArrayList *arr, int index);

/**
 * Sets the element at the given index
 * @param arr The list
 * @param data The element to put in
 * @param index The index
 */
void setJAL(JobArrayList *arr, Job* data, int index);

/**
 * Removes the element at the given index
 * @param arr The list
 * @param index The index
 */
void removeFromJAL(JobArrayList *arr, int index);

/**
 * Prints the list to the screen
 * @param arr The list
 */
void printJAL(JobArrayList *arr);

/**
 * Sorts the JobArrayList
 * @param arr The list of jobs
 */
void sortJAL(JobArrayList *arr);

#endif //CS203_PROJECT1_JOBARRAYLIST_H
