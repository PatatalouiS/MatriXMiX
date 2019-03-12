
#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "Fraction.h"


using namespace std;





int main ( void )
{
   // Exemples d'utilisation //


    Matrix a (4, 4, VectorX {1,2,3,4,5,6,7,8,1,10,11,12,13,14,15,0},"A");
    Matrix b (4, 4, VectorX {1,2,3,4,5,6,7,8,1,10,11,12,13,14,15,0},"B");
    Matrix d (4, 4, VectorX {1,2,3,4,5,6,7,8,1,10,11,12,13,14,15,0},"MatriceD");
    Matrix c;

    a.saveMatrix();d.saveMatrix();
    c=c.calculate("+","A","MatriceD");
    cout << a << endl << b << endl << c << endl ;


    return 0;
}


