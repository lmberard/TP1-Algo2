#include "bignum.h"
#include <string>
#include <algorithm>
using namespace std;


bignum::bignum(void)
{
  signo = true;
  len = 10;
  digits = new unsigned short[len];

  for(size_t i=0;i<len;i++)
  {digits[i]=0;}
}


bignum::bignum(const unsigned short a)
{
  signo = true;
  len = a;
  digits = new unsigned short[len];
  for(size_t i=0;i<len;i++)
  {digits[i]=0;}
}

bignum::bignum(const string &str1)
{

  //Saco los espacios en blanco.
  string str;
  for(char c:str1) if(!isspace(c)) str += c ;

  if(!(str.find_first_not_of("0123456789") == string::npos) && (str[0]!='-' && str[0]!='+'))
  {
    cerr<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }

  //Defino el signo.
  bool hay_signo;
  if(str[0]=='-')
  {
    signo=false;
    hay_signo=true;
    len=str.length()-1;
  } else if(str[0]=='+')
  {
    signo=true;
    hay_signo=true;
    len=str.length()-1;
  }else{
    hay_signo=true;
    len=str.length();
  }
  //Creo el arreglo de shorts
  digits=new unsigned short[len];


  for(size_t i=0;i<len;i++)
  {
    digits[len-1-i]=str[len+hay_signo-i]-ASCII_FIX;
  }
}

bignum::~bignum()
{
  if(digits)
  {delete[] digits;}
}

void bignum::set_signo(bool s){
  signo=s;
}
bool bignum::get_signo(){
  return signo;
}
unsigned char bignum::get_len(){
  return len;
}

void bignum::set_precision(const unsigned short precision){
  if(precision>0 && len>precision)
  {
    for(int i=0; i<len-precision; i++){
      if(digits[precision]>=5)
        digits[precision-1]++;
      digits[precision+i]=0;
    }
  }
}


const bignum& bignum::operator=(const bignum& right)
{
  if(&right !=this)
  {
    signo=right.signo;
    if(len!=right.len)
    {
      unsigned short *aux;
      aux=new unsigned short[right.len];
      delete[]digits;
      len=right.len;
      digits=aux;
      for(int i=0; i<len; i++)
        {digits[i]=right.digits[i];}
      return *this;
    }
    else
    {
      for(int i=0; i<len; i++)digits[i]=right.digits[i];
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
    cerr<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  bool hay_signo=false;
  if(str[0]=='-'){signo=false;hay_signo=true;}
  if(str[0]=='+'){signo=true;hay_signo=true;}
  if(len!=str.length())
  {
    unsigned short *aux;
    aux=new unsigned short[str.length()-hay_signo];
    delete[]digits;
    len=str.length()-hay_signo;
    digits=aux;
    for(int i=0; i<len; i++)
      digits[len-1-i]=str[len+hay_signo-i-1]-ASCII_FIX;
    return *this;
  }else
  {
    for(int i=0; i<len; i++)
      digits[len-1-i]=str[len+hay_signo-i]-ASCII_FIX;
    return *this;
  }
}

bignum operator+(const bignum& a, const bignum& b)
{

  unsigned short n = a.len;
  unsigned short m = b.len;
  bignum result(max(n,m)+1);
  if(!a.signo && b.signo){
    bignum c = -a;
    result=b-c;
    return result;
  }
  if(a.signo && !b.signo){
    bignum c = -b;
    result=a-c;
    return result;
  }
  if(!a.signo && !b.signo){
    result.signo=false;
  }
  unsigned short carry = 0;
  unsigned short aux = 0;

  for(int i=0; i< max(n,m)+1;i++){

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

  unsigned short n = a.len;
  unsigned short m = b.len;
  bignum result(max(n,m));


  if(a==b){
    return result;
  }
  if(a<b){
    result = b-a;
    result.signo=false;
    return result;
  }
  if(!a.signo && b.signo){
    bignum c=-a;
    result = c+b;
    result.signo=false;
    return result;
  }
  if(a.signo && !b.signo){
    bignum c = -b;
    result=a+c;
    return result;
  }
  if(!a.signo && !b.signo){

    bignum c= -b;
    bignum d= -a;
    result = c-d;
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
    result.digits[result.len-i-1]=aux;
  }
  return result;
}

bignum operator-(const bignum& num)
{
  bignum result;
  result=num;
  result.signo=!num.signo;

  return result;
}

bignum operator*(const bignum& a, const bignum& b){

  unsigned short n = a.len;
  unsigned short m = b.len;
  unsigned short carry = 0;
  bignum aux(n+m);
  bignum aux2(n+m);
  bignum result(n+m);

  for(size_t j = 0; j < m; j++){
    for(size_t i = 0; i < n; i++){
      aux.digits[n+m-1-i-j] = a.digits[n-1-i]*b.digits[m-1-j] + carry;
      if(aux.digits[n+m-1-i-j] >= 10){
        carry = aux.digits[n+m-1-i-j]/10;
        aux.digits[n+m-1-i-j] -=  10*(aux.digits[n+m-1-i-j]/10);
      }
      else carry = 0;
    }
    aux.digits[m-1-j] = carry;

  for(size_t k = 0; k < j; k++){
    aux.digits[n+m-1-k] = 0;
  }
    aux2 = aux2 + aux;
    carry = 0;
  }

  result = aux2;
  if((!a.signo && b.signo) ||(a.signo && !b.signo) ){
    result.signo = false;
  }
  return result;
}
bool operator==(const bignum&a, const bignum&b)
{
  if(a.signo==b.signo && a.len==b.len)
  {
    for(size_t i = 0; i < a.len; i++)
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
  if(a.len<b.len)
    return true;
  else if(b.len<a.len)
    return false;
  else{
    for(int i=0; i<a.len; i++)
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
  if(a.len>b.len)
    return true;
  else if(b.len>a.len)
    return false;
  else{
    for(int i=0; i<a.len; i++)
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
  for(int i = 0; i< num.len;i++)
  {
    //saco los ceros de la izquierda
    if(num.digits[i]==0 && aux==false)
    {
      if(i==num.len-1){
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
    cerr << "El valor ingresado no es correcto. Intente nuevamente." << endl;
    is >> s;
  }
  num = s;
  return is;
}
