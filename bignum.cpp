#include "bignum.h"
#include <string>
#include <algorithm>
using namespace std;


bignum::bignum(void)
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

  if(!(str.find_first_not_of("0123456789") == string::npos) && (str[0]!='-' && str[0]!='+'))
  {
    cout<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }

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
void bignum::set_signo(bool s){
  signo=s;
}

const bignum& bignum::operator=(const bignum& right)
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
  if(!(str.find_first_not_of("0123456789") == string::npos) && (str[0]!='-' && str[0]!='+'))
  {
    cout<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  if(str[0]=='-'){signo=false;}
  if(precision!=str.length())
  {
    unsigned short *aux;
    aux=new unsigned short[str.length()-!signo];
    delete[]digits;
    precision=str.length()-!signo;
    digits=aux;
    for(int i=0; i<precision; i++)
      digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
    return *this;
  }else
  {
    for(int i=0; i<precision; i++)
      digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
    return *this;
  }
}

const bignum& bignum::operator=(const char*& right)
{
  string str;
  string s = right;
  for(char c:s) if(!isspace(c)) str += c ;

  if(!(str.find_first_not_of("0123456789") == string::npos) && (str[0]!='-' && str[0]!='+'))
  {
    cout<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  if(str[0]=='-'){signo=false;}
  if(precision!=str.length())
  {
    unsigned short *aux;
    aux=new unsigned short[str.length()-!signo];
    delete[]digits;
    precision=str.length()-!signo;
    digits=aux;
    for(int i=0; i<precision; i++)
      digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
    return *this;
  }else
  {
    for(int i=0; i<precision; i++)
      digits[precision-1-i]=str[precision-signo-i]-ASCII_FIX;
    return *this;
  }
}

bignum operator+(const bignum& a, const bignum& b)
{
  unsigned short n = a.precision;
  unsigned short m = b.precision;
  bignum result(max(n,m)+1);
  if(!a.signo && b.signo){
    bignum c = -a;
    result=b-c;
    return result;
  }
  if(a.signo && !b.signo){
    bignum c = -a;
    result=a-c;
    return result;
  }
  if(!a.signo && !b.signo){
    result.signo=false;
  }
  unsigned short carry = 0;
  unsigned short aux = 0;

  for(size_t i=0; i< max(n,m)+1;i++){

    if((short)(m-i-1)<0 && (short)(n-i-1)<0){
      aux=carry;
    } else if((short)(n-i-1)<0){
      aux=b.digits[m-i-1]+carry;
    } else if((short)(m-i-1)<0){
      aux=a.digits[n-i-1]+carry;
    } else {
      aux=a.digits[n-i-1]+b.digits[m-i-1]+carry;
    }

    if(aux>=10){
      aux-=10;
      carry=1;
    } else {
      carry=0;
    }
    result.digits[max(n,m)-i]=aux;
    result.digits[0] = aux;
  }

  return result;
}

bignum operator-(const bignum& a, const bignum& b)
{

  unsigned short n = a.precision;
  unsigned short m = b.precision;
  bignum result(max(n,m));


  if(a==b){
    return result;
  }
  if(!a.signo && b.signo){
    result = a+b;
    result.signo=false;
    return result;
  }
  if(a.signo && !b.signo){
    bignum c = -b;
    result=a+c;
    return result;
  }
  if(!a.signo && !b.signo){
    result = (-b)-a;
    return result;
  }
  if(a<b){
    result = b-a;
    result.signo=false;
    return result;
  }

  short carry = 0;
  short aux = 0;

  for(size_t i=0; i< max(n,m);i++){

    if((short)(m-i-1)<0 && (short)(n-i-1)<0){
      aux=carry;
    } else if((short)(m-i-1)<0){
      aux=a.digits[n-i-1]-carry;
    } else {
      aux=(short)a.digits[n-i-1]-(short)b.digits[m-i-1]-carry;
    }


    if(aux<0){
      aux+=10;
      carry=1;
    } else {
      carry=0;
    }
    result.digits[result.precision-i-1]=aux;
  }
  return result;
}
bignum operator-(const bignum& num)
{
  bignum result;
  result.precision=num.precision;
  result.signo=!num.signo;
  result.digits=num.digits;
  return result;
}
bool operator==(const bignum&a, const bignum&b)
{
  if(a.signo==b.signo && a.precision==b.precision)
  {
    for(size_t i = 0; i < a.precision; i++)
    {
      if(a.digits[i]!=b.digits[i])
        return false;
    }
    return true;
  }
  return false;
}

bool operator<(const bignum& a, const bignum& b)
{
  if(a.precision<b.precision)
    return true;
  else if(b.precision<a.precision)
    return false;
  else{
    for(int i=0; i<a.precision; i++)
    {
      if(a.digits[i]<b.digits[i]){
        return true;
      }else if(b.digits[i]<a.digits[i])
        return false;
    }
  }
  return false;
}
bool operator>(const bignum& a, const bignum& b)
{
  if(a.precision>b.precision)
    return true;
  else if(b.precision>a.precision)
    return false;
  else{
    for(int i=0; i<a.precision; i++)
    {
      if(a.digits[i]>b.digits[i]){
        return true;
      }else if(b.digits[i]>a.digits[i])
        return false;
    }
  }
  return false;
}

ostream& operator<<(ostream& os, const bignum& num)
{
  if(num.signo==false)
  { os << '-'; }
  bool aux= false;
  for(size_t i = 0; i< num.precision;i++)
  {
    //saco los ceros de la izquierda
    if(num.digits[i]==0 && aux==false)
    {
      if(i==num.precision-1){
        os<<'0';
        return os;
      }
      continue;
    }
    os << num.digits[i];
    aux=true;
  }
  return os;
}

istream& operator>>(istream& is, bignum& num)
{
  string s;
  is >> s;
  while(!(s.find_first_not_of( "0123456789" ) == string::npos) && (s[0]!='-' && s[0]!='+'))
  {
    cout << "El valor ingresado no es correcto. Intente nuevamente." << endl;
    is >> s;
  }
  num = s;
  return is;
}
