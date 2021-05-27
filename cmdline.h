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

#ifndef _CMDLINE_H_INCLUDED_
#define _CMDLINE_H_INCLUDED_

#include <string>
#include <iostream>

#define OPT_DEFAULT   0
#define OPT_SEEN      1
#define OPT_MANDATORY 2

struct option_t {
	int has_arg;
	const char *short_name;
	const char *long_name;
	const char *def_value;
	void (*parse)(std::string const &); // Puntero a función de opciones
	int flags;
};

class cmdline {
	// Este atributo apunta a la tabla que describe todas
	// las opciones a procesar. Por el momento, sólo puede
	// ser modificado mediante contructor, y debe finalizar
	// con un elemento nulo.
	//
	option_t *option_table;

	// El constructor por defecto cmdline::cmdline(), es
	// privado, para evitar construir "parsers" (analizador 
	// sintáctico, recibe una palabra y lo interpreta en 
	// una acción dependiendo su significado para el programa) 
	// sin opciones. Es decir, objetos de esta clase sin opciones.
	//

	cmdline();
	int do_long_opt(const char *, const char *);
	int do_short_opt(const char *, const char *);
public:
	cmdline(option_t *);
	void parse(int, char * const []);
};

#endif
