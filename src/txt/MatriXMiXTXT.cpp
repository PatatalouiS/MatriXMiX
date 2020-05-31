
#include <iostream>
#include "MatriXMiXTXT.h"

using namespace std;


static const double EPSILON = 0.000001;


// Simplifications des appels systeme POSIX
// NON PORTABLE, UNIX UNIQUEMENT

void cl()
{
    int * n = new int;
    *n = system("clear");
    delete n;
}


void wait()
{
    std::cout << "Appuyez sur ENTREE pour continuer..." << std::endl;
    getchar();
    getchar();
}



// Fonctions d'AFFICHAGE

complex<double> MatriXMiXTXT:: checkCast(const complex<double> & c) const
{
    int l;
    double re, im;

    l = -150;
    re = c.real();
    while (l < 151)
    {
        if ( abs(c.real() - l) < EPSILON )
            {
                re = l;
                break;
            }
        l++;
    }

    l = -150;
    im = c.imag();
    while (l < 151)
    {
        if ( abs(c.imag() - l) < EPSILON )
            {
                im = l;
                break;
            }
        l++;
    }

    return (complex<double>(re,im));

}


VectorX MatriXMiXTXT:: checkCast(const VectorX & v) const
{
    VectorX res;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        res.push_back(checkCast(v[i]));
    }
    return res;
}


string MatriXMiXTXT::print(const complex<double> & z) const
{
    ostringstream ss;
    complex<double> c (checkCast(z));
    double re = c.real();
    double im = c.imag();

    if (re > 0.0)
    {
        if (im > 0.0)
            ss << "(" << re << "+" << im << "i)";
        else if (im == 0.0)
            ss << re;
        else
            ss << "(" << re << im << "i)";
    }
    else if (re == 0.0)
    {
        if (im != 0.0)
            ss << im << "i";
        else
            ss << "0";
    }
    else
    {
        if (im > 0.0)
            ss << "(" << re << "+" << im << "i)";
        else if (im == 0.0)
            ss << re;
        else
            ss << "-(" << abs(re) << "+" << abs(im) << "i)";
    }

    return ss.str();
}


std::string MatriXMiXTXT::print(const VectorX & vx) const
{
    std::ostringstream ss;
    VectorX v (checkCast(vx));

    for (unsigned int i = 0; i < vx.size(); i++)
    {
        ss << "{ " << print(v[i]) << " }" << endl;
    }

    return ss.str();
}


string MatriXMiXTXT::print(const Matrix & m) const
{
    ostringstream ss;
    ss << m.checkCast();
    return ss.str();
}





// Sous fonctions pour faciliter l'écriture du menu

void MatriXMiXTXT:: MsgEmptyLib () const
{
    cout << "Aucune Matrice n'a été entrée !" << endl;
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


void MatriXMiXTXT:: unaryOperation(const short int & op) const
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

    cout << endl << "Resultat: " << endl << endl;

	switch(op)
	{
    case 8 : cout << op1->trace() << endl; break;
    case 9 : cout << op1->determinant() << endl; break;
    case 10 : cout << print(op1->inverse()) << endl; break;
    case 11 : cout << print(op1->gaussReduction()) << endl; break;
    case 12 : displayDimensionsStudy(op1,name); break;
    case 13 : displayCharacteristicPolynomial(op1,name); break;
    case 14 : displayEigenValVect(op1); break;
    case 15 : displayStudyDiagonalise(op1); break;
    case 16 : displayLUDecomposition(op1); break;
    case 17 : displayQRHouseholder(op1) ; break;
    case 18 : displayCholesky(op1) ; break;
    case 19 : displayStudyMatrix(op1,name); break;
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

        cout << "1 -  Ajouter une Matrice " << endl;
        cout << "2 -  Afficher les Matrices " << endl;
        cout << "3 -  Addition de Matrices (A+B) "<< endl;
        cout << "4 -  Soustraction de Matrices (A-B)" << endl;
        cout << "5 -  Multiplication de Matrices (A*B)" << endl;
        cout << "6 -  Division de Matrices (A/B) " << endl;
        cout << "7 -  Puissance d'une Matrice (A^n)" << endl;
        cout << "8 -  Trace d'une Matrice" << endl;
        cout << "9 -  Determinant d'une Matrice" << endl;
        cout << "10 - Inverse d'une Matrice" << endl ;
        cout << "11 - Echelonner une Matrice" << endl ;
        cout << "12 - Etudier les dimensions de l'application linéaire associée à une Matrice" << endl ;
        cout << "13 - Pôlynome caractéristique d'une Matrice" << endl ;
        cout << "14 - Valeurs & Vecteurs propres d'une Matrice" << endl ;
        cout << "15 - Diagonalisation" << endl ;
        cout << "16 - Décomposition LU" << endl;
        cout << "17 - Décomposition QR" << endl;
        cout << "18 - Décomposition Cholesky" << endl;
        cout << "19 - Etudier..." << endl ;
        cout << "20 - Calcul d'expression" << endl;
        cout << "\n0 -  Quitter " << endl << endl << "Votre choix : " ;
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
            case 10 : inverse() ; break;
            case 11 : gaussReduction() ; break;
            case 12 : dimensionsStudy(); break;
            case 13 : characteristicPolynomial(); break;
            case 14 : eigenValVect() ; break;
            case 15 : studyDiagonalise() ; break;
            case 16 : luDecomposition(); break;
            case 17 : qrHouseholder(); break;
            case 18 : cholesky(); break;
            case 19 : studyMatrix() ; break;
            case 20 : calculateExpression(); break;
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
      char char_array[1];
      do
      {
          cout << "Entrez le nom de la matrice : ";
  		    cin >> name;

          strcpy(char_array,name.c_str());
          if (char_array[0] >= '0' && char_array[0] <= '9')
          {
              cout << "Le nom de la matrice doit débuter par une lettre (A-Z,a-z)" << endl;
          }
      } while (char_array[0] >= '0' && char_array[0] <= '9');

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


void MatriXMiXTXT:: puissance() const
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


void MatriXMiXTXT:: trace() const
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
        unaryOperation(8);
	}
}


void MatriXMiXTXT:: determinant() const
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
        unaryOperation(9);
	}
}


void MatriXMiXTXT:: inverse() const
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
        unaryOperation(10);
	}
}


void MatriXMiXTXT:: gaussReduction() const
{
  cl();
	cout << "===================================================" << endl;
	cout << "=================== ÉCHELONNAGE ===================" << endl;
	cout << "===================================================" << endl << endl;

	if (lib.isEmpty())
	{
		MsgEmptyLib();
	}
	else
	{
        unaryOperation(11);
	}
}


void MatriXMiXTXT:: dimensionsStudy() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "============== ETUDE DES DIMENSIONS ===============" << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(12);
    }
}


void MatriXMiXTXT:: displayDimensionsStudy(const Matrix * m, const string & name) const
{
   cout << "La dimension de l'image est dim(Im("
        << name << ")) = " << m->dimensionsStudy().first
        << "\nLa dimension du noyau est dim(Ker(" << name
        << ")) = " << m->dimensionsStudy().second << endl << endl << endl;
}


void MatriXMiXTXT:: characteristicPolynomial() const
{
  cl();
  cout << "===================================================" << endl;
  cout << "============ POLYNÔME CARACTÉRISTIQUE =============" << endl;
  cout << "===================================================" << endl << endl;

  if (lib.isEmpty())
  {
      MsgEmptyLib();
  }
  else
  {
      unaryOperation(13);
  }
}


void MatriXMiXTXT:: displayCharacteristicPolynomial(const Matrix * m, const string & name) const
{
    cout << endl << "Polynôme charactéristique développé..." << endl;
    Polynomial p (m->characteristicPolynomial());
    cout << "P" << name << "(X) = " << p.check() << endl << endl;

    vector<Polynomial> v (m->splitCharacteristicPolynomial());
    cout << "Polynôme charactéristique décomposé... (produit de " << v.size() << " polynômes)" << endl;
    cout << "(" << v[0] << ")";
    for (unsigned int i = 1; i < v.size(); i++)
    {
        cout << " * (" << v[i] <<  ")" << endl;
    }

}


void MatriXMiXTXT:: eigenValVect() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "============ VALEURS/VECTEURS PROPRES =============" << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(14);
    }
}


void MatriXMiXTXT:: displayEigenValVect(const Matrix * m) const
{
    vector<pair<complex<double>,VectorX>> tab;
    tab = m->allEigen();

        unsigned long int i, s = tab.size();
        VectorX vect;
        cout << "Valeur propre et vecteur propre associé " << endl << endl;

        for (i = 0; i < s; i++)
        {
            cout << "Valeur propre : " << print(tab[i].first) << endl ;
            cout << "Vecteur propre: " ;
            cout << endl << print(tab[i].second) << endl;
        }
         cout << endl ;

}


void MatriXMiXTXT:: studyDiagonalise() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "================= DIAGONALISATION =================" << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(15);
    }
}


void MatriXMiXTXT:: displayStudyDiagonalise(const Matrix *m) const
{
    std::ostringstream ss;
    if(!(m->isDiagonalisableC()))
    {
        ss << "La matrice n'est pas diagonalisable dans C"
                "\ni.e il n'existe aucune base dans laquelle la matrice étudiée est diagonale"
                << endl << endl << endl;
    }
    else
        {
            Matrix P1(m->getNbRows(),m->getNbCols());
            Matrix D(m->getNbRows(),m->getNbCols());
            Matrix P2(m->getNbRows(),m->getNbCols());
            m->allMatrix(P1,D,P2);
            if (m->isDiagonalisableR())
            {
                ss << "La matrice est diagonalisable dans R "
                        "\nie Il existe une base dans laquelle la matrice est diagonale "
                        << endl << endl;
            }
            else
            {
                ss << "La matrice est diagonalisable dans C "
                        "\nie Il existe une base dans laquelle la matrice est diagonale "
                         << endl << endl;
            }
        ss << "La matrice de passage P vers cette base est: " << endl << print(P1) << endl;
        ss << "La matrice diagonale s'exprime alors comme suit: " << endl << print(D) << endl;
        ss << "La matrice de passage P^-1 vers la base canonique est: " << endl << print(P2) << endl << endl;
    }
    cout << ss.str();
}


void MatriXMiXTXT:: luDecomposition() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "======================= LU ======================== " << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(16);
    }
}


void MatriXMiXTXT:: displayLUDecomposition(const Matrix * m) const {
    if (m->isSQMatrix()
        && m->isSymetric()
        && m->isPositiveDefinite()) {
            cout << "La matrice admet la décomposition LU suivante : " << endl
                << endl << "L = " << endl << m->LUDecomposition().first.checkCast() 
                << endl << "U = " << endl << m->LUDecomposition().second.checkCast() 
                << endl;
        }
    else {

        if (!m->isSQMatrix()) {
            cout << "Cette matrice n'est pas carrée!" << endl;
        }
        if (!m->isSymetric()) {
            cout << "Cette matrice n'est pas symétrique!" << endl;
        }
        if (!m->isPositiveDefinite()) {
            cout << "Cette matrice n'est pas définie positive!" << endl;
        }

        cout << "Elle n'admet pas de décomposition LU..." << endl << endl
            << "RAPPEL : Une matrice A admet une décomposition LU SSI elle est:"
            << endl << "    - carrée" << endl << "    - symétrique" << endl
            << "    - définie positive" << endl << endl << endl;
    }
}


void MatriXMiXTXT:: qrHouseholder() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "======================= QR ======================== " << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(17);
    }
}


void MatriXMiXTXT:: displayQRHouseholder(const Matrix * m) const {
    if (m->getNbRows() >= m->getNbCols()) {
        cout << "La matrice admet la décomposition QR suivante : " << endl
            << endl << "Q = " << endl << m->QR_Householder().first.checkCast()
            << endl << "R = " << endl << m->QR_Householder().second.checkCast() 
            << endl;
        }
    else {

        cout << "Le nombre de colonnes est plus grand que le nombre de lignes..."
            << endl << "RAPPEL : Une matrice A(n lignes, m colonnes) admet une"
            << "décomposition QR SSI n >= m" << endl << endl << endl;
    }
}


void MatriXMiXTXT:: cholesky() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "==================== CHOLESKY ===================== " << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(18);
    }
}


void MatriXMiXTXT:: displayCholesky(const Matrix * m) const {
    if (m->isSQMatrix()
        && m->isSymetric()
        && m->isPositiveDefinite()) {
            cout << "La matrice admet la décomposition de Cholesky suivante : "
                << endl << endl << "C = " << endl << m->cholesky().first.checkCast()
                << endl << "C* = " << endl << m->cholesky().second.checkCast() 
                << endl;
        }
    else {

        if (!m->isSQMatrix()) {
            cout << "Cette matrice n'est pas carrée!" << endl;
        }
        if (!m->isSymetric()) {
            cout << "Cette matrice n'est pas symétrique!" << endl;
        }
        if (!m->isPositiveDefinite()) {
            cout << "Cette matrice n'est pas définie positive!" << endl;
        }

        cout << "Elle n'admet pas de décomposition de Cholesky..." << endl << endl
            << "RAPPEL : Une matrice A admet une décomposition de Cholesky SSI elle est:"
            << endl << "    - carrée" << endl << "    - symétrique" << endl
            << "    - définie positive" << endl << endl << endl;
    }
}


void MatriXMiXTXT:: studyMatrix() const
{
    cl();
    cout << "===================================================" << endl;
    cout << "================== TOUT ETUDIER ===================" << endl;
    cout << "===================================================" << endl << endl;

    if (lib.isEmpty())
    {
        MsgEmptyLib();
    }
    else
    {
        unaryOperation(19);
    }
}


void MatriXMiXTXT:: displayStudyMatrix(const Matrix *m, const string & name) const
{
    cout << "La dimension du noyau dim(Im) = " << m->dimensionsStudy().first <<
            "\nLa dimension de l'image est dim(Ker) = " << m->dimensionsStudy().second << endl << endl << endl << endl;

    displayCharacteristicPolynomial(m,name);
    cout << endl << endl;

    displayEigenValVect(m);
    cout << endl;

    displayStudyDiagonalise(m);

    displayLUDecomposition(m);

    displayQRHouseholder(m);

    displayCholesky(m);
}


void MatriXMiXTXT:: calculateExpression() const {
    cl();
    cout << "===================================================" << endl;
    cout << "=============== CALCUL D'EXPRESSION ===============" << endl;
    cout << "===================================================" << endl << endl;

    std::string expr;

    std::cout << "Saisir l'expression à évaluer " << std::endl;
    std::cin >> expr;
    std::cout << endl << endl << "Résultat... " << endl << endl
            << lib.calculateExpression(expr).checkCast() << endl << endl;

    wait();
}