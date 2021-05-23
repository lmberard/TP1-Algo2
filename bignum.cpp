#include "bignum.h"
#include <string>
#include <algorithm>
using namespace std;

bignum::bignum()
{
  signo = true;
  precision = 10;
  digits = new unsigned short[precision];
}

// bignum a; hola amor


bignum::bignum(const unsigned short a)
{
  signo = true;
  precision = a;
  digits = new unsigned short[precision];
}

bignum::bignum(const string &str1)
{
  //Saco los espacios en blanco.
  string str;
  for(char c:str1) if(!isspace(c)) str += c ;
  //Defino el signo.
  if(str[0]=='-')
  {
    signo=false;
    precision=str.length()-1;
  } else
  {
    signo=true;
    precision=str.length();
  }
  //Creo el arreglo de shorts
  digits=new unsigned short[precision];
  for(size_t i=0;i<precision;i++)
  {
    digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
  }
}

bignum::~bignum()
{
  if(digits)
  {delete[] digits;}
}

void bignum::set_p(unsigned short a)
{
  precision=a;
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
      return *this;
    }
  }
  return *this;
}

/*const bignum bignum::operator=(const string& right)
{
  if(right[0]=='-'){signo=false;}
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
    return *this;
  }
}*/


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
  bool aux= false;
  for(size_t i = 0; i< num.precision;i++)
  {
    //saco los ceros de la izquierda
    if(num.digits[i]==0 && aux==true)
    {continue;}
    os << num.digits[i];
    aux=true;
  }
  return os;
}
