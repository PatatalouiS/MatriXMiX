#ifndef USER_MATRIX_HPP
#define USER_MATRIX_HPP

#include <complex>
#include "../maths/Matrix.h"
#include "UserInputs.hpp"

using Value = std::complex<double>;

struct UserMatrix {
    Matrix matrix;
    UserInputs entries;
};


#endif // USER_QMATRIX_HPP
