
#ifndef _MATRIX_H
#define _MATRIX_H


#include <vector>
#include "VectorX.h"





class Matrix
{
    protected:

    unsigned int rows;
    unsigned int cols;
    std::vector<std::vector<double>> tab;
    
    Matrix subMatrix(const unsigned int a, const unsigned int b ) const;
    double determinant(unsigned int dim) const;

    public:
    
    // type énuméré pour l'initialisation
    enum initMatrix { Z, I, R };
    
   // Constructeurs et Destructeurs
    Matrix ();
    Matrix ( const unsigned int rows, const unsigned int cols, const double value );
    Matrix ( const unsigned int rows, const unsigned int cols, const enum initMatrix& type = Z );
    Matrix ( const unsigned int rows, const unsigned int cols, const VectorX& values );
    Matrix ( const Matrix & m );
    ~Matrix ();

    //Fonctions de calcul algébrique et opérateur de calculs
    const Matrix operator + (const Matrix & m) const;
    const Matrix operator - (const Matrix & m) const;
    const Matrix operator * (const Matrix & m) const;
    const Matrix operator * (const double & lambda) const;
    bool operator == (const Matrix & m) const;
    bool operator != (const Matrix & m) const;
    double traceMatrix() const;
    double determinant() const;
    Matrix coMatrix() const;
    Matrix transposeMatrix() const;
    Matrix inverse() const;
    const Matrix operator / (const Matrix & m) const;
    const Matrix operator ^ (const int & p) const;
    
    //Fonctions diverses et accesseurs
    double& getVal ( const unsigned int indice );
    double getVal ( const unsigned int indice ) const;
    std::vector<double>& operator [] ( const unsigned int indice );
    const std::vector<double>& operator [] ( const unsigned int indice ) const;
    friend std::ostream& operator << ( std::ostream& flux, const Matrix & m );
    unsigned int getNbRows() const;
    unsigned int getNbCols() const;
    bool IsSQMatrix() const;
    void saveMatrix(const std::string & filename) const;
    void readMatrix(const std::string & filename);
};


#endif
