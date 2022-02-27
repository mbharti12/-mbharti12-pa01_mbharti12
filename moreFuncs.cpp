#include "moreFuncs.h"
#include <iostream>
using namespace std;

int charSuitToInt(char c){
    //clubs - 1, diamonds - 2, spades - 3, hearts - 4
    if (c == 'c'){
        return 1;
    }
    else if (c == 'd'){
        return 2;
    }
    else if (c == 's'){
        return 3;
    }
    else if (c == 'h'){
        return 4;
    }
    return 0;
}

int charValueToInt(char c){
    //ace - 1, 2, 3, . . . 10, jack - 11, queen - 12, king - 13
    if (isalpha(c)){
        if (c == 't'){
            return 10;
        }
        if (c == 'j'){
            return 11;
        }
        else if (c == 'q'){
            return 12;
        }
        else if (c == 'k'){
            return 13;
        }
        else if (c == 'a'){
            return 1;
        }
        return 0;
    }
    return c - '0';
}

char intSuitToChar(int i){
    //clubs - 1, diamonds - 2, spades - 3, hearts - 4
    if (i == 1){
        return 'c';
    }
    else if (i == 2){
        return 'd';
    }
    else if (i == 3){
        return 's';
    }
    else if (i == 4){
        return 'h';
    }
    return '0';
}

char intValueToChar(int i){
    //ace - 1, 2, 3, . . . 10, jack - 11, queen - 12, king - 13
    if (i == 10){
        return 't';
    }
    if (i == 11){
        return 'j';
    }
    else if (i == 12){
        return 'q';
    }
    else if (i == 13){
        return 'k';
    }
    else if (i == 1){
        return 'a';
    }
    return '0' + i;
}