/*
Universidad de Buenos Aires
Facultad de Ingenieria

Algoritmos y Programación II - Trabajo Practico N°0 

Integrantes:
Berard, Lucıa Magdalena		101213  lberard@fi.uba.ar
Guglieri, Mariano Federico    	99573	mguglieri@fi.uba.ar
Rubin, Ivan Eric		100577  irubin@fi.uba.ar
Sandoval, Diego Ariel		101639  dsandoval@fi.uba.ar
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctype.h>
#include <string>
#include <bits/stdc++.h>
#include "cmdline.h"
#include "bignum.h"
using namespace std;


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_precision(string const &);
static void opt_help(string const &);

/*
// Tabla de opciones de linea de comando. El formato de la tabla
// consta de un elemento por cada opcion a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opcion lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opcion.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opcion en caso que no este explicitamente presente
//   en la linea de comandos del programa. Si la opcion no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al metodo de parseo de la opcion,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La ultima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opcion: cuando la
//   opcion es obligatoria, debera activarse OPT_MANDATORY.
//
// Ademas, la ultima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//
*/
/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{1, "p", "precision",NULL, opt_precision, OPT_DEFAULT},
};

//static int factor;
static unsigned int precision;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

/********** *******************************************/   

static void
opt_precision(string const &arg)
{
	istringstream iss(arg);

	if (!(iss >> precision)
	    || !iss.eof()) {
		cerr << "non-integer precision: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}

	if (iss.bad()) {
		cerr << "cannot read integer precision."
		     << endl;
		exit(1);
	}
}

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estandar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// est�ndar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminaci�n del programa en su totalidad
	}
}


static void
opt_help(string const &arg)
{
	cout << "cmdline -p precision [-i file] [-o file]"
	     << endl;
	exit(0);
}


void operar(istream *is, ostream *os)
{
  string str;
  string s;
  string a;
  string b;

  while(getline(*iss,str))
  {
    a="";
    b="";
    s="";
    for(char c:str) if(!isspace(c)) s += c;

    if(!s.empty()){
      //Chequeo que no haya letras ni caracteres invalidos
      if(!(s.find_first_not_of("0123456789+-*") == string::npos))
      {
        cerr<<"Operacion invalida"<<endl;
        exit(1);
      }
      //Chequeo que la operacion sea valida
      size_t n = count(s.begin(),s.end(),'*');
      if(n>1){
        cerr<<"Operacion invalida"<<endl;
        exit(1);
      }
      n += count(s.begin(),s.end(),'+');
      n += count(s.begin(),s.end(),'-');


      if(n==0){
        cerr<<"Operacion invalida"<<endl;
        exit(1);
      }
      if(n > 3){
        cerr<<"Operacion invalida"<<endl;
        exit(1);
      }
      if(s[s.length()-1]=='+'||s[s.length()-1]=='-'){
        cerr<<"Operacion invalida"<<endl;
        exit(1);
      }

      size_t pos_op;
      if(n==1)
      {
        if(s[0]=='+'||s[0]=='-'){
          cerr<<"Operacion invalida"<<endl;
          exit(1);
        }
        pos_op = s.find_first_of("+-*");
        for(size_t i=0; i<pos_op;i++)
          a.push_back(s[i]);
        for(size_t i=pos_op+1; i<s.length();i++)
          b.push_back(s[i]);
      }

      if(n==2)
      {
        if(s[0]=='+'||s[0]=='-'){
          pos_op = s.find_first_of("+-*",1);
        }else{
          pos_op = s.find_first_of("+-*");
        }

        if(s[pos_op+1]!='+'&&s[pos_op+1]!='-'&&s[0]!='-'&&s[0]!='+'){
          cerr<<"Operacion invalida"<<endl;
          exit(1);
        }
        for(size_t i=0; i<pos_op;i++)
          a.push_back(s[i]);
        for(size_t i=pos_op+1; i<s.length();i++)
          b.push_back(s[i]);
      }
      if(n==3)
      {

        if(s[0]!='+'&&s[0]!='-'){
          cerr<<"Operacion invalida"<<endl;
          exit(1);
        }
        pos_op = s.find_first_of("+-*",1);

        if(s[pos_op+1]!='+'&&s[pos_op+1]!='-'){
          cerr<<"Operacion invalida"<<endl;
          exit(1);
        }
        for(size_t i=0; i<pos_op;i++)
          a.push_back(s[i]);
        for(size_t i=pos_op+1; i<s.length();i++)
          b.push_back(s[i]);

      }

      bignum res;
      bignum num1;
      bignum num2;

      num1=a;
      num2=b;

      num1.set_precision(precision);
      num2.set_precision(precision);

      if(s[pos_op]=='+')
        res=num1+num2;
      if(s[pos_op]=='-')
        res=num1-num2;
      if(s[pos_op]=='*')
        res=num1*num2;

      *oss<<res<<endl;
    }

  }
  if(!is->eof()){
    cerr<<"No se encontro EOF en la entrada"<<endl;
    exit(1);
  }
  if(is->bad()){
    cerr<<"No se pudo leer la entrada"<<endl;
    exit(1);
  }
  if(os->bad()){
    cerr<<"No se pudo escribir en la salida"<<endl;
    exit(1);
  }
}

int main(int argc, char * const argv[])
{

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente. Ver l�nea 51 main.cc
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
  operar(iss, oss);	    // Funci�n externa, no es un metodo de ninguna clase o estructura usada en el c�digo


  return 0;
}
