#ifndef TP1_INCLUDE
#define TP1_INCLUDE

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <bits/stdc++.h>
#include <exception>
#include <stack>
#include "cmdline.h"
#include "bignum.h"
#include "shunting.h"
using namespace std;

#define VALID_INPUT "+-*/0123456789()"
#define NUMBERS "0123456789"
#define OPERATORS "*+-/"
#define METHOD_KARATSUBA "karatsuba"
#define METHOD_STANDARD "standard"

#define ERR_INVALID_INPUT "Invalid Input"

bool contains(string, string);
bool contains_different_of(string, string);
void validate_input_string(string);
void validate_operation(stack<string>*);
size_t count_op(stack<string>);
size_t count_num(stack<string>);
void interpret(istream*, ostream*);

#endif
