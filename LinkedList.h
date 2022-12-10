#ifndef CS203_PROJECT1_LINKEDLIST_H
#define CS203_PROJECT1_LINKEDLIST_H

#include "Job.h"

typedef struct Node_struct {
    struct Node_struct *next;
    struct Node_struct *prev;
    Job *data;
} Node;

typedef struct LinkedList_struct {
    Node* head;
    Node* tail;
    int length;
} LinkedList;

/**
 * Creates a new Job LinkedList
 * @return A pointer to the new LinkedList
 */
LinkedList* createLinkedList();

/**
 * Deletes a LinkedList
 * @param ll The LinkedList
 */
void deleteLinkedList(LinkedList *ll);

/**
 * Clones all data from the given LinkedList
 * @param ll The location to copy to
 * @param original The list to copy
 * @return A copy of the given list
 */
void cloneLinkedList(LinkedList *pointer, LinkedList *original);

/**
 * Inserts an element to the end of the LinkedList
 * @param ll The list
 * @param data The element to add
 */
void insertLinkedList(LinkedList *ll, Job *data);

/**
 * Inserts an element at the given index of the LinkedList
 * @param ll The list
 * @param data The element to add
 * @param index The index to put it at
 */
void insertAtIndexLinkedList(LinkedList *ll, Job *data, int index);

/**
 * Inserts an element in the list sorted correctly
 * @param ll The list
 * @param data The element to add
 */
void insertInOrderLinkedList(LinkedList *ll, Job *data);

/**
 * Places an element into its correct sorted position
 * @param ll The list
 * @param data The element to move
 */
void modifyElementLinkedList(LinkedList *ll, Job *data);

/**
 * Removes the element at the given index
 * @param ll The list
 * @param index The index
 */
void removeFromLinkedList(LinkedList *ll, int index);

/**
 * Removes the given element from the list, if present
 * @param ll The list
 * @param data The element to remove
 */
void removeDataFromLinkedList(LinkedList *ll, Job *data);

/**
 * Prints the list to the screen
 * @param ll The list
 */
void printLinkedList(LinkedList *ll);

#endif //CS203_PROJECT1_LINKEDLIST_H
