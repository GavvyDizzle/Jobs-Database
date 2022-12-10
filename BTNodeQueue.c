#include <malloc.h>
#include "BTNodeQueue.h"

BTNodeQueue* createQueue() {
    BTNodeQueue* queue = malloc(sizeof(BTNodeQueue));
    queue->arr = malloc(sizeof(BTNode) * 10);
    queue->length = 0;
    queue->queueSize = 10;
    return queue;
}

// Only pointers to existing jobs are added, so the individual jobs do not need to be freed
void deleteQueue(BTNodeQueue* queue) {
    free(queue->arr);
    free(queue);
}

/**
 * Doubles the size of the ArrayList so it can hold more elements
 */
void doubleSizeQueue(BTNodeQueue *queue) {
    queue->queueSize *= 2;
    queue->arr = realloc(queue->arr, sizeof(BTNode) * queue->queueSize);
}

// Inserts jobs at the back of the array if the node is non-null
void insertQueue(BTNodeQueue* queue, BTNode* data) {
    if (data == NULL) return;

    if (queue->length == queue->queueSize) {
        doubleSizeQueue(queue);
    }

    BTNode** p = queue->arr;
    p += queue->length;
    *p = data;
    queue->length++;
}

// Removes the first job and sets the head to the second node, if present
BTNode* popQueue(BTNodeQueue* queue) {
    if (queue->length <= 0) return NULL;

    BTNode* popped = *(queue->arr);

    for (int i = 0; i < queue->length - 1; i++) {
        queue->arr[i] = queue->arr[i+1];
    }
    queue->length--;

    return popped;
}

// length 0 means empty
bool isQueueEmpty(BTNodeQueue* queue) {
    return queue->length == 0;
}
