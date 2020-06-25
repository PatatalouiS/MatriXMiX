#include <iostream>
#include "../maths/Fraction.h"
#include "../maths/MatrixLibrary.h"


int main ()
{
	MatrixLibrary lib;
	Matrix m;
	Polynomial p;
	Fraction f;

	p.regressionTest();
	f.regressionTest();
	m.regressionTest();
	lib.regressionTest();

    return 0;

}
