/* Based on RBT implemented by GeeksForGeeks here
 * https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/ */

/* The RedBlackTree will has as value for it's Nodes a Voter */

#ifndef UNTITLED_REDBLACKTREE_H
#define UNTITLED_REDBLACKTREE_H

#include "RedBlackTreeNode.h"
// TODO remove queue and levelorder in order after checking that works
#include <queue>
#include <iostream>

using namespace std;

class RedBlackTree {

public:
    RedBlackTreeNode* root;
    RedBlackTree();
    RedBlackTreeNode* getRoot();
    int getSize();
    int getVotersThatHaveVoted();
    RedBlackTreeNode* searchForVoter(Voter*);
    Voter* findVoterWith(char*);
    void insertVoterToTree(Voter*);
    void deleteVoterFromTree(Voter*);
    void printInOrder();
    void printLevelOrder();
    void voteOfVoterWith(char*);
private:
    int size;
    int votersThatHaveVoted;
    void rotateLeft(RedBlackTreeNode*);
    void rotateRight(RedBlackTreeNode*);
    void swapColorsBetweenNodes(RedBlackTreeNode*, RedBlackTreeNode*);
    void swapVotersBetweenNodes(RedBlackTreeNode*, RedBlackTreeNode*);
    void fixAdjacentRedNodesViolation(RedBlackTreeNode*);
    RedBlackTreeNode* findSuccessorInSubTree(RedBlackTreeNode*);
    RedBlackTreeNode* findNodeToReplaceDeletedNodeInBST(RedBlackTreeNode*);
    void deleteNode(RedBlackTreeNode*);
    void convertDoubleBlackChildToSingleAfterDeletion(RedBlackTreeNode*);
    void levelOrder(RedBlackTreeNode *x);
    void inorder(RedBlackTreeNode *x);
};

#endif //UNTITLED_REDBLACKTREE_H

