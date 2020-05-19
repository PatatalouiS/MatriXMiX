#include <iostream>
#include "../maths/MatrixLibrary.h"
#include "../maths/Fraction.h"


static const int EPSILON = 0.000001;


static std::string double2sqrt(const double & d) {

    double res = abs(d);
    std::string s;

    s += "sqrt(";

    if (res < 1) // cas 1/sqrt(x)
        res = 1 / res;

    int n = round(res * res);

    if (res * res < 2.0) {
        std::cout << res * res << std::endl;
    }

    if (abs((res * res) - n) < EPSILON)
        s += std::to_string(n);
    else if (abs((res * res) - n - 1) < EPSILON)
        s += std::to_string(n);
    else if (abs((res * res) - n + 1) < EPSILON)
        s += std::to_string(9);
    else {
        s += "nada";
    }

    s += ")";

    if (abs(d) < 1)
        s = "1/" + s;
    if (d < 0.0)
        s = "-" + s;

    return s;

}


int main ()
{

	std::cout << double2sqrt(0.70710678118) << std::endl;

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
