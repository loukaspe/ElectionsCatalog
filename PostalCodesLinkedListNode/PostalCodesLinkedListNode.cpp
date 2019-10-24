#include "PostalCodesLinkedListNode.h"

PostalCodesLinkedListNode::PostalCodesLinkedListNode(int postalCode) {
    this->postalCode = postalCode;
    this->next = nullptr;
    this->list = new LinkedList();
}

//PostalCodesLinkedListNode::PostalCodesLinkedListNode(
//        PostalCodesLinkedListNode* node
//) {
//        this->postalCode = node->postalCode;
//        this->next = null;
//        this->list
//}
