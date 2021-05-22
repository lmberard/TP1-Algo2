#include<iostream>
#include<string>

#ifndef BIGNUM_INCLUDED
#define BIGNUM_INCLUDED

class bignum
{
  private:
    unsigned short *digits;
    unsigned short precision;
    unsigned short len;
    bool signo; //True sea positivo y False sea Negativo
    //...
  public:
    //...
    friend bignum();
    friend bignum(unsigned short);
    friend bignum(string);
    friend ~bignum();
    friend void set_p();
    friend unsigned char get_p();
    friend void set_len();
    friend unsigned char get_len();
    friend bignum to_bignum(int);

    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend bignum operator=(const bignum&);
    friend bignum operator=(const int&);
    friend bignum operator=(const string&);
    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);
};


#endif
