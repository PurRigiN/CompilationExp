#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
using namespace std;

class LLTable
{
public:
    static const int MAX_SYMBOL=20;
    static bool if_terminator(int id);
    static int lookup(int X, int a,int * prod_right_rev);

};