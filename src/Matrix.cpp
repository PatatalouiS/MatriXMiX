
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include <stack>
#include "Matrix.h"


using namespace std;

const string PATH = "../../data/sauvergarde.txt";



// ********* CONSTRUCTEURS / DESTRUCTEUR *********


Matrix:: Matrix (const string& name) : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
    this->name = name;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const double value, const string& name ) :
        tab (vector<vector<double>>(rows,vector<double> (cols, value)))
{
    this->rows = rows;
    this->cols = cols;
    this->name = name;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const enum initMatrix& type, const string& name ) :
        tab (vector<vector<double>> (rows, vector<double> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;
    this->name = name;

    switch ( type )
    {
        case Z: break;
        case R:
        {
            srand(time(NULL));

            for ( auto& i : tab )
            {
                for ( auto& j : i )
                {
                    j = (rand()% 20000) + 10000;
                }
            }
            break;
        }
        case I:
        {
            if ( cols != rows )
            {
                cerr << "Initialisatin d'une matrice identité impossible (rows != cols)" << endl;
                exit(EXIT_FAILURE);
            }

            for ( unsigned int i = 0; i < rows; ++i )
            {
                tab[i][i] = 1;
            }
        }
        default: break;
    }
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values, const string& name )
{
    if ( values.size() != rows * cols )
    {
        cout << "Erreur : la dimension du vecteur passé en paramètre ne correspond pas aux dimensions de la matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    this->cols = cols;
    this->rows = rows;
    this->name = name;

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


Matrix:: Matrix (const Matrix & m, const string& name) : tab ( vector<vector<double>> (m.tab))
{
    cols = m.cols;
    rows = m.rows;
    this->name = name;
}


Matrix:: ~Matrix ()
{
}



// ******** FONCTIONS STATIQUES *********


Matrix Matrix:: ID ( const unsigned int size )
{
    return Matrix(size, size, Matrix::I);
}







// ******* FONCTIONS DE CALCUL ALGEBRIQUE ET OPERATEURS DE CALCUL ********


const Matrix Matrix:: operator+ (const Matrix & m) const
{
    if ( (rows!=m.rows) || (cols!=m.cols) )
    {
        cout << "Addition impossible!" << endl;
        exit ( EXIT_FAILURE );
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
    Matrix copie(*this);

    for (unsigned int i=0; i<copie.rows; i++)
    {
        for (unsigned int j=0; j<m.cols; j++)
        {
            s=0;
            for (unsigned int k=0; k<copie.rows; k++)
            {
                s+=tab[i][k]*(m[k][j]);
            }
            copie[i][j]=s;
        }
    }
    return copie;
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


bool isOperator (const string & chaine)
{
    return ( (chaine.compare("+")  ==  0)
             ||  (chaine.compare("-")  ==  0)
             ||  (chaine.compare("/") == 0)
             || (chaine.compare("^") == 0)
             || (chaine.compare("*") == 0));
}


vector<string> decoupe (const string & expression)
{
    unsigned int i, taille=expression.length();
    vector<string> tab;
    string c, temp;
    temp="";

    for (i=0; i<taille; i++)
    {
        c=expression[i];

        if(isOperator(c))
        {
            tab.push_back(temp);
            tab.push_back(c);
            temp="";
        }
        else
        {
            temp+=c;
            cout << temp << endl;
        }
    }
    tab.push_back(temp);

    return tab;
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


string Matrix:: getName() const
{
    return name;
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


void Matrix:: saveMatrix ()
{

    string matrixname(this->name);

    string filename ("PATH");
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
        cout << "Une matrice du même nom a déjà été sauvergardée"
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

}


void Matrix:: readMatrix(const string & matrixname)
{
    string filename("PATH");
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


void cleanSaves()
{
    string filename(PATH);
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
        exit(EXIT_FAILURE);
    }

    file.close();
    cout << "Fichier de sauvegarde nettoyé" << endl << endl;

}