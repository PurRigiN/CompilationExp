#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "SymbolTable.h"
#include "Token.h"

using namespace std;

class LexicalAnalysis
{
private:
    char temp_c;
    int row;
    int column;
    int total;
    void get_a_char(FILE* instream);
    bool letter(char *);
    bool digit(char *);
    void unexpect();
    int find_key(string);
public:
    LexicalAnalysis();
    bool Analysis(queue<Token> * token ,SymbolTable *table);
};

#endif