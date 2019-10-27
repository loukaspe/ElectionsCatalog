/* This is the LinkedList that will hold the Voters of the same PostalCode */
/* Based on https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm */

#ifndef ELECTIONSCATALOG_LINKEDLIST_H
#define ELECTIONSCATALOG_LINKEDLIST_H

#include <iostream>
#include "LinkedListNode/LinkedListNode.h"
#include <cstring>
#include <assert.h>

using namespace std;

class LinkedList {
    public:
        LinkedList();
        void print();
        void addAtStart(RedBlackTreeNode*);
        void deleteNodeWithId(char*);
        void deleteAll();
        int getSize();
        bool isEmpty();
        LinkedListNode* findVoterWithId(char*);
        int getHowManyVotersHaveVoted();
    private:
        LinkedListNode* head;
        int size;
};


#endif //ELECTIONSCATALOG_LINKEDLIST_H
