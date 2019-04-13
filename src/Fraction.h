//
// Created by tarik on 09/03/19.
//

#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
using namespace std;

class Fraction
{

private:

    long int numerateur, denominateur;

public:

    Fraction();
    Fraction(const long int & n);
    Fraction(const long int & n, const long int & m);
    void afficher(std::ostream& out) const;
    bool estEgal(const Fraction & f) const;
    bool estPlusPetitQue(const Fraction & f) const;
    Fraction& operator+=(const Fraction & f);
    long int pgcd(long int a, long int b);
    void simplifie();
    Fraction double2Fraction(const double & f);

};


std::ostream& operator<<(std::ostream& flux, Fraction const& fraction);

bool operator==(const Fraction & f1, const Fraction & f2);

bool operator<(const Fraction & f1, const Fraction & f2);

Fraction operator+(const Fraction & f1, const Fraction & f2);




#endif
