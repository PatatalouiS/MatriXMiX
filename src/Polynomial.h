//
// Created by tarik on 09/03/19.
//

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

public:
    Polynomial();
    Polynomial(const unsigned int & d);
    Polynomial(const unsigned int & d, const VectorX & values);
    Polynomial(const Polynomial & p);
    ~Polynomial ();
    void check ();
    Polynomial& operator =(const Polynomial & p);
    friend std::ostream& operator << (std::ostream& flux, const Polynomial & p);
    const Polynomial operator +(const Polynomial & p);
    const Polynomial operator -(const Polynomial & p);
    const Polynomial operator *(const Polynomial & p);
    const Polynomial operator *(const double & scale);
    void equation2degre (unsigned int & nbsolution, double & x1, double & x2);
    const Polynomial division (const Polynomial & divisor, Polynomial & reste);


};




#endif
