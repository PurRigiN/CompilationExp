#include "ObjectCode.h"
#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "MyTree.h"
#include "Serial.h"
#include "Token.h"
#include "Quaternion.h"
#include "LabelTable.h"

using namespace std;

string ObjectCode::analysis(queue<Quaternion> * quaternions)
{
    string obj;
    LabelTable LTable("L");
    LabelTable rTable("t");
    int size=quaternions->size();

    //先找到所有的标签，放进LTable里面
    for(int i=0;i<size;i++)
    {
        Quaternion qua=quaternions->front();
        if(qua.op=="bne")
        {
            string tempLabel=LTable.lookupLabelStraight(to_string(*qua.result_type));
        }
        else if(qua.op=="goto")
        {
            string tempLabel=LTable.lookupLabelStraight(to_string(*qua.result_type));
        }
        quaternions->push(qua);
        quaternions->pop();
    }


    for(int i=0;i<size;i++)
    {
        Quaternion qua=quaternions->front();
        string temp="";
        if(qua.op=="=")
        {
            //判断是整数还是变量
            const char *p = qua.arg1.c_str();
            //整数
            if(p[0]>='0' && p[0]<='9')
            {
                string r_result=rTable.lookupLabelStraight(qua.result);
                temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"li",r_result+",",qua.arg1," ");
            }
            //变量类型
            else
            {
                string r_result=rTable.lookupLabelStraight(qua.result);
                string r_arg1=rTable.lookupLabelStraight(qua.arg1);
                temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"move",  r_result+","  ,  r_arg1,  " ");
            }
        }
        else if(qua.op=="+")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"add",  r_result+","  ,  r_arg1+",",  r_arg2);
        }
        else if(qua.op=="`-")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"sub",  r_result+","  ,  r_arg1+",",  r_arg2);
        }
        else if(qua.op=="==")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"slt",  r_result+","  ,  r_arg1+",",  r_arg2);
        }
        else if(qua.op=="&&")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"and",  r_result+","  ,  r_arg1+",",  r_arg2);
        }
        else if(qua.op=="||")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"or",  r_result+","  ,  r_arg1+",",  r_arg2);
        }
        else if(qua.op=="bne")
        {
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            string r_arg2=rTable.lookupLabelStraight(qua.arg2);
            string r_result=LTable.lookupLabelStraight(to_string(*qua.result_type));
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"bne",  r_arg1+","  ,  r_arg2+",",  r_result);
        }
        else if(qua.op=="goto")
        {
            string r_result=LTable.lookupLabelStraight(to_string(*qua.result_type));
            temp=insertHelp(LTable.lookupLabel(to_string(qua.num)),"j",  ""  ,  "",  r_result);
        }
        else if(qua.op=="put")
        {
            string r_arg1=rTable.lookupLabelStraight(qua.arg1);
            obj+=insertHelp(LTable.lookupLabel(to_string(qua.num)),"move","a0,",r_arg1," ");
            obj+=insertHelp("","li","v0,","1","");
            obj+=insertHelp(" ","syscall","","","");
        }
        else if(qua.op=="get")
        {
            string r_result=rTable.lookupLabelStraight(qua.result);
            obj+=insertHelp(LTable.lookupLabel(to_string(qua.num)),"li","v0,","5","");
            obj+=insertHelp(" ","syscall","","","");
            obj+=insertHelp(" ","move",r_result,"v0","");
        }

        obj+=temp;
        delete qua.result_type;
        quaternions->pop();
    }
    obj+=insertHelp(LTable.lookupLabel(to_string(size)),"","","","");
    return obj;
}

string ObjectCode::insertHelp(string L,string op, string result,string arg1,string arg2)
{
    string temp="";
    int wid=7;
    string list[5];
    list[0]=L;
    list[1]=op;
    list[2]=result;
    list[3]=arg1;
    list[4]=arg2;
    for(int i=0;i<5;i++)
    {
        temp+=list[i];
        for(int j=0;j<wid-list[i].length();j++)
        {
            temp+=" ";
        }
    }
    temp+="\n";
    return temp;

}