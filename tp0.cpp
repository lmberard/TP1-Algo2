#include <iostream>
#include <string>
#include <cstring>

#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[]) {

  bignum resultado;

  //testeo
  string stra="670";
  bignum a=stra;
  cout << a <<endl;
  string str = "615";
  bignum b(str);
  cout << b << endl;
  bignum c = a+b;
  cout << "Resultado de la suma:" << endl;
  cout << c << endl;


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
