#ifndef _MATRIXMIX_TXT_H_
#define _MATRIXMIX_TXT_H_

#include "MatrixLibrary.h"


class MatriXMiXTXT
{
private:

	MatrixLibrary lib;


	void binaryOperation (const char op) const;
	void binaryOperationPow() const;
	void unaryOperation(const char op) const;
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



public:

	void mainMenu ();


};



#endif
