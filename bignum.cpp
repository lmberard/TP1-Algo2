#include "bignum.h"

friend bignum::bignum()
{

}
friend bignum::bignum(int a)
{

}
friend bignum::~bignum()
{

}

friend bignum operator+(const bignum&, const bignum&)
{
  1 1 1 2 5 7 // El 7 es a[5] (es un bignum)
  4 5 7 3 5 8 // Le sumas b[5] si da mas de 10 carry++;
}
