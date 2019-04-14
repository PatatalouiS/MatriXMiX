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
    void row_scale(tab2D_iter row, double ratio);
    //void row_scale(Matrix & m, const double & scale);
    void row_replace(tab2D_iter base, tab2D_iter op, double ratio);
    void row_exchange(tab2D_iter a, tab2D_iter b);
    int is_nonzero_column(const Matrix & matrix, int column_id, int rows, int next_row_id);


};


#endif // GAUSS_H
