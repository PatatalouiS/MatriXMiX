
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "Matrix.h"


using namespace std;



Matrix:: Matrix () : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
}


Matrix:: Matrix ( const unsigned int rows, const unsigned int cols) :
        tab (vector<vector<double>> (rows, vector<double> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;
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
    assert ( indice < (rows*cols) );

    return tab[indice/rows][indice%rows];
}



double Matrix:: getVal ( const unsigned int indice ) const
{
    assert ( indice < (rows*cols) );

    return tab[indice/rows][indice%rows];
}



vector<double>&  Matrix:: operator [] ( const unsigned int indice )
{
    return tab[indice];
}



const std::vector<double>& Matrix:: operator [] ( const unsigned int indice ) const
{
    return tab[indice];
}



ostream& operator << ( ostream& flux, const Matrix & m )
{
    for ( unsigned int i = 0; i < m.rows; ++i )
    {
        for ( unsigned int j = 0; j < m.cols; ++j )
        {
            if((int)(m.tab[i][j]*1000000)==0)
            {
                flux << "0" << "  ";
            }
            else
            {
                flux << m.tab[i][j] << "  ";
            }
        }

        flux << endl;
    }

    return flux;
}


Matrix:: ~Matrix ()
{
}



unsigned int Matrix:: getRows() const
{
    return rows;
}


unsigned int Matrix:: getCols() const
{
    return cols;
}


Matrix Matrix:: randomMatrix(const unsigned int & r, const unsigned int & c)
{
    Matrix m(r,c);

    srand(time(NULL));

    for (unsigned int i=0; i<r; i++)
    {
        for (unsigned int j=0; j<c; j++)
        {
            m[i][j]=rand();
        }
    }

    return m;
}


Matrix Matrix:: identityMatrix()
{
    Matrix c(*this);

    for (unsigned int i=0; i<c.getRows(); i++)
    {
        for (unsigned int j=0; j<c.getCols(); j++)
        {
            if (i==j)
                c[i][j]=1;
            else
                c[i][j]=0;
        }
    }

    return c;

}


Matrix identityMatrix(const unsigned int & n)
{
    Matrix m(n,n);

    for (unsigned int i=0; i<n; i++)
    {
        m[i][i]=1.0;
    }

    return m;
}


Matrix Matrix:: transposeMatrix()
{
    Matrix copie(*this);

    for (unsigned int i=0; i<copie.getRows(); i++)
    {
        for (unsigned int j=0; j<copie.getCols(); j++)
        {
            copie[i][j]=tab[j][i];
        }
    }

    return copie;
}


Matrix Matrix:: additionMatrix(const Matrix & m)
{
    if ( (getRows()!=m.getRows()) || (getCols()!=getCols()) )
    {
        cout << "Addition impossible!" << endl;
    }

    else
    {
        Matrix copie(*this);

        for (unsigned int i=0; i<m.getRows(); i++)
        {
            for (unsigned int j=0; j<m.getCols(); j++)
            {
                copie[i][j]=copie[i][j]+m[i][j];
            }
        }

        return copie;
    }

}


Matrix Matrix:: soustractionMatrix(const Matrix & m)
{
    if ( (getRows()!=m.getRows()) || (getCols()!=getCols()) )
    {
        cout << "Soustraction impossible!" << endl;
    }

    else
    {
        Matrix copie(*this);

        for (unsigned int i=0; i<m.getRows(); i++)
        {
            for (unsigned int j=0; j<m.getCols(); j++)
            {
                copie[i][j]=copie[i][j]-m[i][j];
            }
        }
        return copie;
    }
}


Matrix Matrix:: multiplicationScale(const double & lambda)
{
    Matrix copie(*this);

    for (unsigned int i=0; i<getRows(); i++)
    {
        for (unsigned int j=0; j<getCols(); j++)
        {
            copie[i][j]=lambda*copie[i][j];
        }
    }
    return copie;
}


Matrix Matrix:: multiplicationMatrix(const Matrix & m)
{
    if (getCols() != m.getRows())
    {
        cout << "Multiplication impossible!" << endl << "A * B->Le nombre de ligne de A = nombre de colonne de B!" << endl;
    }

    else
    {
        double s;
        Matrix copie(*this);

        for (unsigned int i=0; i<copie.getRows(); i++)
        {
            for (unsigned int j=0; j<m.getCols(); j++)
            {
                s=0;
                for (unsigned int k=0; k<copie.getRows(); k++)
                {
                    s+=tab[i][k]*(m[k][j]);
                }
                copie[i][j]=s;
            }
        }
        return copie;
    }
}


bool Matrix:: squareMatrix() const
{
    return (getRows()==getCols());
}


bool Matrix:: isEqualMatrix(const Matrix &m)
{

    bool equal;
    equal = true;

    if ((m.getCols() == getCols()) && (m.getRows() == getRows())) {


        for (unsigned int i = 0; i < getRows(); i++)
        {
            for (unsigned int j = 0; j < getCols(); j++)
            {
                if (tab[i][j] != m.tab[i][j]) {

                    equal= false;
                    return equal;
                }
            }
        }

    }

    return equal;

}


const Matrix Matrix:: operator+ (const Matrix & m)
{
    return additionMatrix(m);
}


const Matrix Matrix:: operator- (const Matrix & m)
{
    return soustractionMatrix(m);
}


const Matrix Matrix:: operator* (const Matrix & m)
{
    return multiplicationMatrix(m);
}


const Matrix Matrix:: operator * (const double & lambda)
{
    return multiplicationScale(lambda);
}


bool Matrix:: operator == (const Matrix & m)
{
    return isEqualMatrix(m);
}


bool Matrix::operator != (const Matrix & m)
{
    bool different = isEqualMatrix(m);
    return !different;
}


Matrix Matrix:: powerMatrix(const int & p)
{
    Matrix copie(*this);
    return powerMat(copie,p);
}


Matrix Matrix:: powerMat(Matrix & m, const int & p)
{

    if(p==0)
    {
        return (m.identityMatrix());
    }
    else if(p>0)
    {
        Matrix copie(m);
        return copie*(copie.powerMat(copie,p-1));
    }
    else
    {
        Matrix copie(m.inverse());
        return (copie.powerMat(copie,-p));
    }


}


void Matrix:: saveMatrix (const string & matrixname)
{

    string filename ("../sauvegarde.txt");
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
    file << getRows() << " " << getCols() << endl;

    for (unsigned int i = 0; i < getRows(); i++)
    {
        for (unsigned int j = 0; j < getCols(); j++)
        {

            file << tab[i][j] << " ";
        }
        file << endl;
    }

    cout << "Sauvegarde de la matrice " << filename << " est réussie" << endl << endl;

    file.close();

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


void Matrix:: readMatrix(const string & filename)
{
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

        file >> rows >> cols;

        tab = vector<vector<double>> (rows, vector<double> (cols, 0));

        for (unsigned int i = 0; i < getRows(); i++)
        {
            for (unsigned int j = 0; j < getCols(); j++)
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


double Matrix:: traceMatrix() const
{
    double s=0;

    for (unsigned int i=0; i<getRows(); i++)
    {
        s+=tab[i][i];
    }

    return s;
}


Matrix Matrix :: subMatrix(const unsigned int & a, const unsigned int & b)
{
    unsigned int ii=0,jj=0;
    unsigned int r=getRows();
    unsigned int c=getCols();

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


double Matrix:: determinant(unsigned int dim)
{
    Matrix submatrix (dim,dim);
    double det = 0;

    if (dim == 2)
        return ((tab[0][0] * tab[1][1]) - (tab[1][0] * tab[0][1]));
    else
    {
        for (int x = 0; x < dim; x++)
        {
            int subi = 0;
            for (int i = 1; i < dim; i++)
            {
                int subj = 0;
                for (int j = 0; j < dim; j++)
                {
                    if (j == x)
                        continue;
                    submatrix.tab[subi][subj] = tab[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * tab[0][x] * submatrix.determinant(dim - 1));
        }
    }


    return det;
}


double Matrix:: determinant()
{
    assert(getCols() == getRows());
    return determinant(getRows());
}


Matrix Matrix::coMatrix()
{
    unsigned int r=getRows();
    unsigned int c=getCols();

    Matrix com(r,c);
    Matrix sub(r-1,c-1);

    for (unsigned int i=0; i<r; i++)
    {
        for (unsigned int j=0; j<c; j++)
        {
            sub=subMatrix(i,j);
            com[i][j]=pow(-1,i+j)*sub.determinant();
        }
    }

    return com;
}


Matrix Matrix:: inverse()
{
    double det=determinant();

    if (det==0)
    {
        cout << "Le déterminant est nul, la matrice n'est donc pas inversible!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        Matrix temp(getRows(),getCols()), inverse(getRows(),getCols());
        temp=(*this).coMatrix();
        temp=temp.transposeMatrix();
        inverse=temp*(1/det);
        return inverse;
    }

}


Matrix Matrix:: divideMatrix(const Matrix & m)
{
    Matrix temp(m);
    if(temp.determinant()==0)
    {
        cout << "Le déterminant est nul, la matrice n'est donc pas inversible!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        temp=temp.inverse();
        return multiplicationMatrix(temp);
    }
}


const Matrix Matrix:: operator / (const Matrix & m)
{
    return divideMatrix(m);
}


const Matrix Matrix:: operator ^ (const int & p)
{
    return powerMatrix(p);
}
