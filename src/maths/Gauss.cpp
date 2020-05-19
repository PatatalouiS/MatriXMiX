#include <iostream>
#include <vector>
#include <complex>
#include "VectorX.h"
#include "Gauss.h"


using namespace std;

Gauss::Gauss() {}

Gauss::Gauss(const int & row,
    const int & col) {
    this -> row = row;
    this -> col = col;
}

int Gauss::getRow() {
    return row;
}

int Gauss::getCol() {
    return col;
}

complex<double> Gauss::getVal(const Matrix & m) const {
    return m[static_cast<unsigned int>(row)][static_cast<unsigned int> (col)];
}

void Gauss::rowScale(tab2D_iter row,
    const complex < double > & ratio) const {
    //cout << "Le ratio : " << ratio << endl;
    for (auto & i: * row) {
        i *= ratio;
    }
}

void Gauss::rowReplace(tab2D_iter base, tab2D_iter op,
    const complex < double > & ratio) const {

    for (std::vector<complex<double>>::iterator i = base->begin(); i < base->end(); i++) {
        *i += *(op->begin() + (i - base->begin())) * ratio;
    }
}

void Gauss::rowExchange(tab2D_iter a, tab2D_iter b) const {
    for (std::vector<complex<double>>::iterator i = a->begin(); i < a->end(); i++) {
        complex<double> temp = * (b->begin() + (i - a->begin()));
        *(b ->begin() + (i - a ->begin())) = *i;
        *i = temp;
    }
}

int Gauss::isNonZeroColumn(const Matrix & matrix,
    const int & column_id,
        const int & rows,
            const int & next_row_id) const {
    for (int row = next_row_id; row < rows; row++) {
        if (matrix[static_cast<unsigned int> (row)]
            [static_cast <unsigned int> (column_id)].real() != 0.0 ||
            matrix[static_cast <unsigned int> (row)]
            [static_cast <unsigned int> (column_id)].imag() != 0.0) {
            return row;
        }
    }
    return -1;
}