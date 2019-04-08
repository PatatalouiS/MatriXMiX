
#include <iostream>
#include "MatriXMiXTXT.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    /*Matrix a(3,3,{1,2,3,4,5,6,7,8,9});

    a=a.diagonalise();
    cout << a;*/

    /* exemple 1 */
    /*Polynomial dividende(4,{5,1,-2,-3,1});
    Polynomial diviseur(1,{-1,1});
    Polynomial quotient;
    Polynomial reste;
    Polynomial resultat;

    quotient=dividende.division(diviseur,reste);
    cout<<quotient;
    cout<<reste;
    resultat=reste+quotient*diviseur;
    cout<<resultat;*/

    /* exemple 2 */
    /*Polynomial dividende(6,{1,0,1,0,0,0,1});
    Polynomial diviseur(5,{1,2,0,0,0,3});
    Polynomial quotient;
    Polynomial reste;
    Polynomial resultat;

    quotient=dividende.division(diviseur,reste);
    cout<<quotient;
    cout<<reste;
    resultat=reste+quotient*diviseur;
    cout<<resultat;*/

    return 0;

}


