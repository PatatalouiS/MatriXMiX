
#include <iostream>
#include "MatriXMiXTXT.h"


using namespace std;


int main ( void )
{

    Matrix a (3,4,5); // Matrice de taille 3x4 ne contennant que des 5

    a.testRegression();


    a.cleanSaves();


    return 0;
}


