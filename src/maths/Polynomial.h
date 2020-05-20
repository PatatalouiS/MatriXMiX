#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

#include <vector>

#include "VectorX.h"

/**
 * @class The Polynomial class
 */
class Polynomial {

    public:
        unsigned int degree;
    std::vector < std::complex < double >> tab;

    static
    const Polynomial polynomial_null;

    public:

        /**
         * @brief Default constructor
         */
        Polynomial();

    /**
     * @brief Constructor
     * @param [in] d (\e string)
     */
    Polynomial(const unsigned int & d);

    /**
     * @brief Constructor
     * @param [in] d (\e unsigned \e int)
     * @param [in] values (\e vectorX)
     */
    Polynomial(const unsigned int & d,
        const VectorX & values);

    /**
     * @brief Copy constructor
     * @param [in] p (\e Polynomial)
     */
    Polynomial(const Polynomial & p);

    /**
     * @brief Rounded to an anteger epsilon close
     * @return \e Polynomial
     */
    //Polynomial check() const;

    void debugAffiche();

    /**
     * @brief Friend operator << : shows polynomial
     * @param |in-out] flux (\e std::ostream)
     * @param [in] p (\e Polynomial)
     * @return \e std::ostream&
     */
    friend std::ostream & operator << (std::ostream & flux,
        const Polynomial & p);

    /**
     * @brief Operator = : affects a polynomial to another
     * @param [in] p (\e Polynomial)
     * @return \e Polynomial
     */
    Polynomial & operator = (const Polynomial & p);

    /**
     * @brief Operator == : test equality between 2 polynomials
     * @param [in] p (\e Polynomial)
     * @return \e bool
     */
    bool operator == (const Polynomial & p) const;

    /**
     * @brief Operator + : binary operation (addition)
     * @param [in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator + (const Polynomial & p) const;

    /**
     * @brief Operator - : binary operation (substraction)
     * @param [in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator - (const Polynomial & p) const;

    /**
     * @brief  Operator * : binary operation (multiplication)
     * @param [in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator * (const Polynomial & p) const;

    /**
     * @brief Operator * : binary operation (multiplies a polynomial by a scale)
     * @param [in] scale (\e double)
     * @return \e Polynomial
     */
    const Polynomial operator * (const double & scale) const;

    /**
     * @brief Operator / : binary operation (divide 2 polynomials)
     * @details Returns quotient, and affect the rest to the variable \e rest
     * @param [in] divisor (\e Polynomial)
     * @param [in-out] rest (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial division(const Polynomial & divisor, Polynomial & rest);

    /**
     * @brief Solve a 2nd degree equation
     * @param [in-out] nbsolution (\e unsigned \e int)
     * @param [in-out] x1 (\e double)
     * @param [in-out] x2 (\e double)
     */
    void equation2degre(unsigned int & nbsolution, double & x1, double & x2) const;

    /**
     * @brief Regression test
     */
    void regressionTest() const;

};

#endif
