
#include <iostream>
#include "MatriXMiXTXT.h"

using namespace std;


void MatriXMiXTXT:: show () const
{
    system("clear");
    cout << "===============================" << endl;
    cout << "=========== MatriXMiX =========" << endl;
    cout << "===============================" << endl << endl;
    
    cout << "Sélectionner votre choix et faire ENTRER" << endl << endl;
    
    cout << "1 - Ajouter une Matrice " << endl << endl;
}


void MatriXMiXTXT:: loop ()
{
    bool quit = false;
    int choice;
    
    do
    {
        show();
        cin >> choice;
        
        switch (choice)
        {
            case 1 : break;
            case 0 : quit = true; break;
            default: break;
        }
    } while (!quit);
}





