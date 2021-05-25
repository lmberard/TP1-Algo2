bignum operator-(const bignum& a, const bignum& b)
{
  unsigned short cant = max(a.precision,b.precision); 
  unsigned short resto = 0;
  int aux = 0;
  bignum result(cant); 
  int i = 0, contador_a = 0, contador_b = 0;
  unsigned int dif_a = 0, dif_b = 0;
  
  if(a.precision <= b.precision){
    dif_a = cant - a.precision;
    dif_b = 0;
  }
  else {
    dif_b = cant - b.precision;
    dif_a = 0;
  }
  
  for(i = 0; i < cant; i++){
    cout << "Iteracion nro" << i <<endl;

    contador_a = cant - 1 - dif_a - i;
    contador_b = cant - 1 - dif_b - i;

    if(contador_a >= 0 && contador_b >=0){ // para evitar que ingrese a algo que no existe
      cout << "Digito" <<a.digits[contador_a] << endl;
      aux = (int)a.digits[contador_a];
      cout << "Aux casteado:" << aux << endl;
      aux -= resto;

      //verifico si tengo que "pedir" al de al lado 
      if(aux < b.digits[contador_b]){
        aux += 10;
        resto = 1;
      }
      else resto = 0;
      //cout << "aux" << aux <<endl;
      //cout << "resto" << resto <<endl;

      //resto
      aux -= (int)b.digits[contador_b]; 
      //cout << "Rtado final" << aux <<endl;
      
      if(aux <0){ 
        result.signo=false; 
        aux = aux - (aux*2); 
      }

      result.digits[cant-i-1] = aux;
    }

    //si la precision de A es mas chica
    if(contador_a < 0 && contador_b >= 0){

      result.digits[cant-i-1] = b.digits[contador_b] - resto;
      resto=0;
      result.signo = false;
    }
    //si la precision de B es mas chica
    if(contador_b < 0 && contador_a >= 0){
      result.digits[cant-i-1] = a.digits[contador_a]- resto;
      resto=0;
      result.signo = true;
    }



    //cout << result.digits[cant-i-1] << endl;
  }
    //cout << result.digits[0] << endl;
  return result;
}

/*
bool operator<(const bignum& a, const bignum& b)
{
  for(int i=0; i<min(a.precision,b.precision); i++>)
  {
    if(a.digits[i]>b.digits[i]){
      return false;
    }
  }
  return true;
}

bool operator>(const bignum& a, const bignum& b)
{
  for(int i=0; i<min(a.precision,b.precision); i++>)
  {
    if(a.digits[i]<b.digits[i]){
      return false;
    }
  }
  return true;
}
*/