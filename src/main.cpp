
#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "Fraction.h"
#include "VectorX.h"


using namespace std;





int main ( void )
{
    Matrix a; // Constructeur par défaut, 0 lignes, 0 colonnes.
    Matrix c (3, Matrix::Z); // idem que Matrice b
    Matrix d (3, Matrix::I); // Matrice identitée de taille 3x3
    Matrix e (3, Matrix::R); // Matrice random de taille 3x3
    Matrix f (3,4,5); // Matrice de taille 3x4 ne contennant que des 5
    Matrix g (3,4, Matrix::Z); // Matrice nulle de taille 3x4
    Matrix h (3,4, Matrix::R); // Matrice 3x4 random
    Matrix i (3,2, VectorX {1,2,3,4,5,6}); // Matrice 3x2 initialisée avec le VectorX en paramètre
    Matrix j (f); // Constructeur par copie
    
    cout<<a<<endl<<c<<endl<<d<<endl<<e<<endl<<f<<endl
    <<g<<endl<<h<<endl<<i<<endl<<j<<endl;
    
    return 0;
}


