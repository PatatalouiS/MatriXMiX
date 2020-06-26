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

#ifndef GAUSS_H
#define GAUSS_H


#include <iostream>
#include "Matrix.h"

typedef std::vector<std::vector<std::complex<double>>>::iterator tab2D_iter ;


/**
 * @brief Used to perform operations related to gauss reduction
 */
class Gauss
{

private:

    int row; /*< pivot's row */
    int col; /*< pivot's column */

public:

    /**
     * @brief Default constructor without parameter
     */
    Gauss ();

    /**
     * @brief Constructor
     * @param[in] row (\e int)
     * @param[in] col (\e int)
     */
    Gauss (const int & row, const int & col);

    /**
     * @brief Accessor
     * @return \e int : pivot's row
     */
    int getRow();

    /**
     * @brief Accessor
     * @return \e int : pivot's column
     */
    int getCol();

    /**
     * @brief Returns the value of m[row][col]
     * @param[in] m (\e Matrix)
     * @return \e std::complex<double>
     */
    std::complex<double> getVal (const Matrix & m) const;

    /**
     * @brief Multiplies a row by a scale
     * @param[in-out] row (\e vector \e iterator)
     * @param[in] ratio (\e std::complex<double>)
     */
    void rowScale(tab2D_iter row, const std::complex<double> & ratio) const;

    /**
     * @brief Replaces a row
     * @param[in-out] base (\e vector \e iterator)
     * @param[in-out] op (\e vector \e iterator)
     * @param[in] ratio (\e std::complex<double>)
     */
    void rowReplace(tab2D_iter base, tab2D_iter op, const std::complex<double>& ratio) const;

    /**
     * @brief Exchanges two rows
     * @param[in-out] a (\e vector \e iterator)
     * @param[in-out] b (\e vector \e iterator)
     */
    void rowExchange(tab2D_iter a, tab2D_iter b) const;

    /**
     * @brief Test if columns contains non zero coefficients
     * @param[in] matrix (\e Matrix)
     * @param[in] column_id (\e int)
     * @param[in] rows (\e int)
     * @param[in] next_row_id (\e int)
     * @return \e int
     */
    int isNonZeroColumn(const Matrix & matrix, const int & column_id,
                        const int & rows, const int & next_row_id) const;

};


#endif // GAUSS_H
