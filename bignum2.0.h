#include<iostream>
#include<string>
using namespace std;

#ifndef BIGNUM_INCLUDED
#define BIGNUM_INCLUDED

#define ASCII_FIX 48

class bignum
{
  private:
    unsigned short *digits;
    unsigned short len;
    bool signo;

    friend bool is_zero(const bignum&);
    //friend bignum truelen(const bignum&);

  public:

    bignum();
    bignum(const unsigned short);
    ~bignum();

    const bignum& operator=(const bignum&);
    const bignum& operator=(const string&);

    friend bignum operator+(const bignum&, const bignum&);
    friend bignum operator-(const bignum&, const bignum&);
    friend bignum operator*(const bignum&, const bignum&);
    friend bignum operator/(const bignum&, const bignum&);

    friend bool operator==(const bignum&, const bignum&);
    friend bool operator<(const bignum&, const bignum&);
    friend bool operator>(const bignum&, const bignum&);

    friend std::ostream& operator<<(std::ostream&, const bignum&);
    friend std::istream& operator>>(std::istream&, bignum&);

    /*******************DIEGUITO*****************************************/
    //friend bignum operator-(const bignum&);
    friend bignum mult2(const bignum&,const bignum&);
    friend bignum llenar(const bignum&, int);
    friend bignum shift1(const bignum &,int);
    friend bignum operator/(const bignum&, int);
    friend bignum operator%(const bignum&, int);
    friend bignum truelen(const bignum& );

};


#endif
