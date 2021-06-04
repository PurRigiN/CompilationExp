#include<iostream>
#include<string.h>
#include<map>
#include <cstdio>
#include <fstream>
#include <queue>
#include "SymbolTable.h"
#include "LexicalAnalysis.h"
#include "Token.h"

using namespace std;

//当读入的是换行符或者制表符，再递归调用该函数
//行列数控制
LexicalAnalysis::LexicalAnalysis()
{
    row=1;
    column=1;
    total=0;
}
void LexicalAnalysis::get_a_char(FILE* instream)
{
    temp_c = fgetc(instream);
    if(temp_c=='\n'||temp_c=='\r')
    {
        row+=1;
        column=0;
        get_a_char(instream);
    }
    else if(temp_c=='\t')
    {
        column+=4;
        get_a_char(instream);
    }
    else
    {
        column+=1;
    }
    total+=1;
}

bool LexicalAnalysis::letter(char * temp)
{
    if (temp[0]>='a' && temp[0]<='z')
        return true;
    else if(temp[0]>='A' && temp[0]<='Z')
        return true;
    else
        return false;
}

bool LexicalAnalysis::digit(char * temp)
{
    if (temp[0]>='0' && temp[0]<='9')
        return true;
    else
        return false;
}

int LexicalAnalysis::find_key(string str)
{
    if(str=="if")
        return 20;
    else if(str=="else")
        return 21;
    else if(str=="int")
        return 22;
    else if(str=="char")
        return 23;
    else if(str=="bool")
        return 24;
    else if(str=="while")
        return 25;
    else if(str=="get")
        return 26;
    else if(str=="put")
        return 27;
    else if(str=="struct")
        return 28;
    else   
        return -1;
}

void LexicalAnalysis::unexpect()
{
    printf("There is an unexpect symbol:'%c' in \n " , temp_c);
    cout<<"row: "<<row<<"  column: "<<column<<endl;
}

bool LexicalAnalysis::Analysis(queue<Token> *token,SymbolTable *table)
{
    int state=0;

    string temp_string="";
    string singal_str="";

    Token temp_token;
    temp_token.column=0;
    temp_token.num=0;
    temp_token.row=0;
    temp_token.serial=0;
    temp_token.attri=string("");

    FILE* instream = fopen("in.txt", "r");
	FILE* outstream = fopen("out.txt", "w");

    bool wrong_flag=false;
    get_a_char(instream);
    do
    {
        switch (state)
        {
        case 0:
            if(temp_c=='[')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=18;
                temp_string.assign("[");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c==']')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=19;
                temp_string.assign("]");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='(')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=12;
                temp_string.assign("(");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c==')')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=13;
                temp_string.assign(")");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c==';')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=14;
                temp_string.assign(";");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='!')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=17;
                temp_string.assign("!");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c==',')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=29;
                temp_string.assign(",");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='+')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=3;
                temp_string.assign("+");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='-')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=4;
                temp_string.assign("`-");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='{')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=30;
                temp_string.assign("{");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='}')
            {
                temp_token.row=row;
                temp_token.column=column;
                temp_token.serial=31;
                temp_string.assign("}");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(letter(&temp_c))
            {
                state=1;
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else if(temp_c=='0')
            {
                state=2;
            }
            else if(temp_c>='1'&&temp_c<='9')
            {
                state=4;
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else if(temp_c=='<')
            {
                state=5;
            }
            else if(temp_c=='>')
            {
                state=6;
            }
            else if(temp_c=='=')
            {
                state=7;
            }
            else if(temp_c=='&')
            {
                state=8;
            }
            else if(temp_c=='|')
            {
                state=9;
            }
            else if (temp_c==' ')
            {
                get_a_char(instream);
            }
            else if (temp_c=='/')
            {
                state=11;
                get_a_char(instream);
            }
            else
            {
                /*wrong symble*/
                unexpect();
                get_a_char(instream);
            }

            break;
        
        case 1:
            get_a_char(instream);
            if(letter(&temp_c)||digit(&temp_c))
            {
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else
            {
                state=0;
                int value=find_key(temp_string);
                if(value>0)
                {
                    temp_token.serial=value;
                    temp_token.row=row;
                    temp_token.column=column;
                    temp_token.attri=temp_string;
                    token->push(temp_token);
                    temp_string.assign("");
                }
                else
                {

                    temp_token.serial=1;
                    temp_token.row=row;
                    temp_token.column=column;
                    temp_token.attri=temp_string;
                    token->push(temp_token);
                    table->addToMap(temp_string);
                    temp_string.assign("");
                }
                
            }
            break;
        case 2:
            singal_str=temp_c;
            temp_string+=singal_str;
            get_a_char(instream);
            //16进制
            if(temp_c=='X'||temp_c=='x')
            {
                singal_str=temp_c;
                temp_string+=singal_str;
                state=3;
            }
            //8进制
            else if(temp_c>='1'&&temp_c<='7')
            {
                state=10;
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else
            {
                state=0;

                temp_token.serial=2;
                temp_token.row=row;
                temp_token.column=column;
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 3:
            get_a_char(instream);
            if(digit(&temp_c) || (temp_c>='A'&&temp_c<='F') || (temp_c>='a'&&temp_c<='f'))
            {
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else
            {
                state=0;

                temp_token.serial=2;
                temp_token.row=row;
                temp_token.column=column;
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 4:
            get_a_char(instream);
            if(digit(&temp_c))
            {
                singal_str=temp_c;
                temp_string+=singal_str;
            }
            else
            {
                state=0;

                temp_token.serial=2;
                temp_token.row=row;
                temp_token.column=column;
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 5:
            get_a_char(instream);
            if(temp_c=='>')
            {
                state=0;
                temp_token.serial=9;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("<>");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else if(temp_c=='=')
            {
                state=0;
                temp_token.serial=11;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("<=");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else
            {
                state=0;
                temp_token.serial=8;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("<");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 6:
            get_a_char(instream);
            if(temp_c=='=')
            {
                state=0;
                temp_token.serial=10;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign(">=");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else
            {
                state=0;
                temp_token.serial=7;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign(">");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 7:
            get_a_char(instream);
            if(temp_c=='=')
            {
                state=0;
                temp_token.serial=6;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("==");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else
            {
                state=0;
                temp_token.serial=5;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("=");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 8:
            get_a_char(instream);
            if(temp_c=='&')
            {
                state=0;
                temp_token.serial=15;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("&&");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else
            {
                cout<<"Error: expect a symbol '&' here "<<endl;
                cout<<"row: "<<row<<"  column: "<<column<<endl;
                wrong_flag=true;
                state=0;
            }
            break;
        case 9:
            get_a_char(instream);
            if(temp_c=='|')
            {
                state=0;
                temp_token.serial=16;
                temp_token.row=row;
                temp_token.column=column;
                temp_string.assign("||");
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
                get_a_char(instream);
            }
            else
            {
                cout<<"Error: expect a symbol '|' here "<<endl;
                cout<<"row: "<<row<<"  column: "<<column<<endl;
                wrong_flag=true;
                state=0;
            }
            break;
        case 10:
            get_a_char(instream);
            if(temp_c>='1'&&temp_c<='7')
            {
                singal_str=temp_c;
                temp_string+=singal_str;  
            }
            else
            {
                state=0;
                temp_token.serial=2;
                temp_token.row=row;
                temp_token.column=column;
                temp_token.attri=temp_string;
                token->push(temp_token);
                temp_string.assign("");
            }
            break;
        case 11:
            if(temp_c=='*')
            {
                state=12;
                get_a_char(instream);
            }
            else
            {
                unexpect();
                state=0;
            }
            break;
        case 12:
            if(temp_c=='*')
            {
                state=13;
                get_a_char(instream);
            }
            else
            {
                get_a_char(instream);
            }
            break;
        case 13:
            if(temp_c=='/')
            {
                state=0;
                get_a_char(instream);
            }
            else
            {
                state=12;
                get_a_char(instream);
            }
            break;
        default:
            break;
        }
        //cout<<temp_c<<endl;
    }
    while( temp_c != EOF && !wrong_flag );

    fclose(instream);

    //写入至输出文件
    int token_length=token->size();
    for(int i=0;i<token_length;i++)
    {
        int length=token->front().attri.length();
        char temp_char[length+1];
        token->front().attri.copy(temp_char, length, 0);
        temp_char[length]='\0';

        fprintf( outstream, "%d %s\n", token->front().serial, temp_char );
        // printf("%d %s\n",token->front(), temp_char);
        
        token->push(token->front());
        token->pop();
    }
    fclose(outstream);

    //输出统计值
    cout<<"Total row: "<<row<<endl;
    cout<<"id's occurrence number :"<<endl;
    table->printInfo();

    return !wrong_flag;
}