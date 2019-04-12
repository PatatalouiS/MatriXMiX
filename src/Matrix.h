
#ifndef _MATRIX_H
#define _MATRIX_H


#include <vector>
#include <string>
#include "VectorX.h"
#include <string.h>
#include <Dense>

class Matrix
{
private:
    
    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;
    
    
    
private:
    Matrix subMatrix(const unsigned int a, const unsigned int b ) const;
    double determinant(unsigned int dim) const;
    bool isOperator (const std::string & chaine);
    const std::string saveRights(const std::string & filename, const std::string & matrixname);
    Eigen::MatrixXd class2Eigen ();
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
    
    
    //Fonctions de calcul algébrique et opérateur de calculs
    const Matrix operator + (const Matrix & m) const;
    const Matrix operator - (const Matrix & m) const;
    const Matrix operator * (const Matrix & m) const;
    const Matrix operator * (const double & lambda) const;
    const Matrix operator / (const Matrix & m) const;
    const Matrix operator ^ (const int & p) const;
    bool operator == (const Matrix & m) const;
    bool operator != (const Matrix & m) const;
    double traceMatrix() const;
    double determinant() const;
    Matrix coMatrix() const;
    Matrix transposeMatrix() const;
    Matrix inverse() const;
 
    
    //Fonctions diverses et accesseurs
    unsigned int getNbRows() const;
    unsigned int getNbCols() const;
    double& getVal ( const unsigned int indice );
    double getVal ( const unsigned int indice ) const;
    std::vector<double>& operator [] ( const unsigned int indice );
    const std::vector<double>& operator [] ( const unsigned int indice ) const;
    friend std::ostream& operator << ( std::ostream& flux, const Matrix & m );
    bool isSQMatrix() const;
    void saveMatrix();
    void readMatrix(const std::string & matrixname);
    void cleanSaves();
    void testRegression();
    void setMatrixKB();
    void setMatrixRA();
    
    //Fonctions d'étude poussée des matrices et utilisation de la librairie externe eigen3
    std::vector<double> eigenValues();
    Matrix diagonalise ();
    std::vector<VectorX> eigenVectors();
    Matrix transferMatrix();
    std::vector<std::pair<double,VectorX>> allEigen();
    void allMatrix (Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C);
    bool isDiagonalisable();

};


#endif

