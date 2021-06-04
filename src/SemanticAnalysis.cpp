#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include <stack>
#include "SemanticAnalysis.h"
#include "SyntaxAnalysis.h"
#include "SymbolTable.h"
#include "LLTable.h"
#include "MyTree.h"
#include "Serial.h"
#include "Token.h"
using namespace std;

bool SemanticAnalysis::analysis(SymbolTable *table,MyTree * analysis_tree, MyTree * ASTree)
{
    bool if_Seman_succ=true;
    ChangeTreeAST1(analysis_tree,ASTree);
    cout<<SyntaxAnalysis::printTree(ASTree)<<endl;
    bool checkType_bool=SemanticAnalysis::checkType(ASTree,table);
    if(checkType_bool)
    {
        cout<<"Type OK"<<endl;
    }
    else
    {
        cout<<"Type failed"<<endl;
        if_Seman_succ=false;
    }
    
    return if_Seman_succ;
}

MyTree * SemanticAnalysis::NonTerR(MyTree * R_node)
{
    if(R_node->child_num!=2)
        return NULL;
    MyTree * T= R_node->LeftMostChild;
    MyTree * R1=T->getRightSibling();
    if(R1->child_num==0)
    {
        //如果R'没有孩子，那就不用展开R'，只展开T
        return NonTerT(T);
    }
    else
    {
        //找到符号
        MyTree * al_symbol=R1->LeftMostChild;
        //新建一个节点，将用于返回
        MyTree * return_node;
        return_node=new MyTree();
        //该节点的Token即为找到的运算符号
        return_node->token=al_symbol->token;
        //左孩子
        return_node->newChild(NonTerT(T));
        //右孩子
        return_node->newChild(NonTerR1(R1));
        return return_node;
    }
    
}

MyTree * SemanticAnalysis::NonTerT(MyTree * T_node)
{
    //T→(R)
    if(T_node->child_num==3)
    {
        MyTree * R_node=T_node->LeftMostChild->getRightSibling();
        return NonTerR(R_node);
    }
    //T→id | num
    else if(T_node->child_num==1)
    {
        //返回该id/num
        MyTree * return_node;
        return_node=new MyTree();
        //该节点即为id/num
        return_node->token=T_node->LeftMostChild->token;
        return return_node;
    }
    //T→!T
    else if(T_node->child_num==2)
    {
        MyTree * return_node;
        return_node=new MyTree();
        //该节点即为 ! 
        return_node->token=T_node->LeftMostChild->token;
        //接着将接下来的T1为新孩子
        MyTree * T1=T_node->LeftMostChild->getRightSibling();
        return_node->newChild(NonTerT(T1));
        return return_node;
    }
    return NULL;
}

MyTree * SemanticAnalysis::NonTerR1(MyTree * R_node)
{
    if(R_node->child_num!=3)
        return NULL;
    MyTree * T=R_node->LeftMostChild->getRightSibling();
    MyTree * R1=T->getRightSibling();
    if(R1->child_num==0)
    {
        //如果R'没有孩子，那就不用展开R'，只展开T
        return NonTerT(T);
    }
    else
    {
        //找到符号
        MyTree * al_symbol=R1->LeftMostChild;
        //新建一个节点，将用于返回
        MyTree * return_node;
        return_node=new MyTree();
        //该节点的Token即为找到的运算符号
        return_node->token=al_symbol->token;
        //左孩子
        return_node->newChild(NonTerT(T));
        //右孩子
        return_node->newChild(NonTerR1(R1));
        return return_node;
    }
}

void SemanticAnalysis::ChangeTreeAST1(MyTree * ana_node,MyTree * ast_node)
{
    if(ana_node->token.serial==104) //R
    {
        // ast_node=new MyTree();
        ast_node->token=ana_node->token;
        ast_node->newChild(NonTerR(ana_node));
    }
    else
    {
        // ast_node=new MyTree();
        ast_node->token=ana_node->token;
        if(ana_node->child_num==0)
            return ;

        MyTree * ana_temp=ana_node->LeftMostChild;
        MyTree * ast_temp;
        for(int i=0;  i<  (ana_node->child_num)  ;i++)
        {
            ast_temp=new MyTree();
            ast_node->newChild(ast_temp);
            ChangeTreeAST1(ana_temp,ast_temp);
            ana_temp=ana_temp->getRightSibling();
        }
    }

}

bool SemanticAnalysis::checkType(MyTree * ASTree,SymbolTable * table)
{
    //对int和bool声明语句做检查
    if(ASTree->token.serial==101)   //A
    {
        if(ASTree->child_num==5)  
        {
            MyTree * firstChild = ASTree->LeftMostChild;
            //如果第一个孩子是int 或者是 bool 节点
            if(firstChild->token.serial==22 || firstChild->token.serial==24) //int 或者 bool
            {
                int type=0;
                if(firstChild->token.serial==22)
                    type=1;
                else   
                    type=2;
                //找到id节点和D'节点
                MyTree *  id_node=firstChild->getRightSibling();
                MyTree *  D1_node=id_node->getRightSibling();
                //先设置id的type
                Token id_token=id_node->token;
                //迭代器
                map<string, Symbol>::iterator  iter;
                //找到id的那一行
                iter=table->table.find(id_token.attri);
                //如果type被设置过了，那么返回false，表示失败
                if(iter->second.type!=0)
                {
                    cout<<"redeclear var: `"<<id_token.attri<<"` in row: "<<id_token.row<<endl;
                    return false;
                }               
                else
                {
                    //如果没被设置过，则设置，并且调用函数，递归地对D'里的id进行设置
                    iter->second.type=type;
                    bool setType_bool=setTypeD1(D1_node,table,type);
                    if (setType_bool==false)
                        return setType_bool;
                }
            }
        }
    }
    if(ASTree->token.serial==104) //R 要进行检查
    {
        int type=checkTypeExpress(ASTree->LeftMostChild, table);
        if(type==-1)
            return false;
        else
            return true;
    }
    else
    {
        if(ASTree->child_num==0)
            return true;
        else
        {
            bool flag=true;
            MyTree * temp_node=ASTree->LeftMostChild;
            int cul=ASTree->child_num;
            bool temp_flag=true;
            for(int i=0 ; i< cul  ; i++)
            {
                temp_flag=SemanticAnalysis::checkType(temp_node,table);
                temp_node=temp_node->getRightSibling();
                if(temp_flag==false)
                    flag=false;
            }
            return flag;
        }
    
    }
    
    
}

void SemanticAnalysis::NonTerA(MyTree * A_node)
{
    
}

//检查节点，返回-1表示出错，1表示int类型，2表示bool类型，3表示数值
int SemanticAnalysis::checkTypeExpress(MyTree * node, SymbolTable * table)
{
    if(node->child_num==0) //叶子节点，返回相应的值
    {
        Token token=node->token;
        if(token.serial==2)
            return 3;
        else
        {
            //迭代器
            map<string, Symbol>::iterator  iter;
            //找到id的那一行
            iter=table->table.find(token.attri);
            int type=iter->second.type;
            if(type==0)
            {
                //没有先声明，出错，返回-1
                cout<<"undecleared var: `"<<token.attri<<"` in row: "<<token.row<<endl;
                return -1;
            }
            else
            {
                return type;
            }
        }
    }
    else if(node->child_num==1)
    {
        return checkTypeExpress(node->LeftMostChild, table);
    }
    else if(node->child_num==2)
    {
        MyTree * LChild=node->LeftMostChild;
        MyTree * RChild=LChild->getRightSibling();
        int LType=checkTypeExpress(LChild,table);
        int RType=checkTypeExpress(RChild,table);
        if(LType==-1||RType==-1)
            return -1;
        else if(LType==RType)
            return LType;
        else if((LType==1&&RType==2) || (LType==2&&RType==1))
        {
            cout<<"cannot mix 'int' and 'bool' in row: "<<LChild->token.row<<endl;
            return -1;
        }
        else if( (LType==1&&RType==3) || (LType==3&&RType==1) )
            return 1;
        else if( (LType==2&&RType==3) || (LType==3&&RType==2) )
            return 2;
        else   
            return -1;
    }
    else
    {
        return -1;
    }
}

//type 为 0则未初始化，为1为int ，为2为bool
bool SemanticAnalysis::setTypeD1(MyTree * D1_node,SymbolTable * table,int type)
{
    //如果不等于3，则不需要设置类型
    if(D1_node->child_num!=3)
        return true;
    
    //如果等于3
    MyTree * id_node=D1_node->LeftMostChild->getRightSibling();
    MyTree * D1_node2=id_node->getRightSibling();
    Token id_token=id_node->token;
    //迭代器
    map<string, Symbol>::iterator  iter;
    //找到id的那一行
    iter=table->table.find(id_token.attri);
    //如果type被设置过了，那么返回false，表示失败
    if(iter->second.type!=0)
    {
        cout<<"redeclear var: `"<<id_token.attri<<"` in row: "<<id_token.row<<endl;
        return false;
    }
    else
    {
        //如果没被设置过，则设置，并且继续递归下去设置
        iter->second.type=type;
        return setTypeD1(D1_node2,table,type);
    }

}