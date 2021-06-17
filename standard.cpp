#include "standard.h"
using namespace std;

bignum standard::multiply(const bignum& a, const bignum& b)const{
  //cout<<"standard"<<endl;
  unsigned long n = a.len;
  unsigned long m = b.len;
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
