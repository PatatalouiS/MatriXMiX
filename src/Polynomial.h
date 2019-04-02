//
// Created by tarik on 09/03/19.
//

#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H

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
    void check(Polynomial & p);
    Polynomial& operator =(const Polynomial & p);
    friend std::ostream& operator << (std::ostream& flux, const Polynomial & p);
    const Polynomial operator +(const Polynomial & p);
    const Polynomial operator -(const Polynomial & p);
    const Polynomial operator *(const Polynomial & p);
    const Polynomial operator *(const float & scale);
    const Polynomial division (const Polynomial & divisor, Polynomial & reste);
    void equation2degre (unsigned int & nbsolution, double & x1, double & x2);


};




#endif
