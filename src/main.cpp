#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "SymbolTable.h"
#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "SemanticAnalysis.h"
#include "Token.h"
#include "MyTree.h"
#include "Quaternion.h"
#include "InterCode.h"
#include "ObjectCode.h"

using namespace std;
int InterCode::tempVarNum=0;
int InterCode::numOfQua=0;
int main()
{
    //token序列
    queue<Token> *token;
    
    //符号表
    SymbolTable *table;
    //new空间
    token=new queue<Token>;
    
    table=new SymbolTable;
    //词法分析，得到一个序列
    LexicalAnalysis Lex_ana;
    bool if_Lex_succ=Lex_ana.Analysis(token,table);
    if(if_Lex_succ)
    {
        // cout<<(*token).front()<<endl;
        // (*table).printInfo();

        MyTree * analysis_tree=new MyTree(SyntaxAnalysis::creatNonToken(100));

        bool if_Syn_succ=SyntaxAnalysis::analysis(token,table,analysis_tree);
        if (if_Syn_succ)
        {
            cout<<"Syntax Analysis succeeded!"<<endl;
        } 
        else
        {
            cout<<"SyntaxAnalysis failed!"<<endl;
        }
        bool if_Seman_succ=false;
        if (if_Syn_succ)
        {
            //进行实验3
            MyTree * ASTree=new MyTree();
            if_Seman_succ=SemanticAnalysis::analysis(table,analysis_tree, ASTree);
            if(if_Seman_succ){
                cout<<"Semantic Analysis succeeded!"<<endl;
                queue<Quaternion> * quaternions;
                quaternions=new queue<Quaternion>;
                bool if_InterC_succ=InterCode::analysis(table,ASTree,quaternions);
                InterCode::printQuas(quaternions);
                cout<<"\n生成目标代码\n"<<endl;
                cout<<ObjectCode::analysis(quaternions);
                
            }
            else
                cout<<"Semantic Analysis failed!"<<endl;
            delete analysis_tree;
            delete ASTree;

        }
    }

    delete token;
    delete table;
    
    return 0;
}
