//cards.cpp
//Implementation of the classes defined in cards.h
#include "cards.h"
#include "utility.h"
#include <iostream>

using namespace std;

// constructor sets up empty tree
CardBST::CardBST(){
    root = nullptr;
}

// recursive helper for destructor
void clear(Node *n){
    if (n){
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// destructor deletes all nodes
CardBST::~CardBST(){
    clear(root);
}

Node* CardBST::getMinHelper(Node* n){
    if (n){
        if (n->left){
            return getMinHelper(n->left);
        }
        return n;
    }
}

Node* CardBST::getMaxHelper(Node* n){
    if (n){
        if (n->right){
            return getMaxHelper(n->right);
        }
        return n;
    }  
}

Node* CardBST::getMin(){
    if (root){
        return getMinHelper(root);
    }
    return nullptr;
}

Node* CardBST::getMax(){
    if (root){
        return getMaxHelper(root);
    }
    return nullptr;
}

Node CardBST::ForwardInOrderSearch(CardBST &hand){
    return ForwardInOrderSearchHelper(this->getMin(), hand);
}

Node CardBST::ForwardInOrderSearchHelper(Node* min, CardBST &hand){
    if (min){
        //cout << "start" << endl;
        //min->printNode();
        //seg fault here, so min probably doesn't point to anything (nullptr)
        if (min->suit == 0 && min->value == 0){
            //cout << "SE:KGH" << endl;
            return Node();
        }
        //cout << "middle" << endl;
        if (hand.find(intSuitToChar(min->suit), intValueToChar(min->value))){
            return *min;
        }
        //cout << getSuccessorNode(intSuitToChar(min->suit), intValueToChar(min->value)) << endl;
        //cout << "end" << endl;
        return this->ForwardInOrderSearchHelper(getSuccessorNode(intSuitToChar(min->suit), intValueToChar(min->value)), hand);
    }
    return Node();
}

Node CardBST::BackwardInOrderSearch(CardBST &hand){
    return BackwardInOrderSearchHelper(this->getMax(), hand);
}

Node CardBST::BackwardInOrderSearchHelper(Node* max, CardBST &hand){
    if (max){
        if (max->suit == 0 && max->value == 0){
            return Node();
        }
        if (hand.find(intSuitToChar(max->suit), intValueToChar(max->value))){
            return *max;
        }
        return this->BackwardInOrderSearchHelper(getPredecessorNode(intSuitToChar(max->suit), intValueToChar(max->value)), hand);
    }
    return Node();
}

Node* getNodeFor(Node& getNode, Node* n){
    if(n){
        if(getNode == *n){
            return n;
        }
        else if(getNode < *n){
            return getNodeFor(getNode, n->left);
        }
        else if(getNode > *n){
            return getNodeFor(getNode, n->right);
        }
    }
    return nullptr;
}

Node* getNodeFor(char suit, char value, Node* n){
    Node getNode = Node(suit, value);
    return getNodeFor(getNode, n);
}

Node* getNodeFor(int suit, int value, Node* n){
    Node getNode = Node(suit, value);
    return getNodeFor(getNode, n);
}

bool CardBST::insert(Node insertNode, Node*& n) {
    if (n){
        if (insertNode == *n){
            return false;
        }
        else if (insertNode < *n) {
            if (n->left){
                return insert(insertNode, n->left);
            }
            else {
                n->left = new Node(insertNode.suit, insertNode.value);
                n->left->parent = n;
                return true;
            }
        }
        else if (insertNode > *n) {
            if (n->right){
                return insert(insertNode, n->right);
            }
            else {
                n->right = new Node(insertNode.suit, insertNode.value);
                n->right->parent = n;
                return true;
            }
        }
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(char suit, char value) {
    if (!root) {
        root = new Node(suit, value);
        return true;
    }
    Node insertNode = Node(suit, value);
    return insert(insertNode, root);
}

void CardBST::copyConstructorHelper(Node *n){
    if (n){
        insert(intSuitToChar(n->suit), intValueToChar(n->value));
        copyConstructorHelper(n->left);
        copyConstructorHelper(n->right);
    }
}
CardBST::CardBST(const CardBST& source){
    root = nullptr;
    Node* sourceRoot = source.root;
    copyConstructorHelper(sourceRoot);
}

// returns the Node containing the predecessor of the given value
Node* CardBST::getPredecessorNode(char suit, char value) const{
    Node* n = getNodeFor(suit, value, root);

    if (n){
        if (n->left){
            n = n->left;
            while(n->right){
                n = n->right;
            }
            return n;
        }
        else{
            if (n->parent->right == n){
                return n->parent;
            }
            else if (n->parent->left == n){      
                while(n->parent != root && n->parent->left == n){
                    n = n->parent;
                }
                if (*n->parent < *n){
                    n = n->parent;
                }
                else if (*n->parent > *n){
                    return nullptr;
                }
                return n;
                
            }
        }
    }
    return nullptr;
}

// returns the Node containing the successor of the given value
Node* CardBST::getSuccessorNode(char suit, char value) const{
    Node* n = getNodeFor(suit, value, root);

    if(n){
        if(n->right){
            n = n->right;
            while(n->left){
                n = n->left;
            }
            return n;
        }
        else{
            if(n->parent->left == n){
                return n->parent;
            }
            else if(n->parent->right == n){
                while(n->parent != root && n->parent->right == n){
                    n = n->parent;
                }
                int nodeSuit = n->suit;
                int nodeValue = n->value;                
                if(n->parent->suit > nodeSuit){
                    n = n->parent;
                }
                else if(n->parent->suit < nodeSuit){
                    return nullptr;
                }
                else{
                    if(n->parent->value > nodeValue){
                        n = n->parent;
                    }
                    else if(n->parent->value < nodeValue){
                        return nullptr;
                    }        
                }
                return n;
                
            }
        }
    }
    return nullptr;
}

bool CardBST::remove(char suit, char value){
    Node* p = getNodeFor(suit, value, root);

    if (!p->left && !p->right){
        if(p != root){
            if(p->parent->left == p){
                p->parent->left = nullptr;
            }
            else{
                p->parent->right = nullptr;
            }
        }
        else{
            root = nullptr;
        }

        delete(p); 
        return true;
    }
    else if (p->left && p->right){
        Node* successor = getSuccessorNode(suit, value);
        char sucSuit = intSuitToChar(successor->suit);
        char sucVal = intValueToChar(successor->value);
        remove(sucSuit, sucVal);
        p->suit = charSuitToInt(sucSuit);
        p->value = charValueToInt(sucVal);
        return true;
    }
    else{
        Node* next;
        
        if(p->left){
            next = p->left;
        }
        else{
            next = p->right;
        }

        if(p!= root){
            if(p == p->parent->left){
                p->parent->left = next;
            }
            else{
                p->parent->right = next;
            }
            next->parent = p->parent;
        }
        else{
            root = next;
        }

        delete(p);
        return true;
    }
    return false;
}

// returns true if value is in the tree; false if not
bool CardBST::find(char suit, char value) const {
    if(getNodeFor(suit, value, root)){
        return true;
    }
    return false;
}

bool CardBST::find(int suit, int value) const {
    if(getNodeFor(suit, value, root)){
        return true;
    }
    return false;
}

int CardBST::getPredecessorSuit(char suit, char value) const{
    Node* n = getPredecessorNode(suit, value);
    if (n){
        return n->suit;
    }
    return 0;
}

int CardBST::getPredecessorValue(char suit, char value) const{
    Node* n = getPredecessorNode(suit, value);
    if (n){
        return n->value;
    }
    return 0;
}

int CardBST::getSuccessorSuit(char suit, char value) const{
    Node* n = getSuccessorNode(suit, value);
    if (n){
        return n->suit;
    }
    return 0;
}

int CardBST::getSuccessorValue(char suit, char value) const{
    Node* n = getSuccessorNode(suit, value);
    if (n){
        return n->value;
    }
    return 0;
}

//figure out spacing for these print functions (although it isn't too big of a deal)
void Node::printNode() const{
    if (value == 10){
        cout << intSuitToChar(suit) << " " << "10" << endl;
    }
    else{
        cout << intSuitToChar(suit) << " " << intValueToChar(value) << endl;
    }
}

void CardBST::printLeastToGreatest() const{
    printLeastToGreatestHelper(root);
}

void CardBST::printLeastToGreatestHelper(Node* n) const{
    if(n){
        printLeastToGreatestHelper(n->left);
        n->printNode();
        printLeastToGreatestHelper(n->right);
    }
}

void CardBST::printGreatestToLeast() const{
    printGreatestToLeastHelper(root);
}

void CardBST::printGreatestToLeastHelper(Node* n) const{
    if(n){
        printGreatestToLeastHelper(n->right);
        n->printNode();
        printGreatestToLeastHelper(n->left);
    }
}

void Node::setSuit(const char suit){
    int suitInt = charSuitToInt(suit);
    this->suit = suitInt;
}

void Node::setValue(const char value){
    int valueInt = charValueToInt(value);
    this->value = valueInt;
}

void Node::setSuit(const int suit){
    this->suit = suit;
}

void Node::setValue(const int value){
    this->value = value;
}

Node::Node(){
    suit = 0;
    value = 0;
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}

Node::Node(const char suit, const char value){
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->suit = charSuitToInt(suit);
    this->value = charValueToInt(value);
}

Node::Node(const int suit, const int value){
    this->parent = nullptr;
    this->right = nullptr;
    this->left = nullptr;
    this->suit = suit;
    this->value = value;
}

bool Node::operator<(Node& n){
    if (this->suit < n.suit){
        return true;
    }
    else if (this->suit > n.suit){
        return false;
    }
    else{
        if (this->value < n.value){
            return true;
        }
    }
    return false;
}

bool Node::operator==(Node& n){
    if (this->suit == n.suit && this->value == n.value){
        return true;
    }
    return false;
}

bool Node::operator>(Node& n){
    if (this->suit > n.suit){
        return true;
    }
    else if (this->suit < n.suit){
        return false;
    }
    else{
        if (this->value > n.value){
            return true;
        }
    }
    return false;
}