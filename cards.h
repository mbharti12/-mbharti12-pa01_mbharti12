//cards.h
//Authors: Your name and your partner's name
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

//bst.cpp
//BST ADT
class Node{
   public:
      Node* left;
      Node* right;
      Node* parent;
      //can represent suit & value as integers
      //it would make sense for value to be an integer since most are ints already (aside from the royals)
      //and since we'd be using integers to represent values, it would also make sense to represent them as suits (since we have to compare them anyway)

      int suit;
      int value;
      //can overload the constructor so that it takes in chars
      //and stores them with corresponding integers
      //if i defined a dictionary with corresponding character values pairs, that would be helpful
      
      Node(){
         suit = 0;
         value = 0;
      }
      //not sure if the member functions defined for CardBST (charSuitToInt and charValueToInt) can be used
      //if not it's fine, although it's not the most efficient thing
      Node(const char suit, const char value);
      Node(const int suit, const int value);
      bool operator<(Node*& n);   
      bool operator==(Node*& n);
      bool operator>(Node*& n);
      void setSuit(const char suit);
      void setValue(const char value);
      void printNode() const;

};

class CardBST{
   public:
   //WE CAN PUT HELPER FUNCTIONS IN THE PRIVATE SECTION
      CardBST();
      ~CardBST();
      //void clear(); //deletes all the nodes in the BST
      void copyConstructorHelper(Node *n);
      CardBST(const CardBST& source);
      //void copyConstructorHelper(Node *n);
      //we have to add 'int suit' to the arguments of some of these functions
      //since cards are made up of two components: suits and values
      //int charSuitToInt(char c);
      //int charValueToInt(char c);
      Node* getPredecessorNode(char suit, char value) const;
      Node* getSuccessorNode(char suit, char value) const;

      bool insert(char suit, char value); // return false if the value already exists
      bool insert(int suit, int value, Node*& n);
      //bool insert(int suit, int value, Node *n);
      bool remove(char suit, char value);
      bool find(char suit, char value) const;
      //make sure that this is the proper syntax (for a Node* return type)
      //CardBST::Node* getNodeFor(int suit, int value, Node* n) const;
      //Node* getPredecessorNode(char suit, char value) const;
      //int getPredecessor(char suit, char value) const;
      //Node* getSuccessorNode(char suit, char value) const;
      int getPredecessorSuit(char suit, char value) const;
      int getPredecessorValue(char suit, char value) const;
      int getSuccessorSuit(char suit, char value) const;
      int getSuccessorValue(char suit, char value) const;
      
      void printLeastToGreatestHelper(Node* n) const;
      void printGreatestToLeastHelper(Node* n) const;
      //void printNode(Node *n) const;
      void printLeastToGreatest() const;
      //void printLeastToGreatestHelper(Node* n) const;
      void printGreatestToLeast() const;
      //void printGreatestToLeastHelper(Node* n) const;
      Node* getMin();
      Node* getMax();
      Node* getMinHelper(Node* n);
      Node* getMaxHelper(Node* n);

      Node ForwardInOrderSearch(CardBST &hand);
      Node ForwardInOrderSearchHelper(Node* min, CardBST &hand);
      Node BackwardInOrderSearch(CardBST &hand);
      Node BackwardInOrderSearchHelper(Node* max, CardBST &hand);

   private:
      Node* root;
    //   bool insert(int value, bstNode* n);
    //   void printInOrderHelper(bstNode* n) const;
    //   void clear(bstNode* n);
    //   bstNode* getNode(int value) const;
     
};

// int bst::predecessor(int value) const{
//    //get a pointer to the node that has the key value
//    //Node* n = getNode(value);
//    return 42;

// }
// void bst::clear(bstNode* n){
//    //post order traversal!
//    if(!n) return;
//    clear(n->left); 
//    clear(n->right); //accessinhg memory that has been deleted
//    delete n;
// }

// void bst::printInOrderHelper(bstNode* n) const{
//    if(!n) return;
//    printInOrderHelper(n->left);
//    cout<<n->data<<" ";
//    printInOrderHelper(n->right);
// }



// int bst::max() const{
//    return std::numeric_limits<int>::max();
// }

// bool bst::insert(int value){
//    if(!root) {
//       root = new bstNode{value};
//       return true;
//    }else {
//       return insert(value, root);
//    }

// }

// bool bst::insert(int value, bstNode* n){
//    if (value == n->data)
//       return false;
//     if (value < n->data) {
//    if (n->left)
//        return insert(value, n->left);
//    else {
//        n->left = new bstNode(value);
//        n->left->parent = n;
//        return true;
//    }
//     }
//     else {
//    if (n->right)
//        return insert(value, n->right);
//    else {
//        n->right = new bstNode(value);
//        n->right->parent = n;
//        return true;
//    }
//  }
// }

#endif
