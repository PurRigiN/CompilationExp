#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "Symbol.h"

using namespace std;

class SymbolTable
{
    
public:
    map<string,Symbol> table;
    SymbolTable();
    void addToMap(string id);       //添加到符号表中的函数
    bool inTable(string id);
    void printInfo();               //打印输出统计信息
};
#endif 