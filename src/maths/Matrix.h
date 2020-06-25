#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <../../ext/Eigen/Dense>  // extern library eigen 3.3.7
#include "VectorX.h"
#include "Polynomial.h"


/**
 * @brief Representation of matrices
 */

class Matrix
{

private:
    unsigned int rows;  /*< Number of matrix rows */
    unsigned int cols;  /*< Number of matrix cols */
    std::vector<std::vector<std::complex<double>>> tab; /*< Matrix factors*/


public:
   enum initMatrix { Z, I, R }; /*< enum type (Z:Zero, I:Identity, R:Random) */

   static const Matrix matrix_null;
   static const std::complex<double> complex_null;




/*************** CONSTRUCTORS ***************/

public:

    /**
     * @brief Default constructor
     */
    Matrix ();

    /**
     * @brief Constructor
     * @param[in] rows (\e unsigned \e int)
     * @param[in] cols \e unsigned \e int)
     * @param[in] values (\e std::complex<double>) : matrix factors, row by row ({1,2,3,4,5,6})
     */
    Matrix (const unsigned int rows, const unsigned int cols,
            const std::complex<double> values);

    /**
     * @brief Constructor
     * @param[in] rows (\e unsigned \e int)
     * @param[in] cols (\e unsigned \e int)
     * @param[in] type (\e enum \e type)
     */
    Matrix (const unsigned int rows, const unsigned int cols,
            const enum initMatrix& type = Z);

    /**
     * @brief Constructor
     * @param[in] rows (\e unsigned \e int)
     * @param[in] cols (\e unsigned \e int)
     * @param[in] values (\e VectorX)
     */
    Matrix (const unsigned int rows, const unsigned int cols,
            const VectorX& values);

    /**
     * @brief Copy constructor
     * @param[in] m (\e Matrix)
     */
    Matrix (const Matrix & m);



// ******** STATIC FUNCTION *********

    /**
     * @brief Returns Identity matrix
     * @param[in] size (\e unsigned \e int)
     * @return \e Matrix
     */
    static Matrix ID ( const unsigned int size );





/*************** PRIVATE FUNCTIONS ***************/


private:


    std::vector<std::string> explode (const std::string & expression) const;

    /**
     * @brief Round values to nearests integers (if difference < EPSILON)
     * @param[in] v (\e VectorX)
     * @return rounded \e VectorX
    */
    VectorX checkCast (const VectorX & v) const;

    /**
     * @brief Returns the submatrix (eliminates row a and column b)
     * @param[in] a (\e unsigned \e int)
     * @param[in] b (\e unsigned \e int)
     * @return \e Matrix
     */
    Matrix subMatrix(const unsigned int & a, const unsigned int & b ) const;

    /**
     * @brief Return matrix row
     * @param[in] i (\e unsigned \e int) : index of the row to return
     * @return \e Matrix
    */
    Matrix matrixRow(const unsigned int & i) const;

    /**
     * @brief Return matrix column
     * @param[in] j (\e unsigned \e int) : index of the column to return
     * @return \e Matrix
    */
    Matrix matrixCol(const unsigned int & j) const;

    /**
     * @brief Calculate a column norm
     * @return \e std::complex<double> : the column norm
    */
    std::complex<double> colNorm() const;

    /**
     * @brief Calculate a row norm
     * @return \e std::complex<double> : the row norm
    */
    std::complex<double> rowNorm() const;

    /**
     * @brief Normalize a VectorX
     * @param[in] v (\e VectorX)
     * @return normalized \e VectorX
    */
    VectorX normalizeVectorX(const VectorX & v) const;

    /**
     * @brief Convert Matrix type to eigen MatrixXcd type
     * @return \e Eigen::MatrixXcd (eigen3)
     */
    Eigen::MatrixXcd class2Eigen() const;

    /**
     * @brief Convert eigen MatrixXcd type to Matrix type
     * @param[in] m \e Eigen::MatrixXcd (eigen3)
     * @return \e Matrix
     */
    const Matrix eigen2Class(const Eigen::MatrixXcd & m) const;





/*************** ACCESSORS / MUTATORS / BASIC FUNCTIONS ***************/

public:


    /**
     * @brief Accessor
     * @return Number of rows (\e unsigned \e int)
     */
    unsigned int getNbRows() const;

    /**
     * @brief Accessor
     * @return Number of cols (\e unsigned \e int)
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
     * @param[in] index (\e unsigned \e int)
     * @return \e std::complex<double>&
     */
    std::complex<double>& getVal(const unsigned int index);

    /**
     * @brief Gets index value
     * @param[in] index (\e unsigned \e int)
     * @return \e std::complex<double>
     */
    std::complex<double> getVal(const unsigned int index) const;

    /**
     * @brief Operator [] which gets index value
     * @param[in] index (\e unsigned \e int)
     * @return \e std::vector<std::complex<double>>&
     */
    std::vector<std::complex<double>>& operator [] (const unsigned int index);

    /**
     * @brief Operator [] which gets index value
     * @param[in] index (\e unsigned \e int)
     * @return \e std::vector<std::complex<double>>&
     */
    const std::vector<std::complex<double>>& operator [] (const unsigned int index) const;

    /**
     * @brief Friend operator << : shows matrix
     * @param |in-out] flux \e std::ostream
     * @param[in] m (\e Matrix)
     * @return std::ostream&
     */
    friend std::ostream& operator << (std::ostream& flux, const Matrix & m);

    /**
     * @brief Operator << : set matrix values
     * @param[in] values (\e std::string)
     * @return \e Matrix
     */
    Matrix operator << (const std::string& values);

    /**
     * @brief Operator >> : set matrix values
     * @param[in-out] flux \e istream
     * @param[in-out] m \e Matrix
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
     * @param[in] m (\e Matrix)
     * @return \e Matrix
     */
    const Matrix operator + (const Matrix & m) const;

    /**
     * @brief Operator - : binary operation (substraction)
     * @param[in] m (\e Matrix)
     * @return \e Matrix
     */
    const Matrix operator - (const Matrix & m) const;

    /**
     * @brief Operator * : binary operation (multiplication)
     * @param[in] m (\e Matrix)
     * @return \e Matrix
     */
    const Matrix operator * (const Matrix & m) const;

    /**
     * @brief Operator * : binary operation (scalar multiplication)
     * @param[in] lambda (\e std::complex<double>) : scale
     * @return \e Matrix
     */
    const Matrix operator * (const std::complex<double> & lambda) const;

     /**
     * @brief Operator * : friend operator, multiplies a Matrix by a scale
     * @param[in] lambda \e std::complex<double> : scale
     * @param[in] m \e Matrix
     * @return Matrixstd::complex<double>
     */
    friend const Matrix operator * (const std::complex<double> & lambda,
                                    const Matrix & m) ;

    /**
     * @brief Operator / : binary operation (division)
     * @param[in] m (\e Matrix)
     * @return \e Matrix
     */
    const Matrix operator / (const Matrix & m) const;

    /**
     * @brief Operateur ^ : binary operation (Matrix power)
     * @param[in] p (\e int)
     * @return \e Matrix
     */
    const Matrix operator ^ (const int & p) const;

    /**
     * @brief Operator == : test equality between 2 matrices
     * @param[in] m (\e Matrix)
     * @return \e bool
     */
    bool operator == (const Matrix & m) const;

    /**
     * @brief Operator != : test the non equality between 2 matrices
     * @param[in] m (\e Matrix)
     * @return \e bool
     */
    bool operator != (const Matrix & m) const;

    /**
     * @brief Test if the matrix is a square matrix
     * @return \e bool
     */
    bool isSQMatrix() const;

    /**
     * @brief Rounds up coefficients (if difference < EPSILON)
     * @return \e Matrix
     */
    Matrix checkCast () const;

    /**
     * @brief Normalize a Matrix
     * @return \e Matrix : normalized matrix
    */
    Matrix normalizeMatrix() const;

    /**
     * @brief Returns the matrix trace
     * @return \e std::complex<double>
     */
    std::complex<double> trace() const;

    /**
     * @brief Returns the matrix determinant
     * @return \e std::complex<double>
     */
    std::complex<double> determinant() const;

    /**
     * @brief Returns the coMatrix
     * @return \e Matrix
     */
    Matrix coMatrix() const;

    /**
     * @brief Returns the transpose matrix
     * @return \e Matrix
     */
    Matrix transposeMatrix() const;

    /**
     * @brief Returns the conjugate transpose matrix
     * @return \e Matrix
     */
    Matrix conjugateTranspose() const;

    /**
     * @brief Tests if the matrix is symetric
     * @return \e bool
    */
    bool isSymetric() const;

    /**
     * @brief Tests if the matrix is self adjoint
     * @return \e bool
    */
    bool isSelfAdjoint() const;

    /**
     * @brief Returns the matrix inverse
     * @return \e Matrix
     */
    Matrix inverse() const;


    /**
     * @brief Returns the staggered matrix
     * @return \e Matrix
     */
    const Matrix gaussReduction() const;

    /**
     * @brief Returns the matrix rank
     * @return \e unsigned \e int
    */
    unsigned int rank()const;

    /**
     * @brief Returns the kernel and image dimensions
     * @return \e std::pair<dim(im),dim(ker)>
     */
    const std::pair<unsigned int, unsigned int> dimensionsStudy() const;





/*************** ADVANCED MATRIX FUNCTIONS ***************/


    /**
     * @brief Returns the matrix eigenvalues
     * @return \e VectorX
     */
    const VectorX eigenValues() const;

    /**
     * @brief Returns the matrix characteristic polynomial
     * @return \e Polynomial
     */
    const Polynomial characteristicPolynomial()const;

    /**
     * @brief Returns the matrix splited characteristic polynomial
     * @return \e std::vector<Polynomial>
     */
    const std::vector<Polynomial> splitCharacteristicPolynomial()const;

    /**
     * @brief Returns the matrix eigenvectors
     * @return \e Matrix
     */
    const Matrix eigenVectors() const;

    /**
     * @brief Returns the matrix eigenvalues and eigenvectors
     * @return \e std::vector<std::pair<std::complex<double>,VectorX>>
     */
    const std::vector<std::pair<std::complex<double>,VectorX>> allEigen() const;

    /**
    * @brief Returns true if the matrix is diagonalizable in \e C set
    * @return \e bool
    */
   bool isDiagonalisableC() const;

    /**
     * @brief Returns true if the matrix is diagonalizable in \e R set
     * @return \e bool
     */
    bool isDiagonalisableR() const;

    /**
     * @brief Tests if the matrix is positive definite
     * @return \e bool
    */
    bool isPositiveDefinite() const;

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
     * @param[in-out] transferC2B (\e Matrix) : transfer matrix to the base where the matrix is diagonalizable
     * @param[in-out] diagonal (\e Matrix) : diagonal is the associated diagonal matrix
     * @param[in-out] transferB2C (\e Matrix) : transfer matrix from the base where the matrix is diagonalizable to the former base
     */
    void allMatrix(Matrix & transferC2B, Matrix & diagonal,
                   Matrix & transferB2C) const;

    /**
     * @brief Calculate LU decomposition
     * @details Only if A is positive definite
     * @return \e std::pair<Matrix,Matrix> : std::pair<L,U>
    */
    std::pair<Matrix,Matrix> LUDecomposition() const;

    /**
     * @brief Solves Ax=b equation using LU decomposition
     * @details Only if A is positive definite
     * @param[in] b (\e Matrix)
     * @return \e Matrix : x
    */
    Matrix solveAx_LU(const Matrix & b) const;

    /**
     * @brief Calculate orthogonal family using Gram Schmidt method
     * @brief \e Matrix : orthogonal vectors
    */
    Matrix gramSchmidt() const ;

    /**
     * @brief Calculate QR decomposition using Gram Schmidt method
     * @return \e std::pair<Matrix,Matrix> : pair<Q,R>
    */
    std::pair<Matrix,Matrix> QR_GramSchmidt() const;

    /**
     * @brief Calculate QR decomposition using Householder method (more efficient than the Gram Schmidt method)
     * @return \e std::pair<Matrix,Matrix> : pair<Q,R>
    */
    std::pair<Matrix,Matrix> QR_Householder() const;

    /**
     * @brief Calculate Cholesky decomposition
     * @return \e std::pair<Matrix,Matrix> : pair<C,C*>
    */
    std::pair<Matrix,Matrix> cholesky() const;

    /**
     * @brief Solves Ax=b equation using QR decomposition
     * @details Only if A has rows >= cols
     * @param[in] b (\e Matrix)
     * @return \e Matrix : x
    */
    Matrix solveAx(const Matrix & b) const;


    /**
     * @brief Regression test
     */
    void regressionTest() const;

};


#endif
