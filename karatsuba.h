<<<<<<< HEAD
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
=======
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
>>>>>>> 6a25f85f88a3be9fe41b8dbe151c36882a74fdeb
