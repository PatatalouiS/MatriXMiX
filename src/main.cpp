
#include <iostream>
#include "Matrix.h"


using namespace std;





int main ( void )
{
   // Exemples d'utilisation //
    
    Matrix a;
    Matrix b (3, 3);
    Matrix c (3, 3, VectorX {1,2,3,4,5,6,7,8,9});
    Matrix d (c);
    cout << a << endl << b << endl << c << endl << d << endl;
    
    b[1][1] = 57;
    c.getVal(6) = 12;
    cout << a << endl << b << endl << c << endl << d << endl;
    
    return 0;
}
