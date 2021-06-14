/*
Universidad de Buenos Aires
Facultad de Ingenieria

Algoritmos y Programación II - Trabajo Practico N°0 

Integrantes:
Berard, Lucıa Magdalena		101213  lberard@fi.uba.ar
Guglieri, Mariano Federico    	99573	mguglieri@fi.uba.ar
Rubin, Ivan Eric		100577  irubin@fi.uba.ar
Sandoval, Diego Ariel		101639  dsandoval@fi.uba.ar
*/


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

  unsigned short *aux;
  aux=new unsigned short[str.length()-hay_signo];
  delete[]digits;
  len=str.length()-hay_signo;
  digits=aux;
  
  for(int i=0; i<len; i++)
      digits[len-1-i]=str[len+hay_signo-i-1]-ASCII_FIX;
    
  return *this;

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

    bignum c= -a;
    bignum d= -b;
    result = d-c;
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



// NO ES LA DIVISION
//s es la cantidad de digitos menos significativos que le saco a
// "right", esto me da el a1 de
//  a = a1*10^s + a2 , 
//  s=n/2, n el largo del bignum
bignum operator/(const bignum& right, int s){
  bignum res(right.len-s);
  res.signo=right.signo;
  if(s>=1)
  {
    for(int i=0; i<res.len; i++)
        {res.digits[i]=right.digits[i];
        cout<<"res.digits["<<i<<"] / "<<res.digits[i]<<endl;
        }
    return res;
  }
  return res;
}
//No es el RESTO, es el complemento del anterior
//s es el largo del bignum a devolver con los s digitos menos
// significativos de right me dá el a2 de
//a = a1*10^s + a2 , s=n/2, n el largo del bignum
bignum operator%(const bignum& right, int s){
  bignum res(s);
  res.signo=right.signo;
  if(s>=1)
  {
    for(int i=right.len-s; i<right.len; i++)
      {res.digits[i-(right.len-s)]=right.digits[i];
      cout<<"res.digits["<<i-(right.len-s)<<"] % "<<res.digits[i-(right.len-s)]<<endl;
      }
    //cout<<"salgo del for y res vale "<<res<<endl;  
    return res;   
  }
  return res;
}

//me coloca los ceros al principio necesarios para
//poder hacer el algoritmo de karatsuba
//así ambos bignum tienen el mismo largo
// diff es la diferencia de largos entre los bignums
//right es el bignum a agregarle ceros
bignum llenar(const bignum& right, int diff){
  bignum aux(right.len + diff);
  aux.signo= right.signo;
  for(int i=diff; i<aux.len; i++)
      {aux.digits[i]= right.digits[i-diff];
      cout<<"aux.digits["<< i-diff <<"] llenar "<<aux.digits[i-diff]<<endl;
    }
  return aux;
}

//saca los ceros a izquierda y corrige el len
bignum truelen(const bignum& right){
  int i;
  bignum res(1);
  for( i=0;  i<right.len && right.digits[i]==0   ; i++);

  if(i==right.len){
    cout <<"res.len truelen1 "<< res.len << endl;
    cout <<"res.digits[0] truelen1 "<< res.digits[0] << endl;
  //  cout <<"res.digits[1] "<< res.digits[1] << endl;
    res.signo=right.signo;
    return res;
  }
  else if(i==0){
    //cortó en la primera y el número es correcto
    res = right;
    cout <<"res.len truelen2 "<< res.len << endl;
    for(int j=0; j<res.len; j++)
      cout<<"res.digits["<< j <<"] truelen2 "<<res.digits[j]<<endl;
    return res;
  }
  else{
    //el numero tiene ceros adelante
    //achicar digits y ajustar len de res
    unsigned short *aux;
    aux=new unsigned short[right.len-i];
    delete[]res.digits;
    res.len=right.len-i;
    res.digits=aux;
    res.signo = right.signo;
    for(int j=0; j<res.len; j++)
    {
      res.digits[j]=right.digits[i+j];
      cout<<"right.digits["<< i+j <<"] truelen3 "<<right.digits[i+j]<<endl;
      cout<<"res.digits["<< j <<"] truelen3 "<<res.digits[j]<<endl;
    }
    cout<< "res.len truelen3 "<<res.len<<endl;
    return res;
  }
}


//se usa sólo para hacer la cuenta final sustituye el 10^s
// del algoritmo, si se aplica dos veces equivale a 10^(2s)
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

//mult por karatsuba
bignum mult2(const bignum& u, const bignum& v){
//agregar mas prints
cout << "empieza mult("<< u <<","<<v<<")"<<endl;
  //modifico los bignum, me saca los ceros a izquierda y corrige el len

  bignum u1 = truelen(u);
//  cout << "u1 es "<< u1 <<endl;
  bignum v1 = truelen(v);
//  cout << "v1 es "<< v1 <<endl;
//si alguno es cero devuelvo cero con signo correspondiente
/*
  if(u1.digits[0]==0 || v1.digits[0]==0){
    bignum aux(1);
    if(!u1.signo && !v1.signo){
      aux.signo = true; //ambos negativos
    }
    else 
      {aux.signo = u1.signo && v1.signo;} //ambos positivos o tienen distinto signo
    return aux;
  }
 */ 
  int a = u1.len;
  int b = v1.len;

  int n = max(a,b);
  cout << "n "<< n << endl;

  bignum v2(n);
  bignum u2(n);
  //if a > b, llenar de ceros a izq a v
  
  if (a==1 && b==1)
  {
    u2 = u1;
    v2 = v1;
  }
  else if(a>b)
  {
    cout<< "empiaza llenar "<<endl;
    v2 = llenar(v1,a-b);
    u2 = u1;

  }
  //if b>a, llenar de ceros a izq a u
  else if(b>a)
  { cout<< "empiaza llenar "<<endl;
    u2 = llenar(u1,b-a); //llenar con ceros sin errores
    v2 = v1;
  }
  else{
    u2 = u1;
    v2 = v1;
  }
  
  //pruebas de los contenidos de u2 y v2
  cout << "u termina siendo k "<< u2 <<endl;
  cout << "v termina siendo k "<< v2 <<endl;
  for(int i=0; i< u2.len; i++){
  cout<<"u2.digits["<<i<<"] k "<<u2.digits[i]<<endl;
  cout<<"v2.digits["<<i<<"] k "<<v2.digits[i]<<endl;
  } 
  
  int L = 1;
  //si n es de largo mayor a 1, hace la recursividad
  //sino, es de largo 1 (caso base) y devuelve la multiplicación
  if(n>L){
    int s = n/2;
    cout << "s k "<< s << endl;
    bignum w = u2/s;
    cout << "u/s k "<< w << endl;
    bignum x = u2%s;
    cout << "u%s k "<< x << endl;
    bignum y = v2/s;
    cout << "v/s k "<< y << endl;
    bignum z = v2%s;
    cout << "v%s k "<< z << endl;
//probar truelen en rpq o en los shifts
    cout << "r"<< endl;
    bignum r = mult2(w+x,y+z);  //
    cout << "p"<<endl;
    bignum p = mult2(w,y);      //
//    bignum aux;
//    aux = r-p;
    cout <<"q"<<endl;
    bignum q = mult2(x,z);     
//    bignum aux2;
//    aux2 = aux - q;
     //
    //bignum res = 
    //cout << "res.len k" << res.len << endl;
/*    for(int j=0; j<res.len; j++)
    {
      cout<<"res.digits["<< j <<"] "<<res.digits[j]<<endl;
    }    */
    cout << "termina mult("<< u2 <<","<<v2<<")"<<endl;
    cout <<"s="<<s<<" p="<<p<< " q="<<q <<" r="<<r<<endl;
    cout <<"p * 10^(2s)           + (r-p-q) * 10^s    + q" << endl;
    cout <<  "shift1(shift1(p,s),s) " << shift1(shift1(p,s),s)<<endl;
    cout << "q+p = " << q+p <<endl;
    cout << "r-(p+q) = " << r-(p+q) <<endl;
    cout << "shift1(r-p-q,s) " << shift1(r-p-q,s) << endl;
    cout << "resultado con shifts " << shift1(shift1(p,s),s) + shift1(r-p-q,s) + q<<endl;
    return truelen(shift1(shift1(p,s),s)) + truelen(shift1(r-p-q,s)) + truelen(q);
    //     p * 10^(2s)           + (r-p-q) * 10^s    + q
  }
  else{ 
    cout << "caso base u2*v2 " << u2<<" * "<<v2<<" es "<< u2*v2<<endl; 
    return u2*v2;} //acá estoy abusando del * que teníamos
                    // capaz deberia crear un bignum resultado
                    // y darle el valor, pero eso jode en strategy
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
{ //signos distintos
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


bool operator>(const bignum& a, const bignum& b)
{
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
