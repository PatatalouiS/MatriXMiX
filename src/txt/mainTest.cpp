#include <iostream>
#include "../maths/MatrixLibrary.h"
#include "../maths/Fraction.h"


static const int EPSILON = 0.000001;



int main ()
{
    
    double temps;
    clock_t t1 = clock(), t2;


    Matrix m;
    Matrix b;
    Matrix x;

    unsigned int i = 0, nb_tests = 1000, nb_corrects = 0;

    while(i < nb_tests) {
        m = Matrix(100,100,Matrix::R);
        b = Matrix(100,1,Matrix::R);
        x = m.solveAx(b);
        if (m * x != b)
            std::cout << "ERROR" << std::endl << std::endl
                       << ((m * x) - b).transposeMatrix().checkCast()  << std::endl << std::endl;
        else
           nb_corrects++;
    
        i++;
    }

    std::cout << std::endl << std::endl << (nb_corrects*100)/nb_tests 
                << " % de tests validés" << std::endl;


    t2 = clock();
    temps = (double)(t2-t1)/CLOCKS_PER_SEC;

    std::cout << "Temps d'exécution : " << temps << std::endl; 

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
