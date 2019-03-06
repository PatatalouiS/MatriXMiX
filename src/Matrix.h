
#ifndef _MATRIX_H
#define _MATRIX_H


#include <vector>
#include "VectorX.h"


class Matrix
{
    private:
    
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;
    
    public:
    
    Matrix ();
    Matrix ( const unsigned int rows, const unsigned int cols );
    Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values );
    Matrix ( const Matrix & m );
    ~Matrix ();
    
    
    double& getVal ( const unsigned int indice );
    double getVal ( const unsigned int indice ) const;
    std::vector<double>& operator [] ( const unsigned int indice );
    const std::vector<double>& operator [] ( const unsigned int indice ) const;
    friend std::ostream& operator << ( std::ostream& flux, const Matrix & m );
};



#endif
