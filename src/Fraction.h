
#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <vector>
using namespace std;

class Fraction
{

public:
    long int numerateur, denominateur;

public:
    Fraction();
    Fraction(const long int & n);
    Fraction(const long int & n, const long int & m);

    friend std::ostream& operator<<(std::ostream& flux, Fraction const& fraction);
    bool estEgal(const Fraction & f) const;
    bool estPlusPetitQue(const Fraction & f) const;
    Fraction& operator+=(const Fraction & f);
    long int pgcd(long int a, long int b);
    void simplifie();
    Fraction double2Fraction(const double & f);
    Fraction inverse();
    bool isFraction(const double & d);
    Fraction attal(const double & d);
    void recursivite (std::vector<long int> & table,double rest);
    Fraction hanattal (double d);
};



bool operator==(const Fraction & f1, const Fraction & f2);
bool operator<(const Fraction & f1, const Fraction & f2);
Fraction operator+(const Fraction & f1, const Fraction & f2);
Fraction operator* (const Fraction & f1, const Fraction & f2);
Fraction operator+ (const long int & d, const Fraction & f1);
Fraction operator/ (const Fraction & f1, const Fraction & f2);




#endif
