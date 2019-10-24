#include "PostalCodesLinkedList.h"

PostalCodesLinkedList::PostalCodesLinkedList() {
    this->head = nullptr;
}

void PostalCodesLinkedList::print() {
    PostalCodesLinkedListNode* temp = this->head;

    while(temp != nullptr) {
        cout << temp->postalCode << endl;
        temp = temp->next;
    }
}

void PostalCodesLinkedList::addAtStart(int postalCode) {
    PostalCodesLinkedListNode* newNode = new PostalCodesLinkedListNode(
            postalCode
    );

    newNode->next = this->head;
    this->head = newNode;
    this->size++;
}

void PostalCodesLinkedList::deleteNodeWithPostalCode(int postalCode) {
    if( isEmpty() ) {
        return;
    }

    PostalCodesLinkedListNode* current = head;
    PostalCodesLinkedListNode* previous = nullptr;

    while( postalCode == current->postalCode) {

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

void PostalCodesLinkedList::deleteAll() {
    if( isEmpty() ) {
        return;
    }

    PostalCodesLinkedListNode* current = head;
    PostalCodesLinkedListNode* temp;

    while(current != nullptr) {
        temp = current;
        current = current->next;
        free(temp);
        this->size--;
    }

    free(this->head);
    assert(this->size == 0);
}

int PostalCodesLinkedList::getSize() {
    return this->size;
}

bool PostalCodesLinkedList::isEmpty() {
    return this->size == 0;
}

PostalCodesLinkedListNode* PostalCodesLinkedList::findNodeWithPostalCode(
        int postalCode
) {
    PostalCodesLinkedListNode* current = this->head;

    while( current != nullptr ) {
        if( postalCode == current->postalCode ) {
            return current;
        }

        current = current->next;
    }

    return nullptr;
}