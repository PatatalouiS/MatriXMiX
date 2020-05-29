#include <iostream>
#include "../maths/MatrixLibrary.h"
#include "../maths/Fraction.h"


static const int EPSILON = 0.000001;



int main ()
{
   
    Matrix m;                

    for (unsigned long int i = 0; i < ULONG_MAX; i++) {
        m = Matrix (10,10,Matrix::R);
        if (m == m.transposeMatrix() && m.isPositiveDefinite()) {
            std::cout << i << std::endl;
            std::pair<Matrix,Matrix> qr (m.choleskyDecomposition());
            if (m != (qr.first * qr.second)) {
            std::cout << "ERROR " << std::endl << m
                        << std::endl << std::endl;
        }
        }
        
            
    }


	//std::cout << double2sqrt(0.70710678118) << std::endl;

    /*Fraction f(0.79012187654);
    double t = 9/8;
    Fraction temp(t);
    double d(0.6666666666);
    Fraction res(d);


    std::cout << std::endl;
    std::cout << "Résultat attendu : " << f << std::endl;
    std::cout << "Résultat obtenu : " << res << std::endl;//(f.double2sqrt(d)) << std::endl;
    //std::cout << std::endl << sqrt((f.double2sqrt(d).getNumerator())) /  sqrt((f.double2sqrt(d).getDenominator())) << std::endl;
    */





	/*MatrixLibrary lib;
	Matrix m;
	Polynomial p;
	Fraction f;


	p.regressionTest();
	f.regressionTest();
	m.regressionTest();
	lib.regressionTest();*/

    return 0;

}
