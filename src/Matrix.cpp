
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include "Matrix.h"


using namespace std;


Matrix:: Matrix () : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, enum initMatrix type ) :
tab (vector<vector<double>> (rows, vector<double> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;
    
    switch ( type )
    {
        case ZERO: break;
        case RANDOM:
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
        case IDENTITY:
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


Matrix:: Matrix (unsigned int rowsAndCols, enum initMatrix type) :
Matrix (rowsAndCols, rowsAndCols, type)
{
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const double value ) :
tab (vector<vector<double>>(rows,vector<double> (cols, value)))
{
    this->rows = rows;
    this->cols = cols;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values )
{
    if ( values.size() != rows * cols )
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


Matrix:: ~Matrix ()
{
}


unsigned int Matrix:: getNbRows() const
{
    return rows;
}


unsigned int Matrix:: getNbCols() const
{
    return cols;
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


bool Matrix:: IsSQMatrix() const
{
    return rows==cols;
}


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


const Matrix Matrix:: operator* (const Matrix & m) const
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


void Matrix:: saveMatrix (const std::string & filename) const
{
    std:: ofstream fichier (filename.c_str());

    assert(fichier.is_open());

    fichier << rows << " " << cols << endl;

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {

            fichier << tab[i][j] << " ";
        }
        fichier << endl;
    }

    fichier.close();

    cout << "Sauvegarde de la matrice " << filename << " est réussie" << endl << endl;
}


void Matrix:: readMatrix(const string & filename)
{
    std:: ifstream fichier (filename.c_str());

    assert(fichier.is_open());

    fichier >> rows >> cols;

    tab = vector<vector<double>> (rows, vector<double> (cols, 0));

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            fichier >> tab[i][j];
        }
    }

    fichier.close();
    cout << "ouverture réussie" << endl << endl;
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
        return Matrix (rows, IDENTITY);
    }
    
    if ( p == -1 )
    {
        return inverse();
    }
    
    Matrix temp (*this);
    
    for ( int i = 1; i < p; ++i )
    {
        temp = temp * temp;
    }
    return temp;
}
