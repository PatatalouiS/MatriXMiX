
#ifndef MATRIXMIX_TXT_H
#define MATRIXMIX_TXT_H

#include "MatrixLibrary.h"


class MatriXMiXTXT
{
    private:
    
    MatrixLibrary lib;
	
	
	void binaryOperation (const char op) const;
	void binaryOperationPow() const;
    void unaryOperation(const short int & op) const;
    void MsgEmptyLib () const;
	
	
    void addMatrixMenu ();
    void showLibrary () const;
    void addition () const;
	void soustraction () const;
	void multiplication () const;
	void division () const;
	void puissance () const;
	void trace() const;
	void determinant() const;
	void inverse() const;
    void gaussReduction() const;
    void dimensionsStudy() const;
    void displayDimensionsStudy(const Matrix * m) const;
    void characteristicPolynomial() const;
    void displayCharacteristicPolynomial(const Matrix * m)const;
    void eigenValVect() const;
    void displayEigenValVect(const Matrix * m) const;
    void studyDiagonalise() const;
    void displayStudyDiagonalise(const Matrix * m) const;
    void studyMatrix() const;
    void displayStudyMatrix(const Matrix * m) const;
    
    

    public:
    
    void mainMenu ();
    
    
};



#endif
