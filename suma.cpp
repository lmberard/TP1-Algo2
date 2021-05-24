bignum operator+(const bignum& a, const bignum& b)
{

  unsigned short cant = a.precision + 1;
  unsigned short carry = 0, aux = 0;
  bignum result(cant); 
  unsigned int i = 0;
  
  for(i = 0; i < cant-1; i++){

    aux = a.digits[cant-2-i];
    aux = aux + b.digits[cant-2-i] + carry;

    //verifico el carry 
    if(aux >= 10){
      aux -= 10;
      carry = 1;
    }
    else carry = 0;
    
    result.digits[cant-i-1] = aux;
    //cout << result.digits[cant-i-1] << endl;

  }
  result.digits[0] = carry;
  //cout << result.digits[0] << endl;
  return result;
}

/*en el main poner:
//testeo
  string stra="670";
  bignum a=stra;
  cout << a <<endl;
  string str = "615";
  bignum b(str);
  cout << b << endl;
  bignum c=a+b;
  cout << "Resultado de la suma:" << endl;
  cout << c << endl;

*/
