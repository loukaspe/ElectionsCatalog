/* Based on RBT implemented by GeeksForGeeks here
 * https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/ */

/* The RedBlackTree will has as value for it's Nodes a Voter */

#ifndef UNTITLED_REDBLACKTREE_H
#define UNTITLED_REDBLACKTREE_H

#include "Node.h"
// TODO remove queue and levelorder in order after checking that works
#include <queue>
#include <iostream>

using namespace std;

class RedBlackTree {

public:
    Node* root;
    RedBlackTree();
    Node* getRoot();
    int getSize();
    Node* searchForVoter(Voter*);
    void insertVoterToTree(Voter*);
    void deleteVoterFromTree(Voter*);
    void printInOrder();
    void printLevelOrder();
private:
    int size;
    void rotateLeft(Node*);
    void rotateRight(Node*);
    void swapColorsBetweenNodes(Node*, Node*);
    void swapVotersBetweenNodes(Node*, Node*);
    void fixAdjacentRedNodesViolation(Node*);
    Node* findSuccessorInSubTree(Node*);
    Node* findNodeToReplaceDeletedNodeInBST(Node*);
    void deleteNode(Node*);
    void convertDoubleBlackChildToSingleAfterDeletion(Node*);
    void levelOrder(Node *x);
    void inorder(Node *x);
};

#endif //UNTITLED_REDBLACKTREE_H

