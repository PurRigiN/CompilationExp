#ifndef SYMBOL_H
#define SYMBOL_H
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
using namespace std;

struct Symbol
{
    string symbol_str;      //对应的符号
    int occ_num;            //出现次数
    int type;               //类型
};
#endif 