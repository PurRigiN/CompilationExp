#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "InterCode.h"
#include "MyTree.h"
#include "Serial.h"
#include "Token.h"
#include "Quaternion.h"
using namespace std;

bool InterCode::analysis(SymbolTable *table, MyTree * ASTree, queue<Quaternion> * quaternions)
{
    interCodeA(ASTree->LeftMostChild,quaternions);
    return true;
}
string InterCode::interCodeR(MyTree * node,queue<Quaternion> * quaternions)
{
    if(node->child_num==0)      //变量或者数值
    {
        //返回数值或者变量的名字
        //但是不进行四元式的生成
        return node->token.attri;
    }
    else if(node->child_num==1) // "!" 
    {
        Quaternion qua;
        qua.op="!";
        qua.arg1=interCodeR(node->LeftMostChild,quaternions);
        qua.num=numOfQua;
        numOfQua++;
        qua.result=newTempVar();
        qua.result_type=new int;
        (*qua.result_type)=-1;
        quaternions->push(qua);
        return qua.result;
    }
    else //node->child_num==2  代表两个结果运算
    {
        Quaternion qua;
        qua.op=node->token.attri;
        qua.arg1=interCodeR(node->LeftMostChild,quaternions);
        qua.arg2=interCodeR(node->LeftMostChild->getRightSibling(),quaternions);
        qua.num=numOfQua;
        numOfQua++;
        qua.result=newTempVar();
        qua.result_type=new int;
        (*qua.result_type)=-1;
        quaternions->push(qua);
        return qua.result;
    }

}
void InterCode::interCodeA(MyTree * node,queue<Quaternion> * quaternions)
{
    if(node->child_num==0)
        return ;
    Token temp=node->LeftMostChild->token;
    cout<<"正在处理A"<<endl;
    //如果是if语句，处理if语句
    if(temp.attri=="if")
    {
        cout<<"正在处理if语句"<<endl;
        interCodeIf(node,quaternions);
        return ;
    }
    //如果是赋值语句，进行处理
    else if(temp.serial==1)
    {
        cout<<"正在处理赋值语句"<<endl;
        interCodeId(node,quaternions);
        return ;
    }
    else if(temp.attri=="get")
    {
        cout<<"正在处理Get"<<endl;
        interCodeGet(node,quaternions);
        return ;
    }
    else if(temp.attri=="put")
    {
        interCodePut(node,quaternions);
        return ;
    }
    else if(temp.attri=="while")
    {
        interCodeWhile(node,quaternions);
        return ;
    }
    MyTree * Last=node->getRightMostChild();
    interCodeA(Last,quaternions);

}
void InterCode::interCodeIf(MyTree * node,queue<Quaternion> * quaternions)
{
    MyTree * Rnode=node->LeftMostChild->getRightSibling()->getRightSibling();
    MyTree * Anode=Rnode->getRightSibling()->getRightSibling()->getRightSibling();
    Quaternion qua;
    qua.op="bne";
    qua.arg1="1";
    //先生成表达式的四元式
    qua.arg2=interCodeR(Rnode->LeftMostChild,quaternions);
    qua.num=numOfQua;
    numOfQua++;
    qua.result_type=new int;
    //生成待定的bne语句
    quaternions->push(qua);
    //生成代码体四元式
    interCodeA(Anode,quaternions);
    //根据最后生成的位置，回填label
    *(qua.result_type)=numOfQua;
    //对最后一个A继续遍历
    MyTree * LastAnode=Anode->getRightSibling()->getRightSibling()->getRightSibling()->getRightSibling();
    interCodeA(LastAnode,quaternions);
}
void InterCode::interCodeWhile(MyTree * node,queue<Quaternion> * quaternions)
{
    MyTree * Rnode=node->LeftMostChild->getRightSibling()->getRightSibling();
    MyTree * Anode=Rnode->getRightSibling()->getRightSibling()->getRightSibling();
    int label=numOfQua;
    Quaternion qua;
    qua.op="bne";
    qua.arg1="1";
    //先生成表达式的四元式
    qua.arg2=interCodeR(Rnode->LeftMostChild,quaternions);
    qua.num=numOfQua;
    numOfQua++;
    qua.result_type=new int;
    //生成待定的bne语句
    quaternions->push(qua);
    //生成代码体四元式
    interCodeA(Anode,quaternions);
    //生成一个Goto四元式
    Quaternion qua2;
    qua2.op="goto";
    qua2.arg1="  ";
    qua2.arg2="  ";
    qua2.num=numOfQua;
    numOfQua++;
    qua2.result_type=new int;
    //跳转的地址为一开始记录好的地址
    *qua2.result_type=label;
    quaternions->push(qua2);

    //根据最后生成的位置，回填label
    *(qua.result_type)=numOfQua;

    //对最后一个A继续遍历
    MyTree * LastAnode=Anode->getRightSibling()->getRightSibling()->getRightSibling();
    interCodeA(LastAnode,quaternions);

}
void InterCode::interCodePut(MyTree * node,queue<Quaternion> * quaternions)
{
    MyTree * Rnode= node->LeftMostChild->getRightSibling()->getRightSibling();
    Quaternion qua;
    qua.op="put";
    //先生成表达式的四元式
    qua.arg1=interCodeR(Rnode,quaternions);
    qua.arg2="  ";
    qua.num=numOfQua;
    numOfQua++;
    qua.result="  ";
    qua.result_type=new int;
    *qua.result_type=-1;
    quaternions->push(qua);
    //对最后一个A继续遍历
    //对最后一个A继续遍历
    MyTree * LastAnode=Rnode->getRightSibling()->getRightSibling()->getRightSibling();
    interCodeA(LastAnode,quaternions);
    
}
void InterCode::interCodeGet(MyTree * node,queue<Quaternion> * quaternions)
{
    MyTree * IDnode= node->LeftMostChild->getRightSibling()->getRightSibling();
    Quaternion qua;
    qua.op="get";
    qua.arg1="  ";
    qua.arg2="  ";
    qua.num=numOfQua;
    numOfQua++;
    qua.result=IDnode->LeftMostChild->token.attri;
    qua.result_type=new int;
    *qua.result_type=-1;
    quaternions->push(qua);
    //对最后一个A继续遍历
    MyTree * LastAnode=IDnode->getRightSibling()->getRightSibling()->getRightSibling();
    interCodeA(LastAnode,quaternions);
}
void InterCode::interCodeId(MyTree * node,queue<Quaternion> * quaternions)
{
    MyTree * Rnode=node->LeftMostChild->getRightSibling()->getRightSibling();
    Quaternion qua;
    qua.op="=";
    //先生成表达式的四元式序列
    qua.arg1=interCodeR(Rnode->LeftMostChild,quaternions);
    qua.num=numOfQua;
    numOfQua++;
    qua.arg2="  ";
    qua.result=node->LeftMostChild->token.attri;
    qua.result_type=new int;
    *qua.result_type=-1;
    //将赋值语句的这条四元式push进序列中
    quaternions->push(qua);
    //继续对最右边的A进行处理
    MyTree * LastA=Rnode->getRightSibling()->getRightSibling();
    interCodeA(LastA,quaternions);
}
string InterCode::newTempVar()
{
    string temp="t";
    int temp_num=tempVarNum;
    tempVarNum++;
    return temp+to_string(temp_num);
}
void InterCode::printQuas(queue<Quaternion> * quaternions)
{
    int size=quaternions->size();
    for(int i=0;i<size;i++)
    {
        InterCode::printQua(quaternions->front());
        quaternions->push(quaternions->front());
        quaternions->pop();
    }
}
void InterCode::printQua(Quaternion qua)
{
    int wid=6;
    cout<<qua.num;
    for(int i=0;i<wid-to_string(qua.num).length();i++)
    {
        cout<<" ";
    }
    cout<<qua.op;
    for(int i=0;i<wid-qua.op.length();i++)
    {
        cout<<" ";
    }
    cout<<qua.arg1;
    for(int i=0;i<wid-qua.arg1.length();i++)
    {
        cout<<" ";
    }
    cout<<qua.arg2;
    for(int i=0;i<wid-qua.arg2.length();i++)
    {
        cout<<" ";
    }
    if(*qua.result_type==-1)
    {
        cout<<qua.result<<endl;
    }
    else
    {
        cout<<*qua.result_type<<endl;
    }
}