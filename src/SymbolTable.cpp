#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "SymbolTable.h"

using namespace std;
SymbolTable::SymbolTable(){}

bool SymbolTable::inTable(string id)
{
    map<string, Symbol>::iterator  iter;
    iter=table.find(id);
    //如果没有的返回假
    if(iter==table.end())
        return false;
    else 
        return true;
}

void SymbolTable::addToMap(string id)
{
    //新建一个symbol
    Symbol new_symbol;
    new_symbol.symbol_str=id;
    new_symbol.type=0;
    //迭代器
    map<string, Symbol>::iterator  iter;
    iter=table.find(id);
    //如果没有的，加入到该表中
    if(iter==table.end())
    {
        new_symbol.occ_num=1;
        table.insert(map<string, Symbol>::value_type (id,new_symbol));
    }
    //否则将表内的出现次数+1
    else
    {
        (iter->second).occ_num+=1;
    }
}

void SymbolTable::printInfo()
{
    map<string, Symbol>::iterator  iter;
    for (iter = table.begin(); iter != table.end(); iter++)
    {
        cout<<iter->first<<"    Times: "<<(iter->second).occ_num<<endl;
    }
}