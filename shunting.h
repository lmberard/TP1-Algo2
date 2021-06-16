<<<<<<< HEAD
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
=======
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
>>>>>>> 6a25f85f88a3be9fe41b8dbe151c36882a74fdeb
