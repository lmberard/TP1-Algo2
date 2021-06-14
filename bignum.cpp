#include "bignum.h"
#include <string>
#include <algorithm>
using namespace std;

/**************************CONSTRUCTORES Y DESTRUCTORES************************************************/
bignum::bignum()
  : signo(true),
    len(1)
{digits = new unsigned short[len]();}

bignum::bignum(const unsigned short a)
  : signo(true),
    len(a)
{digits = new unsigned short[len]();}

bignum::~bignum(){
  if(digits)
  {delete[] digits;}
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
void bignum::set_signo(bool s){
  signo=s;
}

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
  for(size_t i=0; i<len; i++){
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

const bignum& bignum::operator=(const string& right){
  string str;
  for(char c:right) if(!isspace(c)) str += c ;
  if(!(str.find_first_not_of("0123456789") == string::npos) && (str[0]!='-' && str[0]!='+')){
    cerr<<"Asignacion de numero invalida"<<endl;
    exit(1);
  }
  bool hay_signo=false;
  if(str[0]=='-'){signo=false;hay_signo=true;}
  if(str[0]=='+'){signo=true;hay_signo=true;}

  // PARTE NUEVAAAAAAAAA
  unsigned short num = 0;
  for(size_t i =0; i < str.length()-hay_signo;i++){
    num += str[i+hay_signo]-ASCII_FIX;
  }
  /************************************/
  unsigned short *aux;
  //PARTE NUEVAAAAAAAAAA
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
  /*******************************************************///Y A TODO SE LE AGREGA Z
  aux=new unsigned short[str.length()-hay_signo-z];
  delete[]digits;
  len=str.length()-hay_signo-z;
  digits=aux;

  for(int i=0; i< len; i++)
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

bignum operator/(const bignum& a, const bignum& b){
  unsigned short cont = 0;
  bignum result(a.len);
  bignum result2;
  bignum diez;
  diez = "10";
  if(is_zero(b)){
    exit(1);
  }
  if(a.len < b.len){
    result = result2;
    return result;
  }

  bignum aux(b.len);
  for(size_t i = 0; i < aux.len; i++){
    aux.digits[aux.len-1 -i] = a.digits[b.len-1 -i];
  }

  for(size_t j = 0;j < (a.len-b.len); j++){
    while((aux > b) || (aux == b)){
      aux = aux - b;
      cont++;
    }
    result.digits[j+b.len-1] = cont;
    cont = 0;
    aux = aux*diez;
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
      for(int i=0; i<a.len; i++)
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
      for(int i=0; i<a.len; i++)
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
  //Ambos negativos
  else{
    if(a.len>b.len)
      return false;
    else if(b.len>a.len)
      return true;
    //son de mismo largo
    else{
      for(int i=0; i<a.len; i++)
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
  if(num.signo==false)
  { os << '-'; }
  bool aux= false;
  for(int i = 0; i< num.len;i++)
  {
    os << num.digits[i];
    aux=true;
  }
  return os;
}

istream& operator>>(istream& is, bignum& num){
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

/*******************************************KARATSUBA***************************************************/

bignum operator/(const bignum& right, int s){
  bignum res(right.len-s);
  res.signo=right.signo;
  if(s>=1)
  {
    for(int i=0; i<res.len; i++)
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
    for(int i=right.len-s; i<right.len; i++)
      {res.digits[i-(right.len-s)]=right.digits[i];}
    return res;
  }
  return res;
}

bignum llenar(const bignum& right, int diff){
  bignum aux(right.len + diff);
  aux.signo= right.signo;
  for(int i=diff; i<aux.len; i++)
      {aux.digits[i]= right.digits[i-diff];}
  return aux;
}

bignum shift1(const bignum &right, int s){
  bignum aux(right.len+s);
  aux.signo=right.signo;
  int i;
  for( i=0; i<right.len; i++)
    {aux.digits[i]=right.digits[i];}
  for( i=right.len; i<aux.len;i++)
    {aux.digits[i]=0;}
  return aux;
}

bignum mult2(const bignum& u, const bignum& v){
  //modifico los bignum, me saca los ceros a izquierda y corrige el len
  bignum u1 = truelen(u);
  bignum v1 = truelen(v);

  int a = u1.len;
  int b = v1.len;

  int n = max(a,b);

  bignum v2(n);
  bignum u2(n);
  //if a > b, llenar de ceros a izq a v
  if(a>b)
  {
    v2 = llenar(v1,a-b);
    u2 = u1;
  }
  //if b>a, llenar de ceros a izq a u
  else if(b>a)
  {
    u2 = llenar(u1,b-a);
    v2 = v1;
  }
  else{
    u2 = u1;
    v2 = v1;
  }
  int L = 1;
  //si n es de largo mayor a 1, hace la recursividad
  //sino, es de largo 1 (caso base) y devuelve la multiplicación
  if(n>L){
    int s = n/2;
    //u2 = w*10^s + x
    bignum w = u2/s;  // w = u2 / 10^s
    bignum x = u2%s;  // x = u2 % 10^s
    //v2= y*10^s + z
    bignum y = v2/s;  // y = v2 / 10^s
    bignum z = v2%s;  // z = v2 % 10^s
    //consigo los parámetros de karatsuba
    bignum r = mult2(w+x,y+z);
    bignum p = mult2(w,y);
    bignum q = mult2(x,z);
    //     p * 10^(2s)                    + (r-p-q) * 10^s           + q
    return truelen(shift1(shift1(p,s),s)) + truelen(shift1(r-p-q,s)) + truelen(q);

  }
  else{             //caso base si n=1
    return u2*v2;} //acá estoy abusando del * que teníamos
                    // capaz deberia crear un bignum resultado
                    // y darle el valor, pero eso jode en strategy
}
