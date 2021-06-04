#ifndef MYTREE_H
#define MYTREE_H
#include <iostream>
#include "Token.h"
using namespace std;

class MyTree
{
public:
    Token token;
    int child_num;
    MyTree * par;
    MyTree * LeftMostChild;
    MyTree * rightSibling;

    MyTree();
    MyTree(Token token_in);
    ~MyTree();

    MyTree * getRightMostChild();
    MyTree * getPar();
    MyTree * getRightSibling();
    void newChild(Token token_in);
    void newChild(MyTree * node);

};

#endif