#ifndef SEMANTICANALYSIS_H
#define SEMANTICANALYSIS_H
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

class SemanticAnalysis
{
public:
    static bool analysis(SymbolTable *table,MyTree * analysis_tree, MyTree * ASTree);
    static MyTree * NonTerR(MyTree * R_node);
    static MyTree * NonTerR1(MyTree * R_node);
    static MyTree * NonTerT(MyTree * T_node);
    static void ChangeTreeAST1(MyTree * ana_node,MyTree * ast_node);
    static bool checkType(MyTree * ASTree,SymbolTable * table);
    static void NonTerA(MyTree * A_node);
    static bool setTypeD1(MyTree * D1_node,SymbolTable * table,int type);
    static int checkTypeExpress(MyTree * node, SymbolTable * table);
};

#endif