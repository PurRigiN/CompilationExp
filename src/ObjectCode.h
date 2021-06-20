#ifndef OBJECTCODE_H
#define OBJECTCODE_H

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
#include "LabelTable.h"
using namespace std;

class ObjectCode
{
public:
    static string analysis(queue<Quaternion> * quaternions);
    static string insertHelp(string L,string op, string result,string arg1,string arg2);
};

#endif