// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(nullptr){}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(IntBST::Node *n) {
    if(!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
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

    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(IntBST::Node *n) const {
    if(!n) return;

    cout << n->info << " "; // IMPLEMENT HERE

    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(IntBST::Node *n) const {
    if(!n) return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(IntBST::Node *n) const {
    if(!n) return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

int IntBST::sum() const {
    return sum(root); 
}

// recursive helper for sum
int IntBST::sum(IntBST::Node *n) const {
    if(!n) return 0;
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(IntBST::Node *n) const {
    return 1 + count(n->right) + count(n->left);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, IntBST::Node* n) const{
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
    Node* pre = nullptr;
    while(curr){
        if(value > curr->info) { 
            pre = curr;
            curr = curr->right;
        }
        else curr = curr->left;
    }
    return pre;
}


// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* p = getPredecessorNode(value);
    return p ? p->info : 0;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* curr = root;
    Node* pre = nullptr;
    while(curr){
        if(value < curr->info) { 
            pre = curr;
            curr = curr->left;
        }
        else curr = curr->right;
    }
    return pre;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return getSuccessorNode(value)->info;
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
     Node* curr = root;
    Node* parent = nullptr;

    while (curr && curr->info != value) {
        parent = curr;
        if (value < curr->info)
            curr = curr->left;
        else
            curr = curr->right;
    }

    if (!curr) return false; 

    
    if (!curr->left || !curr->right) {
        Node* child = curr->left ? curr->left : curr->right;

        if (!parent)
            root = child;
        else if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;

        delete curr;
    }
    
    else {
        Node* pred = getPredecessorNode(value);
        int predValue = pred->info;
        remove(predValue);
        curr->info = predValue;
    }

    return true;
}

