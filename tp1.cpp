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
#include "shunting.h"
using namespace std;


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_metodo(string const &);
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
	{1, "m", "metodo","standard", opt_metodo, OPT_DEFAULT},
};

//static int factor;
static string metodo;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

/*****************************************************/

static void
opt_metodo(string const &arg)
{
	istringstream iss(arg);

	if (!(iss >> metodo)
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

	if(metodo != "karatsuba" && metodo!= "standard"){
		cerr<<"Metodo invalido"<<endl;
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

  string a;
  string b;

  while(getline(*is,str))
  {

		string s;
		bignum res;

		stack<string> rpn;
    for(char c:str) if(!isspace(c)) s += c;
		rpn = shunting_yard(s);
		str = operate(rpn, metodo);
		res=str;

    *oss<<res<<endl;

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

	cmdline cmdl(options);	// Objeto con parametro tipo option_t (struct) declarado globalmente.
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
  operar(iss, oss);	    // Funci�n externa, no es un metodo de ninguna clase o estructura usada en el codigo


  return 0;
}
