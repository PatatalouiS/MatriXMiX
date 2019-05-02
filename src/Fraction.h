#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <vector>

class Fraction
{

private:
    long int numerator, denominator;


private:
    void recursived2f (std::vector<long int> &tab, const double & rest) const;


public:
    Fraction();
    Fraction(const long int & n);
    Fraction(const long int & n, const long int & d);

    long int getNumerator() const;
    long int getDenominator() const;
    friend std::ostream& operator << (std::ostream& flux, Fraction const& fraction);
    Fraction& operator = (const Fraction & f);
    Fraction& operator = (const double &d);
    bool operator == (const Fraction & f) const;
    bool operator < (const Fraction & f) const;
    const Fraction inverse () const;
    long int pgcd (long int a, long int b) const;
    const Fraction simplify () const;
    const Fraction operator + (const Fraction & f) const;
    const Fraction operator + (const long int & d) const;
    const Fraction operator * (const Fraction & f) const;
    const Fraction operator / (const Fraction & f) const;
    bool isFraction (const double & d) const;
    const Fraction double2fraction (const double & d) const;

};










#endif
