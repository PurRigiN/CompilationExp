#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <queue> 
#include "LLTable.h"
using namespace std;

bool LLTable::if_terminator(int token)
{
    if(token>=1&&token<=99)
        return true;
    else
        return false;
}

//返回-1代表有问题
//返回-2代表查到的是X→ε
//返回正数代表需要多少个字符，并且已经将字符放入到prod_right中
int LLTable::lookup(int X, int a,int * prod_right)
{
    if(X==100)//S
    {
        if(a==25)//while
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==20)//if
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==26)//put
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==27)//get
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==24)//bool
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==22)//int
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==1)//id
        {
            prod_right[0]=101;
            return 1;
        }
        else if(a==-1)//$
        {
            prod_right[0]=101;
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else if(X==101)//A
    {
        if(a==25)//while
        {
            prod_right[0]=25;
            prod_right[1]=12;
            prod_right[2]=104;
            prod_right[3]=13;
            prod_right[4]=30;
            prod_right[5]=101;
            prod_right[6]=31;
            prod_right[7]=14;
            prod_right[8]=101;
            return 9;
        }
        else if(a==20)//if
        {
            prod_right[0]=20;   //if
            prod_right[1]=12;   //(
            prod_right[2]=104;  //R
            prod_right[3]=13;   //)
            prod_right[4]=30;   //{
            prod_right[5]=101;  //A
            prod_right[6]=31;   //}
            prod_right[7]=14;   //;
            prod_right[8]=102;  //B
            prod_right[9]=101;  //A
            return 10;
        }
        else if(a==26)//put
        {
            prod_right[0]=26;   //put
            prod_right[1]=12;   //(
            prod_right[2]=104;  //R
            prod_right[3]=13;   //)
            prod_right[4]=14;   //;
            prod_right[5]=101;  //A
            return 6;
        }
        else if(a==27)//get
        {
            prod_right[0]=27;   //get
            prod_right[1]=12;   //(
            prod_right[2]=1;    //id
            prod_right[3]=13;   //)
            prod_right[4]=14;   //;
            prod_right[5]=101;  //A
            return 6;
        }
        else if(a==24)//bool
        {
            prod_right[0]=24;   //bool
            prod_right[1]=1;    //id
            prod_right[2]=103;   //D'
            prod_right[3]=14;   //;
            prod_right[4]=101;  //A
            return 5;
        }
        else if(a==22)//int
        {
            prod_right[0]=22;   //int
            prod_right[1]=1;    //id
            prod_right[2]=103;  //D'
            prod_right[3]=14;   //;
            prod_right[4]=101;  //A
            return 5;
        }
        else if(a==1)//id
        {
            prod_right[0]=1;    //id
            prod_right[1]=5;    //=
            prod_right[2]=104;  //R
            prod_right[3]=14;   //;
            prod_right[4]=101;  //A
            return 5;
        }
        else if(a==-1)//$
        {
            return -2;
        }
        else if(a==31)//}
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else if(X==102)//B
    {
        if(a==21)//else
        {
            prod_right[0]=21;   //else
            prod_right[1]=30;   //{
            prod_right[2]=101;  //A
            prod_right[3]=31;   //}
            prod_right[4]=14;   //;
            return 5;
        }
        else if(a==25 || a==20 || a==26 ||a==27 || a==24 || a==22 || a==1 || a==-1 ||a==31 )
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else if(X==103)//D'
    {
        if(a==29)//,
        {
            prod_right[0]=29;   //,
            prod_right[1]=1;    //id
            prod_right[2]=103;  //D'
            return 3;
        }
        else if(a==5)//=
        {
            prod_right[0]=5;    //=
            prod_right[1]=104;    //R
            return 2;
        }
        else if(a==14)//;
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else if(X==104)//R
    {
        if(a==1||a==2||a==17||a==12)//id num ! (
        {
            prod_right[0]=106;    //T
            prod_right[1]=105;    //R'
            return 2;
        }
        else
        {
            return -1;
        }
    }
    else if(X==105)//R'
    {
        if(a==3)//+
        {
            prod_right[0]=3;      //+
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==4)//-
        {
            prod_right[0]=4;      //-
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==16)//||
        {
            prod_right[0]=16;     //||
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==15)//&&
        {
            prod_right[0]=15;      //&&
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==10)//>=
        {
            prod_right[0]=10;      //>=
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==11)//<=
        {
            prod_right[0]=11;      //<=
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==9)//<>
        {
            prod_right[0]=9;      //<>
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==7)//>
        {
            prod_right[0]=7;      //>
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==8)//<
        {
            prod_right[0]=8;      //<
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==6)//==
        {
            prod_right[0]=6;      //==
            prod_right[1]=106;    //T
            prod_right[2]=105;    //R'
            return 3;
        }
        else if(a==13 || a==14)
        {
            return -2;
        }
        else
        {
            return -1;
        }
    }
    else if(X==106)//T
    {
        if(a==1)//id
        {
            prod_right[0]=1;      //id
            return 1;
        }
        else if(a==2)//num
        {
            prod_right[0]=2;      //num
            return 1;
        }
        else if(a==17)//`!
        {
            prod_right[0]=17;       //`!
            prod_right[1]=106;      //T
            return 2;
        }
        else if(a==12)//(
        {
            prod_right[0]=12;       //(
            prod_right[1]=104;      //R
            prod_right[2]=13;       //)
            return 3;
        }
        else
        {
            return -1;
        }
    }
    else
        return -1;
}