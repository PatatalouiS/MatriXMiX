
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
    getchar();
    getchar();
}


// Sous fonctions pour faciliter l'écriture du menu

void MatriXMiXTXT:: MsgEmptyLib () const
{
    cout << "Aucune Matrice n'est rentrée !" << endl;
    cout << "Vous pouvez en ajouter via sur le menu principal " << endl;
    wait();
}


void MatriXMiXTXT:: binaryOperation (const char op) const
{
	string name1;
	string name2;
	
	cout << "Entrez le nom de la Matrice 1 : ";
	cin >> name1;
	const Matrix* op1 = lib.find(name1);
	
    if (op1 == nullptr)
	{
		cerr << "Erreur, Il n'existe pas de matrice nommée " << name1 << "!" << endl;
		wait();
		return;
	}
	
	cout << "Entrez le nom de la Matrice 2 : ";
	cin >> name2;
	const Matrix* op2 = lib.find(name2);
	
    if (op2 == nullptr)
	{
		cerr << "Erreur, Il n'existe pas de matrice nommée " << name2 << "!" << endl;
		wait();
		return;
	}
	
	cout << endl << "Résultat de " << name1 << " " << op << " " << name2 << " est : ";
	cout << endl <<endl;
	
	switch(op)
	{
		case '+' : cout << *op1 + *op2; break;
		case '-' : cout << *op1 - *op2; break;
		case '*' : cout << *op1 * *op2; break;
		case '/' : cout << *op1 / *op2; break;
		default: break;
	}
	wait();
}

void MatriXMiXTXT:: binaryOperationPow() const
{
	string name;
	int pow;

	cout << "Entrez le nom de la Matrice : ";
	cin >> name;

	const Matrix* op = lib.find(name);

    if (op == nullptr)
	{
		cerr << "Erreur, Il n'existe pas de matrice nommée " << name << "!" << endl;
		wait();
		return;
	}	

	cout << "Entrez la puissance : ";
	cin >> pow;

	cout << endl << "Resultat de " << name << " " << '^' << " "<< pow << " est :" << endl << endl;
	cout << ((*op) ^ pow);
	wait();

}

void MatriXMiXTXT:: unaryOperation(const char op) const
{
	string name;

	cout << "Entrez le nom de la matrice : ";
	cin >> name;

	const Matrix* op1 = lib.find(name);

    if (op1 == nullptr)
	{
        cerr << "Erreur, Il n'existe pas de matrice nommée " << name << " !" << endl;
		wait();
		return;
	}

	cout << endl << "Resultat est : " << endl << endl;	

	switch(op)
	{
		case 't' : cout << op1->traceMatrix(); break;
		case 'd' : cout << op1->determinant(); break;
		case 'i' : cout << op1->inverse(); break;
		default: break;
	}
	wait();
}

// Fonctions de menu

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
        cout << "3 - Addition de Matrices (A+B) "<< endl;
		cout << "4 - Soustraction de Matrices (A-B)" << endl;
		cout << "5 - Multiplication de Matrices (A*B)" << endl;
		cout << "6 - Division de Matrices (A/B) " << endl;
		cout << "7 - Puissance d'une Matrice (A^n)" << endl;
		cout << "8 - Trace d'une Matrice" << endl;
		cout << "9 - Determinant d'une Matrice " << endl;
		cout << "10- Inverse d'une Matrice " << endl << endl;
        cout << "0 - Quitter " << endl << endl << "Votre choix : " ;
        cin >> choice;
        
        switch (choice)
        {
            case 1 : addMatrixMenu(); break;
            case 2 : showLibrary(); break;
            case 3 : addition(); break;
			case 4 : soustraction(); break;
			case 5 : multiplication(); break;
			case 6 : division(); break;
			case 7 : puissance(); break;
			case 8 : trace() ; break;
			case 9 : determinant() ; break;
			case 10: inverse() ; break;
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
		string name;
		
		cout << "Rentrez le nom de la matrice : ";
		cin >> name;
		
        if (lib.find(name) != nullptr)
		{
			cout << "Attention, il y a déja une matrice avec le nom " << name << " !" << endl;
			wait();
			return;
		}
		
		Matrix m;
			
        if (choice == 1)
        {
            m.setMatrixRA();
        }
        else
        {
            m.setMatrixKB();
        }
        lib.addMatrix(name, m);
        
        cout << endl << "Ajout effectué : voici votre matrice " << name << " : " << endl << endl;
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
    
    if(lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        lib.print(); 
        wait();
    }
}


void MatriXMiXTXT:: addition() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "===================== ADDITION ====================" << endl;
    cout << "===================================================" << endl << endl;
    
    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
		binaryOperation('+');
	}
}


void MatriXMiXTXT:: soustraction() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "=================== SOUSTRACTION===================" << endl;
	cout << "===================================================" << endl << endl;
	
	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		binaryOperation('-');
	}
}


void MatriXMiXTXT:: multiplication() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "================= MULTIPLICATION ==================" << endl;
	cout << "===================================================" << endl << endl;
	
	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		binaryOperation('*');
	}
}


void MatriXMiXTXT:: division() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "==================== DIVISION =====================" << endl;
	cout << "===================================================" << endl << endl;
	
	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		binaryOperation('/');
	}
}

void MatriXMiXTXT::puissance() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "==================== PUISSANCE ====================" << endl;
	cout << "===================================================" << endl << endl;

	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		binaryOperationPow();
	}
}

void MatriXMiXTXT::trace() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "====================== TRACE ======================" << endl;
	cout << "===================================================" << endl << endl;

	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		unaryOperation('t');
	}
}

void MatriXMiXTXT::determinant() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "=================== DETERMINANT ===================" << endl;
	cout << "===================================================" << endl << endl;

	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		unaryOperation('d');
	}
}

void MatriXMiXTXT::inverse() const
{
	cl();
	cout << "===================================================" << endl;
	cout << "===================== INVERSE =====================" << endl;
	cout << "===================================================" << endl << endl;

	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
		unaryOperation('i');
	}
}


