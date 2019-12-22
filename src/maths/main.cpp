#include <iostream>
#include "MatriXMiXTXT.h"
using namespace std;

int main ()
{

    //Matrix a(2,2,{-1,2,-1,1});
    Matrix a(3,3,{1,2,3,4,5,6,7,8,9});
    cout << "La matrice A: " << endl << a << endl << endl;

    cout << "La matrice A après échelonnage " << endl << a.gaussReduction() << endl << endl;

    /*if (a.isDiagonalisable())
    {
        cout << "La matrice A est diagonalisable" << endl << endl;
        cout << "La matrice de passage vers la base dans laquelle A est diagonalisable est donnée par: "
                << endl << a.transferMatrix() << endl << endl;
        cout << "La matrice diagonale est alors" << endl << a.diagonalise() << endl << endl;
        cout << "La matrice de passage vers la base canonique est" << endl << a.transferMatrix().inverse() << endl;
    } else
        cout << "La matrice A n'est pas diagonalisable" ;*/


    return 0;

}
