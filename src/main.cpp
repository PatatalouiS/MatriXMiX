
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    Matrix a(3,3,{1,2,3,4,5,6,7,8,9});

    a=a.diagonalise();
    cout << a;


    return 0;

}


