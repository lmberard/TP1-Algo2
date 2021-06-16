#include "bignum.h"
using namespace std;

multiply_interface* bignum::mult=new standard();
int bignum::instances = 0;

/**************************CONSTRUCTORES Y DESTRUCTORES************************************************/
bignum::bignum()
  : signo(true),
    len(1)
{
  digits = new unsigned short[len]();
  instances++;
}

bignum::bignum(const unsigned long a)
  : signo(true),
    len(a)
{
  digits = new unsigned short[len]();
  instances++;
}

bignum::bignum(const string& s){
  string str;
  instances++;
  for(char c:s) if(!isspace(c)) str += c ;
  if(!(str.find_first_not_of(NUMBERS) == string::npos) && (str[0]!='-' && str[0]!='+')){
    cerr<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  bool hay_signo=false;
  if(str[0]=='-'){signo=false;hay_signo=true;}
  if(str[0]=='+'){signo=true;hay_signo=true;}

  unsigned short num = 0;
  for(size_t i =0; i < str.length()-hay_signo;i++){
    num += str[i+hay_signo]-ASCII_FIX;
  }
  unsigned short *aux;

  if(!num){
    aux = new unsigned short[1];
    len = 1;
    digits = aux;
    digits[0] = 0;
    return;
  }
  size_t z = 0;
  while(str[z++ +hay_signo] == '0'){};z--;

  aux=new unsigned short[str.length()-hay_signo-z];
  len=str.length()-hay_signo-z;
  digits=aux;

  for(unsigned long i=0; i< len; i++)
      digits[len-1-i]=str[len+z+hay_signo-i-1]-ASCII_FIX;
}

bignum::~bignum(){
  if(digits)
  {delete[] digits;}
  this->instances--;
  if(!this->instances){
    delete mult;
    mult=NULL;
  }
}

void bignum::set_mult_strategy(multiply_interface* m){
  if(mult)
    delete mult;
  this->mult=m;
}

bignum::bignum(const bignum& right){
  if(&right !=this)
  {
    signo=right.signo;
    digits=new unsigned short[right.len];
    len=right.len;
    for(unsigned long i=0; i<len; i++)
      {digits[i]=right.digits[i];}
  }
}

/*************************FUNCIONES PRIVADAS****************************************************************/
bignum truelen(const bignum& right){

  bignum res;
  if(is_zero(right)){
    return res;
  }
  size_t z = 0;
  while(!right.digits[z++]){};z--;
  bignum res2(right.len -z);
  for(size_t i = 0; i < res2.len; i++){
    res2.digits[i] = right.digits[i+z];
  }
  res2.signo = right.signo;
  res = res2;
  return res;
}

bool is_zero(const bignum& a){
  for(size_t i = 0; i < a.len; i++){
    if(a.digits[i])
      return false;
  }
  return true;
}


/***************************FUNCIONES PUBLICAS**************************************************************/

bool bignum::get_signo(){
  return signo;
}

unsigned char bignum::get_len(){
  return len;
}

string bignum::to_string(){
  string str;
  if(!signo)
    str.push_back('-');
  char c;
  for(unsigned long i=0; i<len; i++){
    c=digits[i]+ASCII_FIX;
    str.push_back(c);
  }
  return str;
}

/***************************OPERACIONES DE ASIGNACION********************************************************/
const bignum& bignum::operator=(const bignum& right){
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
      for(unsigned long i=0; i<len; i++)
        {digits[i]=right.digits[i];}
      return *this;
    }
    else
    {
      for(unsigned long i=0; i<len; i++)digits[i]=right.digits[i];
      return *this;
    }
  }
  return *this;
}

const bignum& bignum::operator=(const string& right){
  string str;
  for(char c:right) if(!isspace(c)) str += c ;
  if(!(str.find_first_not_of(NUMBERS) == string::npos) && (str[0]!='-' && str[0]!='+')){
    cerr<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  bool hay_signo=false;
  if(str[0]=='-'){signo=false;hay_signo=true;}
  if(str[0]=='+'){signo=true;hay_signo=true;}

  unsigned short num = 0;
  for(size_t i =0; i < str.length()-hay_signo;i++){
    num += str[i+hay_signo]-ASCII_FIX;
  }
  unsigned short *aux;
  if(!num){
    aux = new unsigned short[1];
    delete[]digits;
    len = 1;
    digits = aux;
    digits[0] = 0;
    return *this;
  }
  size_t z = 0;
  while(str[z++ +hay_signo] == '0'){};z--;
  /*******************************************************///Y A TOoDO SE LE AGREGA Z
  aux=new unsigned short[str.length()-hay_signo-z];
  delete[]digits;
  len=str.length()-hay_signo-z;
  digits=aux;

  for(unsigned long i=0; i< len; i++)
      digits[len-1-i]=str[len+z+hay_signo-i-1]-ASCII_FIX;
  return *this;
}

/****************************************OPERACIONES ARITMETICAS**************************************/

bignum operator+(const bignum& a, const bignum& b){
  unsigned short carry = 0;
  bignum aux, baux;
  bignum result(max(a.len,b.len)+1);
  aux = a;
  baux = b;
  aux.signo = true;
  baux.signo = true;

  if(a.signo && !b.signo){
    result = a - baux;
    return result;
  }
  if(!a.signo && b.signo){
    result = b - aux;
    return result;
  }
  if(!a.signo && !b.signo){
    result.signo = false;
  }
  if(aux < baux){
    result = b + a;
    return result;
  }
  for(size_t i = 0; i < min(aux.len,baux.len); i++){
    result.digits[max(aux.len,baux.len)-i] = aux.digits[aux.len -1-i] + baux.digits[baux.len-1-i] + carry;
    if(result.digits[max(aux.len,baux.len)-i] >= 10){
      result.digits[max(aux.len,baux.len)-i] -=10;
      carry = 1;
    }
    else carry = 0;
  }
  for(size_t j = min(aux.len,baux.len); j < max(aux.len,baux.len); j++){
    result.digits[max(aux.len,baux.len)-j] = aux.digits[max(aux.len,baux.len)-1-j]+carry;
    if(result.digits[max(aux.len,baux.len)-j] >= 10){
      result.digits[max(aux.len,baux.len)-j] -= 10;
      carry = 1;
    }
    else carry = 0;
  }
  result.digits[0] = carry;
  result = truelen(result);
  return result;
}

bignum operator-(const bignum& a, const bignum& b){
  unsigned short carry = 0;
  bignum aux, baux;
  bignum result(max(a.len, b.len));
  aux = a;
  baux = b;
  aux.signo = true;
  baux.signo = true;

  if(a.signo && !b.signo){
    result = a + baux;
    return result;
  }
  if(!a.signo && b.signo){
    result = aux + b;
    result.signo = false;
    return result;
  }
  if(a < b){
    result.signo = false;
  }
  if(aux < baux){
    result = baux - aux;
    if( a < b)
      result.signo = false;
    return result;
  }
  for(size_t i = 0; i< min(aux.len, baux.len); i++){
    result.digits[max(aux.len,baux.len)-1-i] = aux.digits[aux.len -1-i] -baux.digits[baux.len-1-i] + carry;
    if(result.digits[max(aux.len, baux.len)-1-i] >= 10){
      result.digits[max(aux.len,baux.len)-1-i] -= 65526;
      carry = -1;
    }
    else carry = 0;
  }
  for(size_t j = min(aux.len,baux.len); j < max(aux.len,baux.len); j++){
    result.digits[max(aux.len,baux.len)-1-j] = aux.digits[max(aux.len,baux.len)-1-j]+carry;
    if(result.digits[max(aux.len,baux.len)-1-j] >= 10){
      result.digits[max(aux.len,baux.len)-1-j] -= 65526;
      carry = -1;
    }
    else carry = 0;
  }
  result = truelen(result);
  return result;
}

bignum operator*(const bignum& a, const bignum& b){
  return a.mult->multiply(a,b);
}

bignum operator/(const bignum& a, const bignum& b){
  unsigned short cont = 0;
  bignum result(a.len);
  bignum result2;
  bignum diez;
  diez = "10";
  if(is_zero(b)){
    cout<<"Operacion invalida"<<endl;
    return 0;
    //exit(1);
  }

  if(a.len < b.len){
    result = result2;
    return result;
  }

  bignum aux(b.len);
  for(unsigned long i = 0; i < aux.len; i++){
    aux.digits[aux.len-1 -i] = a.digits[b.len-1 -i];
  }

  for(unsigned long j = 0;j < (a.len-b.len); j++){
    while((aux > b) || (aux == b)){
      aux = aux - b;
      cont++;
    }
    result.digits[j+b.len-1] = cont;
    cont = 0;

    aux = aux * diez;

    aux.digits[aux.len-1] = a.digits[b.len+j];
  }
  while((aux > b) || (aux == b)){
    aux = aux - b;
    cont++;
  }
  result.digits[a.len-1] = cont;

  if((!a.signo && b.signo) ||(a.signo && !b.signo) ){
    result.signo = false;
  }
  result = truelen(result);
  return result;
  }

/***************************************OPERACIONES LOGICAS******************************************/
bool operator==(const bignum&a, const bignum&b){
  if(a.signo==b.signo && a.len==b.len){
    for(size_t i = 0; i < a.len; i++){
      if(a.digits[i]!=b.digits[i])
        return false;
    }
    return true;
  }
  return false;
}

bool operator<(const bignum& a, const bignum& b){
  //signos distintos
  if(!a.signo && b.signo){
    return true;
  }
  else if(a.signo && !b.signo){
    return false;
  }
  //ambos positivos
  else if(a.signo && b.signo){
    if(a.len<b.len)
      return true;
    else if(b.len<a.len)
      return false;
    //son de mismo largo
    else{
      for(unsigned long i=0; i<a.len; i++)
      {
        if(a.digits[i]<b.digits[i]){
          return true;
        }else if(b.digits[i]<a.digits[i])
          return false;
      }
      return false; //son iguales
    }
  }
  //ambos negativos
  else{
    if(a.len>b.len)
      return true;
    else if(b.len>a.len)
      return false;
    //son de mismo largo
    else{
      for(unsigned long i=0; i<a.len; i++)
      {
        if(a.digits[i]>b.digits[i]){
          return true;
        }else if(b.digits[i]>a.digits[i])
          {return false;}
      }
      return false;  //son iguales
    }
  }
}

bool operator>(const bignum& a, const bignum& b){
  if(!a.signo && b.signo){
    return false;
  }
  else if(a.signo && !b.signo){
    return true;
  }

  //ambos positivos
  else if(a.signo && b.signo){
    if(a.len>b.len)
      return true;
    else if(b.len>a.len)
      return false;
    else{
      for(unsigned long i=0; i<a.len; i++)
      {
        if(a.digits[i]>b.digits[i]){
          return true;
        }else if(b.digits[i]>a.digits[i])
          return false;
      }
    }
    return false;
  }
  //Ambos negativos
  else{
    if(a.len>b.len)
      return false;
    else if(b.len>a.len)
      return true;
    //son de mismo largo
    else{
      for(unsigned long i=0; i<a.len; i++)
      {
        if(a.digits[i]>b.digits[i]){
          return false;
        }else if(b.digits[i]>a.digits[i])
          {return true;}
      }
      return false;  //son iguales
    }
  }
}

/**************************************OPERADORES ENTRADA Y SALIDA***************************************/

ostream& operator<<(ostream& os, const bignum& num){
  if(num.signo==false && !(num.len==1 && num.digits[0]==0))
  { os << '-'; }
  for(unsigned long i = 0; i< num.len;i++)
  {
    os << num.digits[i];
  }
  return os;
}

istream& operator>>(istream& is, bignum& num){
  string s;
  is >> s;
  while(!(s.find_first_not_of(NUMBERS) == string::npos) && (s[0]!='-' && s[0]!='+'))
  {
    cerr << "El valor ingresado no es correcto. Intente nuevamente." << endl;
    is >> s;
  }
  num = s;
  return is;
}

/*******************************************KARATSUBA***************************************************/

bignum operator/(const bignum& right, int s){
  bignum res(right.len-s);
  res.signo=right.signo;
  if(s>=1)
  {
    for(unsigned long i=0; i<res.len; i++)
        {res.digits[i]=right.digits[i];}
    return res;
  }
  return res;
}

bignum operator%(const bignum& right, int s){
  bignum res(s);
  res.signo=right.signo;
  if(s>=1)
  {
    for(unsigned long i=right.len-s; i<right.len; i++)
      {res.digits[i-(right.len-s)]=right.digits[i];}
    return res;
  }
  return res;
}

bignum llenar(const bignum& right, int diff){
  bignum aux(right.len + diff);
  aux.signo= right.signo;
  for(unsigned long i=diff; i<aux.len; i++)
      {aux.digits[i]= right.digits[i-diff];}
  return aux;
}

bignum shift1(const bignum &right, int s){
  bignum aux(right.len+s);
  aux.signo=right.signo;
  unsigned long i;
  for( i=0; i<right.len; i++)
    {aux.digits[i]=right.digits[i];}
  for( i=right.len; i<aux.len;i++)
    {aux.digits[i]=0;}
  return aux;
}
