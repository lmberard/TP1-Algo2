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
// bignum a; hola puto

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

const bignum bignum::operator=(const string& right)
{
  if(right[0]=='-'){signo=false;}
  if(precision!=right.length())
  {
    unsigned short *aux;
    aux=new unsigned short[right.length()];
    delete[]digits;
    precision=right.length();
    digits=aux;
    for(int i=0; i<precision; i++)
      {digits[precision-1-i]=right[precision-signo-i]-ASCII_FIX;}
    return *this;
  }
  else
  {
    for(int i=0; i<precision; i++)
    {digits[precision-1-i]=right[precision-signo-i]-ASCII_FIX;}
    return *this;
  }
}


//tomo resta como una suma pero de numeros negativos?
//-a - b = -(a+b)
// a - b =  a +(-b)

bignum operator+(const bignum& a, const bignum& b)
{

  unsigned short precision = max(a.precision,b.precision);
  unsigned short carry = 0, aux = 0;
  bignum result(precision + 1);//como mucho el resultado va a tener un valor extra 9999+999= 5 de precision

  //suponiendo que ambos valores a y b son positivos, sino seria una resta
  //verificar y de ultima mandarlo a la funcion con -?
  /*
  EJEMPLO:a+(-b) ó (-a)+b
  if(!a.signo || !b.signo)
    result = a-b;

  EJEMPLO AMBOS NEGATIVOS: -a-b = -(a+b)
  if(!a.signo && !b.signo)
    result = a+b;
    result.signo= false;
  */

  for(unsigned int i = precision - 1; i >= 0; i--){//recorro de atras para adelante

    aux = a.digits[i];
    aux = aux + b.digits[i] + carry;

    //verifico el carry
    if(aux >= 10){
      aux -= 10;
      carry = 1;
    }
    else carry = 0;

    //si llego al principio, tengo que poner los dos numeros:
    if(i!= 0){
      result.digits[i+1] = aux;
    }
    else{
      result.digits[i+1] = aux;
      result.digits[i] = carry;

    }
  }
  return result;
}

//suponiendo la funcion a - b
bignum operator-(const bignum& a, const bignum& b)
{
  unsigned short precision = max(a.precision,b.precision);
  unsigned short resta = 0, aux = 0;
  bignum result(precision);

  //chequear esto
  if(a.digits[0] < b.digits[0]){
    result.signo = false;
  }

  for(unsigned int i = precision - 1; i >= 0; i--){

    aux = a.digits[i] - resta;
    if(aux < b.digits[i]){
      aux += 10;
      resta = 1;
    }
    else {
      resta = 0;
    }

    aux -= b.digits[i];
    result.digits[i] = aux;
  }

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
    if(num.digits[i]==0 && aux==false)
    {continue;}
    os << num.digits[i];
    aux=true;
  }
  return os;
}
