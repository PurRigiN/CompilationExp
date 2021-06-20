#ifndef LABELTABLE_H
#define LABELTABLE_H
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>

using namespace std;

class LabelTable
{
public: 
    int LabelNum;
    string first_str;
    map<string,string> table;
    LabelTable(string str);
    string lookupLabel(string varName);
    string lookupLabelStraight(string varName);
    string addToLabel(string varName);
    string newLabel();
    
};

#endif