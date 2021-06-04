#ifndef SYNTAXANALYSIS_H
#define SYNTAXANALYSIS_H
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SymbolTable.h"
#include "MyTree.h"
#include "Token.h"
using namespace std;

class SyntaxAnalysis
{
public:
    static bool analysis(queue<Token> *token,SymbolTable *table,MyTree * analysis_tree);
    static MyTree * getNextNode(MyTree * temp_node);
    static string printTree(MyTree * temp_node);
    static Token creatNonToken(int serial);
    static void printError(Token token);
};

#endif