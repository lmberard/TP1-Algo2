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
#define BEHIND_MINUS ")0123456789"
#define OPERATORS "*+-/"
#define LEFT_PARENTHESES "("
#define RIGHT_PARENTHESES ")"
#define SUM "+"
#define MINUS "-"
#define MULTIPLY "*"
#define DIVIDE "/"
#define METHOD_KARATSUBA "karatsuba"
#define METHOD_STANDARD "standard"

#define HELP_MSG "cmdline -m method [-i file] [-o file]"
#define CANT_OPEN_MSG "Cannot open "
#define INVALID_METHOD_MSG "Invalid method"
#define CANT_READ_METHOD "Cannot read method."

#define ERR_INVALID_INPUT "Invalid Input."
#define ERR_DIVIDE_BY_ZERO "Invalid Input (Divides by zero value)."
#define ERR_NO_EOF "No se encontro EOF en la entrada."
#define ERR_CANT_READ_INPUT "No se pudo leer la entrada."
#define ERR_CANT_WRITE_OUTPUT "No se pudo escribir en la salida."
#define ERR_NO_MULT_INTERFACE "Error assigning multiplication interface"


bool contains(string, string);
bool contains_different_of(string, string);
void validate_input_string(string);
void validate_operation(stack<string>*);
size_t count_op(stack<string>*);
size_t count_num(stack<string>*);
void interpret(istream*, ostream*);

#endif
