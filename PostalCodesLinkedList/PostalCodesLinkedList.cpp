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
            free(current->list);
            free(current);
            this->size--;
            return;
        }

        previous = current;
        current = current->next;
    }

    if(current == head) {
        head = head->next;
        free(current->list);
        free(current);
        this->size--;
        return;
    }

    previous->next = current->next;
    free(current);
    this->size--;
}

void PostalCodesLinkedList::deleteVoterWithId(int postalCode, char* key) {

    int a = 2;
    PostalCodesLinkedListNode* postalCodesLinkedListNode = findNodeWithPostalCode(
            postalCode
    );

    if(postalCodesLinkedListNode != nullptr) {
        postalCodesLinkedListNode->list->deleteNodeWithId(key);
    }
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

int PostalCodesLinkedList::getHowManyVotersHaveVotedInPostalCode(int postalCode) {
    PostalCodesLinkedListNode* node = findNodeWithPostalCode(postalCode);
    if(node == nullptr) {
        return -1;
    }

    return node->list->getHowManyVotersHaveVoted();
}

int PostalCodesLinkedList::getVotersInPostalCode(int postalCode) {
    PostalCodesLinkedListNode* node = findNodeWithPostalCode(postalCode);
    if(node == nullptr) {
        return -1;
    }

    return node->list->getSize();
}

double PostalCodesLinkedList::getPercentageOfVotersThatHaveVotedInPostalCode(
        int postalCode
) {
    PostalCodesLinkedListNode* node = findNodeWithPostalCode(postalCode);
    if(node == nullptr) {
        return -1;
    }

    double votersThatHaveVoted = (double) getHowManyVotersHaveVotedInPostalCode(
            postalCode
    );

    double totalsVoters = (double) getVotersInPostalCode(postalCode);

    return (double)(votersThatHaveVoted/totalsVoters);
}

void PostalCodesLinkedList::getPercentageOfVotersThatHaveVotedForEveryPostalCode()
 {
    PostalCodesLinkedListNode* current = this->head;
    double votersThatHaveVoted;
    double totalVoters;
    double percentage;

    while( current != nullptr ) {

        int postalCode = current->postalCode;

        votersThatHaveVoted = (double) getHowManyVotersHaveVotedInPostalCode(
                postalCode
        );

        totalVoters = (double) getVotersInPostalCode(postalCode);

        assert(totalVoters != 0);

        percentage =  (double)(votersThatHaveVoted/totalVoters);

        cout << "In postal code " << postalCode << ", the percantage of voters"
           << " who have voted is " << percentage << "%." << endl;

        current = current->next;
    }
 }