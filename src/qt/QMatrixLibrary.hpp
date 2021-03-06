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

#ifndef MATRIX_LIBRARY
#define MATRIX_LIBRARY

#include "../maths/Matrix.h"
#include <QMap>
#include <complex>
#include <mpParser.h>
#include "UserMatrix.hpp"

/**
 * @class The MatrixLibrary class
 */

class QMatrixLibrary
{
    private:

    static mup::ParserX parser;

    QMap<QString, UserMatrix> tab;

    public:
/**
 * @brief Default constructor
 */
    QMatrixLibrary ();

/**
 * @brief Copy constructor
 * @param [in] lib (\e MatrixLibrary)
 */
   QMatrixLibrary (const QMatrixLibrary & lib);

/**
 * @brief Returns the size of the library
 * @return \e unsigned \e int
 */
    unsigned int long size () const;

/**
 * @brief Returns true if the library is empty
 * @return \e bool
 */
    bool isEmpty () const;

/**
 * @brief Clear the library
 */
    void clear ();

/**
 * @brief Returns the existance of a matrix in the library
 * @param [in] name (\e string)
 * @return \e bool
 */
    bool exist (const QString& name) const;

/**
 * @brief Returns if the chain can be accepted as name
 * @return \e bool
 */
    bool isName(const QString & chain) const;


/**
 * @brief Add a matrix to the library by a UserInputs instance
 * @param [in] name (\e string)
 * @param [in] m the userInputs instance
 */
    const Matrix& addMatrix (const QString& name, const UserInputs& m);

/**
 * @brief Add a matrix to the library.
 * @param [in] name (\e string)
 * @param [in] m the Matrix to add
 */
    void addMatrix(const QString& name, const Matrix& m);

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name (\e string)
 * @return \e Matrix*
 */
    const Matrix* find (const QString& name) const;

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name
 * @return \e Matrix*
 */
    Matrix* find (const QString& name);

/**
 * @brief find_inputs find a UserInputs in the library using its name
 * @param [in] name
 * @return a pointer to a UserInputs if exists, else nullptr
 */
    const UserInputs* find_inputs(const QString& name) const;

/**
 * @brief find_inputs find a UserInputs in the library using its name
 * @param [in] name
 * @return a pointer to a UserInputs if exists, else nullptr
 */
    UserInputs* find_inputs(const QString& name);

/**
 * @brief find_all find a UserMatfrix in the library using its name
 * @param [in] name (\e string)
 * @return a pointer to a UserMatrix if exists, else nullptr
 */
    const UserMatrix* find_all(const QString& name) const;

/**
 * @brief find_all find a UserMatfrix in the library using its name
 * @param [in] name (\e string)
 * @return a pointer to a UserMatrix if exists, else nullptr
 */
    UserMatrix* find_all(const QString& name);

/**
 * @brief Erase a matrix from the library
 * @param [in] name (\e string)
 */
    void erase (const QString & name);

/**
 * @brief Return the map of matrices
 * @return \e std::map<std::string, Matrix>
 */
    const QMap<QString, UserMatrix>& data () const;

/**
 * @brief begin allow range based for on the QMatrixLibrray by returning an iterator
 * @return an iterator set on the fist element of the QMatrixLibrary
 */
    const QMap<QString, UserMatrix>::const_key_value_iterator begin() const;

/**
 * @brief begin allow range based for on the QMatrixLibrray by returning an iterator
 * @return an iterator set on the fist element of the QMatrixLibrary
 */
    const QMap<QString, UserMatrix>::const_key_value_iterator end() const;


/**
 * @brief Saves the matrix library in \e mtmx format
 */
    void saveFile (const std::string & filename)const;

/**
 * @brief Reads a mtmx file to load the matrix library
 * @details The string contains the path of the file
 * @param [in] filename (\e string)
 */
    void readFile (const std::string & filename);

/**
 * @brief Regression test
 */
    void regressionTest() const;

private:

    /**
     * @brief Copy a vector of std::string in another
     * @param[out] expression (\e std::vector<std::string>)
     * @param[in] resultat (\e std::vector<std::string>)
     */
    void copyVector(std::vector<std::string>& expression,
                     const std::vector<std::string>&resultat)const;

    /**
     * @brief Returns true if the parameter is a float
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isFloat(const std::string & chain) const;

    /**
     * @brief Returns true if the parameter is an operator
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isOperator (const std::string & chain) const;

    /**
     * @brief Test if the caracthere is tolerated in function calculateExpression
     * @details Returns true if the caractere is not tolerated
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isSpecialCaractere(const std::string & chain) const;

    /**
     * @brief Separates matrices and operators
     * @param[in] expression (\e std::string)
     * @return \e std::vector<std::string>
     */
    std::vector<std::string> explode (const std::string & expression)const;

    /**
     * @brief Returns true if both operators have equal priority or one of them have a higher priority than the other
     * @param[in] opr (\e std::string) : right operator
     * @param[in] opl (\e std::string) : left operator
     * @return \e bool
     */
    bool highEqualPriority (const std::string & opr,
                              const std::string & opl) const;

    /**
     * @brief Returns the result of binary operation between two matrices
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first matrix name
     * @param[in} b (\e std::string) : second matrix name
     * @return \e Matrix
     */
    Matrix calculate (const std::string & op, const std::string & a,
                      const std::string & b) const;

    /**
     * @brief Returns the results of a binary operation of doubles
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first double
     * @param[in] b (\e std::string) : second double
     * @return \e double
     */
    double calculateFloat (const std::string & op, const std::string & a,
                           const std::string & b)const;

    /**
     * @brief Returns the results of a binary operation between a matrix and a float
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : matrix name
     * @param[in] b (\e std::string) : double
     * @return \e Matrix
     */
    Matrix calculateMatrixFloat (const std::string & op, const std::string & a,
                                 const double & b)const;

    /**
     * @brief Returns the results of a binary operation between a matrix and a float
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first matrix name
     * @param[in] b (\e std::string) : second matrix name
     * @return \e Matrix
     */
    Matrix calculateFloatMatrix (const std::string & op, const std::string & a,
                                 const float & b)const;

    /**
     * @brief Write a std::string in a Polish notation
     * @param[in] chain (\e std::string)
     * @param[out] polish_notation (\e std::vector<std::string>)
     */
    void polish(const std::string & chain, std::vector<std::string> & polish_notation)const;



public:

    /**
     * @brief Tests if the expression is computable
     * @details Returns "computable" if the expression is computable, otherwise returns a std::string to guide the user
     * @param[in] expression (\e std::string)
     * @return \e std::string
     */
    std::string isCalculableExpression(const std::string & expression)const;

    /**
     * @brief Evaluates the result of a matrix expression
     * @param[in] chain (\e std::string)
     * @return \e Matrix
     */
    Matrix calculateExpression(const std::string & chain) const;
};


#endif
