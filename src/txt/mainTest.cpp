#include <iostream>
#include "../maths/MatrixLibrary.h"
#include "../maths/Fraction.h"


int main ()
{
	MatrixLibrary lib;
	Matrix m;
	Polynomial p;
	Fraction f;

	f.regressionTest();
	p.regressionTest();
	m.regressionTest();
	lib.regressionTest();

    return 0;

}
