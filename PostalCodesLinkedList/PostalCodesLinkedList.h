/* The structure that will hold the RBTree records according to their PostalCode
 * will be a simple LinkedList, the PostalCodesLinkedList. More specifically,
 * this class will be a linked list in which, each node, the PostalCodesLinkedListNode,
 * will hold a PostalCode and a pointer to another LinkedList, the LinkedList,
 * which will contain an id, the id of each Voter in this PostalCode, and a pointer
 * to the according node of the RedBlackTree of Voters */
/* Based on https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm */

#ifndef ELECTIONSCATALOG_POSTALCODESLINKEDLIST_H
#define ELECTIONSCATALOG_POSTALCODESLINKEDLIST_H

#include <iostream>
#include "PostalCodesLinkedListNode/PostalCodesLinkedListNode.h"
#include <cstring>
#include <cassert>

class PostalCodesLinkedList {
public:
    PostalCodesLinkedList();
    void addAtStart(int);
    void deleteVoterWithId(int, char*);
    void getPercentageOfVotersThatHaveVotedForEveryPostalCode();
    int getHowManyVotersHaveVotedInPostalCode(int);
    int getVotersInPostalCode(int);
    bool isEmpty();
    PostalCodesLinkedListNode* findNodeWithPostalCode(int);
private:
    PostalCodesLinkedListNode* head;
    int size;
};


#endif //ELECTIONSCATALOG_POSTALCODESLINKEDLIST_H
