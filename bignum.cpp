#include "bignum.h"
#include <string>

friend bignum::bignum()
{
  precision = 10;
  digits = new unsigned short[precision];
}
// bignum a;

friend bignum::bignum(unsigned char a)
{
  precision = a;
  digits = new unsigned short[precision];
}
friend bignum::bignum(int a)
{

}
friend bignum::bignum(string str)
{
  //pones signo
  if(str[0]=='-')
  {
    signo=False;
    precision=length(str)-1;
    digits=new unsigned short[precision];
  }
  else
  {
    //pasas el nro a bignum
    signo=True;
    precision=length(str);
    digits=new unsigned short[precision];
  }
  for(i=0;i<precision;i++)
  {
    digits[precision-1-i]=str[precision-1-i];
  }

}

friend bignum::~bignum()
{
  if(digits)
  {delete[] digits;}
}

friend bignum operator=(const int& nro)// bignum a = 123415;
{
  //destruyo a
  // bignum resultado(nro);
  // creo otro bignum con el creador al que le pasas la precision
  // return resultado;
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
