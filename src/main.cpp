
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    Matrix a(5,5,{3,1,0,0,4,6,9,7,8,9,2,4,5,6,2,4,7,6,3,2,1,4,0,0,2});
    Matrix b(5,5);
    Matrix c(2,2,{3,1,0,0});

    c.valeurspropres();


    return 0;

}


