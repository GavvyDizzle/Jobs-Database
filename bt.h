#ifndef CS203_PROJECT1_BT_H
#define CS203_PROJECT1_BT_H

#include "Job.h"

#define MAXPRINTBUFFER 500

typedef enum {
    PREORDER,
    INORDER,
    POSTORDER
} TreeOrder;

typedef struct BTNode_struct {
    Job* data;
    struct BTNode_struct* left;
    struct BTNode_struct* right;
} BTNode;

typedef struct BinaryTree_struct {
    BTNode *root;
    int size;
} BinaryTree;

BTNode* createBTNode(Job* data);
BinaryTree* createBinaryTree();
void initializeBinaryTree();
void deleteBinaryTree(BinaryTree* bt);
void insertInBinaryTree(BinaryTree* bt, Job* data);
char* toStringBinaryTree(BinaryTree* bt, TreeOrder order);
bool isLeaf(BTNode* node);

#endif //CS203_PROJECT1_BT_H
