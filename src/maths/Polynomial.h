#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

#include "VectorX.h"

/**
 * @brief Representation of polynomials
 */
class Polynomial {

private:

    unsigned int degree; /*< polynomial degree*/

public:

    std::vector < std::complex < double >> tab; /*< factors (from 0 to degree)*/

    /**
    * @brief Default constructor
    */
    Polynomial();

    /**
     * @brief Constructor
     * @param[in] degree (\e std::unsigned \e int) : polynomial degree
     */
    Polynomial(const unsigned int & degree);

    /**
     * @brief Constructor
     * @param[in] d (\e unsigned \e int)
     * @param[in] values (\e VectorX) : polynomial factors (from 0 to degree)
     */
    Polynomial(const unsigned int & d,
        const VectorX & values);

    /**
     * @brief Copy constructor
     * @param[in] p (\e Polynomial)
     */
    Polynomial(const Polynomial & p);

    /**
     * @brief Round to the nearest integer (if difference < EPSILON)
     * @return \e Polynomial
     */
    //Polynomial check() const;

    void debugAffiche();

    /**
     * @brief Friend operator << : shows polynomial
     * @param|in-out] flux (\e std::ostream)
     * @param[in] p (\e Polynomial)
     * @return \e std::ostream&
     */
    friend std::ostream & operator << (std::ostream & flux,
        const Polynomial & p);

    /**
     * @brief Operator = : affects a polynomial to another
     * @param[in] p (\e Polynomial)
     * @return \e Polynomial
     */
    Polynomial & operator = (const Polynomial & p);

    /**
     * @brief Operator == : test equality between 2 polynomials
     * @param[in] p (\e Polynomial)
     * @return \e bool
     */
    bool operator == (const Polynomial & p) const;

    /**
     * @brief Operator + : binary operation (addition)
     * @param[in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator + (const Polynomial & p) const;

    /**
     * @brief Operator - : binary operation (substraction)
     * @param[in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator - (const Polynomial & p) const;

    /**
     * @brief  Operator * : binary operation (multiplication)
     * @param[in] p (\e Polynomial)
     * @return \e Polynomial
     */
    const Polynomial operator * (const Polynomial & p) const;

    /**
     * @brief Operator * : binary operation (multiplies a polynomial by a scale)
     * @param[in] scale (\e double)
     * @return \e Polynomial
     */
    const Polynomial operator * (const double & scale) const;

    /**
     * @brief Operator / : binary operation (divide 2 polynomials)
     * @details Returns quotient, and affect the remainder to the variable \e rest
     * @param[in] divisor (\e Polynomial)
     * @param[in-out] remain (\e Polynomial)
     * @return \e Polynomial : the remainder
     */
    const Polynomial division(const Polynomial & divisor, Polynomial & remain);

    /**
     * @brief Regression test
     */
    void regressionTest() const;

    Polynomial check() const;

};

#endif
