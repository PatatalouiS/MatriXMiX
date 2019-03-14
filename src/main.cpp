
#include <iostream>
#include "MatriXMiXTXT.h"


using namespace std;


int main ( void )
{

    Matrix a (3,4,5); // Matrice de taille 3x4 ne contennant que des 5

    cout << a << endl;

    std::vector<std::string> tab;
    tab = a.polonaise("a+b");
    cout << "AFFICHAGE" <<  tab[0] << tab[1] << tab[2] << endl;
    a.cleanSaves();


    return 0;
}


