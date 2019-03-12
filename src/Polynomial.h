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
private:
    unsigned int degree;
    std::vector<double> tab;

public:
    Polynomial();
    Polynomial(const unsigned int & d);
    Polynomial(const unsigned int & d, const VectorX & values);
    Polynomial(const Polynomial & p);
   // ~Polynomial ();



};




#endif
