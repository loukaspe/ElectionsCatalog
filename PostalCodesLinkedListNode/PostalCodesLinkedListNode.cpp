#include "PostalCodesLinkedListNode.h"

PostalCodesLinkedListNode::PostalCodesLinkedListNode(int postalCode) {
    this->postalCode = postalCode;
    this->next = nullptr;
    this->list = new LinkedList();
}

