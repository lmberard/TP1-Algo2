#ifndef SHUNTING_INCLUDED
#define SHUNTING_INCLUDED

#include<iostream>
#include<string>
#include "bignum.h"
using namespace std;

string operate(stack<string>, string);
stack<string> shunting_yard(string &s);
bool contains(string s, string cont);
size_t count_op(stack<string>);
size_t count_num(stack<string>);

#endif
