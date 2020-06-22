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
}

#endif
