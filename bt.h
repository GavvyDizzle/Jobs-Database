#ifndef CS203_PROJECT1_BT_H
#define CS203_PROJECT1_BT_H

#include "Job.h"
#include "LinkedList.h"

typedef struct BTNode_struct {
    Job* data;
    struct BTNode_struct* left;
    struct BTNode_struct* right;
} BTNode;

typedef struct BinaryTree_struct {
    BTNode *root;
    int height;
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
 * Creates an array of BTNode pointers in level order for the BinaryTree
 * @param bt The BinaryTree
 * @return An array of BTNode pointers
 */
BTNode* getLevelOrder(BinaryTree* bt);

/**
 * Inserts all of this node's child nodes into the array
 * @param arr The BTNode array
 * @param node The node to add the children of
 * @param nodeIndex The index of the node
 */
void insertChildren(BTNode* arr, BTNode* node, int nodeIndex);

/**
 * Determines if this node is a leaf
 * @param node The node
 * @return True if this node is a leaf
 */
bool isLeaf(BTNode* node);

#endif //CS203_PROJECT1_BT_H
