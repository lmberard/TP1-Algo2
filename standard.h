<<<<<<< HEAD
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
=======
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
>>>>>>> 6a25f85f88a3be9fe41b8dbe151c36882a74fdeb
