#include<iostream>
#include "bignum.h"
using namespace std;

int main(int argc, char const *argv[]) {
  bignum resultado;
//hola probandOooooo
  for (size_t i = 1; i < argc; i++)
  {
    if(argv[i]=="-p")
    {
      resultado.set_p(argv[i+1]);
      //seteo la precisión en argv[i+1]
      //break;
    }
    if(tiene_char(argv[i],'*'))
    {

      cout << a*b << endl;
    }

    if(tiene_char(argv[i],'+')
    {
      bignum a=argv[i-1];
      bignum b=argv[i+1];
      cout << a+b << endl;
    }
  }


  return 0;
}
