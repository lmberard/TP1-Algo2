#include <iostream>
#include <string>
#include <cstring>

#include "bignum.h"

using namespace std;

int main(int argc, char const *argv[]) {

  bignum resultado;

  //testeo
  bignum a("-1");
  bignum b("-10");
  bignum c = a-b;

  cout << c << endl;

  return 0;
}
