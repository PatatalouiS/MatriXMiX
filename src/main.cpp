
#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "SQMatrix.h"
#include "Fraction.h"
#include "VectorX.h"


using namespace std;





int main ( void )
{
    SQMatrix sq (3, VectorX{1,2,3,4,5,6,7,8,9});
    Matrix sk (3, 2, VectorX {1,2,3,4,5,6});
    
    cout << sk + sq;
    
    
    
    Matrix a; // Constructeur par défaut, 0 lignes, 0 colonnes.
    Matrix b (3); // Matrice carée nulle de taille 3x3
    Matrix c (3, ZERO); // idem que Matrice b
    Matrix d (3, IDENTITY); // Matrice identitée de taille 3x3
    Matrix e (3, RANDOM); // Matrice random de taille 3x3
    Matrix f (3,4,5); // Matrice de taille 3x4 ne contennant que des 5
    Matrix g (3,4, ZERO); // Matrice nulle de taille 3x4
    Matrix h (3,4, RANDOM); // Matrice 3x4 random
    Matrix i (3,2, VectorX {1,2,3,4,5,6}); // Matrice 3x2 initialisée avec le VectorX en paramètre
    Matrix j (f); // Constructeur par copie
    
    
    
    cout<<a<<endl<<b<<endl<<c<<endl<<d<<endl<<e<<endl<<f<<endl
    <<g<<endl<<h<<endl<<i<<endl<<j<<endl;
    
    return 0;
}


