//cards.cpp
//Authors: Your name and your partner's name
//Implementation of the classes defined in cards.h
#include "cards.h"
#include "utility.h"
#include <iostream>
// using std::cout;
// using std::endl;
using namespace std;

// int charSuitToInt(char c){
//     //clubs - 1, diamonds - 2, spades - 3, hearts - 4
//     if (c == 'c'){
//         return 1;
//     }
//     else if (c == 'd'){
//         return 2;
//     }
//     else if (c == 's'){
//         return 3;
//     }
//     else if (c == 'h'){
//         return 4;
//     }
//     return 0;
// }
// int charValueToInt(char c){
//     //ace - 1, 2, 3, . . . 10, jack - 11, queen - 12, king - 13
//     if (isalpha(c)){
//         if (c == 't'){
//             return 10;
//         }
//         if (c == 'j'){
//             return 11;
//         }
//         else if (c == 'q'){
//             return 12;
//         }
//         else if (c == 'k'){
//             return 13;
//         }
//         else if (c == 'a'){
//             return 1;
//         }
//         return 0;
//     }
//     return c - '0';
// }
// char intSuitToChar(int i){
//     //clubs - 1, diamonds - 2, spades - 3, hearts - 4
//     if (i == 1){
//         return 'c';
//     }
//     else if (i == 2){
//         return 'd';
//     }
//     else if (i == 3){
//         return 's';
//     }
//     else if (i == 4){
//         return 'h';
//     }
//     return '0';
// }

// char intValueToChar(int i){
//     //ace - 1, 2, 3, . . . 10, jack - 11, queen - 12, king - 13
//     if (i == 10){
//         return 't';
//     }
//     if (i == 11){
//         return 'j';
//     }
//     else if (i == 12){
//         return 'q';
//     }
//     else if (i == 13){
//         return 'k';
//     }
//     else if (i == 1){
//         return 'a';
//     }
//     return '0' + i;
// }

// constructor sets up empty tree
CardBST::CardBST(){
    root = nullptr;
}

// recursive helper for destructor
void clear(Node *n){
    //MAKE SURE THAT THIS FUNCTION ALSO DELETES THE ROOT
    if (n){
        //cout << "inside if" << endl;
        clear(n->left);
        clear(n->right);
        // if (n->left){
        //     clear(n->left);
        // }
        // if (n->right){
        //     clear(n->right);
        // }
        delete n;
    }
}

// destructor deletes all nodes
CardBST::~CardBST(){
    clear(root);
    //cout << "destructor" << endl;
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
// Node* getNodeFor(int suit, int value, Node* n){
//     if(n){
//         if(n->suit == suit && n->value == value){
//             return n;
//         }
//         else if(n->suit < suit){
//             return getNodeFor(suit, value, n->right);
//         }
//         else if(n->suit > suit){
//             return getNodeFor(suit, value, n->left);
//         }
//         //can change to else, but might have to specify the condition (playing it safe for now)
//         else if (n->suit == suit){
//             if(n->value < value){
//                 return getNodeFor(suit, value, n->right);
//             }
//             else if(n->value > value){
//                 return getNodeFor(suit, value, n->left);
//             }            
//         }
//     }
//     //this is probably fine, but make sure
//     return nullptr;
// }
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
    //this is probably fine, but make sure
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

// recursive helper for insert (assumes n is never 0)
// bool CardBST::insert(int suit, int value, Node*& n) {
//     if (n){
//         if (suit == n->suit && value == n->value){
//             //cout << "first if" << endl;
//             return false;
//         }
//         else if (suit < n->suit) {
//             //cout << "second if" << endl;
//             if (n->left){
//                 return insert(suit, value, n->left);
//             }
//             else {
//                 n->left = new Node(suit, value);
//                 n->left->parent = n;
//                 return true;
//             }
//         }
//         else if (suit > n->suit) {
//             //cout << "else if 1" << endl;
//             //cout << "current suit: " << suit << " n->suit: " << n->suit << endl;
//             //IT'S ENTERING THE BELOW IF STATEMENT EVEN THOUGH N->RIGHT SHOULD BE NULL
//             if (n->right){
//                 //cout << "LLIJSDFLJ" << endl;
//                 //cout << n->right << endl;
//                 return insert(suit, value, n->right);
//             }
//             else {
//                 n->right = new Node(suit, value);
//                 n->right->parent = n;
//                 return true;
//             }
//         }
//         else{
//             //cout << "else" << endl;
//             if (value < n->value){
//                 if (n->left){
//                     return insert(suit, value, n->left);
//                 }
//                 else {
//                     n->left = new Node(suit, value);
//                     n->left->parent = n;
//                     return true;
//                 }
//             }
//             else{
//                 if (n->right){
//                     return insert(suit, value, n->right);
//                 }
//                 else {
//                     n->right = new Node(suit, value);
//                     n->right->parent = n;
//                     return true;
//                 }
//             }
//         }
//         //cout << "after else" << endl;
//     }
// }

bool CardBST::insert(Node insertNode, Node*& n) {
    if (n){
        //cout << "inside helper insert if" << endl;
        if (insertNode == *n){
            //cout << "first if" << endl;
            return false;
        }
        //cout << "after first under if" << endl;
        else if (insertNode < *n) {
            //cout << "second if" << endl;
            //cout << "inside first else if" << endl;
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
            //cout << "else if 1" << endl;
            //cout << "current suit: " << suit << " n->suit: " << n->suit << endl;
            //IT'S ENTERING THE BELOW IF STATEMENT EVEN THOUGH N->RIGHT SHOULD BE NULL
            //cout << "inside second else if" << endl;
            if (n->right){
                //cout << "LLIJSDFLJ" << endl;
                return insert(insertNode, n->right);
            }
            else {
                n->right = new Node(insertNode.suit, insertNode.value);
                n->right->parent = n;
                return true;
            }
        }
        //cout << "after else" << endl;
    }
}

// insert value in tree; return false if duplicate
bool CardBST::insert(char suit, char value) {
    // int suitInt = charSuitToInt(suit);
    // int valueInt = charValueToInt(value);
    // handle special case of empty tree first
    if (!root) {
        //cout << "inside !ROOT if" << endl;
        root = new Node(suit, value);
        return true;
    }
    //cout << "after main insert if" << endl;
    // otherwise use recursive helper
    //cout << "GOING INTO HELPER INSERT FUNCTION" << endl;
    Node insertNode = Node(suit, value);
    //cout << "after insertNode constructor" << endl;
    return insert(insertNode, root);
    //cout << "after main insert return statement" << endl;
}

// bool CardBST::insert(int suit, int value) {
//     // handle special case of empty tree first
//     if (!root) {
//         root = new Node(suit, value);
//         return true;
//     }
//     // otherwise use recursive helper
//     //cout << "GOING INTO HELPER INSERT FUNCTION" << endl;
//     Node insertNode = Node(suit, value);
//     return insert(insertNode, root);
// }

void CardBST::copyConstructorHelper(Node *n){
    //cout << "inside copy constructor helper" << endl;
    if (n){
        //cout << n->suit << endl;
        //cout << "inside copy constructor if" << endl;
        insert(intSuitToChar(n->suit), intValueToChar(n->value));
        //cout << "after copy constructor insert" << endl;
        copyConstructorHelper(n->left);
        //cout << "LSDJF" << endl;
        copyConstructorHelper(n->right);
    }
}
CardBST::CardBST(const CardBST& source){
    //need to delete the current source CardBST object (that's been inputted in the function argument)
    //basically we just call the clear() function
    //then we allocate memory for source's root
    //then we traverse through the current BST and use the insert function to insert nodes into the copy
    //cout << "before clear" << endl;
    //if (!root){}
    //clear(root);
    //cout << "after clear function" << endl;
    root = nullptr;
    
    //make sure that the below line is valid (not sure if reference is necessary or not in this case)
    Node* sourceRoot = source.root;
    //cout << (sourceRoot->value) << endl;
    //cout << "after sourceRoot" << endl;
    copyConstructorHelper(sourceRoot);
    //cout << "after copy constructor helper" << endl;
}

// returns the Node containing the predecessor of the given value
Node* CardBST::getPredecessorNode(char suit, char value) const{
    // int suitInt = charSuitToInt(suit);
    // int valueInt = charValueToInt(value);
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
                //LOOK INTO THE PLACEMENT OF THE BELOW TWO LINES (THINK ABOUT HOW THE FUNCTION WORKS)
                // int nodeSuit = n->suit;
                // int nodeValue = n->value;                
                while(n->parent != root && n->parent->left == n){
                    n = n->parent;
                }
                //we're saying that if the card's total value is less than the parent's total value
                //then assign the current node to the parent node (not sure if this the right way to do the function tho, but it's fine for now ig)
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
// returns the Node containing the predecessor of the given value
// Node* CardBST::getPredecessorNode(char suit, char value) const{
//     // int suitInt = charSuitToInt(suit);
//     // int valueInt = charValueToInt(value);
//     Node* n = getNodeFor(suit, value, root);

//     if (n){
//         if (n->left){
//             n = n->left;
//             while(n->right){
//                 n = n->right;
//             }
//             return n;
//         }
//         else{
//             if (n->parent->right == n){
//                 return n->parent;
//             }
//             else if (n->parent->left == n){
//                 cout << "AS;JASDF;J" << endl;
//                 //LOOK INTO THE PLACEMENT OF THE BELOW TWO LINES (THINK ABOUT HOW THE FUNCTION WORKS)
//                 // int nodeSuit = n->suit;
//                 // int nodeValue = n->value;
                
//                 while(n->parent != root && n->parent->left == n){
//                     cout << "iteration" << endl;
//                     n = n->parent;
//                 }
//                 cout << "after while" << endl;
//                 //n->printNode();
//                 //cout << n << endl;
//                 // cout << n->parent << endl;
//                 // cout << (n->parent == root) << endl;
//                 cout << "OUEROU" << endl;
//                 if (n->parent == root){
//                     cout << "SD:FJ" << endl;
//                     return nullptr;
//                     cout << "PIPPIPI" << endl;
//                 }
//                 cout << "after if" << endl;
//                 // int nodeSuit = n->suit;
//                 // int nodeValue = n->value;
//                 if (*n->parent < *n){
//                     n = n->parent;
//                 }
//                 else if (*n->parent > *n){
//                     return nullptr;
//                 }
//                 return n;
//             }
//         }
//     }
//     return nullptr;
// }

// returns the Node containing the successor of the given value
Node* CardBST::getSuccessorNode(char suit, char value) const{
    // int suitInt = charSuitToInt(suit);
    // int valueInt = charValueToInt(value);
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
                // int nodeSuit = n->suit;
                // int nodeValue = n->value;
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

// //returns true if the node exist and was deleted or false if the node does not exist
// bool CardBST::remove(char suit, char value){
//     int suitInt = charSuitToInt(suit);
//     int valueInt = charValueToInt(value);
//     Node* removeNode = getNodeFor(suitInt, valueInt, root);

//     if(removeNode){
//         //is using a reference okay in this instance?
//         Node* parent = removeNode->parent;

//         if (removeNode->left == nullptr && removeNode->right == nullptr){
//             //this if statement doesn't seem necessary (just need the opposite - case where we del a non-root node)
//             if (removeNode == root){
//                 root = nullptr;
//             }
//             //we need to check if the removeNode is the left or right child of the parent node
//             //oh ig since there are no duplicates in the BST, we can still use the == operator
//             else{ 
//                 if (parent->left == removeNode){
//                     parent->left = nullptr;
//                 }  
//                 else{
//                     parent->right = nullptr;
//                 }
//             }
//             delete removeNode;
//         }

//         else if (removeNode->left != nullptr && removeNode->right == nullptr) {
//             //if root is the node that we want to remove, we simply point it 
//             if (removeNode == root) {
//                 root = removeNode->left;
//             } 
//             else {
//                 if (parent->left == removeNode) {
//                     removeNode->left->parent = parent;
//                     parent->left = removeNode->left;
                    
//                 }
//                 else {
//                     removeNode->left->parent = parent;
//                     parent->right = removeNode->left;
//                 }
//             }
//             //not sure if this below line matters since we're deallocating removeNode anyway
//             //so these 'changes' won't be saved
//             //removeNode->left->parent = parent;
//             delete removeNode;
//         }

//         else if (removeNode->left == nullptr && removeNode->right != nullptr) {
//             if (removeNode == root) {
//                 root = removeNode->right;
//             }
//             else {
//                 if (parent->left == removeNode) {
//                     removeNode->right->parent = parent;
//                     parent->left = removeNode->right;
//                 }
//                 else {
//                     removeNode->right->parent = parent;
//                     parent->right = removeNode->right;
//                 }
//             }
//             //same as above
//             //removeNode->right->parent = parent;
//             delete removeNode;
//         }

//         else {
//             //this is for if the removeNode has two children
//             //we're replacing the value of the removeNode with the value of it's successor
//             //and then we're pointing the removeNode to the successorNode
//             //then we update the parent node of the successorNode to null (based on whether it's a left/right child)
//             //then we delete the successorNode
//             Node* successor = getSuccessorNode(intSuitToChar(removeNode->suit), intValueToChar(removeNode->value));

//             if (successor){
//                 removeNode->suit = successor->suit;
//                 removeNode->value = successor->value;
//                 removeNode = successor;
//                 parent = removeNode->parent;
//                 if (removeNode->parent->left == removeNode) {
//                     parent->left = nullptr;
//                 }
//                 else {
//                     parent->right = nullptr;
//                 }
//             }
//             else{

//             }
//             delete removeNode;

        
//             // Node* successor = getSuccessorNode(intSuitToChar(removeNode->suit), intValueToChar(removeNode->value));

//             // Card sucVal = suc->info;
//             // remove(suc->info);
//             // p->info = sucVal;
//             // return true;
        





//         }
//         return true;
//     }
//     return false;
// }
// bool Cards::remove(Card value){
//     Node* p = getNodeFor(value, root);

//     if (!p->left && !p->right){
//         if(p != root){
//             if(p->parent->left == p){
//                 p->parent->left = nullptr;
//             }
//             else{
//                 p->parent->right = nullptr;
//             }
//         }
//         else{
//             root = nullptr;
//         }

//         delete(p); 
//         return true;
//     }
//     else if (p->left && p->right){
//         Node* suc = getSuccessorNode(value);

//         Card sucVal = suc->info;
//         remove(suc->info);
//         p->info = sucVal;
//         return true;
//     }
//     else{
//         Node* next;
        
//         if(p->left){
//             next = p->left;
//         }
//         else{
//             next = p->right;
//         }

//         if(p!= root){
//             if(p == p->parent->left){
//                 p->parent->left = next;
//             }
//             else{
//                 p->parent->right = next;
//             }
//             next->parent = p->parent;
//         }
//         else{
//             root = next;
//         }

//         delete(p);
//         return true;
//     }
//     return false;
// }

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
        //if (successor){
        char sucSuit = intSuitToChar(successor->suit);
        char sucVal = intValueToChar(successor->value);
        remove(sucSuit, sucVal);
        p->suit = charSuitToInt(sucSuit);
        p->value = charValueToInt(sucVal);
        return true;
        //}
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


// bool CardBST::remove(char suit, char value){
//     // int suitInt = charSuitToInt(suit);
//     // int valueInt = charValueToInt(value);
//     cout << "YYYY: " << suit << " " << value << endl;
//     Node* p = getNodeFor(suit, value, root);
//     cout << "after get node for" << endl;
//     if (p){
//         p->printNode();
//     }
//     cout << "after print node" << endl;
//     cout << p << endl;
//     cout << "bnbnbnbn" << endl;
//     if (!p->left && !p->right){
//         cout << "first if" << endl;
//         if(p != root){
//             if(p->parent->left == p){
//                 p->parent->left = nullptr;
//             }
//             else{
//                 p->parent->right = nullptr;
//             }
//         }
//         else{
//             cout << "root else statement" << endl;
//             root = nullptr;
//         }

//         delete(p); 
//         return true;
//     }
//     else if (p->left && p->right){
//         cout << " main else if" << endl;
//         Node* successor = getSuccessorNode(suit, value);
//         cout << "after successor" << endl;

//         if (successor){
//             cout << "inside successor" << endl;
//             char sucSuit = intSuitToChar(successor->suit);
//             char sucVal = intValueToChar(successor->value);
//             successor->printNode();
//             cout << "sfd;jsdf;j" << endl;
//             remove(sucSuit, sucVal);
//             cout << "qweqweqwe" << endl;
//             p->suit = intSuitToChar(sucSuit);
//             p->value = intValueToChar(sucVal);
//             return true;
//         }
//     }
//     else{
//         Node* next;
        
//         if(p->left){
//             next = p->left;
//         }
//         else{
//             next = p->right;
//         }

//         if(p!= root){
//             if(p == p->parent->left){
//                 p->parent->left = next;
//             }
//             else{
//                 p->parent->right = next;
//             }
//             next->parent = p->parent;
//         }
//         else{
//             root = next;
//         }

//         delete(p);
//         return true;
//     }
//     return false;
// }

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
// // print tree data pre-order
// void CardBST::printPreOrder() const {
//     printPreOrder(root);
// }

// // recsive helper for printPreOrder()
// void CardBST::printPreOrder(Node *n) const {
//     if (n) {
//         cout << n->info << " ";
//         printPreOrder(n->left);
//         printPreOrder(n->right);
//     }
// }

// // print tree data in-order, with helper
// void CardBST::printInOrder() const {
//     printInOrder(root);
// }
// void CardBST::printInOrder(Node *n) const {
//     if(n){
//         printInOrder(n->left);
//         cout << n->info << " ";
//         printInOrder(n->right);
//     }
// }

// // prints tree data post-order, with helper
// void CardBST::printPostOrder() const {
//     printPostOrder(root);
// }

// void CardBST::printPostOrder(Node *n) const {
//     if(n){
//         printPostOrder(n->left);
//         printPostOrder(n->right);
//         cout << n->info << " ";
//     }
// }


// // return count of values
// int CardBST::count() const {
//     return count(root);
// }

// // recsive helper for count
// int CardBST::count(Node *n) const {
//     if(n){
//         return 1 + count(n->left) + count(n->right);
//     }
//     return 0;
// }
