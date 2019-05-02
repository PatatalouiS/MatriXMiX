
#include <iostream>
#include <math.h>
#include "Fraction.h"
using namespace std;


const double EPSILON = 0.0001;


Fraction::Fraction()
{
    numerator = 0 ;
    denominator = 1;
}


Fraction::Fraction(const long int & n)
{
    numerator = n;
    denominator = 1;
}


Fraction::Fraction(const long int & n, const long int & d)
{
    numerator = n;
    denominator = d;
}


long int Fraction:: getNumerator() const
{
    return numerator;
}


long int Fraction:: getDenominator() const
{
    return denominator;
}


ostream& operator << (ostream& flux, const Fraction & f)
{
    flux << f.numerator << "/" << f.denominator;
    return flux;
}


Fraction& Fraction:: operator = (const Fraction &f)
{
    numerator = f.numerator;
    denominator = f.denominator;

    return *this;
}


Fraction& Fraction:: operator = (const double &d)
{
    numerator = double2fraction(d).numerator;
    denominator = double2fraction(d).denominator;
    return *this;
}


bool Fraction:: operator == (const Fraction &f) const
{
    long int num1, num2;
    num1 = numerator * f.denominator;
    num2 = f.numerator * denominator;

    return (num1 == num2);

}


bool Fraction:: operator < (const Fraction &f) const
{
    double d1 = numerator / denominator;
    double d2 = f.numerator/f.denominator;

    return (d1 < d2);
}


const Fraction Fraction:: inverse() const
{
    Fraction f (denominator,numerator);
    return f;
}


long int Fraction::pgcd(long int a, long int b) const
{
    while (b!=0)
    {
        long int t = b;
        b = a % b;
        a = t;
    }

    return a;
}


const Fraction Fraction::simplify() const
{
    long int div, num, den;
    div = pgcd(numerator,denominator);
    num = numerator / div;
    den = denominator / div;

    if(den < 0)
    {
        den *= -1;
        num *= -1;
    }

    Fraction f (num,den);

    return f;

}


const Fraction Fraction:: operator + (const Fraction & f) const
{
    long int num, den;
    num = numerator * f.denominator + f.numerator * denominator;
    den = denominator * f.denominator;
    Fraction res (num,den);
    res = res.simplify();
    return res;
}


const Fraction Fraction:: operator + (const long int &d) const
{
    long int temp = d * denominator;
    temp = temp + numerator;
    Fraction res (temp, denominator);
    return res;
}


const Fraction Fraction:: operator * (const Fraction & f) const
{
    long int num, den;
    num = numerator * f.numerator;
    den = denominator * f.denominator;
    Fraction res(num,den);
    res = res.simplify();
    return res;
}


const Fraction Fraction:: operator / (const Fraction & f) const
{
    long int num, den;
    num = numerator * f.denominator;
    den = denominator * f.numerator;
    Fraction res(num,den);
    res = res.simplify();
    return res;
}


bool Fraction:: isFraction(const double & d) const
{
    long int integer = static_cast<long int>(d);
    double r = d - integer;
    if (r == 0.0)
        return false;

    return true;
}


void Fraction:: recursived2f (vector<long int> &tab, const double &rest) const
{
    if ( tab.size() < 10 && rest > EPSILON)
    {
        double div, rest2;
        long int integer;
        div = 1 / rest;
        integer = static_cast<long int>(floor(div));
        rest2 = div - integer;
        tab.push_back(integer);
        recursived2f(tab,rest2);
    }

}


const Fraction Fraction:: double2fraction(const double &d) const
{
    double abs_d = abs(d);
    vector <long int> tab;

    double rest;
    long int integer;
    unsigned long int size;

    integer = static_cast<long int>(floor(abs_d));
    rest = abs_d - integer;

    tab.push_back(integer);
    recursived2f(tab,rest);

    size = tab.size();

    if (size == 1)
    {
        Fraction f (tab[0],1);
        if ( d * f.numerator > 0 && d * f.denominator > 0 )
        {
            return f;
        }
        else
        {
            f.numerator *= -1;
            return f;
        }
    }
    if (size == 2)
    {
        Fraction f (1,tab[1]);
        f = f + tab[0];
        if ( d * f.numerator > 0 && d * f.denominator > 0 )
        {
            return f;
        }
        else
        {
            f.numerator *= -1;
            return f;
        }
    }

    Fraction f (1,tab[size-2]);

    for (unsigned long int i = size - 2 ; i > 0 ; i--)
    {
        f = f + tab[i];
        f = f.inverse();
        f = f.simplify();
    }

    f = f + tab[0];
    f = f.simplify();

    if ( d * f.numerator > 0 && d * f.denominator > 0 )
    {
        return f;
    }
    else
    {
        f.numerator *= -1;
        return f;
    }

}
