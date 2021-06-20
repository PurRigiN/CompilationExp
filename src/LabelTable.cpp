#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "LabelTable.h"

using namespace std;


LabelTable::LabelTable(string str)
{
    LabelNum=1;
    first_str=str;
}
string LabelTable::lookupLabel(string varName)
{
    //迭代器
    map<string, string>::iterator  iter;
    iter=table.find(varName);
    //如果没有则返回错误
    if(iter==table.end())
    {
        // string L_str=newLabel();
        // table.insert(map<string, string>::value_type (varName,L_str));
        return "  ";
    }
    else
    {
        return iter->second;
    }
}
string LabelTable::lookupLabelStraight(string varName)
{
    //迭代器
    map<string, string>::iterator  iter;
    iter=table.find(varName);
    //如果没有则直接新加入
    if(iter==table.end())
    {
        string L_str=newLabel();
        table.insert(map<string, string>::value_type (varName,L_str));
        return L_str;
    }
    else
    {
        return iter->second;
    }
}
string LabelTable::addToLabel(string varName)
{
    string L_str=newLabel();
    table.insert(map<string, string>::value_type (varName,L_str));
    return L_str;
}
string LabelTable::newLabel()
{
    string Lstr=first_str;
    int num=LabelNum;
    LabelNum++;
    return Lstr+to_string(num);
}