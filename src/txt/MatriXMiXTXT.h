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

#ifndef MATRIXMIX_TXT_H
#define MATRIXMIX_TXT_H

#include <complex>
#include <sstream>
#include "../maths/MatrixLibrary.h"

class MatriXMiXTXT
{
    private:

    MatrixLibrary lib;

    //Fonctions d'AFFICHAGE

    std::complex<double> checkCast(const std::complex<double> & c) const;

    VectorX checkCast(const VectorX & v) const;

    std::string print(const std::complex<double> & z) const;

    std::string print(const VectorX & v) const;

    std::string print(const Matrix & m) const;


/**
 * @brief Shows result of binary operation called
 * @param [in] op (\e char)
 */
    void binaryOperation (const char op) const;

/**
 * @brief Shows Matrix^p result
 */
    void binaryOperationPow() const;

/**
 * @brief Shows result of unary operation called
 * @param [in] op (\e short \e int)
 */
    void unaryOperation(const short int & op) const;

/**
 * @brief Shows message if no matrix entered
 */
    void MsgEmptyLib () const;

/**
 * @brief Shows the add matrix menu
 */
    void addMatrixMenu ();

/**
 * @brief Shows matrix library
 */
    void showLibrary () const;

/**
 * @brief Shows addition menu and calls its function
 */
    void addition () const;

/**
 * @brief Shows soustraction menu and calls its function
 */
    void soustraction () const;

/**
 * @brief Shows multiplication menu and calls its function
 */
    void multiplication () const;

/**
 * @brief Shows division menu and calls its function
 */
    void division () const;

/**
 * @brief Shows power menu and calls its function
 */
    void puissance () const;

/**
 * @brief Shows trace menu and calls its function
 */
    void trace() const;

/**
 * @brief Shows determinant menu and calls its function
 */
    void determinant() const;

/**
 * @brief Shows inverse menu and calls its function
 */
    void inverse() const;

/**
 * @brief Shows gauss reduction menu and calls its function
 */
    void gaussReduction() const;

/**
 * @brief Shows gauss reduction menu and calls its function
 */
    void dimensionsStudy() const;

/**
 * @brief Shows dimensions study menu and calls its function
 */
    void displayDimensionsStudy(const Matrix * m, const std::string & name) const;

/**
 * @brief Calls characteristic poynomial function
 */
    void characteristicPolynomial() const;

/**
 * @brief Shows characteristic polynomial result
 */
    void displayCharacteristicPolynomial(const Matrix * m, const std::string & name)const;

/**
 * @brief Calls eigenValues and eigenVectors functions
 */
    void eigenValVect() const;

/**
 * @brief Shows eigenValues and eigenVectors results
 */
    void displayEigenValVect(const Matrix * m) const;

/**
 * @brief Calls diagonalization functions
 */
    void studyDiagonalise() const;

/**
 * @brief Shows diagonalization results
 */
    void displayStudyDiagonalise(const Matrix * m) const;

    void luDecomposition() const;

    void displayLUDecomposition(const Matrix * m) const;

    void qrHouseholder() const;

    void displayQRHouseholder(const Matrix * m) const;

    void cholesky() const;

    void displayCholesky(const Matrix * m) const;

/**
 * @brief Calls all functions
 */
    void studyMatrix() const;

/**
 * @brief Shows all results
 */
    void displayStudyMatrix(const Matrix * m, const std::string & name) const;

    void calculateExpression() const;


    public:

/**
 * @brief Shows global menu
 */
    void mainMenu ();


};



#endif
