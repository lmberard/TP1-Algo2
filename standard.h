#ifndef STANDARD
#define STANDARD

#include<iostream>
#include "bignum.h"
#include "multiply_interface.h"
using namespace std;

class standard: public multiply_interface{
  friend class bignum;
  public:
    virtual ~standard(){}
    bignum multiply(const bignum&, const bignum&) const override;
};

#endif
