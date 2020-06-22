#ifndef USER_MATRIX_HPP
#define USER_MATRIX_HPP

#include <complex>
#include "../maths/Matrix.h"
#include "UserInputs.hpp"

using Value = std::complex<double>;

/**
 * @brief The UserMatrix struct A little Wrapper to symbolise a Matrix by the
 *  user entries but with the parsed values too.
 */

struct UserMatrix {
    Matrix matrix;
    UserInputs entries;
};


#endif // USER_QMATRIX_HPP
