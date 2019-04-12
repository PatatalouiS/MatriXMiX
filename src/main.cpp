
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
    MatrixLibrary lib;
    vector<string> resultat;
    string expression1("((objet-1)+x*tmp/8)/25-12");

    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{0,0,0,1});
    Matrix res;

    /*bool r;
    r=lib.priorite_sup_egal("-","+");
    if (r){
        cout<<"true";
    }else cout<<"false";*/


    lib.addMatrix("identite",a);
    lib.addMatrix("matriceb",b);
    /*const Matrix* resu; r=lib.priorite_sup_egal("-","+");
    if (r==1){
        cout<<true;
    }else cout<<false;

    resu=lib.find("identite");
    cout<<*resu;
    lib.print();*/

    //cout << "cout avant appel à polonaise " << endl  ;



    //lib.polonaise("variable=((objet-1)+x*tmp/8)/25-1",resultat);

    res=lib.expressionCalcul("identite*matriceb");

    cout<<res;

    /*for (int i=0; i<resultat.size(); i++)
    {
        cout<<resultat[i]<<" ";
    }*/

    return 0;

}


