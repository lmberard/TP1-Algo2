#include<iostream>

#ifndef BIGNUM_INCLUDED
#define BIGNUM_INCLUDED

class bignum
{
  private:
    unsigned short *digits;
    int precision;
    //...
  public:
    //...
    friend bignum();
    friend bignum(int);
    friend ~bignum();
    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);
};


#endif
