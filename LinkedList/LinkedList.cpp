#include "LinkedList.h"

LinkedList::LinkedList() {
    this->head = nullptr;
}

void LinkedList::print() {
    LinkedListNode* temp = this->head;

    while(temp != nullptr) {
        cout << temp->voterNode->voter->getId() << endl;
        temp = temp->next;
    }
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
            free(current);
            this->size--;
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

void LinkedList::deleteAll() {
    if( isEmpty() ) {
        return;
    }

    LinkedListNode* current = head;
    LinkedListNode* temp;

    while(current != nullptr) {
        temp = current;
        current = current->next;
        free(temp);
        this->size--;
    }

    free(this->head);
    assert(this->size == 0);
}

int LinkedList::getSize() {
    return this->size;
}

bool LinkedList::isEmpty() {
    return this->size == 0;
}

LinkedListNode* LinkedList::findVoterWithId(char* id) {
    LinkedListNode* current = this->head;

    while( current != nullptr ) {
        if( strcmp( current->voterNode->voter->getId(), id ) != 0 ) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}