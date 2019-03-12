
#include <iostream>
#include <cstring>
#include <cassert>

#include "Matrix.h"


using namespace std;



Matrix:: Matrix () : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
}



Matrix:: Matrix ( const unsigned int cols, const unsigned int rows) :
tab (vector<vector<double>> (rows, vector<double> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;
}



Matrix:: Matrix ( const unsigned int rows, const unsigned int cols, const VectorX & values )
{
    if ( values.size() != rows * cols )
    {
        cout << "Erreur : la dimension du vector passé en paramètre ne correspond pas aux dimensions de la matrice" << endl;
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
            flux << m.tab[i][j] << "  ";
        }
        flux << endl;
    }
    
    return flux;
}



Matrix:: ~Matrix ()
{
}


