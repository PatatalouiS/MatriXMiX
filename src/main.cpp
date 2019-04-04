
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"

using namespace std;


int main (void)
{
    Polynomial p1(5, {-5,1,0,3,0,1});
    Polynomial p2(1, {0, 1});
    Polynomial p3;
    Polynomial p4;

    unsigned int a;
    double b,c;

    cout << "p1 = " << p1;
    cout << "p2 = " << p2;
    cout << endl;

    p3 = p1 * p2;
    cout << "p1 * p2 = " << p3 << endl;



    return 0;

}


