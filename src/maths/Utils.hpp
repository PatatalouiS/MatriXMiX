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

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <complex>

#include "Fraction.h"

/**
 * This namespace provides little utils functions like conversions or TeX formatting
 */

namespace Utils {

    /**
     * @brief isFraction return if a double is a fraction.
     * @param d the double to test
     * @return true if d is a Fraction, else false.
     */
    bool isFraction(const double & d);

    /**
     * @brief double2fraction return a Fraction based on the given double
     * @param d the double to convert
     * @return the fractionized double
     */
    const Fraction double2fraction(const double & d);

    /**
     * @brief double2sqrt return a LaTeX representation of a sqrt-friendly given double
     * @param d the double to stringify
     * @return the LaTeX formatted string
     */
    std::string double2sqrt(const double & d);

    /**
     * @brief print convert a given double to his TeX representation
     * @param d the double to stringify
     * @return the LaTeX formatted string
     */
    std::string print(const double & d);

    /**
     * @brief complex2LaTeX return the TeX representatin of a complex
     * @param c the complex to stringify
     * @return the LaTeX formatted string
     */
    std::string complex2LaTeX(const std::complex<double>& c);

    /**
     * @brief Round to the nearest integer (if difference < EPSILON)
     * @param[in] z (\e std::complex<double>)
     * @return rounded \e std::complex<double>
    */
    std::complex<double> checkCast (const std::complex<double> & z);
}

#endif
