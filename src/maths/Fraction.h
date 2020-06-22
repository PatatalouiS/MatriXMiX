#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <vector>
#include <string>


/**
 * @brief Representation of fractions
 */
class Fraction
{

private:

    long int numerator, denominator;

    std::string num, den;

public:
/**
 * @brief Default constructor
 */
    Fraction();

/**
 * @brief Constructor
 * @param [in] n (\e long \e int)
 */
    Fraction(const long int & n);

/**
 * @brief Constructor
 * @param [in] n (\e long \e int)
 * @param [in] d (\e long \e int)
*/
    Fraction(const long int & n, const long int & d);

/**
 * @brief Constructor
 * @param [in] d (\e double)
 */
    Fraction(const double & d);

/**
 * @brief Accessor
 * @return Numerator (\e long \e int)
 */
    long int getNumerator() const;

/**
 * @brief Accessor
 * @return Denominator (\e long \e int)
 */
    long int getDenominator() const;

/**
 * @brief Setter
 * @param the new Numerator of Fraction
 */
    void setNumerator(const long int& n);

/**
 * @brief Setter
 * @param the new Denominator of Fraction
 */
    void setDenominator(const long int& d);

/**
 * @brief Operator <<
 * @param [out] flux (\e std::ostream)
 * @param [in] fraction (\e Fraction)
 * @return \e flux
 */
    friend std::ostream& operator << (std::ostream& flux, Fraction const& fraction);

/**
 * @brief  Operator = : affects a Fraction
 * @param [in] f (\e Fraction)
 * @return \e Fraction
 */
    Fraction& operator = (const Fraction & f);

/**
 * @brief Operator = : convert the double into a fraction and returns it
 * @param [in] d (\e double)
 * @return \e double
 */
    Fraction& operator = (const double &d);

/**
 * @brief Operator == : tests equality between 2 fractions
 * @param [in] f (\e Fraction)
 * @return \e bool
 */
    bool operator == (const Fraction & f) const;

/**
 * @brief Operator < : tests if the first fraction is inferior to the second
 * @param [in] f (\e Fraction)
 * @return \e bool
 */
    bool operator < (const Fraction & f) const;

/**
 * @brief Returns the inverse of a fraction
 * @return \e Fraction
 */
    const Fraction inverse () const;

/**
 * @brief Returns the fraction gdc
 * @param [in] a (\e long \e int)
 * @param [in] b (\e long \e int)
 * @return \e long \e int
 */
    long int gcd (long int a, long int b) const;

/**
 * @brief Simplifies the fraction
 * @return \e Fraction
 */
    const Fraction simplify () const;

/**
 * @brief Operator + : add 2 fractions
 * @param [in] f \e Fraction
 * @return \e Fraction
 */
    const Fraction operator + (const Fraction & f) const;

/**
 * @brief Operator + : convert a double and add it to the fraction
 * @param [in] d \e double
 * @return \e Fraction
 */
    const Fraction operator + (const long int & d) const;

/**
 * @brief Operator * : multiplies 2 fractions
 * @param [in] f \e Fraction
 * @return \e Fraction
 */
    const Fraction operator * (const Fraction & f) const;

/**
 * @brief Operator / : divide 2 fractions
 * @param [in] f \e Fraction
 * @return \e Fraction
 */
    const Fraction operator / (const Fraction & f) const;

/**
 * @brief test if the real is not an integer
 * @param [in] d \e double
 * @return \e bool \n Return false if the fraction is an integer
 */
    //bool isFraction (const double & d) const;

/**
 * @brief regressionTest
 */
    void regressionTest() const;
};

#endif
