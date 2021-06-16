#ifndef MULTIPLY_INTERFACE
#define MULTIPLY_INTERFACE

#include "bignum.h"

class bignum;

class multiply_interface{
  friend class bignum;

  public:
    virtual ~multiply_interface(){}
    virtual bignum multiply(const bignum &, const bignum&) const=0;
};


#endif
