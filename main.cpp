#include "cards.h"
#include "utility.h"
//#include "moreFuncs.cpp"

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

  //cout << "BEFORE READ" << endl;
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
    //cout << suit << " " << value << endl;
    aliceBST.insert(suit, value);
    //cout << "after insert" << endl;
  }
  cardFile1.close();
  //cout << "after cardfile1 close" << endl;



  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line.at(0);
    stringValue = line.substr(2);

    if (stringValue == "10"){
        value = 't';
    }
    else{
        value = stringValue.at(0);
    }
    //cout << suit << " " << value << endl;
    bobBST.insert(suit, value);
    //cout << "after insert" << endl;
  }
  cardFile2.close();
  //cout << "after cardfile2 close" << endl;
  //cout << "AFTER READ" << endl;
  //IMPLEMENT THE GAME ITSELF (SHOULDNT TAKE TOO LONG, ASSUMING THAT THE BST FUNCTIONS WORK)
  
  //aliceBST.printGreatestToLeast();
  //cout << endl;
  //bobBST.printGreatestToLeast();

  //set to false if they don't have duplicate cards anymore (we would then print out there decks)
  bool duplicateCards = true;
  Node card;
  //cout << "OUTSIDE WHILE LOOP" << endl;
  while (duplicateCards){
    //cout << "Inside WHILE LOOP" << endl;
    card = aliceBST.ForwardInOrderSearch(bobBST);
    //cout << "SDLFJ" << endl;
    //cout << card.suit << " " << card.value << endl;
    if ((card.suit + card.value) != 0){
      cout << "Alice picked matching card ";
      card.printNode();
      aliceBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
      bobBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
      //cout << "after remove" << endl;
    }
    else{
      //cout << "INSIDE FIRST ELSE" << endl;
      duplicateCards = false;
      break;
    }

    card = bobBST.BackwardInOrderSearch(aliceBST);
    //cout << card.suit << " " << card.value << endl;
    if ((card.suit + card.value) != 0){
      cout << "Bob picked matching card ";
      card.printNode();
      aliceBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
      bobBST.remove(intSuitToChar(card.suit), intValueToChar(card.value));
    }
    else{
      //cout << "INSIDE SECOND ELSE" << endl;
      duplicateCards = false;
      break;
    }
    //iterate from least to greatest in alice's hand, and for every card in alice's hand, use the find function to see if it's in
  }
  //cout << "AFTER WHILE LOOP" << endl;
  cout << endl;

  cout << "Alice's cards:" << endl;
  aliceBST.printLeastToGreatest();
  cout << endl;

  cout << "Bob's cards:" << endl;
  bobBST.printLeastToGreatest();
  cout << endl;

  return 0;
}