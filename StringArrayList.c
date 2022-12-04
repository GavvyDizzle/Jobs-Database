#include <malloc.h>
#include <string.h>
#include "StringArrayList.h"
#include "JobManager.h"

StringArrayList* createStringArrayList() {
    StringArrayList* arr = malloc(sizeof(StringArrayList));
    arr->arr = malloc(sizeof(char*) * 10);
    arr->length = 0;
    arr->arrSize = 10;
    return arr;
}

// Deletes the list with elements that were NOT dynamically allocated memory
void deleteStringArrayList(StringArrayList *arr) {
    free(arr->arr);
    free(arr);
}

// Deletes the list with elements that were dynamically allocated memory
void deleteStringArrayListDeep(StringArrayList *arr) {
    free(arr->arr[0]);
    free(arr->arr);
    free(arr);
}

/**
 * Doubles the size of the ArrayList so it can hold more elements
 */
void doubleSizeSAL(StringArrayList *arr) {
    arr->arrSize *= 2;
    arr->arr = realloc(arr->arr, sizeof(char*) * arr->arrSize);
}

/**
 * Inserts a string to the end of the ArrayList.
 * If the list is full, its size will be increased before adding the new element.
 */
void insertSAL(StringArrayList *arr, char* data) {
    if (arr->length == arr->arrSize) {
        doubleSizeSAL(arr);
    }

    char** p = arr->arr;
    p += arr->length;
    *p = data;
    arr->length++;
}

/**
 * Inserts a string to the provided index.
 * If the index is out of bounds, it will be ignored.
 * If the list is full, its size will be increased before adding the new element.
 */
void insertAtIndexSAL(StringArrayList *arr, char* data, int index) {
    if (index < 0 || index > arr->length) { // Index out of bounds
        return;
    }
    else if (index == arr->length) {
        insertSAL(arr, data);
        return;
    }
    else {
        if (arr->length == arr->arrSize) {
            doubleSizeSAL(arr);
        }
        arr->length += 1;

        for (int i = arr->length; i > index; i--) {
            setSAL(arr, getSAL(arr, i-1), i);
        }
        setSAL(arr, data, index);
    }
}

/**
 * Gets the string at the given index.
 * If the index is out of bounds, NULL will be returned.
 */
char* getSAL(StringArrayList *arr, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return NULL;
    }

    char** p = arr->arr;
    p += index;
    return *p;
}

/**
 * Sets the string at the given index to the new one.
 * If the index if out of bounds, it will be ignored.
 */
void setSAL(StringArrayList *arr, char* data, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return;
    }

    char** p = arr->arr;
    p += index;
    *p = data;
}

/**
 * Removes the string at the given index.
 * If the index if out of bounds, nothing will be removed.
 */
void removeFromSAL(StringArrayList *arr, int index) {
    if (index < 0 || index >= arr->length) { // Index out of bounds
        return;
    }

    for (int i = index; i < arr->length - 1; i++) {
        setSAL(arr, getSAL(arr, i+1), i);
    }

    arr->length--;
}

/**
 * Determines if the list contains a close match to the input.
 * For example, {"hello", "world"} given "ell" would return true because "ell" is in "hello"
 */
bool containsSAL(StringArrayList *arr, char* str, bool exactMatch) {
    if (exactMatch) return containsExactSAL(arr, str);

    for (int i = 0; i < arr->length; i++) {
        if (stristr(str, getSAL(arr,i)) != NULL) return true;
    }
    return false;
}

/**
 * Determines if the list contains an exact match to the input.
 * For example, {"hello", "world"} given "hello" would return true because "hello" is in one of the elements exactly
 */
bool containsExactSAL(StringArrayList *arr, char* str) {
    unsigned long strLength = strlen(str);

    for (int i = 0; i < arr->length; i++) {
        char *arrStr = getSAL(arr,i);
        if (strlen(arrStr) != strLength) continue;

        // If the strings are the same length stristr is non-null if the strings are the same
        if (stristr(str, arrStr) != NULL) return true;
    }
    return false;
}

/**
 * Determines if the list contains a close match to any element of the other list
 * For example, {"hello", "world"} given {"sunny", "ell"} would return true because "ell" is in "hello" from the first list
 */
bool containsListMatchSAL(StringArrayList *arr, StringArrayList *o, bool exactMatch) {
    if (exactMatch) return containsExactListMatchSAL(arr, o);

    for (int i = 0; i < arr->length; i++) {
        for (int j = 0; j < o->length; j++) {
            if (stristr(getSAL(arr, i), getSAL(o, j)) != NULL) return true;
        }
    }
    return false;
}

/**
 * Determines if the lists contain an exact match between one of their elements
 * For example, {"hello", "world"} given {"sunny", "hello"} would return true because "hello" is in the first list
 */
bool containsExactListMatchSAL(StringArrayList *arr, StringArrayList *o) {
    for (int i = 0; i < arr->length; i++) {
        char *arrStr = getSAL(arr,i);

        for (int j = 0; j < o->length; j++) {
            char *oStr = getSAL(o, j);
            if (strlen(arrStr) != strlen(oStr)) continue;

            // If the strings are the same length stristr is non-null if the strings are the same
            if (stristr(arrStr, oStr) != NULL) return true;
        }
    }
    return false;
}

/**
 * Prints out the list with outer brackets and commas between elements.
 */
void printSAL(StringArrayList *arr) {
    printf("[");
    for (int i = 0; i < arr->length-1; i++) {
        printf("%s, ", arr->arr[i]);
    }
    printf("%s", arr->arr[arr->length-1]);
    printf("]\n");
}