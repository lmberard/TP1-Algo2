
  unsigned short cant = a.precision; //aca en realidad es la precision maxima =>max(a,b)
  unsigned short resto = 0, aux = 0;
  bignum result(cant); 
  unsigned int i = 0;
  
  for(i = 0; i < cant; i++){

    aux = a.digits[cant-1-i];
    aux -= resto;

    //verifico si tengo que "pedir" al de al lado 
    if(aux < b.digits[cant-1-i]){
      aux += 10;
      resto = 1;
    }
    else resto = 0;

    //resto
    aux -= b.digits[cant-1-i]; 
    
    //cuando llega al principio:=> aca esta el problema
    // ej: si hago 3-4 = -1
    //verificar si el valor de aux es negativo, creo que ahi esta el problema
    //tratar de cambiarlo a int 
    if(aux <0){ 
      result.signo=false; //porque es 
      aux = aux - (aux*2); //para que lo haga positivo
    }

    result.digits[cant-i-1] = aux;
    cout << result.digits[cant-i-1] << endl;
  }
    //cout << result.digits[0] << endl;
  return result;
}
