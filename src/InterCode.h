#ifndef INTERCODE_H
#define INTERCODE_H

#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "MyTree.h"
#include "Serial.h"
#include "Token.h"
#include "Quaternion.h"
using namespace std;

class InterCode
{
public:
    static int tempVarNum;
    static int numOfQua;
    static bool analysis(SymbolTable *table, MyTree * ASTree, queue<Quaternion> * quaternions);
    static string interCodeR(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodeA(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodeIf(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodeWhile(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodePut(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodeGet(MyTree * node,queue<Quaternion> * quaternions);
    static void interCodeId(MyTree * node,queue<Quaternion> * quaternions);
    static void printQuas(queue<Quaternion> * quaternions);
    static void printQua(Quaternion qua);

    static string newTempVar();
};
// int InterCode::tempVarNum=0;
// int InterCode::numOfQua=0;
#endif