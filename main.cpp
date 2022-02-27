#include "cards.h"
#include "utility.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  CardBST aliceBST;
  CardBST bobBST;
  string suitRead;
  string stringValue;
  char suit;
  char value;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    suit = line.at(0);
    stringValue = line.substr(2);

    if (stringValue == "10"){
        value = 't';
    }
    else{
        value = stringValue.at(0);
    }
    aliceBST.insert(suit, value);
  }
  cardFile1.close();

  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line.at(0);
    stringValue = line.substr(2);

    if (stringValue == "10"){
        value = 't';
    }
    else{
        value = stringValue.at(0);
    }
    bobBST.insert(suit, value);
  }
  cardFile2.close();

  bool duplicateCards = true;
  Node card;
  
  while (duplicateCards){
    card = aliceBST.ForwardInOrderSearch(bobBST);
    if ((card.suit + card.value) != 0){
      cout << "Alice picked matching card ";
      card.printNode();
      if (aliceBST.find(card.suit, card.value) && bobBST.find(card.suit, card.value)){
        aliceBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
        bobBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
      }
    }
    else{
      duplicateCards = false;
      break;
    }

    card = bobBST.BackwardInOrderSearch(aliceBST);
    if ((card.suit + card.value) != 0){
      cout << "Bob picked matching card ";
      card.printNode();
      if (aliceBST.find(card.suit, card.value) && bobBST.find(card.suit, card.value)){
        aliceBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
        bobBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
      }
    }
    else{
      duplicateCards = false;
      break;
    }
  }
  cout << endl;

  cout << "Alice's cards:" << endl;
  aliceBST.printLeastToGreatest();

  cout << endl;

  cout << "Bob's cards:" << endl;
  bobBST.printLeastToGreatest();

  return 0;
}