#include "PostalCodesLinkedList.h"

PostalCodesLinkedList::PostalCodesLinkedList() {
    this->head = nullptr;
}

void PostalCodesLinkedList::addAtStart(int postalCode) {
    PostalCodesLinkedListNode* newNode = new PostalCodesLinkedListNode(
            postalCode
    );

    newNode->next = this->head;
    this->head = newNode;
    this->size++;
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