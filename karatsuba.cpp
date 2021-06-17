#include "karatsuba.h"
using namespace std;


bignum karatsuba::multiply(const bignum& u, const bignum& v)const{
  //cout<<"karatsuba"<<endl;
  //modifico los bignum, me saca los ceros a izquierda y corrige el len
  bignum u1 = truelen(u);
  bignum v1 = truelen(v);

  int a = u1.get_len();
  int b = v1.get_len();

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
    bignum r = karatsuba::multiply(w+x,y+z);
    bignum p = karatsuba::multiply(w,y);
    bignum q = karatsuba::multiply(x,z);
    //     p * 10^(2s)                    + (r-p-q) * 10^s           + q
    return truelen(shift1(shift1(p,s),s)) + truelen(shift1(r-p-q,s)) + truelen(q);

  }else{//caso base si n=1
    u2= to_string(stoi(u2.to_string())*stoi(v2.to_string()));
    return u2;
  }
}
