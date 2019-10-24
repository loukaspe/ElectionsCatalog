/* This Class represents the node of the LinkedList class that will contain every
 * Voter of a specific PostalCode. So each node will have as data the id of the
 * Voter and a pointer to it's according RedBlackTreeNode */

#ifndef ELECTIONSCATALOG_LINKEDLISTNODE_H
#define ELECTIONSCATALOG_LINKEDLISTNODE_H


#include "RedBlackTreeNode/RedBlackTreeNode.h"
#include "Helper/Helper.h"

class LinkedListNode {
    public:
        char* id;
        LinkedListNode* next;
        RedBlackTreeNode* voterNode;
        LinkedListNode(RedBlackTreeNode*);
        LinkedListNode(LinkedListNode*);
};


#endif //ELECTIONSCATALOG_LINKEDLISTNODE_H
