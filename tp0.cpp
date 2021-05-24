#include <iostream>
#include <string>
#include <cstring>

#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[]) {

  bignum resultado;

  //testeo
  bignum a;
  bignum b("6546");
  string str = "45646s";
  bignum c = str;
  cout << c <<endl;
  // cout << "Ingrese el valor de a: "<< endl;
  // cin >> a;
  // cout << "Ingrese el valor de b: "<< endl;
  // cin >> b;
  // cout << "Resultado de -a es " << -a <<endl;



  for (size_t i = 1; i < argc; i++)
  {
    if(!strcmp(argv[i],"-p") || !strcmp(argv[i],"-precision"))
    {
      //resultado.set_p(argv[i+1]);
      //seteo la precisión en argv[i+1]
      //continue;
    }
    //if(tiene_char(argv[i],'*')||)
    //{

      //cout << a*b << endl;
    //}
    string str=argv[i];
    if(str.find('+')!=string::npos)
    {
      int a=stoi(argv[i-1]);
      int b=stoi(argv[i+1]);
      cout << a+b << endl;
    }
  }


  return 0;
}
