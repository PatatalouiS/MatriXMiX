
#include <iostream>
#include "MatriXMiXTXT.h"
#include "VectorX.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    Matrix a(3,3,{1,2,3,4,5,6,7,8,9});

    VectorX v;
    v.push_back(0.70710);
    v.push_back(0.70710);
    cout << v[0] << " " << v[1] << endl;
    cout << v[0] << " " << v[1] << endl;




    return 0;

}


