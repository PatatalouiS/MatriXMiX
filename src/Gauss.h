#ifndef GAUSS_H
#define GAUSS_H


#include <iostream>
#include "Matrix.h"

typedef std::vector<std::vector<double>>::iterator tab2D_iter ;

class Gauss
{

public:

    int row;
    int col;



public:

    Gauss ();
    Gauss (const int & row, const int & col);
    double getVal (const Matrix & m);
    void rowScale(tab2D_iter row, double ratio);
    void rowReplace(tab2D_iter base, tab2D_iter op, double ratio);
    void rowExchange(tab2D_iter a, tab2D_iter b);
    int isNonZeroColumn(const Matrix & matrix, int column_id, int rows, int next_row_id);


};


#endif // GAUSS_H
