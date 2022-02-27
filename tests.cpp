#include "cards.h"

#include <fstream>
#include <iostream>

using namespace std;

int getTest();

int main() {

    CardBST bst1;
    string line;
    ifstream myfile ("a1.txt");
    string suitRead;
    string stringValue;

    char suit;
    char value;

    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            suit = line.at(0);
            stringValue = line.substr(2);

            if (stringValue == "10"){
                value = 't';
            }
            else{
                value = stringValue.at(0);
            }
            bst1.insert(suit, value);
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file";
    }
    bst1.printLeastToGreatest();
    bst1.remove('c', 'a');
    bst1.remove('c', '6');
    bst1.remove('c', '7');
    bst1.remove('c', '8');
    bst1.remove('c', 't');
    bst1.remove('d', 'a');
    bst1.remove('d', '2');
    cout << endl << endl << endl;
    bst1.printLeastToGreatest();
    cout << endl << endl << endl;
    CardBST bst2 = CardBST(bst1);
    bst2.printLeastToGreatest();

    cout << endl;
    cout << bst2.getPredecessorNode('c', '6') << endl;
    //bst2.getPredecessorNode('c', '4')->printNode();
    // bst2.getPredecessorNode('c', '6')->printNode();
    // bst2.getPredecessorNode('c', '7')->printNode();
    // bst2.getPredecessorNode('c', '8')->printNode();
    // bst2.getPredecessorNode('c', 't')->printNode();
    // bst2.getPredecessorNode('d', 'a')->printNode();
    // bst2.getPredecessorNode('d', '2')->printNode();

    cout << endl;
    cout << bst2.getSuccessorNode('h', 't') << endl;
    bst2.printLeastToGreatest();
    bst2.getSuccessorNode('c', '4')->printNode();
    bst2.getSuccessorNode('c', '6')->printNode();
    bst2.getSuccessorNode('c', '7')->printNode();
    bst2.getSuccessorNode('c', '8')->printNode();
    bst2.getSuccessorNode('c', 't')->printNode();
    bst2.getSuccessorNode('d', 'a')->printNode();
    bst2.getSuccessorNode('d', '2')->printNode();

    // bst2.getPredecessorNode('d', '4')->printNode();
    // bst2.getPredecessorNode('c', '5')->printNode();
    // bst2.getPredecessorNode('4', 'f')->printNode();
    // Node *a = new Node(1, 2);
    // Node *b = new Node(1, 2);
    // Node *c = new Node(2, 2);
    // Node *d = new Node(1, 10);
    // Node *e = new Node(3, 11);
    // Node *f = new Node();
    // Node *g = new Node('c', 't');
    // Node *h = new Node('h', 'a');

    // Node a = Node(1, 2);
    // Node b = Node(1, 2);
    // Node c = Node(2, 2);
    // Node d = Node(1, 10);
    // Node e = Node(3, 11);
    // Node f = Node();
    // Node g = Node('c', 't');
    // Node h = Node('h', 'a');

    // cout << (a > b) << endl;
    // cout << (b > c) << endl;
    // cout << (a > d) << endl;
    // cout << (c > f) << endl;
    // cout << (a > f) << endl;
    // cout << (f > g) << endl;
    // cout << (d > d) << endl;
    // cout << (h > g) << endl;

    // delete a;
    // delete b;
    // delete c;
    // delete d;
    // delete e;
    // delete f;
    // delete g;
    // delete h;
    // bst1.printLeastToGreatest();
    // bst1.remove('c', '3');
    // cout << endl << endl << endl;
    // bst1.printLeastToGreatest();
    return 0;
}