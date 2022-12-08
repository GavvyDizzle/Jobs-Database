#ifndef CS203_PROJECT1_BTNODEQUEUE_H
#define CS203_PROJECT1_BTNODEQUEUE_H

#include "Job.h"
#include "bt.h"

typedef struct BTNodeQueue_struct {
    BTNode** arr;
    int length;
    int queueSize;
} BTNodeQueue;

/**
 * Creates a new JobQueue
 * @return A pointer to the new JobQueue
 */
BTNodeQueue* createQueue();

/**
 * Deletes a JobQueue
 * @param queue The queue
 */
void deleteQueue(BTNodeQueue* queue);

/**
 * Inserts a job to the end of the queue
 * @param queue The queue
 * @param job The job to add
 */
void insertQueue(BTNodeQueue* queue, BTNode* job);

/**
 * Removes the first job in the queue
 * @param queue The queue
 * @return The job removed or NULL if empty
 */
BTNode* popQueue(BTNodeQueue* queue);

/**
 * Determines if this queue is empty
 * @param queue The queue
 * @return True if there are no elements in the queue
 */
bool isQueueEmpty(BTNodeQueue* queue);

#endif //CS203_PROJECT1_BTNODEQUEUE_H
