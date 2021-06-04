#include <iostream>
#include <string.h>
#include "Serial.h"
using namespace std;

string intToStr(int token)
{
    switch (token)
    {
        case 3:
            return string("+");
            break;
        case 4:
            return string("-");
            break;
        case 5:
            return string("=");
            break;
        case 6:
            return string("==");
            break;
        case 7:
            return string(">");
            break;
        case 8:
            return string("<");
            break;
        case 9:
            return string("<>");
            break;
        case 10:
            return string(">=");
            break;
        case 11:
            return string("<=");
            break;
        case 12:
            return string("(");
            break;
        case 13:
            return string(")");
            break;
        case 14:
            return string(";");
            break;
        case 15:
            return string("&&");
            break;
        case 16:
            return string("||");
            break;
        case 17:
            return string("!");
            break;
        case 18:
            return string("8");
            break;
        case 19:
            return string("9");
            break;
        case 29:
            return string(",");
            break;
        case 30:
            return string("{");
            break;
        case 31:
            return string("}");
            break;
        case 20:
            return string("if");
            break;
        case 21:
            return string("else");
            break;
        case 22:
            return string("int");
            break;
        case 23:
            return string("char");
            break;
        case 24:
            return string("bool");
            break;
        case 25:
            return string("while");
            break;
        case 28:
            return string("struct");
            break;
        case 26:
            return string("put");
            break;
        case 27:
            return string("get");
            break;
        
        case 100:
            return string("S");
            break;
        case 101:
            return string("A");
            break;
        case 102:
            return string("B");
            break;
        case 103:
            return string("D'");
            break;
        case 104:
            return string("R");
            break;
        case 105:
            return string("R'");
            break;
        case 106:
            return string("T");
            break;
        case 1:
            return string("id");
            break;
        case 2:
            return string("num");
            break;
        default:
            return string("NULL");
            break; 
        
    }

}
