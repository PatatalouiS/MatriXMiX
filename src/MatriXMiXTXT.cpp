
#include <iostream>
#include "MatriXMiXTXT.h"


using namespace std;

// Simplifications des appels systeme POSIX
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






void MatriXMiXTXT:: MsgEmptyLib () const
{
    cout << "Aucune Matrice n'est rentrée !" << endl;
    cout << "Vous pouvez en ajouter via sur le menu principal " << endl;
    wait();
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
        cout << "2 - Afficher les Matrices " << endl;
        cout << "3 - Addition de Matrices (A+B) "<< endl << endl;
        cout << "0 - Quitter " << endl << endl << "Votre choix : " ;
        cin >> choice;
        
        switch (choice)
        {
            case 1 : addMatrixMenu(); break;
            case 2 : showLibrary(); break;
            case 3 : addition(); break;
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
    
    if(lib.empty())
    {
        MsgEmptyLib();
    }
    else
    {
        lib.print();
        wait();
    }
}


void MatriXMiXTXT:: addition()
{
    cl();
    cout << "===================================================" << endl;
    cout << "===================== ADDITION ====================" << endl;
    cout << "===================================================" << endl << endl;
    
    if (lib.empty())
    {
        MsgEmptyLib();
    }
    else
    {
        string name1;
        string name2;
        
        cout << "Entrez le nom de la Matrice 1 : ";
        cin >> name1;
        const Matrix* op1 = lib.search(name1);
        
        if (op1 == NULL)
        {
            cerr << "Erreur, Il n'existe pas de matrice nommée " << name1 << "!" << endl;
            wait();
            return;
        }
        
        cout << "Entrez le nom de la Matrice 2 : ";
        cin >> name2;
        const Matrix* op2 = lib.search(name2);
        
        if (op2 == NULL)
        {
            cerr << "Erreur, Il n'existe pas de matrice nommée " << name2 << "!" << endl;
            wait();
            return;
        }
        
        cout << endl << "Résultat de " << name1 << " + " << name2 << " est : " << endl <<endl;
        cout << *op1 + *op2 << endl;
        wait();
    }
}



