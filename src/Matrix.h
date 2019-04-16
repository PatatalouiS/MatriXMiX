
#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <Dense>
#include "VectorX.h"
#include "Polynomial.h"


class Matrix
{
private:
    
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;
    
    
    
private:
    Matrix subMatrix(const unsigned int a, const unsigned int b ) const;
    double determinant(unsigned int dim) const;
    Eigen::MatrixXd class2Eigen() const;
    const Matrix eigen2Class(const Eigen::MatrixXd & m) const;
    
public:

    // Fonction statique, renvoie, la matrice identité demandée
    static Matrix ID ( const unsigned int size );
    
    
    // type énuméré pour l'initialisation
    enum initMatrix { Z, I, R };
    
    // Constructeurs et Destructeurs
    Matrix ();
    Matrix (const unsigned int rows, const unsigned int cols, const double value);
    Matrix (const unsigned int rows, const unsigned int cols, const enum initMatrix& type = Z);
    Matrix (const unsigned int rows, const unsigned int cols, const VectorX& values);
    Matrix (const Matrix & m);
    ~Matrix ();
    
    
    //Accesseurs / Opérateurs de calcul / Fonctions de calcul algébrique
    unsigned int getNbRows() const;
    unsigned int getNbCols() const;
    double& getVal(const unsigned int indice);
    double getVal(const unsigned int indice) const;
    std::vector<double>& operator [] (const unsigned int indice);
    const std::vector<double>& operator [] (const unsigned int indice) const;
    friend std::ostream& operator << (std::ostream& flux, const Matrix & m);
    void setMatrixKB();
    void setMatrixRA();
    const Matrix operator + (const Matrix & m) const;
    const Matrix operator - (const Matrix & m) const;
    const Matrix operator * (const Matrix & m) const;
    const Matrix operator * (const double & lambda) const;
    const Matrix operator / (const Matrix & m) const;
    const Matrix operator ^ (const int & p) const;
    bool operator == (const Matrix & m) const;
    bool operator != (const Matrix & m) const;
    Matrix checkCast () const;
    bool isSQMatrix() const;
    double traceMatrix() const;
    double determinant() const;
    Matrix coMatrix() const;
    Matrix transposeMatrix() const;
    Matrix inverse() const;
    unsigned int rank() const;
 
    //Fonctions d'étude poussée des matrices et utilisation de la librairie externe eigen3
    const Matrix gaussReduction() const;
    std::pair<unsigned int, unsigned int> dimensionsStudy() const;
    std::vector<double> eigenValues() const;
    const Polynomial characteristicPolynomial() const;
    std::vector<Polynomial> splitCharacteristicPolynomial() const;
    const std::vector<VectorX> eigenVectors() const;
    std::vector<std::pair<double,VectorX>> allEigen() const;
    bool isDiagonalisable() const;
    const Matrix diagonalise() const;
    const Matrix transferMatrix() const;
    void allMatrix(Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C) const;
    void testRegression() const;


};


#endif

