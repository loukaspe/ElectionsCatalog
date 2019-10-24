/* Based on RBT implemented by GeeksForGeeks here
 * https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/ */

/* Each RedBlackTreeNode will has as data a Voter, using it's ID as key */

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <cstring>
#include "Voter.h"

enum COLOR { RED, BLACK };

class RedBlackTreeNode {
    public:
        Voter* voter;
        COLOR color;
        RedBlackTreeNode* left;
        RedBlackTreeNode* right;
        RedBlackTreeNode* parent;

        RedBlackTreeNode(Voter*);
        RedBlackTreeNode* getUncle();
        bool isLeftChild();
        RedBlackTreeNode* getSibling();
        void becomeChildOf(RedBlackTreeNode* newParent);
        bool hasRedChild();

};

#endif //UNTITLED_NODE_H
