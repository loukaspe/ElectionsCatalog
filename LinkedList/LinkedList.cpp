#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
}


void LinkedList::addAtStart(RedBlackTreeNode* voterNode) {
    LinkedListNode* newNode = new LinkedListNode(voterNode);

    newNode->next = this->head;
    this->head = newNode;
    this->size++;
}

void LinkedList::deleteNodeWithId(char* id) {
    if( isEmpty() ) {
        return;
    }

    LinkedListNode* current = head;
    LinkedListNode* previous = nullptr;

    while( strcmp( current->voterNode->voter->getId(), id ) != 0 ) {

        if(current->next == nullptr) {
            return;
        }

        previous = current;
        current = current->next;
    }

    if(current == head) {
        head = head->next;
        free(current);
        this->size--;
        return;
    }

    previous->next = current->next;
    free(current);
    this->size--;
}

int LinkedList::getSize() {
    return this->size;
}

bool LinkedList::isEmpty() {
    return this->size == 0;
}

int LinkedList::getHowManyVotersHaveVoted() {
    LinkedListNode* current = this->head;
    int votersThatHaveVotedNumber = 0;

    while( current != nullptr ) {
        if( current->voterNode->voter->getHasVoted() ) {
            votersThatHaveVotedNumber++;
        }

        current = current->next;
    }

    return votersThatHaveVotedNumber;
}