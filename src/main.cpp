
#include <iostream>
#include "MatriXMiXTXT.h"

using namespace std;


int main ( void )
{
    //Matrix a; // Constructeur par défaut, 0 lignes, 0 colonnes.
    //Matrix c (3,3); // Matrice 3x3 avec seulement des 0
    //Matrix d (3,3, Matrix::Z, "Matricetest"); // idem matrice c
    Matrix e (3,3, Matrix::R); // Matrice random de taille 3x3

   // Matrix a(3,3,Matrix::I,"A");
  //  a.saveMatrix();

    Matrix resultat;

   // resultat=e.expressionCalcul("A+A");

    cout<<resultat<<endl;


    e.cleanSaves() ;


  /*  MatriXMiXTXT app;
    app.mainMenu();*/

    return 0;
}


