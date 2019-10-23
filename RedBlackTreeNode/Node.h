/* Based on RBT implemented by GeeksForGeeks here
 * https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/ */

/* Each Node will has as data a Voter, using it's ID as key */

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <cstring>
#include "Voter.h"

enum COLOR { RED, BLACK };

class Node {
    public:
        Voter* voter;
        COLOR color;
        Node* left;
        Node* right;
        Node* parent;

        Node(Voter*);
        Node* getUncle();
        bool isLeftChild();
        Node* getSibling();
        void becomeChildOf(Node* newParent);
        bool hasRedChild();

};

#endif //UNTITLED_NODE_H
