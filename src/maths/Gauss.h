#ifndef GAUSS_H
#define GAUSS_H


#include <iostream>
#include "Matrix.h"

typedef std::vector<std::vector<std::complex<double>>>::iterator tab2D_iter ;


/**
 * @class The Gauss class
 */
class Gauss
{

private:

    int row;
    int col;



public:

/**
 * @brief Default constructor without parameter
 */
    Gauss ();

/**
 * @brief Constructor
 * @param [in] row (\e int)
 * @param [in] col (\e int)
 */
    Gauss (const int & row, const int & col);

    int getRow();


    int getCol();

/**
 * @brief Return the value of m[row][col]
 * @param [in] m (\e Matrix)
 * @return \e double
 */
    std::complex<double> getVal (const Matrix & m) const;

/**
 * @brief Multiplies a row by a scale
 * @param [in-out] row (\e vector \e iterator)
 * @param [in] ratio (\e double)
 */
    void rowScale(tab2D_iter row, const std::complex<double> & ratio) const;

/**
 * @brief Replaces a row
 * @param [in-out] base (\e vector \e iterator)
 * @param [in-out] op (\e vector \e iterator)
 * @param [in] ratio (\e double)
 */
    void rowReplace(tab2D_iter base, tab2D_iter op, const std::complex<double>& ratio) const;

/**
 * @brief Exchanges two rows
 * @param [in-out] a (\e vector \e iterator)
 * @param [in-out] b (\e vector \e iterator)
 */
    void rowExchange(tab2D_iter a, tab2D_iter b) const;

/**
 * @brief Test if columns contains non zero coefficients
 * @param [in] matrix (\e Matrix)
 * @param [in] column_id (\e int)
 * @param [in] rows (\e int)
 * @param [in] next_row_id (\e int)
 * @return \e int
 */
    int isNonZeroColumn(const Matrix &matrix, const int &column_id,
                        const int &rows, const int &next_row_id) const;


};


#endif // GAUSS_H
