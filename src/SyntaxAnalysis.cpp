#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "LLTable.h"
#include "MyTree.h"
#include "Serial.h"
#include "Token.h"
using namespace std;

bool SyntaxAnalysis::analysis(queue<Token> *token,SymbolTable *table, MyTree * analysis_tree)
{
    //在最后添加末尾符号
    Token last_token;
    last_token.column=0;
    last_token.row=0;
    last_token.num=0;
    last_token.attri=string("$");
    last_token.serial=-1;
    token->push(last_token);

    //分析栈
    stack<int> ana_stack;
    ana_stack.push(-1);
    ana_stack.push(100);
    bool flag=false;
    Token Temp_Token;
    Token token_lastone;
    int temp_token;
    string temp_attri;
    // analysis_tree=new MyTree(creatNonToken(100));
    MyTree * temp_node=analysis_tree;
    int X;                   //栈顶符号X
    int prod_right[LLTable::MAX_SYMBOL];    //暂存产生式右部的符号
    while(!flag)
    {
        token_lastone=Temp_Token;
        temp_token=token->front().serial;
        temp_attri=token->front().attri;
        Temp_Token=token->front();
        X=ana_stack.top();
        if(X==temp_token&&temp_token==-1)
        {
            cout<<"Syntax Analysis succeeded!"<<endl;
            cout<<printTree(analysis_tree)<<endl;
            return true;
        }
        else if(X==temp_token&&temp_token!=-1)
        {
            ana_stack.pop();

            token->push(token->front());
            //弹栈的时候，确认该终结符符合要求，则将树的Token变为序列中的该终结符Token
            temp_node->token=token->front();
            token->pop();

            temp_node=getNextNode(temp_node);
        }
        else if(LLTable::if_terminator(X) && X!=-1)
        {
            //报告错误
            printError(token_lastone);
            // cout<<printTree(analysis_tree)<<endl;
            //如果栈顶符号是括号，意味着在序列中没有找到括号
            if(X==13)   // )
            {
                cout<<"丢失右括号 in row: "<<Temp_Token.row<<endl;
            }
            flag=true;
            return false;
        }
        else if( !(LLTable::if_terminator(X) ))
        {

            int length=LLTable::lookup(X,temp_token,prod_right);
            if(length==-1)      //error
            {
                //报告错误
                printError(token_lastone);
                //如果X为"T"非终结符，意味着没有匹配到操作数
                if(X==106)
                {
                    cout<<"丢失操作数 in row: "<<Temp_Token.row<<endl;
                }
                //如果X为非终结符"R'"，意味着没有匹配到运算符
                if(X==105)
                {
                    cout<<"丢失运算符 in row: "<<Temp_Token.row<<endl;
                }
                flag=true;
                return false;
            }
            else if(length==-2) //X→ε
            {
                ana_stack.pop();
                temp_node=getNextNode(temp_node);
            }
            else
            {
                
                ana_stack.pop();
                for(int i=0;i<length;i++)
                {
                    ana_stack.push(prod_right[length-1-i]);
                    //创建节点，Token由creatToken函数生成，如果是非终结符则返回带非终结符信息的Token
                    //否则返回空Token
                    temp_node->newChild(creatNonToken(prod_right[i]));
                }
                temp_node=temp_node->LeftMostChild;
            }
        }
    }
    cout<<printTree(analysis_tree)<<endl;
    return false;
}

string SyntaxAnalysis::printTree(MyTree * temp_node)
{
    if(temp_node==NULL)
        return string(" ");
    if(temp_node->child_num==0)
    {
        return string("["+temp_node->token.attri+"]");
    }
    string temp_str="";
    temp_str+="[";
    temp_str+=temp_node->token.attri;
    MyTree * temp_temp_node=temp_node->LeftMostChild;
    temp_str+=printTree(temp_temp_node);
    while(temp_temp_node->getRightSibling()!=NULL)
    {
        temp_temp_node=temp_temp_node->getRightSibling();
        temp_str+=printTree(temp_temp_node);
    }
    temp_str+="]";
    return temp_str;
}
MyTree * SyntaxAnalysis::getNextNode(MyTree * node)
{
    if(node==NULL)
        return NULL;
    if(node->getPar()==NULL)
        return NULL;
    if(node->getRightSibling()!=NULL)
        return node->getRightSibling();
    else
        return getNextNode(node->getPar());
     
}

Token SyntaxAnalysis::creatNonToken(int serial)
{
    Token temp;
    temp.attri=string("");
    temp.column=0;
    temp.row=0;
    temp.num=0;
    temp.serial=0;
    if(serial==100)
    {
        temp.attri=string("S");
        temp.serial=100;
        return temp;
    }
    else if(serial==101)
    {
        temp.attri=string("A");
        temp.serial=101;
        return temp;
    }
    else if(serial==102)
    {
        temp.attri=string("B");
        temp.serial=102;
        return temp;
    }
    else if(serial==103)
    {
        temp.attri=string("D'");
        temp.serial=103;
        return temp;
    }
    else if(serial==104)
    {
        temp.attri=string("R");
        temp.serial=104;
        return temp;
    }
    else if(serial==105)
    {
        temp.attri=string("R'");
        temp.serial=105;
        return temp;
    }
    else if(serial==106)
    {
        temp.attri=string("T");
        temp.serial=106;
        return temp;
    }
    else
        return temp;

}

void SyntaxAnalysis::printError(Token token)
{
    cout<<"There is an unexcepted symbol: "<<endl;
    cout<<"row:  "<<token.row<<"    column:"<<token.column<<endl;
    // printf("row: %d   column:%d\n",token.row,token.column); 
}