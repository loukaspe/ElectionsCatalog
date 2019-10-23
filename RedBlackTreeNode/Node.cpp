#include "Node.h"

Node::Node(Voter* voter) {
    this->voter = (Voter*) malloc( sizeof(Voter) );
    this->voter = new Voter(voter);

    left = nullptr;
    right = nullptr;
    parent = nullptr;

    color = RED;
}


bool Node::isLeftChild() {
    return this == parent->left;
}

Node* Node::getUncle() {
    Node* grandparent = parent->parent;

    if(parent == nullptr || grandparent == nullptr) {
        return nullptr;
    }

    if(parent->isLeftChild()) {
        return grandparent->right;
    }

    return grandparent->left;
}

Node* Node::getSibling() {
    if(parent == nullptr) {
        return nullptr;
    }

    if(isLeftChild()) {
        return parent->right;
    }

    return parent->left;
}

void Node::becomeChildOf(Node *newParent) {
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

bool Node::hasRedChild() {
    bool isRightChildRed = (right != nullptr && right->color == RED);
    bool isleftChildRed = (left != nullptr && left->color == RED);

    return isRightChildRed || isleftChildRed;
}