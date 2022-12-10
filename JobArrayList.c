#include <malloc.h>
#include "JobArrayList.h"

JobArrayList* createJobArrayList() {
    JobArrayList* arr = malloc(sizeof(JobArrayList));
    arr->arr = malloc(sizeof(Job) * 10);
    arr->length = 0;
    arr->arrSize = 10;
    return arr;
}

void deleteJobArrayList(JobArrayList *arr) {
    for (int i = 0; i < arr->length; i++) {
        deleteJob(getJAL(arr, i));
    }
    free(arr->arr);
    free(arr);
}

void deleteJobArrayListShallow(JobArrayList *arr) {
    free(arr->arr);
    free(arr);
}

/**
 * Doubles the size of the ArrayList so it can hold more elements
 */
void doubleSizeJAL(JobArrayList *arr) {
    arr->arrSize *= 2;
    arr->arr = realloc(arr->arr, sizeof(Job) * arr->arrSize);
}

/**
 * Inserts a Job to the end of the ArrayList.
 * If the list is full, its size will be increased before adding the new element.
 */
void insertJAL(JobArrayList *arr, Job* data) {
    if (arr->length == arr->arrSize) {
        doubleSizeJAL(arr);
    }

    Job** p = arr->arr;
    p += arr->length;
    *p = data;
    arr->length++;
}

/**
 * Inserts a Job to the provided index.
 * If the index is out of bounds, it will be ignored.
 * If the list is full, its size will be increased before adding the new element.
 */
void insertAtIndexJAL(JobArrayList *arr, Job* data, int index) {
    if (index < 0 || index > arr->length) { // Index out of bounds
        return;
    }
    else if (index == arr->length) {
        insertJAL(arr, data);
        return;
    }
    else {
        if (arr->length == arr->arrSize) {
            doubleSizeJAL(arr);
        }
        arr->length += 1;

        for (int i = arr->length; i > index; i--) {
            setJAL(arr, getJAL(arr, i-1), i);
        }
        setJAL(arr, data, index);
    }
}

/**
 * Gets the Job at the given index.
 * If the index is out of bounds, NULL will be returned.
 */
Job* getJAL(JobArrayList *arr, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return NULL;
    }

    Job** p = arr->arr;
    p += index;
    return *p;
}

/**
 * Sets the Job at the given index to the new one.
 * If the index if out of bounds, it will be ignored.
 */
void setJAL(JobArrayList *arr, Job* data, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return;
    }

    Job** p = arr->arr;
    p += index;
    *p = data;
}

/**
 * Removes the Job at the given index.
 * If the index if out of bounds, nothing will be removed.
 */
void removeFromJAL(JobArrayList *arr, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return;
    }

    for (int i = index; i < arr->length - 1; i++) {
        setJAL(arr, getJAL(arr, i+1), i);
    }

    arr->length--;
}

/**
 * Prints out every Job in the list.
 */
void printJAL(JobArrayList *arr) {
    for (int i = 0; i < arr->length-1; i++) {
        printJob(getJAL(arr, i));
    }
}

/**
 * Uses insertion sort to sort the jobs
 * @param arr The list of jobs
 */
void sortJAL(JobArrayList *arr) {
    int n = arr->length;
    Job *key;

    for (int i = 1; i < n; i++) {
        key = getJAL(arr, i);
        int j = i - 1;

        // Move elements back until they are at the right spot
        while (j >= 0 && compareJobs(key, getJAL(arr, j)) < 0) {
            setJAL(arr, getJAL(arr, j), j + 1);
            j = j - 1;
        }
        setJAL(arr, key, j + 1);
    }
}