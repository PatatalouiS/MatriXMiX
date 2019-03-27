
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"

using namespace std;


int main (void)
{
    Polynomial p1(2,{1,-2,1});
    Polynomial p2(2,{1,-2,1});
    Polynomial p3(4);

    p1+p2;
    cout << p3;

}


