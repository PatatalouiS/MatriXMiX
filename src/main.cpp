
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"

using namespace std;


int main ( void )
{
    /*MatriXMiXTXT app;
    app.mainMenu();*/

    Polynomial p1(1,{1,1});
    Polynomial p2(1,{-1,1});
    Polynomial resultat;
    resultat=p1*p2;
    cout << resultat;

    return 0;
}


