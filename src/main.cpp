
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

    string chaine;
    chaine="Hana+Tarik+";

    vector<string> tableau;
    tableau=decoupe(chaine);
    cout << tableau[0] <<" " << tableau[1] << " " << tableau[2] << tableau[3] << endl;




    return 0;
}


