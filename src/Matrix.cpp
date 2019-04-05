
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include <stack>
#include <utility>
#include <eigen3/Eigen/Dense>
#include "Matrix.h"


using namespace std;

const string PATH = "../../data/sauvegarde.txt";



// ********* CONSTRUCTEURS / DESTRUCTEUR *********



Matrix:: Matrix () : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const double value) :
        tab (vector<vector<double>>(rows,vector<double> (cols, value)))
{
    this->rows = rows;
    this->cols = cols;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const enum initMatrix& type) :
        tab (vector<vector<double>> (rows, vector<double> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;

    switch (type)
    {
        case Z: break;
        case R:
        {
            srand(time(NULL));

            for (auto& i : tab)
            {
                for (auto& j : i)
                {
                    j = (rand()% 20000) + 10000;
                }
            }
            break;
        }
        case I:
        {
            if (cols != rows)
            {
                cerr << "Initialisatin d'une matrice identité impossible (rows != cols)" << endl;
                exit(EXIT_FAILURE);
            }

            for (unsigned int i = 0; i < rows; ++i)
            {
                tab[i][i] = 1;
            }
            break;
        }
        default: break;
    }
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values)
{
    if (values.size() != rows * cols)
    {
        cout << "Erreur : la dimension du vecteur passé en paramètre ne correspond pas aux dimensions de la matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    this->cols = cols;
    this->rows = rows;

    vector<double> temp;

    for ( unsigned int i = 0; i < rows; ++i )
    {
        temp.clear();

        for ( unsigned int j = 0; j < cols; ++j )
        {
            temp.push_back(values[i*cols+j]);
        }
        tab.push_back(temp);
    }
}


Matrix:: Matrix (const Matrix & m) : tab ( vector<vector<double>> (m.tab))
{
    cols = m.cols;
    rows = m.rows;
}


Matrix:: ~Matrix ()
{
}



// ******** FONCTIONS STATIQUES *********


Matrix Matrix:: ID (const unsigned int size)
{
    return Matrix(size, size, Matrix::I);
}







// ******* FONCTIONS DE CALCUL ALGEBRIQUE ET OPERATEURS DE CALCUL ********


const Matrix Matrix:: operator+ (const Matrix & m) const
{
    if ( (rows!=m.rows) || (cols!=m.cols) )
    {
        cout << "Addition impossible!" << endl;
        exit (EXIT_FAILURE);
    }

    Matrix copie(*this);

    for (unsigned int i=0; i< rows; i++)
    {
        for (unsigned int j=0; j< cols; j++)
        {
            copie[i][j]=copie[i][j]+m[i][j];
        }
    }
    return copie;
}


const Matrix Matrix:: operator- (const Matrix & m) const
{
    if ((rows!=m.rows) || (cols!=m.cols))
    {
        cout << "Soustraction impossible!" << endl;
        exit (EXIT_FAILURE);
    }

    Matrix copie(*this);

    for (unsigned int i=0; i<m.rows; i++)
    {
        for (unsigned int j=0; j<m.cols; j++)
        {
            copie[i][j]=copie[i][j]-m[i][j];
        }
    }
    return copie;
}


const Matrix Matrix:: operator * (const Matrix & m) const
{
    if (cols != m.rows)
    {
        cout << "Multiplication impossible!" << endl << "A * B->Le nombre de ligne de A = nombre de colonne de B!" << endl;
        exit ( EXIT_FAILURE );
    }

    double s;
    Matrix temp(rows, m.cols, Matrix::Z);

    for (unsigned int i=0; i<rows; i++)
    {
        for (unsigned int j=0; j<m.cols; j++)
        {
            s=0;
            for (unsigned int k=0; k<cols; k++)
            {
                s+=tab[i][k]*(m[k][j]);
            }
            temp[i][j]=s;
        }
    }
    return temp;
}


const Matrix Matrix:: operator * (const double & lambda) const
{
    Matrix copie(*this);

    for (unsigned int i=0; i < rows; i++)
    {
        for (unsigned int j=0; j < cols; j++)
        {
            copie[i][j]=lambda*copie[i][j];
        }
    }
    return copie;
}


const Matrix Matrix:: operator / (const Matrix & m) const
{
    if ( !m.IsSQMatrix() )
    {
        cerr << "La division est impossible, le diviseur n'est pas une matrice carrée !" << endl;
        exit (EXIT_FAILURE);
    }
    if ( m.determinant()==0 )
    {
        cerr << "division impossible, la metrice diviseur n'est pas inversible !" << endl;
        exit(EXIT_FAILURE);
    }
    return (*this) * m.inverse();
}


const Matrix Matrix:: operator ^ (const int & p) const
{
    if ( p < -1 )
    {
        cerr << "Erreur, la puissance demandée est invalide ! " << endl;
        exit(EXIT_FAILURE);
    }

    if ( !IsSQMatrix() )
    {
        cerr << "Erreur, la matrice n'est pas carrée ! " << endl;
        exit(EXIT_FAILURE);
    }

    if ( p == 0 )
    {
        return Matrix (rows, I);
    }

    if ( p == -1 )
    {
        return inverse();
    }

    Matrix temp (*this);
    Matrix temp2 (*this);

    for ( int i = 1; i < p; ++i )
    {
        temp = temp * temp2;
    }
    return temp;
}


bool Matrix:: operator == (const Matrix & m ) const
{
    if ((m.cols == cols) && (m.rows == rows))
    {
        for (unsigned int i = 0; i < rows; i++)
        {
            for (unsigned int j = 0; j < cols; j++)
            {
                if (tab[i][j] != m.tab[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}


bool Matrix::operator != (const Matrix & m) const
{
    return !((*this) == m);
}


double Matrix:: traceMatrix() const
{
    if ( !IsSQMatrix() )
    {
        cerr << "Calcul de la trace impossible, la matrice n'est pas carrée" << endl;
        exit (EXIT_FAILURE);
    }

    double s = 0;

    for ( unsigned int i=0; i<rows; i++)
    {
        s += tab[i][i];
    }
    return s;
}


double Matrix:: determinant() const
{
    if ( !IsSQMatrix() )
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        exit (EXIT_FAILURE);
    }
    return determinant(rows);
}


Matrix Matrix::coMatrix() const
{
    if ( !IsSQMatrix() )
    {
        cerr << "Calcul de la comatrice impossible, la matrice n'est pas carrée" << endl;
        exit (EXIT_FAILURE);
    }


    Matrix com(rows,cols);
    Matrix sub(rows - 1, cols-1);

    for(unsigned int i = 0; i < rows; i++)
    {
        for(unsigned int j = 0; j < cols; j++)
        {
            sub=subMatrix(i,j);
            com[i][j]=pow(-1,i+j)*sub.determinant();
        }
    }
    return com;
}


Matrix Matrix:: transposeMatrix() const
{
    Matrix copie(*this);

    for (unsigned int i=0; i<copie.rows; i++)
    {
        for (unsigned int j=0; j<copie.cols; j++)
        {
            copie[i][j]=tab[j][i];
        }
    }
    return copie;
}


Matrix Matrix:: inverse() const
{
    if ( !IsSQMatrix() )
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        exit (EXIT_FAILURE);
    }

    if (determinant()==0)
    {
        cerr << "Le déterminant est nul, la matrice n'est donc pas inversible!" << endl;
        exit(EXIT_FAILURE);
    }

    Matrix temp(rows,cols), inverse(rows,cols);
    temp=(*this).coMatrix();
    temp=temp.transposeMatrix();
    inverse=temp*(1/determinant());
    return inverse;
}







// ********   FONCTIONS PRIVEES   ***********


Matrix Matrix :: subMatrix(const unsigned int a, const unsigned int b) const
{
    unsigned int ii = 0, jj = 0;
    unsigned int r = rows;
    unsigned int c = cols;

    Matrix sub(r-1,c-1);

    for(unsigned int i=0; i<r; i++)
    {
        jj=0;
        if(i!=a)
        {
            for (unsigned int j=0; j<c; j++)
            {
                if (j!=b)
                {
                    sub[ii][jj]=tab[i][j];
                    jj++;
                }
            }
            ii++;
        }
    }
    return sub;
}


double Matrix:: determinant(unsigned int dim) const
{
    Matrix submatrix (dim,dim);
    double det = 0;
    int subi = 0;
    int subj = 0;

    if ( dim == 1 )
    {
        return tab[0][0];
    }

    if (dim == 2)
    {
        return ((tab[0][0] * tab[1][1]) - (tab[1][0] * tab[0][1]));
    }

    for ( unsigned int x = 0; x < dim; x++)
    {
        subi = 0;
        for (unsigned int i = 1; i < dim; i++)
        {
            subj = 0;
            for (unsigned int j = 0; j < dim; j++)
            {
                if (j != x)
                {
                    submatrix[subi][subj] = tab[i][j];
                    subj++;
                }
            }
            subi++;
        }
        det = det + (pow(-1, x) * tab[0][x] * submatrix.determinant(dim - 1));
    }
    return det;
}


bool Matrix:: isOperator (const string & chaine)
{
    return ( (chaine == "+")
             ||  (chaine == "-")
             ||  (chaine == "/")
             || (chaine == "^")
             || (chaine == "*"));
}


vector<string> Matrix:: decoupe (const string & expression)
{
    unsigned int i,taille =expression.length();
    vector<string> tab;
    string c, temp;
    temp="";

    for (i=0; i<taille; i++)
    {
        c=expression[i];

        if((isOperator(c)) || (c == ")") || (c == "(") || (c == "=") )
        {
            if (temp.length()!=0) tab.push_back(temp);
            tab.push_back(c);
            temp="";
        }
        else if (!c.empty())
        {
            temp+=c;
        }

    }
    tab.push_back(temp);

    return tab;
}


Matrix Matrix:: calculate (const string & op, const string & a, const string & b)
{
    Matrix m_a;
    Matrix m_b;
    m_a.readMatrix(a);
    m_b.readMatrix(b);

    if(op=="+")
        return m_a+m_b;

    if(op=="-")
        return m_a-m_b;

    if(op=="*")
        return m_a*m_b;

    if(op=="/")
        return m_a/m_b;

}


const string Matrix:: saveRights(const string & filename, const string & matrixname)
{
    ifstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
        exit(EXIT_FAILURE);
    }

    string first_string, stringpos;

    file >> first_string;

    while(!file.eof())
    {
        file >> stringpos;
        if(stringpos==matrixname)
            return string("used");
    }

    return first_string;

}






// *********   FONCTIONS DIVERSES ET ACCESSEURS    *********


unsigned int Matrix:: getNbRows() const
{
    return rows;
}


unsigned int Matrix:: getNbCols() const
{
    return cols;
}


double& Matrix:: getVal ( const unsigned int indice )
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    return tab[indice/rows][indice%rows]; 
}


double Matrix:: getVal ( const unsigned int indice ) const
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    return tab[indice/rows][indice%rows];
}


vector<double>&  Matrix:: operator [] ( const unsigned int indice )
{
    if ( indice >= rows)
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }
    return tab[indice];
}


const std::vector<double>& Matrix:: operator [] ( const unsigned int indice ) const
{
    if ( indice >= rows)
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }
    return tab[indice];
}


ostream& operator << ( ostream& flux, const Matrix & m )
{
    for ( auto i : m.tab )
    {
        for ( auto j : i )
        {
            if((int)(j*1000000)==0)
            {
                flux << "0" << "  ";
            }
            else
            {
                flux << j << "  ";
            }
        }
        flux << endl;
    }
    return flux;
}


bool Matrix:: IsSQMatrix() const
{
    return rows==cols;
}



/*void Matrix:: saveMatrix ()
{

    string matrixname(this->name);

    string filename (PATH);
    ofstream file (filename.c_str(), ios::app);

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
        exit(EXIT_FAILURE);
    }

    string testRights;
    testRights=saveRights(filename,matrixname);

    if (testRights.empty())
    {
        file << "Matrix" << endl;

    }
    else if (testRights=="used")
    {
        cout << "Une matrice du même nom a déjà été sauvegardée"
                "\nVeuillez sélectionner un autre nom" << endl;
        exit(EXIT_FAILURE);
    }
    else if(testRights!="Matrix")
    {
        cout << endl << "Erreur! Modification du fichier 'sauvegarde.txt' " << endl;
        // MAXIME GESTION ERREUR
        exit(EXIT_FAILURE);
    }

    file << endl << matrixname << endl;
    file << getNbRows() << " " << getNbCols() << endl;

    for (unsigned int i = 0; i < getNbRows(); i++)
    {
        for (unsigned int j = 0; j < getNbCols(); j++)
        {

            file << tab[i][j] << " ";
        }
        file << endl;
    }

    cout << "La sauvegarde de la matrice " << filename << " est réussie" << endl << endl;

    file.close();

}*/



void Matrix:: readMatrix(const string & matrixname)
{
    string filename(PATH);
    ifstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
        exit(EXIT_FAILURE);
    }

    string testfile;
    file >> testfile ;

    if( testfile == "Matrix")
    {
        while(!file.eof() && testfile!=matrixname)
        {
            file >> testfile;
        }
        if (file.eof())
        {
            cout << "Problème avec " << matrixname << endl;
            cout << "Cette matrice n'a pas été sauvegardée dans 'sauvegarde.txt' " << endl;
            exit(EXIT_FAILURE);
        }

        file >> rows >> cols;

        tab = vector<vector<double>> (rows, vector<double> (cols, 0));

        for (unsigned int i = 0; i < getNbRows(); i++)
        {
            for (unsigned int j = 0; j < getNbCols(); j++)
            {
                file >> tab[i][j];
            }

        }

        file.close();
        cout << "ouverture réussie" << endl << endl;
    }
    else
    {
        cout << "Erreur" << endl ;
        // exception QT Maxime
    }
}


void Matrix:: cleanSaves()
{
    string filename(PATH);
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
        exit(EXIT_FAILURE);
    }

    file.close();
    cout << "!!!!!! Fichier de sauvegarde nettoyé" << endl << endl;

}


void Matrix::testRegression()
{
    cout << endl << endl << "****** DEBUT DU TEST DE REGRESSION ******" << endl << endl << endl;

    double tra, det ;

    Matrix a(5, 5, {-19,-4,-12,17,4,19,-14,-5,-3,18,-4,-1,-13,0,19,16,5,-25,-22,-23,-9,-9,22,-9,21});
    Matrix b(5, 5, {-13,-24,13,-23,-5,5,12,-24,1,-18,21,-2,-21,-5,-4,-15,13,-11,14,8,12,5,8,-24,-2});
    Matrix c(4, 5, {6,2,0,0,-14,21,-6,21,-16,19,-25,8,-24,-1,-12,15,-6,3,-17,21});
    Matrix d(4, 5, {7,7,14,-13,-12,-7,-10,4,-2,-9,-7,-17,-13,-5,-6,5,19,-15,-3,-21});
    Matrix e(5, 4, {24,-7,15,5,10,-24,-2,-3,-9,-19,5,-9,-5,-22,20,18,-21,18,22,-24});
    Matrix f(5, 5, {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25});
    Matrix g(3, 3, {1,2,3,4,5,6,7,8,0});

    Matrix r1(5, 5, {-32,-28,1,-6,-1,24,-2,-29,-2,0,17,-3,-34,-5,15,1,18,-36,-8,-15,3,-4,30,-33,19});
    Matrix r2(4, 5, {13,9,14,-13,-26,14,-16,25,-18,10,-32,-9,-37,-6,-18,20,13,-12,-20,0});
    Matrix r3(5, 5, {-6,20,-25,40,9,14,-26,19,-4,36,-25,1,8,5,23,31,-8,-14,-36,-31,-21,-14,14,15,23});
    Matrix r4(4, 4, {458,-342,-222,360,-64,292,530,-810,-47,245,-795,337,-83,734,374,-744});
    Matrix r5(3, 3, {-16,8,-1,14,-7,2,-1,2,-1});
    Matrix r6(5, 5, {-16687473,-2859275,4429957,38295027,6405675,11243373,2777717,844201,-31171603,-3135973,-12584028,-3513568,10329116,6874376,20116276,24146480,10255020,-32022704,-24798036,-33093968,-8375425,-5884917,24096783,-17068165,33210649});
    Matrix r7(3, 3, {1,0,0,0,1,0,0,0,1});

    Matrix x(3, 3);
    Matrix y(4, 4);
    Matrix z(5, 5);

    cout << "Matrice A =" << endl << a << endl;
    cout << "Matrice B =" << endl << b << endl;
    cout << "Matrice C =" << endl << c << endl;
    cout << "Matrice D =" << endl << d << endl;
    cout << "Matrice E =" << endl << e << endl;
    cout << "Matrice F =" << endl << f << endl;
    cout << "Matrice G =" << endl << g << endl;


    cout << "! Addition de 2 matrices carrées: 5*5 + 5*5" << endl;
    if ( (a.getNbRows()==b.getNbRows()) && (a.getNbCols()==b.getNbCols()) )
    {
        z = a + b;
        cout << "Résultat attendu: A+B =" << endl << r1 << endl;
        cout << "Résultat produit par l'application: A+B =" << endl << z ;
        if(r1 == z)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl ;
        cout << endl ;
    } else
    {
        cout << "Matrices A et B de tailles différentes"
                "\nAddition impossible!" << endl;
    }

    cout << "! Addition de 2 matrices non carrées: 4*5 + 4*5" << endl;
    if ( (c.getNbRows()==d.getNbRows()) && (c.getNbCols()==d.getNbCols()) )
    {
        z = c + d;
        cout << "Résultat attendu: C+D =" << endl << r2 << endl;
        cout << "Résultat produit par l'application: A+C =" << endl << z ;
        if(r2 == z)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl ;
        cout << endl ;
    } else
    {
        cout << "Matrices C et D de tailles différentes"
                "\nAddition impossible! " << endl;
    }

    cout << "! Soustraction de matrices non carrées: 4*5 - 4*5" << endl;
    if ( (a.getNbRows()==b.getNbRows()) && (a.getNbCols()==b.getNbCols()) )
    {
        z = a - b;
        cout << "Résultat attendu: A-B =" << endl << r3 << endl;
        cout << "Résultat produit par l'application: A-B =" << endl << z ;
        if(r3 == z)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl ;
        cout << endl ;
    } else
    {
        cout << "Matrices A et B de tailles différentes"
                "\nSoustraction impossible! " << endl;
    }

    cout << "! Multiplication de 2 matrices: 4*5 * 5*4" << endl;
    if (b.getNbRows()==a.getNbCols())
    {
        y = c * e;
        cout << "Résultat attendu: C*E =" << endl << r4 << endl;
        cout << "Résultat produit par l'application: C*E =" << endl << y ;
        if(r4 == y)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl ;
        cout << endl ;
    } else {
        cout << "Matrices C et E de tailles incompatibles"
                "\nMultiplication impossible!" << endl;
    }

    cout << "! Calcul de trace" << endl;
    if (a.getNbRows()==a.getNbCols())
    {
        tra = a.traceMatrix();
        cout << "Résultat attendu: tr(A) = -47" << endl;
        cout << "Résultat produit par l'application: tr(A) = " << tra << endl;
        if(tra == -47)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl;
    } else {
        cout << "La matrice A n'est pas carrée"
                "\nCalcul de trace impossible!" << endl;
    }

    cout << "! Calcul de déterminant" << endl;
    if (f.getNbRows()==f.getNbCols())
    {
        det = f.determinant();
        cout << "Résultat attendu: det(F) = 0" << endl;
        cout << "Résultat produit par l'application: det(F) = " << det << endl;
        if(det == 0)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl;
    } else {
        cout << "La matrice A n'est pas carrée"
                "\nCalcul de déterminant impossible!" << endl << endl;
    }

    if (a.getNbRows()==a.getNbCols())
    {
        det = a.determinant();
        cout << "Résultat attendu: det(A) = 8366164" << endl;
        cout << "Résultat produit par l'application: tr(A) = " << det << endl;
        if(det == 8366164)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl;
    } else {
        cout << "La matrice A n'est pas carrée"
                "\nCalcul de déterminant impossible!" << endl;
    }

    cout << "! Calcul d'inverse et test de l'opérateur scale*Matrix" << endl;
    if (g.getNbRows()==g.getNbCols())
    {
        x = (g^-1)*9;
        cout << "Résultat attendu: 9*G^-1 = " << endl << r5 << endl;
        cout << "Résultat produit par l'application: 9*G^-1 = " << endl << x ;
        if(r5 == x)
            cout << "Mêmes résultats, poursuite..." << endl ;
        cout << endl ;
        cout << endl ;
    } else {
        cout << "La matrice G n'est pas carrée"
                "\nCalcul d'inverse impossible!" << endl;
    }

    cout << "! Calcul de puissance" << endl;
    if (a.getNbRows()==a.getNbCols())
    {
        z = a^5;
        cout << "Résultat attendu: A^5 = " << endl << r6 << endl;
        cout << "Résultat produit par l'application: A^5 = " << endl << z ;
        if(r6 == z)
            cout << "Mêmes résultats, poursuite..." << endl;
        cout << endl ;
        cout << endl ;
    } else {
        cout << "La matrice A n'est pas carrée"
                "\nCalcul de puissance impossible!" << endl;
    }

    cout << "! Dernier test " << endl;
    if (g.getNbRows()==g.getNbCols())
    {
        x = g*(g^-1);
        cout << "Résultat attendu: G*G^-1 = " << endl << r7 << endl;
        cout << "Résultat produit par l'application: G*G^-1 = " << endl << x ;
        if(r7 == x)
            cout << "Mêmes résultats, poursuite..." << endl ;
        cout << endl ;
        cout << endl ;
    } else {
        cout << "La matrice G n'est pas carrée"
                "\nCalcul d'inverse impossible!" << endl;
    }

    cout << endl << endl << endl << "****** FIN DU TEST DE REGRESSION ******" << endl << endl ;

}


bool Matrix:: priorite_sup_egal (const string & opd,const string & opg)
{
    switch (opd[0])
    {
        case '*':
            return ((opg[0] == '*') || (opg[0] == '/'));

        case '/':
            return ((opg[0] == '*') || (opg[0] == '/'));

        case '+':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/'));

        case '-':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/'));
        default: return false;
    }
}


void Matrix:: polonaise(const std::string & chaine , std::vector<std::string> & notation_polonaise)
{
    stack<string> p;
    vector<string> expression;
    expression = decoupe(chaine);

    int i;

    for (i = 0; i < expression.size(); i++)
    {
        if ( (!isOperator(expression[i])) && (expression[i] != "(") && (expression[i] != ")") && (expression[i] != "=") )
        {
            notation_polonaise.push_back(expression[i]);
        }
        else if ( (expression[i] == "(") || (expression[i] == "=") )
        {
            p.push(expression[i]);
        }
        else if (isOperator(expression[i]))
        {
            if (!p.empty())
            {
                while (priorite_sup_egal(expression[i],p.top()))
                {
                    notation_polonaise.push_back(p.top());
                    p.pop();
                }
            }

            p.push(expression[i]);

        }
        else if (expression[i] == ")")
        {
            do
            {
                notation_polonaise.push_back(p.top());
                p.pop();

            }while (p.top() !=  "(");
            p.pop();
        }
    }

    while (!p.empty())
    {
        notation_polonaise.push_back(p.top());
        p.pop();
    }
}



/*Matrix Matrix:: expressionCalcul(const std::string & chaine)
{
    vector<string> polish;
    polonaise(chaine,polish);
    stack<string> pile;
    Matrix temp("ppp4");
    temp.saveMatrix();
    unsigned int i;
    unsigned int taille=polish.size();

    for (i = 0; i < taille; i++ )
    {
        if (isOperator(polish[i]))
        {
            string b = pile.top();
            pile.pop();
            string a=pile.top();
            pile.pop();

            temp=calculate(polish[i],a,b);
            pile.push(temp.getName());
            temp.saveMatrix();
        }
        else
        {
            pile.push(polish[i]);
        }
    }
    temp.readMatrix(pile.top());
    return temp;
}*/

void Matrix:: setMatrixKB ()
{
    cout << "Saisir nblignes : ";
    cin >> rows;
    cout << "Saisir nbColonnes : ";
    cin >> cols;
    
    tab.resize(rows, vector<double>(cols));
    
    for(unsigned int i = 1; i <= rows; ++i)
    {
        for(unsigned int j = 1; j <= cols; ++j)
        {
            cout << endl << "Saisir coeff " << "(" << i << " , " << j << ")" << ": ";
            cin >> tab[i-1][j-1];
        }
    }
}


void Matrix:: setMatrixRA ()
{
    cout << "Saisir nblignes : ";
    cin >> rows;
    cout << "Saisir nbColonnes : ";
    cin >> cols;
    
    tab = Matrix(rows, cols, Matrix::R).tab;
}


Eigen::MatrixXd Matrix:: class2Eigen ()
{
    unsigned int i,j,r,c;
    r = getNbRows();
    c = getNbCols();
    Eigen:: MatrixXd m(r,c);

    for(i=0 ; i<r ; i++)
    {
        for(j=0 ; j<c ; j++)
        {
            m(i,j) = tab[i][j] ;
        }
    }

    return m;
}


Matrix Matrix:: eigen2Class(const Eigen::MatrixXd & m)
{
    unsigned int i,j;
    unsigned int r,c;
    r = (unsigned int) m.rows();
    c = (unsigned int) m.cols();
    Matrix a(r,c);

    for(i=0 ; i<r ; i++)
    {
        for(j=0 ; j<c ; j++)
        {
            a.tab[i][j] = m(i,j) ;
        }
    }

    return a;
}


vector<complex<double>> Matrix:: eigenValues()
{
    unsigned int i, n=getNbRows();
    vector<complex<double>> result;
    Eigen::MatrixXd a;

    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> m(a);

    for (i=0; i<n; i++)
    {
        result.push_back(m.eigenvalues()(i));
        cout << result[i] << endl;
    }

    return result;
}


Matrix Matrix:: diagonalise ()
{
    Matrix m;
    Eigen:: MatrixXd a,b;
    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> res(a);
    b = res.pseudoEigenvalueMatrix();
    m = eigen2Class(b);

    return m;

}