#include <malloc.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedList* createLinkedList() {
    LinkedList* ll = malloc(sizeof(LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    ll->length = 0;
    return ll;
}

/**
 * All jobs inserted into the list are pointers to the job from the JobArrayList
 */
void deleteLinkedList(LinkedList *ll) {
    if (ll->head != NULL) {
        Node *curr = ll->head;
        while (curr->next != NULL) {
            curr = curr->next;
            free(curr->prev);
        }
        free(curr);
    }
    free(ll);
}

/**
 * Clones the original LinkedList to the new one. This is used when copying an indexed list to another to avoid pointer issues.
 */
void cloneLinkedList(LinkedList *pointer, LinkedList *original) {
    while(pointer->head != NULL) {
        removeFromLinkedList(pointer, 0);
    }

    Node *curr = original->head;
    if (curr == NULL) return;

    for (int i = 0; i < original->length-1; i++) {
        insertLinkedList(pointer, curr->data);
        curr = curr->next;
    }
    insertLinkedList(pointer, curr->data);
}

/**
 * Inserts a Job to the end of the LinkedList.
 */
void insertLinkedList(LinkedList *ll, Job *data) {
    Node *node = malloc(sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->data = data;

    if (ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
    }
    else {
        ll->tail->next = node;
        node->prev = ll->tail;
        ll->tail = node;
    }

    ll->length += 1;
}

/**
 * Inserts a Job to the provided index.
 * If the index is out of bounds, it will be ignored.
 */
void insertAtIndexLinkedList(LinkedList *ll, Job *data, int index) {
    if (index < 0 || index > ll->length) { // Index out of bounds
        return;
    }

    if (index == 0) {
        Node *node = malloc(sizeof(Node));
        node->prev = NULL;
        node->next = NULL;
        node->data = data;

        node->prev = NULL;
        node->next = ll->head;
        ll->head->prev = node;
        ll->head = node;
    }
    else if (index == ll->length) {
        insertLinkedList(ll, data);
        return;
    }
    else {
        Node *curr = ll->head;
        for (int i = 1; i < index; i++) {
            curr = curr->next;
        }

        Node *node = malloc(sizeof(Node));
        node->data = data;
        node->prev = curr;
        node->next = curr->next;
        curr->next->prev = node;
        curr->next = node;
    }

    ll->length += 1;
}

/**
 * Removes the Job at the given index.
 * If the index if out of bounds, nothing will be removed.
 */
void removeFromLinkedList(LinkedList *ll, int index) {
    if (index < 0 || index >= ll->length) { // Index out of bounds
        return;
    }

    if (ll->length == 1) {
        free(ll->head);
        ll->head = NULL;
        ll->tail = NULL;
        ll->length = 0;
        return;
    }

    if (index == 0) {
        Node *newHead = ll->head->next;
        newHead->prev = NULL;
        free(ll->head);
        ll->head = newHead;
    }
    else if (index+1 == ll->length) {
        Node *newTail = ll->tail->prev;
        newTail->next = NULL;
        free(ll->tail);
        ll->tail = newTail;
    }
    else {
        Node *curr = ll->head;
        for (int i = 0; i < index-1; i++) { // Set curr to 1 node before the one to remove
            curr = curr->next;
        }

        Node *removed = curr->next;  // Removed removing the wrong node
        curr->next = removed->next;
        removed->next->prev = curr;
        free(removed);
    }

    ll->length -= 1;
}


/**
 * Removes the Job that matched the one provided.
 * If the Job is not in the list, nothing will be removed.
 */
void removeDataFromLinkedList(LinkedList *ll, Job *data) {
    Node *curr = ll->head;
    for (int i = 0; i < ll->length; i++) {
        if (curr->data == data) {
            removeFromLinkedList(ll, i);
            return;
        }
        curr = curr->next;
    }
}

/**
 * Prints out every Job in the list.
 */
void printLinkedList(LinkedList *ll) {
    Node *curr = ll->head;
    for (int i = 0; i < ll->length - 1; i++) {
        printJob(curr->data);
        printf("\n");
        curr = curr->next;
    }
    printJob(curr->data);
}