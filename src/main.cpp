
#include <iostream>
#include <math.h>
#include "Matrix.h"
#include "VectorX.h"
#include "MatrixLibrary.h"


using namespace std;





int main ( void )
{
    /*Matrix a; // Constructeur par défaut, 0 lignes, 0 colonnes.
    Matrix c (3,3); // Matrice 3x3 avec seulement des 0
    Matrix d (3,3, Matrix::Z, "Matricetest"); // idem matrice c
    Matrix e (3,3, Matrix::R); // Matrice random de taille 3x3
    Matrix g (3,3, Matrix::I); // Matrice identité de taille 3x3
    Matrix f (3,4,5); // Matrice de taille 3x4 ne contennant que des 5
    Matrix i (3,2, VectorX {1,2,3,4,5,6}); // Matrice 3x2 initialisée avec le VectorX en paramètre
    Matrix j (f); // Constructeur par copie
    
    
    cout << Matrix::ID(20); //Fonction statique qui renvoit l'identité
    
    d.saveMatrix();std::vector<std::string> polonaise(const std::string & chaine);
    a.readMatrix("Matricetest");
    
    cout << a << endl;*/

    vector<string> polo;
    Matrix c;
    c.polonaise("variable=((objet-1)+x*tmp/8)/25-12",polo);

    for (int i=0; i<polo.size();i++){
        cout<<polo[i]<<' ';
    }


    /*Matrix c;
    vector<string> nota =c.decoupe(" variable = ( ( objet - 1 ) + x * tmp / 8 ) / 25 - 12 ");
    for (int i=0; i< nota.size();i++) {
        cout << nota[i] <<"";
    }*/

    return 0;
}


