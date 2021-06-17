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
#ifndef BIGNUM_INCLUDED
#define BIGNUM_INCLUDED

#include <iostream>
#include <string>
#include <algorithm>
#include "tp1.h"
#include "standard.h"
#include "karatsuba.h"
using namespace std;

#define ASCII_FIX 48
#define TEN_STR "10"

class multiply_interface;

class bignum
{
    friend class multiply_interface;
  private:
    friend class standard;

    //Atributos
    bool signo;
    unsigned long len;
    unsigned short *digits;
    static multiply_interface* mult;
    static int instances;

    //Funciones privadas
    friend bool is_zero(const bignum&);
    friend bignum truelen(const bignum&);

    //Funciones usadas en Karatsuba
    friend bignum llenar(const bignum&, int);
    friend bignum shift1(const bignum &,int);
    friend bignum operator/(const bignum&, int);
    friend bignum operator%(const bignum&, int);

  public:

    bignum();
    bignum(const unsigned long);
    bignum(const bignum&);
    bignum(const string&);
    ~bignum();
    void set_mult_strategy(multiply_interface*);
    bool get_signo();
    unsigned char get_len();
    string to_string();

    const bignum& operator=(const bignum&);
    const bignum& operator=(const string&);

    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend bignum operator/(const bignum&, const bignum&);

    friend bool operator==(const bignum&, const bignum&);
    friend bool operator<(const bignum&, const bignum&);
    friend bool operator>(const bignum&, const bignum&);

    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);
};


#endif
