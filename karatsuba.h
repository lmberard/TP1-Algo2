#ifndef KARATSUBA
#define KARATSUBA

#include <iostream>
#include <string>
#include "bignum.h"
#include "multiply_interface.h"
#include "standard.h"
using namespace std;

class karatsuba: public multiply_interface{

  public:
    virtual ~karatsuba(){}
    bignum multiply(const bignum&, const bignum&) const override;

};


#endif
