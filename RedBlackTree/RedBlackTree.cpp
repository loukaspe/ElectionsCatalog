#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    root = nullptr;
    size = 0;
}

Node* RedBlackTree::getRoot() {
    return root;
}

int RedBlackTree::getSize() {
    return size;
}

Node* RedBlackTree::searchForVoter(Voter* voter)  {
    Node* temp = root;
    char* key = Helper::copyString( voter->getId() );

    while(temp != nullptr) {
        if( strcmp( key, temp->voter->getId() ) < 0 ) {
            if(temp->left == nullptr) {
                break;
            }

            temp = temp->left;
            continue;
        }

        if( strcmp( key, temp->voter->getId() ) > 0 ) {
            if(temp->right == nullptr) {
                break;
            }

            temp = temp->right;
            continue;
        }

        // Key was found
        break;
    }

    return temp;
}

void RedBlackTree::insertVoterToTree(Voter* voter) {
    Node* newNode = new Node(voter);

    // If the root is null then insert as root
    if(root == nullptr) {
        //cout << "Root Created" << endl;
        newNode->color = BLACK;
        root = newNode;
        size++;
        return;
    }

    // Else search for the voter in the Tree
    Node* temp = searchForVoter(voter);

    // If we find it then return
    if( strcmp( temp->voter->getId(), newNode->voter->getId() ) == 0 ) {
        //cout << "Voter " << voter->getId() << " already in the RBT" << endl;
        return;
    }

    // Else searchForVoter() returns where to insert the newNode and we have to
    // connect newNode to the correct node of this
    newNode->parent = temp;

    // Insert on left and fix violation
    if( strcmp( newNode->voter->getId(), temp->voter->getId() ) < 0 ) {
        temp->left = newNode;
        size++;
        fixAdjacentRedNodesViolation(newNode);
        //cout << "Voter " << voter->getId() << " INSERTED" << endl;
        return;
    }

    // Insert on right and fix violation
    temp->right = newNode;
    size++;
    fixAdjacentRedNodesViolation(newNode);
    //cout << "Voter " << voter->getId() << " INSERTED" << endl;
}

void RedBlackTree::deleteVoterFromTree(Voter* voter) {
    // If Tree is empty, just return
    if(root == nullptr) {
        return;
    }

    Node* temp = searchForVoter(voter);

    if( strcmp( temp->voter->getId(), voter->getId() ) != 0 ) {
        return;
    }

    deleteNode(temp);
    size--;
}

// prints inorder of the tree
void RedBlackTree::printInOrder() {
    cout << "Inorder: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        inorder(root);
    cout << endl;
}

// prints level order of the tree
void RedBlackTree::printLevelOrder() {
    cout << "Level order: " << endl;
    if (root == NULL)
        cout << "Tree is empty" << endl;
    else
        levelOrder(root);
    cout << endl;
}

void RedBlackTree::rotateLeft(Node* node) {
    Node* newParent = node->right;

    // Update Root if node is the root
    if(node == root) {
        root = newParent;
    }

    node->becomeChildOf(newParent);

    // Connect node with newParent's left element
    node->right = newParent->left;

    // If newParent's left element is not null, connect it with node
    if(newParent->left != nullptr) {
        newParent->left->parent = node;
    }

    // Connect new parent with node
    newParent->left = node;
}

void RedBlackTree::rotateRight(Node* node) {
    Node* newParent = node->left;

    if(node == root) {
        root = newParent;
    }

    node->becomeChildOf(newParent);

    // Connect node with newParent's right element
    node->left =newParent->right;

    // If newParent's right element is not null, connect it with node
    if(newParent->right != nullptr) {
        newParent->right->parent = node;
    }

    // Connect new parent with node
    newParent->right = node;
}

void RedBlackTree::swapColorsBetweenNodes(Node* firstNode, Node* secondNode ) {
    COLOR temp;
    temp = firstNode->color;
    firstNode->color = secondNode->color;
    secondNode->color = temp;
}

void RedBlackTree::swapVotersBetweenNodes(Node* firstNode, Node* secondNode ) {
    Voter* temp = firstNode->voter;
    firstNode->voter = secondNode->voter;
    secondNode->voter = temp;
}

void RedBlackTree::fixAdjacentRedNodesViolation(Node* node) {
    // If our given node is the root, then we make it BLACK and return
    if(node == root) {
        node->color = BLACK;
        return;
    }

    Node* parent = node->parent;
    Node* grandparent = parent->parent;
    Node* uncle = node->getUncle();

    // If parent's color is BLACK, then we don't have to fix anything
    if(parent->color == BLACK) {
        return;
    }

    // If uncle is RED, make it BLACK and recurse through grandparent
    if( uncle != nullptr && uncle->color == RED) {
        parent->color = BLACK;
        uncle->color = BLACK;
        grandparent->color = RED;
        fixAdjacentRedNodesViolation(grandparent);
        return;
    }

    // Else we perform LeftLeft, LeftRight, RightLeft and RightRight
    // configurations

    if( parent->isLeftChild() && node->isLeftChild() ) {
        swapColorsBetweenNodes(parent, grandparent);
        rotateRight(grandparent);
        return;
    }

    if( parent->isLeftChild() ) {
        rotateLeft(parent);
        swapColorsBetweenNodes(node, grandparent);
        rotateRight(grandparent);
        return;
    }

    if( node->isLeftChild() ) {
        rotateRight(parent);
        swapColorsBetweenNodes(node, grandparent);
        rotateLeft(grandparent);
        return;
    }

    swapColorsBetweenNodes(parent, grandparent);
    rotateLeft(grandparent);
}

/* Finds and returns the successor of subtree from node.
 * By successor we mean a leaf node or a node with one child */
Node* RedBlackTree::findSuccessorInSubTree(Node* node) {
    Node* temp = node;

    while(temp->left != nullptr) {
        temp = temp->left;
    }

    return temp;
}


Node* RedBlackTree::findNodeToReplaceDeletedNodeInBST(Node* node) {

     // When node has two children
    if( node->left != nullptr && node->right != nullptr ) {
        return findSuccessorInSubTree(node->right);
    }

    // When node is a leaf node
    if( node->left == nullptr && node->right == nullptr ) {
        return nullptr;
    }

    // When node has a single ..
    if(node->left != nullptr) {
        // .. left child
        return node->left;
    }

    // .. right child
    return node->right;
}

void RedBlackTree::deleteNode(Node* givenNode) {
    Node* nodeToReplaceGivenNode = findNodeToReplaceDeletedNodeInBST(givenNode);

    bool areBothNodesBlack = (
        (givenNode->color == BLACK)
        && (
                nodeToReplaceGivenNode == nullptr
                || nodeToReplaceGivenNode->color == BLACK
        )
    );

    Node* parent = givenNode->parent;

    // If nodeToReplaceGivenNode is null then givenNode is a leaf node
    if(nodeToReplaceGivenNode == nullptr) {

        // If givenNode is the root then we make the root null
        if(givenNode == root) {
            root = nullptr;
            delete givenNode;
            return;
        }

        // If both nodes are black and givenNode is leaf, then
        // fix double black at givenNode and delete it after checking
        // if is the left or the right child
        if( areBothNodesBlack && givenNode->isLeftChild() ) {
            convertDoubleBlackChildToSingleAfterDeletion(givenNode);
            parent->left = nullptr;
            delete givenNode;
            return;
        }

        if(areBothNodesBlack) {
            convertDoubleBlackChildToSingleAfterDeletion(givenNode);
            parent->right = nullptr;
            delete givenNode;
            return;
        }

        // Else, either givenNode or nodeToReplaceGivenNode is red

        // If givenNode's sibling is not null, make it RED
        if(givenNode->getSibling() != nullptr) {
            givenNode->getSibling()->color = RED;
        }

        // Delete givenNode
        if( givenNode->isLeftChild() ) {
            parent->left = nullptr;
            delete givenNode;
            return;
        }

        parent->right = nullptr;
        delete givenNode;
        return;
    }

    // If givenNode has a single child
    if( givenNode->left == nullptr || givenNode->right == nullptr) {

        // If givenNode is the root, set value of nodeToReplaceGivenNode to
        // givenNode's and delete nodeToReplaceGivenNode
        if(givenNode == root) {
            givenNode->voter = nodeToReplaceGivenNode->voter;
            givenNode->left = nullptr;
            givenNode->right = nullptr;
            delete nodeToReplaceGivenNode;
            // TODO isws thelei kai thesimo root
            return;
        }

        // Detach givenNode from tree and move nodeToReplaceGivenNode up
        if(givenNode->isLeftChild()) {
            parent->left = nodeToReplaceGivenNode;
        } else {
            parent->right = nodeToReplaceGivenNode;
        }

        delete givenNode;

        nodeToReplaceGivenNode->parent = parent;

        // If both nodes are BLACK, fix double double at nodeToReplaceGivenNode
        if(areBothNodesBlack) {
            convertDoubleBlackChildToSingleAfterDeletion(nodeToReplaceGivenNode);
            return;
        }

        // Else one is RED, so make nodeToReplaceGivenNode BLACK
        nodeToReplaceGivenNode->color = BLACK;
        return;
    }

    // If givenNode has two children, then swap values with successor and
    // recurse through nodeToReplaceGivenNode
    swapVotersBetweenNodes(nodeToReplaceGivenNode, givenNode);
    deleteNode(nodeToReplaceGivenNode);
}

void RedBlackTree::convertDoubleBlackChildToSingleAfterDeletion(Node* node) {
    // If we reach root in recursion, return
    if(node == root) {
        return;
    }

    Node* sibling = node->getSibling();
    Node* parent = node->parent;

    // No sibling found, double black pushed up
    if(sibling == nullptr) {
        convertDoubleBlackChildToSingleAfterDeletion(parent);
        return;
    }

    // If sibling is RED perform rotation
    if(sibling->color == RED) {
        parent->color = RED;
        sibling->color = BLACK;

        // Left Case
        if( sibling->isLeftChild() ) {
            rotateRight(parent);
            convertDoubleBlackChildToSingleAfterDeletion(node);
            return;
        }

        // Right Case
        rotateLeft(parent);
        convertDoubleBlackChildToSingleAfterDeletion(node);
        return;
    }

    // If sibling is BLACK and has at least one RED child
    if( sibling->hasRedChild() ) {
        // LeftLeft Case
        if (
            (
                sibling->left != nullptr
                && sibling->left->color == RED
            )
            && sibling->isLeftChild()
        ) {
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rotateRight(parent);
            parent->color = BLACK;
            return;
        }

        // RightLeft Case
        if( sibling->left != nullptr && sibling->left->color == RED ) {
            sibling->left->color = parent->color;
            rotateRight(sibling);
            rotateLeft(parent);
            parent->color = BLACK;
            return;
        }

        // LeftRight Case
        if( sibling->isLeftChild() ) {
            sibling->right->color = parent->color;
            rotateLeft(sibling);
            rotateRight(parent);
            parent->color = BLACK;
            return;
        }

        // RightRight Case
        sibling->right->color = sibling->color;
        sibling->color = parent->color;
        rotateLeft(parent);
        parent->color = BLACK;
        return;
    }

    // Both children are BLACK
    sibling->color = RED;

    if (parent->color == BLACK) {
        convertDoubleBlackChildToSingleAfterDeletion(parent);
        return;
    }

    parent->color = BLACK;
}

// prints level order for given node
void RedBlackTree::levelOrder(Node *x) {
    if (x == nullptr)
        // return if node is null
        return;

    // queue for level order
    std::queue<Node *> q;
    Node *curr;

    // push x
    q.push(x);

    while (!q.empty()) {
        // while q is not empty
        // dequeue
        curr = q.front();
        q.pop();

        // print node value
        cout << curr->voter->getId() << " ";

        // push children to queue
        if (curr->left != NULL)
            q.push(curr->left);
        if (curr->right != NULL)
            q.push(curr->right);
    }
}

// prints inorder recursively
void RedBlackTree::inorder(Node *x) {
    if (x == nullptr)
        return;
    inorder(x->left);
    cout << x->voter->getId() << " ";
    inorder(x->right);
}
