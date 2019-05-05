

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include "VectorX.h"

class Polynomial
{

public:
    unsigned int degree;
    std::vector<double> tab;

    static const Polynomial polynomial_null;
    static const Polynomial polynomial_noEigen ;

public:
    Polynomial();
    Polynomial(const unsigned int & d);
    Polynomial(const unsigned int & d, const VectorX & values);
    Polynomial(const Polynomial & p);
    Polynomial check () const;
    friend std::ostream& operator << (std::ostream& flux, const Polynomial & p);
    Polynomial& operator = (const Polynomial & p);
    bool operator == (const Polynomial & p) const;
    const Polynomial operator + (const Polynomial & p) const;
    const Polynomial operator - (const Polynomial & p) const;
    const Polynomial operator * (const Polynomial & p) const;
    const Polynomial operator * (const double & scale) const;


    const Polynomial division(const Polynomial & divisor, Polynomial & rest);
    void equation2degre (unsigned int & nbsolution, double & x1, double & x2)const;

    void testRegression()const;



};




#endif
