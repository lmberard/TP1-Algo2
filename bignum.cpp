#include "bignum.h"
#include <string>
using namespace std;

bignum::bignum()
{
  signo = true;
  precision = 10;
  digits = new unsigned short[precision];
}
// bignum a; eeee putoooooovfdsggfds

bignum::bignum(const unsigned short a)
{
  signo = true;
  precision = a;
  digits = new unsigned short[precision];
}

bignum::bignum(const string &str)
{
  //pones signo
  if(str[0]=='-')
  {
    signo=false;
    precision=str.length()-1;
  }
  else
  {
    //pasas el nro a bignum
    signo=true;
    precision=str.length();
  }
  digits=new unsigned short[precision];
  for(size_t i=0;i<precision;i++)
  {
    digits[precision-1-i]=(short)str[precision-1-i];
    cout << digits[precision-1-i] << endl;
  }

}

bignum::~bignum()
{
  if(digits)
  {delete[] digits;}
}

unsigned short bignum::get_p()
{
  return precision;
}


const bignum bignum::operator=(const bignum& right)
{
  if(&right !=this)
  {
    signo=right.signo;
    if(precision!=right.precision)
    {
      unsigned short *aux;
      aux=new unsigned short[right.precision];
      delete[]digits;
      precision=right.precision;
      digits=aux;
      for(int i=0; i<precision; i++)
        {digits[i]=right.digits[i];}
      return *this;
    }
    else
    {
      for(int i=0; i<precision; i++)digits[i]=right.digits[i];
      return *this; //al retornar una referencia perimite x=y=z;
    }
  }
  return *this;
}
const bignum bignum::operator=(const int &right)
{// bignum a = 123415;
  //destruyo a
  // bignum resultado(nro);
  // creo otro bignum con el creador al que le pasas la precision
  // return resultado;
  bignum a;
  return a;
}
bignum operator+(const bignum& a, const bignum& b)
{
  bignum result;
  /*for(i=0;i<max(a.precision,b.precision);i++)
  {
    if(a[])
  }*/
//  0 0 1 1 1 2 5 7 // El 7 es a[7] (es un bignum)
//  4 5 7 3 5 8 9 5 // Le sumas b[7] si da mas de 10 carry++;
  return result;
}

std::ostream& operator<<(std::ostream& os, const bignum& num)
{
  if(num.signo==false)
  { os << '-'; }
  for(size_t i = 0; i< num.precision;i++)
  {
    os << num.digits[i];
  }
  return os;
}
