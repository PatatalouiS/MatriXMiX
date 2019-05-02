
#include <iostream>
#include <vector>
#include "VectorX.h"
#include "Gauss.h"
#include "Matrix.h"

using namespace std;



Gauss:: Gauss(){}


Gauss:: Gauss(const int &row, const int &col)
{
    this->row = row;
    this->col = col;
}


double Gauss:: getVal(const Matrix &m) const
{
    return m[static_cast<unsigned int>(row)][static_cast<unsigned int>(col)];
}


void Gauss:: rowScale(tab2D_iter row, const double &ratio) const
{
    for (auto &i : *row)
    {
        i *= ratio;
    }
}


void Gauss:: rowReplace(tab2D_iter base, tab2D_iter op,
						const double &ratio) const
{
    for (vector<double>::iterator i = base->begin(); i < base->end(); i++)
    {
        *i += *(op->begin() + (i - base->begin())) * ratio;
    }
}


void Gauss:: rowExchange(tab2D_iter a, tab2D_iter b) const
{
    for (vector<double>::iterator i = a->begin(); i < a->end(); i++)
    {
        double temp = *(b->begin() + (i - a->begin()));
        *(b->begin() + (i - a->begin())) = *i;
        *i = temp;
    }
}


int Gauss:: isNonZeroColumn(const Matrix &matrix, const int &column_id,
							const int &rows, const int &next_row_id) const
{
    for (int row = next_row_id; row < rows; row++)
    {
        if (matrix[static_cast<unsigned int>(row)]
        	[static_cast<unsigned int>(column_id)] != 0.0)
            return row;
    }
    return -1;
}
