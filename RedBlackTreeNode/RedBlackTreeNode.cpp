#include "RedBlackTreeNode.h"

RedBlackTreeNode::RedBlackTreeNode(Voter* voter) {
    this->voter = (Voter*) malloc( sizeof(Voter) );
    this->voter = new Voter(voter);

    left = nullptr;
    right = nullptr;
    parent = nullptr;

    color = RED;
}


bool RedBlackTreeNode::isLeftChild() {
    return this == parent->left;
}

RedBlackTreeNode* RedBlackTreeNode::getUncle() {
    RedBlackTreeNode* grandparent = parent->parent;

    if(parent == nullptr || grandparent == nullptr) {
        return nullptr;
    }

    if(parent->isLeftChild()) {
        return grandparent->right;
    }

    return grandparent->left;
}

RedBlackTreeNode* RedBlackTreeNode::getSibling() {
    if(parent == nullptr) {
        return nullptr;
    }

    if(isLeftChild()) {
        return parent->right;
    }

    return parent->left;
}

void RedBlackTreeNode::becomeChildOf(RedBlackTreeNode *newParent) {
    if(parent != nullptr) {
        if( isLeftChild() ) {
            parent->left = newParent;
        } else {
            parent->right = newParent;
        }
    }

    newParent->parent = parent;
    parent = newParent;
}

bool RedBlackTreeNode::hasRedChild() {
    bool isRightChildRed = (right != nullptr && right->color == RED);
    bool isleftChildRed = (left != nullptr && left->color == RED);

    return isRightChildRed || isleftChildRed;
}