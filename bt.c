#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bt.h"


BTNode* createBTNode(Job* data) {
    BTNode* node = malloc(sizeof(BTNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BinaryTree* createBinaryTree() {
    BinaryTree* bt = malloc(sizeof(BinaryTree));
    return bt;
}

void initializeBinaryTree() {
    ftable[PREORDER] = TreePreOrder;
    ftable[INORDER] = BinaryTreeInOrder;
    ftable[POSTORDER] = BinaryTreePostOrder;
}

void deleteBinaryTree(BinaryTree* bt) {
    //TODO - Free all nodes
}

void insertInBinaryTree(BinaryTree* bt, Job* data) {
    BTNode* newNode = createBTNode(data);
    if (bt->root == NULL) { // Make the node the root if it is the first one
        bt->root = newNode;
        return;
    }

    BTNode* curr = bt->root;

    while (!isLeaf(curr)) { // Loop to determine the new node's parent
        if (compareJobs(curr->data, data) >= 0) {
            curr = curr->right;
        }
        else {
            curr = curr->left;
        }
    }

    // Insert to the right or left of the parent node
    if (compareJobs(curr->data, data) >= 0) {
        curr->right = newNode;
    }
    else {
        curr->left = newNode;
    }
}

char* toStringBinaryTree(BinaryTree* bt, TreeOrder order) {
    if (bt->root != NULL) {
        char* printbuf = (char*) malloc( bt->size*3 );
        // call traversals with printbuf

        return(printbuf);
    }
    else
        return((char*) NULL);
}


void BinaryTreeInOrder(BTNode* bt, char* p) {
}

void BinaryTreePreOrder(BTNode* bt, char* p) {
}

void BinaryTreePostOrder(BTNode* bt, char* p) {
}

bool isLeaf(BTNode* node) {
    return node->left == NULL && node->right == NULL;
}
