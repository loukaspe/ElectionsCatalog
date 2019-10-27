/* This Class represents the node of the PostalCodesLinkedList class that will
 * contain every PostalCode and a LinkedList with Voters in that PostalCode.
 * So each node will have as data the PostalCode and a pointer to the
 * according LinkedList*/

#ifndef ELECTIONSCATALOG_POSTALCODESLINKEDLISTNODE_H
#define ELECTIONSCATALOG_POSTALCODESLINKEDLISTNODE_H


#include "LinkedList/LinkedList.h"

class PostalCodesLinkedListNode {
    public:
        int postalCode;
        PostalCodesLinkedListNode* next;
        LinkedList* list;
        PostalCodesLinkedListNode(int);
};


#endif //ELECTIONSCATALOG_POSTALCODESLINKEDLISTNODE_H
