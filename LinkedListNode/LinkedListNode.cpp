#include "LinkedListNode.h"

LinkedListNode::LinkedListNode(RedBlackTreeNode* voterNode) {
    this->voterNode = voterNode;
    this->next = nullptr;
    this->id = Helper::copyString(this->voterNode->voter->getId());
}

LinkedListNode::LinkedListNode(LinkedListNode* node) {
    this->voterNode = node->voterNode;
    this->next = nullptr;
    this->id = Helper::copyString(this->voterNode->voter->getId());
}
