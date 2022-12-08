#ifndef CS203_PROJECT1_STRINGARRAYLIST_H
#define CS203_PROJECT1_STRINGARRAYLIST_H

#include <stdbool.h>

typedef struct StringArrayList_struct {
    char** arr;
    int length;
    int arrSize;
} StringArrayList;

/**
 * Creates a new StringArrayList
 * @return A pointer to the new StringArrayList
 */
StringArrayList* createStringArrayList();

/**
 * Deletes a StringArrayList, NOT including the elements
 * @param arr The StringArrayList
 */
void deleteStringArrayList(StringArrayList *arr);

/**
 * Deletes a StringArrayList, including all elements
 * @param arr The StringArrayList
 */
void deleteStringArrayListDeep(StringArrayList *arr);

/**
 * Inserts an element to the end of the ArrayList
 * @param arr The list
 * @param data The element to add
 */
void insertSAL(StringArrayList *arr, char* data);

/**
 * Inserts an element at the given index of the ArrayList
 * @param arr The list
 * @param data The element to add
 * @param index The index to put it at
 */
void insertAtIndexSAL(StringArrayList *arr, char* data, int index);

/**
 * Gets the element from the given index
 * @param arr The list
 * @param index The index
 * @return The element at the index, NULL if out of bounds
 */
char* getSAL(StringArrayList *arr, int index);

/**
 * Sets the element at the given index
 * @param arr The list
 * @param data The element to put in
 * @param index The index
 */
void setSAL(StringArrayList *arr, char* data, int index);

/**
 * Removes the element at the given index
 * @param arr The list
 * @param index The index
 */
void removeFromSAL(StringArrayList *arr, int index);

/**
 * Determines if list contains the input
 * @param arr The StringArrayList
 * @param str The string to look for
 * @param exactMatch If exact matches should be required
 * @return True if the list contains the whole input in one of its entries, false otherwise
 */
bool containsSAL(StringArrayList *arr, char* str, bool exactMatch);

/**
 * Determines if list contains the input as one of its elements
 * @param arr The StringArrayList
 * @param str The string to look for
 * @return True if the list contains the exact input as one of its entries, false otherwise
 */
bool containsExactSAL(StringArrayList *arr, char* str);

/**
 * Determines if list contains an element from another list
 * @param arr The StringArrayList (haystacks)
 * @param o The other StringArrayList (needles)
 * @return True if the list contains part of an element from the other list, false otherwise
 */
bool containsListMatchSAL(StringArrayList *arr, StringArrayList *o, bool exactMatch);

/**
 * Determines if list contains an element from another list
 * @param arr The StringArrayList (haystacks)
 * @param o The other StringArrayList (needles)
 * @return True if the list contains an element of the other exactly, false otherwise
 */
bool containsExactListMatchSAL(StringArrayList *arr, StringArrayList *o);

/**
 * Prints the list to the screen
 * @param arr The list
 */
void printSAL(StringArrayList *arr);

/**
 * Prints the list to the file
 * @param arr The list
 * @param fp The file
 */
void printSALToFile(StringArrayList *arr, FILE* fp);

#endif //CS203_PROJECT1_STRINGARRAYLIST_H