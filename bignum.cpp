#include "bignum.h"
#include <string>

friend bignum::bignum()
{
  digits= new unsigned short[1];

}
// bignum a = 1243134;
// a= 12315234;

friend bignum::bignum(unsigned char a)//Le paso 234, lo convierte a bignum
{

}
friend bignum::bignum(string a)
{

}
friend bignum::~bignum()
{

}

friend bignum operator+(const bignum& a, const bignum& b)
{
  bignum result;
  for(i=0;i<max(a.precision,b.precision);i++)
  {
    if(a[])
  }
  0 0 1 1 1 2 5 7 // El 7 es a[7] (es un bignum)
  4 5 7 3 5 8 9 5 // Le sumas b[7] si da mas de 10 carry++;
}
