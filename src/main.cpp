
#include <iostream>
#include "MatriXMiXTXT.h"
#include "VectorX.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    Matrix a(3,3,{1,1,1,1,1,1,1,1,1});

    cout << a << endl;

    a.allEigen();

    if (a.isDiagonalisable())
        cout << "Diagonalisable" << endl;
    else
        cout << "Pas diagonalisable" << endl;

    return 0;

}


