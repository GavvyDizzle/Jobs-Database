#ifndef CS203_PROJECT1_BT_H
#define CS203_PROJECT1_BT_H

#include "Job.h"
#include "LinkedList.h"
#include "JobArrayList.h"

typedef struct BTNode_struct {
    Job* data;
    struct BTNode_struct* left;
    struct BTNode_struct* right;
} BTNode;

typedef struct BinaryTree_struct {
    BTNode *root;
    int height;
    int size;
} BinaryTree;

/**
 * Creates a new BinaryTree
 * @return A pointer to the new BinaryTree
 */
BinaryTree* createBinaryTree();

/**
 * Creates a new BinaryTree node
 * @return A pointer to the new BinaryTree node
 */
BTNode* createBTNode(Job* data);

/**
 * Deletes a BinaryTree and all of its nodes
 * @param bt The BinaryTree
 */
void deleteBinaryTree(BinaryTree* bt);

/**
 * Deletes a BinaryTree node
 * @param node The node
 */
void deleteNode(BTNode* node);

/**
 * Inserts a new job into the BinaryTree
 * @param bt The BinaryTree
 * @param data The job to add
 */
void insertInBinaryTree(BinaryTree* bt, Job* data);

/**
 * Prints out the BinaryTree in level order format
 * @param bt The BinaryTree
 */
void printBinaryTree(BinaryTree* bt);

/**
 * Determines if this node is a leaf
 * @param node The node
 * @return True if this node is a leaf
 */
bool isLeaf(BTNode* node);

/**
 * Creates a list of jobs from this tree
 * @param bt The BinaryTree
 * @return A JobArrayList representing this tree
 */
JobArrayList* getListFromTree(BinaryTree* bt);

/**
 * Creates a sorted list of jobs from this tree
 * @param bt The BinaryTree
 * @return A sorted JobArrayList representing this tree
 */
JobArrayList* getSortedListFromTree(BinaryTree* bt);

#endif //CS203_PROJECT1_BT_H
