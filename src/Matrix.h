
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
    Eigen::MatrixXd class2Eigen();
    Matrix eigen2Class(const Eigen::MatrixXd & m);
    
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
    bool isSQMatrix() const;
    double traceMatrix() const;
    double determinant() const;
    Matrix coMatrix() const;
    Matrix transposeMatrix() const;
    Matrix inverse() const;
    unsigned int rank();
 
    //Fonctions d'étude poussée des matrices et utilisation de la librairie externe eigen3
    std::pair<unsigned int, unsigned int> dimensionsStudy();
    std::vector<double> eigenValues();
    Polynomial characteristicPolynomial();
    std::vector<Polynomial> splitCharacteristicPolynomial();
    std::vector<VectorX> eigenVectors();
    std::vector<std::pair<double,VectorX>> allEigen();
    bool isDiagonalisable();
    Matrix diagonalise();
    Matrix transferMatrix();
    void allMatrix(Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C);
    Matrix gaussReduction();
    void testRegression();
    Matrix solve();



};


#endif

