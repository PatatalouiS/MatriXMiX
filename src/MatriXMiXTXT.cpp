
#include <iostream>
#include "MatriXMiXTXT.h"


using namespace std;

// Simplifications des appells systeme POSIX
// NON PORTABLE, UNIX UNIQUEMENT
void cl()
{
    system("clear");
}


void wait()
{
    std::cout << "Appuyez sur ENTREE pour continuer..." << std::endl;
    system("read -n1 -p '' key");
}


void MatriXMiXTXT:: mainMenu ()
{
    bool quit = false;
    int choice;
    
    do
    {
        cl();
        cout << "===================================================" << endl;
        cout << "==================== MatriXMiX ====================" << endl;
        cout << "===================================================" << endl << endl;
        
        cout << "Saisissez votre choix et pressez ENTREE" << endl << endl;
        
        cout << "1 - Ajouter une Matrice " << endl;
        cout << "2 - Afficher les Matrices " << endl << endl;
        cout << "0 - Quitter " << endl << endl << "Votre choix : " ;
        cin >> choice;
        
        switch (choice)
        {
            case 1 : addMatrixMenu(); break;
            case 2 : showLibrary(); break;
            case 0 : quit = true; break;
            default: break;
        }
    } while (!quit);
    cout << "Quit..." << endl;
}


void MatriXMiXTXT:: addMatrixMenu ()
{
    unsigned int choice;
    
    cl();
    cout << "===================================================" << endl;
    cout << "=================== AJOUT MATRICE =================" << endl;
    cout << "===================================================" << endl;
    cout << endl << "Voulez vous :" << endl << endl;
    cout << "1 : Ajouter une matrice aléatoire" << endl;
    cout << "2 : Saisir une matrice au clavier" << endl << endl;
    cout << "0 : Retour au menu principal" << endl << endl;
        
    cout << "Votre choix : ";
    cin >> choice;
    
    cl();
    cout << "===================================================" << endl;
    cout << "=================== AJOUT MATRICE =================" << endl;
    cout << "===================================================" << endl << endl;
        
    if (choice == 0)
    {
        return;
    }
    else
    {
        Matrix m;
        
        if (choice == 1)
        {
            m.setMatrixRA();
        }
        else
        {
            m.setMatrixKB();
        }
        lib.addMatrix(m);
        
        cout << endl << "Ajout effectué : voici votre matrice " << m.getName() << " : " << endl << endl;
        cout << m << endl;
        wait();
    }
}


void MatriXMiXTXT:: showLibrary () const
{
    cl();
    cout << "===================================================" << endl;
    cout << "================ AFFICHAGE MATRICES ===============" << endl;
    cout << "===================================================" << endl << endl;
    
    if (lib.empty())
    {
        cout << "Aucune Matrice n'est rentrée !" << endl;
        cout << "Vous pouvez en ajouter via sur le menu principal " << endl;;
    }
    else
    {
         lib.print();
    }
    wait();
}




