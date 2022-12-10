#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"
#include "BTNodeQueue.h"

BinaryTree* createBinaryTree() {
    BinaryTree* bt = malloc(sizeof(BinaryTree));
    bt->root = NULL;
    bt->height = 0;
    bt->size = 0;
    return bt;
}

/**
 * Creates a new BTNode and makes the data the first element in its LinkedList
 */
BTNode* createBTNode(Job* data) {
    BTNode* node = malloc(sizeof(BTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void deleteBinaryTree(BinaryTree* bt) {
    if (bt->root != NULL) deleteNode(bt->root);
    free(bt);
}

/**
 * Recursively deletes all of this node's children then itself
 */
void deleteNode(BTNode* node) {
    if (node->left != NULL) deleteNode(node->left);
    if (node->right != NULL) deleteNode(node->right);
    deleteJob(node->data);
    free(node);
}

/**
 * Puts nodes in the tree. Nodes that are equal (compares state) will be contained in a LinkedList in a single node.
 */
void insertInBinaryTree(BinaryTree* bt, Job* data) {
    BTNode* newNode = createBTNode(data);
    if (bt->root == NULL) { // Make the node the root if it is the first one
        bt->root = newNode;
        bt->height = 1;
        bt->size = 1;
        return;
    }

    BTNode* curr = bt->root;

    int currHeight = 1;
    while (!isLeaf(curr)) { // Loop to determine the new node's parent
        if (compareJobsByState(curr->data, data) >= 0) {
            if (curr->right == NULL) break;
            curr = curr->right;
        }
        else {
            if (curr->left == NULL) break;
            curr = curr->left;
        }

        currHeight++;
    }

    // Insert to the right or left of the parent node
    if (compareJobsByState(curr->data, data) >= 0) {
        curr->right = newNode;
    }
    else {
        curr->left = newNode;
    }

    if (currHeight + 1 > bt->height) bt->height = currHeight + 1;
    bt->size++;
}

Job* getJobByTitle(BinaryTree* bt, char* jobTitle) {
    if (bt->root == NULL) return NULL;

    BTNodeQueue* queue = createQueue();
    insertQueue(queue, bt->root);

    bool foundMatch = false;
    BTNode* popped;
    while (!isQueueEmpty(queue)) {
        popped = popQueue(queue);
        if (strcasecmp(popped->data->jobTitle, jobTitle) == 0) {
            foundMatch = true;
            break;
        }

        insertQueue(queue, popped->left);
        insertQueue(queue, popped->right);
    }

    deleteQueue(queue);

    if (foundMatch) {
        return popped->data;
    }
    return NULL;
}

/**
 * Prints out the binary tree using the following format (spaces indicate no node)
 * 0
 * 1-2
 * 3-4-5-6
 * 7-8-9- 11-12- -14
 */
void printBinaryTree(BinaryTree* bt) {
    if (bt->root == NULL) {
        printf("Empty tree\n");
        return;
    }

    BTNodeQueue* queue = createQueue();
    insertQueue(queue, bt->root);

    BTNode* popped;
    while (!isQueueEmpty(queue)) {
        int l = queue->length-1;
        for (int i = 0; i < l; i++) { // loop through enough times to print each node at this level
            popped = popQueue(queue);
            printf("%s-", popped->data->state);

            insertQueue(queue, popped->left);
            insertQueue(queue, popped->right);
        }

        popped = popQueue(queue); // Last node at this level does not need a separator character
        printf("%s\n", popped->data->state);

        insertQueue(queue, popped->left);
        insertQueue(queue, popped->right);
    }

    deleteQueue(queue);
}

/**
 * No children means the node is a leaf
 */
bool isLeaf(BTNode* node) {
    return node->left == NULL && node->right == NULL;
}

JobArrayList* getListFromTree(BinaryTree* bt) {
    JobArrayList* jal = createJobArrayList();
    if (bt->root == NULL) return jal;

    BTNodeQueue* queue = createQueue();
    insertQueue(queue, bt->root);

    BTNode* popped;
    while (!isQueueEmpty(queue)) {
        popped = popQueue(queue);
        insertJAL(jal, popped->data);
        insertQueue(queue, popped->left);
        insertQueue(queue, popped->right);
    }

    deleteQueue(queue);

    return jal;
}

JobArrayList* getSortedListFromTree(BinaryTree* bt) {
    JobArrayList* jal = getListFromTree(bt);
    sortJAL(jal);
    return jal;
}
