//cards.h

#ifndef CARDS_H
#define CARDS_H

class Node{
   public:
      Node* left;
      Node* right;
      Node* parent;

      int suit;
      int value;
      
      Node();
      Node(const char suit, const char value);
      Node(const int suit, const int value);
      bool operator<(Node& n);   
      bool operator==(Node& n);
      bool operator>(Node& n);
      void setSuit(const char suit);
      void setValue(const char value);
      void setSuit(const int suit);
      void setValue(const int value);
      void printNode() const;

};

class CardBST{
   public:
      CardBST();
      ~CardBST();
      void copyConstructorHelper(Node *n);
      CardBST(const CardBST& source);
      Node* getPredecessorNode(char suit, char value) const;
      Node* getSuccessorNode(char suit, char value) const;

      bool insert(char suit, char value);
      bool insert(Node insertNode, Node*& n);
      bool remove(char suit, char value);
      bool find(char suit, char value) const;
      bool find(int suit, int value) const;
      int getPredecessorSuit(char suit, char value) const;
      int getPredecessorValue(char suit, char value) const;
      int getSuccessorSuit(char suit, char value) const;
      int getSuccessorValue(char suit, char value) const;
      
      void printLeastToGreatestHelper(Node* n) const;
      void printGreatestToLeastHelper(Node* n) const;
      void printLeastToGreatest() const;
      void printGreatestToLeast() const;
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
};

#endif
