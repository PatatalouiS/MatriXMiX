
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"

using namespace std;


int main (void)
{
    Polynomial p1(1, {1, 1});
    Polynomial p2(1, {-1, 1});
    Polynomial p3(4);

    unsigned int a;
    double b,c;

    cout << "p1=" << p1;
    cout << "p2=" << p2;
    cout << endl;

    p3 = p1 * p2;
    cout << "p1*p2=" << p3 << endl;

    p3.equation2degre(a,b,c);
    cout << "p3 admet " << a << " solutions: " << b << "  ET  " << c << endl;

    return 0;

}


