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

/**
 * Removes the desired element and inserts it back into the tree
 */
void modifyElementBinaryTree(BinaryTree* bt, Job* data) {
    removeBinaryTree(bt, data);
    insertInBinaryTree(bt, data);
}

/**
 * Frees BTNodes without deleting the job
 */
void deleteNodeShallow(BTNode* node) {
   if (node->left != NULL) deleteNodeShallow(node->left);
   if (node->right != NULL) deleteNodeShallow(node->right);
   free(node);
}

/**
 * Removes the desired element from the tree and fixes the structure of the tree.
 * Does so by removing the job from the list of jobs then remaking the tree.
 * This is inefficient, but removing is annoying :-/
 */
void removeBinaryTree(BinaryTree* bt, Job* data) {
    JobArrayList* jal = getListFromTree(bt);
    int len = jal->length;
    removeDataFromJAL(jal, data);

    if (len == jal->length) return; // Don't remake the whole tree if the job was not found in the list

    if (bt->root != NULL) deleteNodeShallow(bt->root);

    bt->root = NULL;
    bt->height = 0;
    bt->size = 0;

    for (int i = 0; i < jal->length; i++) {
        insertInBinaryTree(bt, getJAL(jal, i));
    }

    deleteJobArrayListShallow(jal);
}

/**
 * Prints out the binary tree by listing all states of the same height on the same line
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

/**
 * Copies the jobs from nodes to a list in level order
 */
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

/**
 * Copies the jobs from nodes to a list then sorts them
 */
JobArrayList* getSortedListFromTree(BinaryTree* bt) {
    JobArrayList* jal = getListFromTree(bt);
    sortJAL(jal);
    return jal;
}
