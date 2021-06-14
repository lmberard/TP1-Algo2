#include<iostream>
#include<string>
#include "bignum.h"
using namespace std;


#ifndef SHUNTING_INCLUDED
#define SHUNTING_INCLUDED


string operate(stack<string>);
stack<string> shunting_yard(string &s);
bool contains(string s, string cont);
size_t count_op(stack<string>);
size_t count_num(stack<string>);

#endif
