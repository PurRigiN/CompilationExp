#include <iostream>
#include "MyTree.h"
using namespace std;

MyTree::MyTree()
{
    par=NULL;
    LeftMostChild=NULL;
    rightSibling=NULL;
    child_num=0;
    token.attri=string("");
    token.column=0;
    token.num=0;
    token.row=0;
    token.serial=0;
}

MyTree::MyTree(Token token_in)
{
    par=NULL;
    LeftMostChild=NULL;
    rightSibling=NULL;
    child_num=0;
    token=token_in;
}

MyTree::~MyTree()
{
    if(LeftMostChild!=NULL)
    {
        delete LeftMostChild;
    }
    if(rightSibling!=NULL)
    {
        delete rightSibling;
    }
}

MyTree * MyTree::getRightMostChild()
{
    MyTree * temp=this->LeftMostChild;
    if(temp==NULL)
        return NULL;

    while(temp->rightSibling!=NULL)
    {
        temp=temp->rightSibling;
    }
    return temp;
}

void MyTree::newChild(Token token_in)
{
    if(this->LeftMostChild==NULL)
    {
        this->LeftMostChild=new MyTree(token_in);
        LeftMostChild->par=this;
    }
    else
    {
        MyTree * temp=new MyTree(token_in);
        temp->par=this;
        getRightMostChild()->rightSibling=temp;
    }
    child_num++;
}

void MyTree::newChild(MyTree * node)
{
    
    if(this->LeftMostChild==NULL)
    {
        this->LeftMostChild=node;
        LeftMostChild->par=this;
    }
    else
    {
        node->par=this;
        getRightMostChild()->rightSibling=node;
    }
    child_num++;
}

MyTree * MyTree::getPar()
{
    return par;
}

MyTree * MyTree::getRightSibling()
{
    return rightSibling;
}