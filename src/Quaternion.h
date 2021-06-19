#ifndef QUATERNION_H
#define QUATERNION_H
#include <string.h>
#include <iostream>
using namespace std;

struct Quaternion
{
    int num;
    string op;
    string arg1;
    string arg2;
    int * result_type; //如果是-1，代表result存放了一个变量，如果是数字，则是跳转的地址
    string result; 
};
#endif 