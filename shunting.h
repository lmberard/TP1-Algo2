#ifndef SHUNTING_INCLUDED
#define SHUNTING_INCLUDED

#include<iostream>
#include<string>
#include <stack>
#include <queue>
#include "bignum.h"
#include "tp1.h"
#include "karatsuba.h"
#include "standard.h"

using namespace std;

string operate(stack<string>&, string);
stack<string>* shunting_yard(string &s);

#endif
