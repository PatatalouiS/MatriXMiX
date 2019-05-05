#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <Dense>  // externe library eigen 3.3.7
#include "VectorX.h"
#include "Polynomial.h"


class Matrix
{

private:
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;

public:
    static const std::vector<double> vector_noEigen;
    static const std::vector<std::pair<double,VectorX>> vector_pair_noEigen;
    static const Matrix matrix_noEigen;
    static const Matrix matrix_null;
    static const double double_notExist;


private:

/**
 * @brief Returns the submatrix (eliminates row a and column b)
 * @param [in] a (\e unsigned \e int)
 * @param [in] b (\e unsigned \e int)
 * @return \e Matrix
 */
    Matrix subMatrix(const unsigned int & a, const unsigned int & b ) const;

/**
 * @brief Private function which rounds up real coefficients
 * @return \e Matrix
 */
    Matrix checkCast () const;

/**
 * @brief Recursive function which returns matrix determinant
 * @param [in] dim (\e unsigned \e int)
 * @return \e double
 */
    double determinant(const unsigned int & dim) const;

/**
 * @brief Tests if the determinant is null
 * @details Returns true if determinant is equal to 0
 * @return \e bool
 */
    bool isNulDeterminant() const;

/**
 * @brief
 * @param expression
 * @return
 */
    std::vector<std::string> explode (const std::string & expression) const;

/**
 * @brief Convert Matrix type to eigen MatrixXd type
 * @return \e MatrixXd (eigen3)
 */
    Eigen::MatrixXd class2Eigen() const;

/**
 * @brief Convert eigen MatrixXd type to Matrix type
 * @param [in] m \e MatrixXd (eigen3)
 * @return \e Matrix
 */
    const Matrix eigen2Class(const Eigen::MatrixXd & m) const;


public:


/**
 * @brief Returns Identity matrix
 * @param [in] size (\e unsigned \e int)
 * @return \e Matrix
 */
    static Matrix ID ( const unsigned int size );



/**
 * @brief enum type
 */
    enum initMatrix { Z, I, R };



 // Constructors


/**
 * @brief Default constructor
 */
    Matrix ();

/**
 * @brief Constructor
 * @param [in] rows (\e unsigned \e int)
 * @param [in] cols \e unsigned \e int)
 * @param [in] value (\e double)
 */
    Matrix (const unsigned int rows, const unsigned int cols, const double value);

/**
 * @brief Constructor
 * @param [in] rows (\e unsigned \e int)
 * @param [in] cols (\e unsigned \e int)
 * @param [in] type (\e enum \e type)
 */
    Matrix (const unsigned int rows, const unsigned int cols, const enum initMatrix& type = Z);

/**
 * @brief Constructor
 * @param [in] rows (\e unsigned \e int)
 * @param [in] cols (\e unsigned \e int)
 * @param [in] values (\e VectorX)
 */
    Matrix (const unsigned int rows, const unsigned int cols, const VectorX& values);

/**
 * @brief Copy constructor
 * @param [in] m (\e Matrix)
 */
    Matrix (const Matrix & m);




// Accessors/Mutators & basic functions


/**
 * @brief Accessor
 * @return Number of rows (\e unsigned \e int)
 */
    unsigned int getNbRows() const;

/**
 * @brief Accessor
 * @return Number of columns (\e unsigned \e int)
 */
    unsigned int getNbCols() const;

/**
 * @brief Mutator : sets number of rows
 * @param row (\e unsigned \e int)
 */
    void setNbRows(unsigned int row);

/**
 * @brief Mutator : sets number of columns
 * @param col (\e unsigned \e int)
 */
    void setNbCols(unsigned int col);

/**
 * @brief Gets index value
 * @param [in] index (\e unsigned \e int)
 * @return \e double&
 */
    double& getVal(const unsigned int index);

/**
 * @brief Gets index value
 * @param [in] index (\e unsigned \e int)
 * @return \e double
 */
    double getVal(const unsigned int index) const;

/**
 * @brief Operator [] which gets index value
 * @param [in] index (\e unsigned \e int)
 * @return \e std::vector<double>&
 */
    std::vector<double>& operator [] (const unsigned int index);

/**
 * @brief Operator [] which gets index value
 * @param [in] index (\e unsigned \e int)
 * @return \e std::vector<double>&
 */
    const std::vector<double>& operator [] (const unsigned int index) const;

/**
 * @brief Friend operator << : shows matrix
 * @param |in] flux \e std::ostream
 * @param [in] m (\e Matrix)
 * @return std::ostream&
 */
    friend std::ostream& operator << (std::ostream& flux, const Matrix & m);

/**
 * @brief Operator << : enter values into Matrix
 * @param [in] values (\e std::string)
 * @return \e Matrix
 */
    Matrix operator << (const std::string& values);

/**
 * @brief Operator >> : enter values into Matrix
 * @param [in-out] flux \e istream
 * @param [in-out] m \e Matrix
 * @return \e istream
 */
    friend std::istream& operator >> (std::istream& flux, Matrix & m);

/**
 * @brief Sets matrix coefficients (keyboard)
 */
    void setMatrixKB();

/**
 * @brief Sets random coefficients to matrix
 */
    void setMatrixRA();

/**
 * @brief Operator + : binary operation (addition)
 * @param [in] m (\e Matrix)
 * @return \e Matrix
 */
    const Matrix operator + (const Matrix & m) const;

/**
 * @brief Operator - : binary operation (substraction)
 * @param [in] m (\e Matrix)
 * @return \e Matrix
 */
    const Matrix operator - (const Matrix & m) const;

/**
 * @brief Operator * : binary operation (multiplication)
 * @param [in] m (\e Matrix)
 * @return \e Matrix
 */
    const Matrix operator * (const Matrix & m) const;

/**
 * @brief Operator * : binary operation (scalar multiplication)
 * @param [in] lambda (\e double)
 * @return \e Matrix
 */
    const Matrix operator * (const double & lambda) const;

 /**
 * @brief Operator * : friend operator, multiplies a Matrix by a scale
 * @param [in] lambda \e double
 * @param [in] m \e Matrix
 * @return Matrix
 */
    friend const Matrix operator * (const double & lambda, const Matrix & m) ;

/**
 * @brief Operator / : binary operation (division)
 * @param [in] m (\e Matrix)
 * @return \e Matrix
 */
    const Matrix operator / (const Matrix & m) const;

/**
 * @brief Operateur ^ : binary operation (Matrix power)
 * @param [in] p (\e int)
 * @return \e Matrix
 */
    const Matrix operator ^ (const int & p) const;

/**
 * @brief Operator == : test equality between 2 matrix
 * @param [in] m (\e Matrix)
 * @return \e bool
 */
    bool operator == (const Matrix & m) const;

/**
 * @brief Operator != : test the non equality between 2 matrix
 * @param [in] m (\e Matrix)
 * @return \e bool
 */
    bool operator != (const Matrix & m) const;

/**
 * @brief Test if the matrix is a square matrix
 * @return \e bool
 */
    bool isSQMatrix() const;

/**
 * @brief Returns the matrix trace
 * @return \e double
 */
    double traceMatrix() const;

/**
 * @brief Returns the matrix determinant
 * @return \e double
 */
    double determinant() const;

/**
 * @brief Returns the coMatrix
 * @return \e Matrix
 */
    Matrix coMatrix() const;

/**
 * @brief Returns the matrix transpose Matrix
 * @return \e Matrix
 */
    Matrix transposeMatrix() const;

/**
 * @brief Returns the matrix inverse
 * @return \e Matrix
 */
    Matrix inverse() const;

/**
 * @brief Returns the matrix rank
 * @return \e unsigned \e int
 */
    unsigned int rank() const;

/**
 * @brief Returns the staggered matrix
 * @return \e Matrix
 */
    const Matrix gaussReduction() const;



 // Advanced matrix study functions

/**
 * @brief Returns the kernel and image dimensions
 * @return \e std::pair <dim(im),dim(ker)>
 */
    const std::pair<unsigned int, unsigned int> dimensionsStudy() const;

/**
 * @brief Returns the matrix eigenvalues
 * @return \e std::vector
 */
    const std::vector<double> eigenValues() const;

/**
 * @brief Returns the matrix characteristic polynomial
 * @return \e Polynomial
 */
    const Polynomial characteristicPolynomial() const;

/**
 * @brief Returns the simplified characteristic polynomial
 * @return \e std::vector<Polynomial>
 */
    const std::vector<Polynomial> splitCharacteristicPolynomial() const;

/**
 * @brief Returns the matrix eigenvectors
 * @return \e std::vector<VectorX>
 */
    const std::vector<VectorX> eigenVectors() const;

/**
 * @brief Returns the matrix eigenvalues and eigenvectors
 * @return \e std::vector<std::pair<double,VectorX>>
 */
    const std::vector<std::pair<double,VectorX>> allEigen() const;

/**
 * @brief Returns true if the matrix is diagonalizable in \e R set
 * @return \e bool
 */
    bool isDiagonalisable() const;

/**
 * @brief Returns the diagonal matrix
 * @return \e Matrix
 */
    const Matrix diagonalise() const;

/**
 * @brief Returns the transfer matrix
 * @return \e Matrix
 */
    const Matrix transferMatrix() const;

/**
 * @brief Calls transferMatrix() and diagonalise()
 * @details transferC2B is the transfer matrix to the base where the matrix is diagonalizable
 * \n diagonal is the associated diagonal matrix
 * \n transferB2C is the transfer matrix from the base where the matrix is diagonalizable to the former base
 * @param [in-out] transferC2B \e Matrix
 * @param [in-out] diagonal \e Matrix
 * @param [in-out] transferB2C \e Matrix
 */
    void allMatrix(Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C) const;

/**
 * @brief Regression test
 */
    void regressionTest() const;


};


#endif
