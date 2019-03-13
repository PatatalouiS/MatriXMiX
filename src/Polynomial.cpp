

#include <iostream>
#include <vector>
#include "VectorX.h"
#include "Polynomial.h"

using namespace std;

Polynomial :: Polynomial() : tab (1,0)
{
    degree=0;
}


Polynomial :: Polynomial(const unsigned int & d) : tab(d,1)
{
    degree=d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d+1 )
    {
        cout << "Erreur : Pas le nombre de coefficients" << endl;
        exit ( EXIT_FAILURE );
    }

    this->degree = d;

    for ( unsigned int i=0; i<d+1; i++ )
    {
        tab.push_back(values[i]);
    }

}

