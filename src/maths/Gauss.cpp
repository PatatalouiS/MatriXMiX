/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

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
