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

#include "tp1.h"
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
	{1, "m", "metodo","karatsuba", opt_metodo, OPT_DEFAULT},
};

//static int factor;
static string metodo;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

/*****************************************************/

static void opt_metodo(string const &arg){
	istringstream iss(arg);
	if(!(iss >> metodo)||!iss.eof()){
		cerr<<INVALID_METHOD_MSG<<": "<<arg<<"."<<endl;
		exit(1);
	}
	if(iss.bad()){
		cerr<<CANT_READ_METHOD<<endl;
		exit(1);
	}
	if(metodo!=METHOD_KARATSUBA&&metodo!=METHOD_STANDARD){
		cerr<<INVALID_METHOD_MSG<<endl;
		exit(1);
	}
}

static void opt_input(string const &arg){
	// Si el nombre del archivos es "-", usaremos la entrada
	// estandar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	if (arg=="-"){
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}else{
		// c_str(): Returns a pointer to an array that contains a null-terminated
		// sequence of characters (i.e., a C-string) representing
		// the current value of the string object.
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}
	// Verificamos que el stream este OK.
	if (!iss->good()){
		cerr<<CANT_OPEN_MSG<<arg<<"."<< endl;
		exit(1);
	}
}

static void opt_output(string const &arg){
	// Si el nombre del archivos es "-", usaremos la salida
	// estandar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	if(arg=="-"){
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	}else{
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}
	// Verificamos que el stream este OK.
	if(!oss->good()){
		cerr<<CANT_OPEN_MSG<<arg<<"."<<endl;
		exit(1);		// EXIT: Terminacion del programa en su totalidad
	}
}

static void opt_help(string const &arg){
	cout << HELP_MSG << endl;
	exit(0);
}

bool contains(string s, string cont){
  if(s.find_first_of(cont) != string::npos){
    return true;
  }else
    return false;
}

bool contains_different_of(string s, string cont){
	if(s.find_first_not_of(cont) != string::npos){
    return true;
  }else
    return false;
}

void validate_input_string(string s){
	if(contains_different_of(s,VALID_INPUT)){
		cerr<<ERR_INVALID_INPUT<<endl;
		exit(1);
	}
}

size_t count_op(stack<string>* s){
  size_t count=0;
  stack<string> aux;

  while(!s->empty()){
    if(!contains(s->top(),NUMBERS)){
      aux.push(s->top());
      s->pop();
      count++;
    }else{
      aux.push(s->top());
      s->pop();
    }
  }

  while(!aux.empty()){
    s->push(aux.top());
    aux.pop();
  }

  return count;
}

size_t count_num(stack<string>* s){
  size_t count=0;
  stack<string> aux;

  while(!s->empty()){
    if(contains(s->top(),NUMBERS)){
      aux.push(s->top());
      s->pop();
      count++;
    }else{
      aux.push(s->top());
      s->pop();
    }
  }

  while(!aux.empty()){
    s->push(aux.top());
    aux.pop();
  }

  return count;
}

void validate_operation(stack<string>* s){

  stack<string> aux;
	bool tiene_par = false;
	if(count_op(s) >= count_num(s)){
		cerr<<ERR_INVALID_INPUT<<endl;
		delete s;
		exit(1);
	}

  while(!s->empty()){
    if(contains(s->top(),LEFT_PARENTHESES)){
      aux.push(s->top());
      s->pop();
      tiene_par=true;
    }else{
      aux.push(s->top());
      s->pop();
    }
  }
	if(tiene_par){
		cerr<<ERR_INVALID_INPUT<<endl;
		delete s;
		exit(1);
	}

  while(!aux.empty()){
    s->push(aux.top());
    aux.pop();
  }
}

void interpret(istream *is, ostream *os){
  string str;
  string a;
  string b;

  while(getline(*is,str))
  {
		string s;
    for(char c:str) if(!isspace(c)) s += c;
		validate_input_string(s);

	  stack<string>* rpn= shunting_yard(s);
		validate_operation(rpn);
		str = operate(*rpn, metodo);
		delete rpn;

		bignum res;
		res=str;
    *oss<<res<<endl;
  }

  if(!is->eof()){
    cerr<<ERR_NO_EOF<<endl;
    exit(1);
  }
  if(is->bad()){
    cerr<<ERR_CANT_READ_INPUT<<endl;
    exit(1);
  }
  if(os->bad()){
    cerr<<ERR_CANT_WRITE_OUTPUT<<endl;
    exit(1);
  }
}

int main(int argc, char * const argv[]){

	cmdline cmdl(options); 	// Objeto con parametro tipo option_t (struct) declarado globalmente.
	cmdl.parse(argc, argv); // Metodo de parseo de la clase cmdline
	interpret(iss, oss); 		// Funcion externa, no es un metodo de ninguna clase o estructura usada en el codigo

  return 0;
}
