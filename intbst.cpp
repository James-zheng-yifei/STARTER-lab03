// intbst.cpp
// Implements class IntBST
// Yifei Zheng 1/30/2026

#include "intbst.h"
#include <vector>
#include <iostream>
using std::cout;
using std::vector;
using namespace std;

// constructor sets up empty tree
IntBST::IntBST() : root(nullptr){}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)

bool IntBST::insert(int value, Node* n) {
    if (value == n->info) return false;

    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        n->left = new Node(value);
        return true;
    } else {
        if (n->right)
            return insert(value, n->right);
        n->right = new Node(value);
        return true;
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    if (root) {
        printPreOrder(root);
    }
    cout << endl;
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n) return;

    cout << n->info;

    if (n->left) {
        cout << " ";
        printPreOrder(n->left);
    }
    if (n->right) {
        cout << " ";
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
    cout << endl;
}
void IntBST::printInOrder(Node *n) const {
    if (!n) return;
    
    // Print left subtree
    if (n->left) {
        printInOrder(n->left);
        cout << " ";
    }
    
    // Print current node
    cout << n->info;
    
    // Print right subtree
    if (n->right) {
        cout << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
    cout << endl;
}

void IntBST::printPostOrder(Node *n) const {
    if(!n) return;
    
    // Print left subtree
    if (n->left) {
        printPostOrder(n->left);
        cout << " ";
    }
    
    // Print right subtree
    if (n->right) {
        printPostOrder(n->right);
        cout << " ";
    }
    
    // Print current node
    cout << n->info;
}

int IntBST::sum() const {
    return sum(root); 
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n) return 0;
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if(!n) return nullptr;
    if(n->info == value) return n;
    if(value < n->info) return getNodeFor(value, n->left);
    else return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* curr = root;
    Node* predecessor = nullptr;

    while (curr) {
        if (value > curr->info) {
            predecessor = curr;
            curr = curr->right;
        } else if (value < curr->info) {
            curr = curr->left;
        } else {
            break;
        }
    }

    if (!curr) return nullptr;

    if (curr->left) {
        curr = curr->left;
        while (curr->right)
            curr = curr->right;
        return curr;
    }

    return predecessor;
}


// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* p = getPredecessorNode(value);
    return p ? p->info : 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
   Node* curr = root;
    Node* successor = nullptr;

    while (curr) {
        if (value < curr->info) {
            successor = curr;
            curr = curr->left;
        } else if (value > curr->info) {
            curr = curr->right;
        } else {
            break;
        }
    }

    if (!curr) return nullptr;

    if (curr->right) {
        curr = curr->right;
        while (curr->left)
            curr = curr->left;
        return curr;
    }

    return successor;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* s = getSuccessorNode(value);
    return s ? s->info : 0;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* parent = nullptr;
    Node* curr = root;
    
    // Find the node to delete and its parent
    while (curr && curr->info != value) {
        parent = curr;
        if (value < curr->info)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    if (!curr) return false; // Value not found
    
    // Case 1: Node has two children
    if (curr->left && curr->right) {
        // Find predecessor (largest in left subtree)
        Node* predParent = curr;
        Node* pred = curr->left;
        
        while (pred->right) {
            predParent = pred;
            pred = pred->right;
        }
        
        // Replace curr's value with predecessor's value
        curr->info = pred->info;
        
        // Now remove the predecessor node
        if (predParent == curr) {
            // Predecessor is direct left child
            predParent->left = pred->left;
        } else {
            predParent->right = pred->left;
        }
        
        delete pred;
    }
    // Case 2 & 3: Node has 0 or 1 child
    else {
        Node* child = (curr->left) ? curr->left : curr->right;
        
        if (!parent) {
            // Deleting root
            root = child;
        } else if (parent->left == curr) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        
        delete curr;
    }
    
    return true;
}

