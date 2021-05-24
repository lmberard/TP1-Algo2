#include "bignum.h"
#include <string>
#include <algorithm>
using namespace std;

bignum::bignum()
{
  signo = true;
  precision = 10;
  digits = new unsigned short[precision];

  for(size_t i=0;i<precision;i++)
  {digits[i]=0;}
}


bignum::bignum(const unsigned short a)
{
  signo = true;
  precision = a;
  digits = new unsigned short[precision];
  for(size_t i=0;i<precision;i++)
  {digits[i]=0;}
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

const bignum& bignum::operator=(const string& right)
{
  string str;
  for(char c:right) if(!isspace(c)) str += c ;

  if(str[0]=='-'){signo=false;}
  if(precision!=str.length())
  {
    unsigned short *aux;
    aux=new unsigned short[str.length()-!signo];
    delete[]digits;
    precision=str.length()-!signo;
    digits=aux;
    for(int i=0; i<precision; i++)
    {
      digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
      cout<<digits[precision-1-i]<<endl;
    }
    return *this;
  }else
  {
    for(int i=0; i<precision; i++)
    {digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;}
    return *this;
  }
}

bignum bignum::operator+(const bignum& a, const bignum& b)
{

}

bignum bignum::operator-(const bignum& a, const bignum& b)
{

}

std::ostream& operator<<(std::ostream& os, const bignum& num)
{
  if(num.signo==false)
  { os << '-'; }
  bool aux= false;
  for(size_t i = 0; i< num.precision;i++)
  {
    //saco los ceros de la izquierda
    if(num.digits[i]==0 && aux==false)
    {continue;}
    os << num.digits[i];
    aux=true;
  }
  return os;
}
