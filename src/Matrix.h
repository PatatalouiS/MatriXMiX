
#ifndef _MATRIX_H
#define _MATRIX_H


#include <vector>
#include <string>
#include "VectorX.h"
#include <string.h>


const std::string NONAME = "";


class Matrix
{
private:
    
    unsigned int rows;
    unsigned int cols;
    std::string name;
    std::vector<std::vector<double>> tab;
    
    
    
private:
    Matrix subMatrix(const unsigned int a, const unsigned int b ) const;
    double determinant(unsigned int dim) const;
    bool isOperator (const std::string & chaine);
    std::vector<std::string> decoupe (const std::string & expression);
    Matrix calculate (const std::string & op, const std::string & a, const std::string & b);
    const std::string saveRights(const std::string & filename, const std::string & matrixname);
    
public:
    
    // Fonction statique, renvoie, la matrice identité demandée
    static Matrix ID ( const unsigned int size );
    
    
    // type énuméré pour l'initialisation
    enum initMatrix { Z, I, R };
    
    // Constructeurs et Destructeurs
    Matrix ( const std::string& name = NONAME);
    Matrix ( const unsigned int rows, const unsigned int cols, const double value, const std::string& name = NONAME );
    Matrix ( const unsigned int rows, const unsigned int cols, const enum initMatrix& type = Z, const std::string& name = NONAME );
    Matrix ( const unsigned int rows, const unsigned int cols, const VectorX& values, const std::string& name = NONAME  );
    Matrix ( const Matrix & m, const std::string& name = NONAME );
    
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
    std::string getName() const;
    double& getVal ( const unsigned int indice );
    double getVal ( const unsigned int indice ) const;
    std::vector<double>& operator [] ( const unsigned int indice );
    const std::vector<double>& operator [] ( const unsigned int indice ) const;
    friend std::ostream& operator << ( std::ostream& flux, const Matrix & m );
    bool IsSQMatrix() const;
    void saveMatrix();
    void readMatrix(const std::string & matrixname);
    void cleanSaves();



};


#endif

