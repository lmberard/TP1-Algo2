
bignum operator*(const bignum& a, const bignum& b)
{  
  unsigned short carry = 0;
  unsigned short aux = 0;
  unsigned short n = a.precision;
  unsigned short m = b.precision;
  unsigned short n_rtado = n+m;
  bignum result_aux1(n+1);
  bignum result(n_rtado);

  //signo
  if(a.signo != b.signo){
    result.signo = false;
    return result;
  }else result.signo=true;

  //recorro b desde atras para adelante
  for(size_t i=0; i < b.precision; i++>){
    
    //verifico casos limites de multiplicar por 1 o cero
    if(b.digits[m-i-1] == 0){
      result_aux1.digits = 0;
      break;
    }
    if(b.digits[m-i-1] == 1){
      result_aux1 = a;
      break;
    }
    
    //multiplico uno de b por todos de a
    for(size_t j=0; i < a.precision; i++){

      aux = a.digits[n-j-1] * b.digits[m-i-1] + carry;

      //carry
      if(aux >=10){
        carry = aux / 10;
        aux = aux % 10;
      }     
      
      //guardo 
      result_aux1.digits[n-j-1] = aux;
    }
    
    result + result_aux1;
  }

  return result;
}