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
    Gauss (const int &row, const int &col);
    double getVal (const Matrix &m) const;
    void rowScale(tab2D_iter row, const double &ratio) const;
    void rowReplace(tab2D_iter base, tab2D_iter op,
                    const double &ratio) const;
    void rowExchange(tab2D_iter a, tab2D_iter b) const;
    int isNonZeroColumn(const Matrix &matrix, const int &column_id,
                        const int &rows, const int &next_row_id) const;


};


#endif // GAUSS_H
