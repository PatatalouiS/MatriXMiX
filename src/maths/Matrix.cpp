/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

#include <iostream>
#include <complex>
#include <cstring>
#include <cmath>
#include <random>
#include <utility>
#include <../../ext/Eigen/Dense>
#include "Matrix.h"
#include "Polynomial.h"
#include "Gauss.h"
#include "Utils.hpp"

using namespace std;

const double EPSILON = 0.00001;


const Matrix Matrix:: matrix_null = Matrix();
const complex<double> Matrix:: complex_null = complex<double>();



// ********* CONSTRUCTORS / DESTRUCTORS *********


Matrix:: Matrix () : tab ( vector<vector<complex<double>>> ())
{
    rows = 0;
    cols = 0;
}


Matrix:: Matrix (const unsigned int rows, const unsigned int cols, const complex<double> value) :
        tab (vector<vector<complex<double>>>(rows,vector<complex<double>> (cols, value)))
{
    this->rows = rows;
    this->cols = cols;
}


Matrix:: Matrix (const unsigned int rows, const unsigned int cols, const enum initMatrix& type) :
        tab (vector<vector<complex<double>>> (rows, vector<complex<double>> (cols, 0)))
{
    this->cols = cols;
    this->rows = rows;

    switch (type)
    {
        case Z: {
            unsigned int i, j;
            std::complex<double> z (0.0,0.0);
            for (i = 0; i < rows; i++) {
                for (j = 0; j < cols; j++) {
                    tab[i][j] = z;
                }
            }
            break;
        }
        case R:
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(-10000,10000);
            float random1 = dis(gen);
            float random2 = dis(gen);

            for (auto& i : tab)
            {
                for (auto& j : i)
                {
                    random1 = dis(gen);
                    random2 = dis(gen);
                    j = std::complex<double>(random1 / 100, random2 / 100);
                }
            }
            break;
        }
        case I:
        {
            if (cols != rows)
            {
                cerr << "Initialisation d'une matrice identité impossible (rows != cols)" << endl;
                exit(EXIT_FAILURE);
            }

            for (unsigned int i = 0; i < rows; ++i)
            {
                tab[i][i] = std::complex<double>(1,0);
            }
            break;
        }
    }
}


Matrix:: Matrix (const unsigned int rows, const unsigned int cols, const VectorX & values)
{
    if (values.size() != rows * cols)
    {
        cerr << "Erreur : la dimension du vecteur passé en paramètre ne correspond pas aux dimensions de la matrice" << endl;
        exit (EXIT_FAILURE);
    }

    this->cols = cols;
    this->rows = rows;

    vector<complex<double>> temp;

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


Matrix:: Matrix (const Matrix & m) : tab ( vector<vector<complex<double>>> (m.tab))
{
    cols = m.cols;
    rows = m.rows;
}



// ******** STATIC FUNCTION *********


Matrix Matrix:: ID (const unsigned int size)
{
    return Matrix(size, size, Matrix::I);
}





/*************** PRIVATE FUNCTIONS ***************/


vector<string> Matrix:: explode (const string & expression) const
{
    unsigned int i;
    unsigned  long l = expression.length();
    vector<string> tab;
    string c, temp;
    temp="";
    for (i = 0; i < l; i++)
    {
        c = expression[i];

        if (c == ",")
        {
            if (temp.length()!=0) tab.push_back(temp);
            temp="";
        }
        else if (!c.empty())
        {
            temp += c;
        }

    }
    if (temp != "")
    tab.push_back(temp);

    return tab;
}


VectorX Matrix:: checkCast(const VectorX & v) const
{
    VectorX res;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        res.push_back(Utils::checkCast(v[i]));
    }
    return res;
}



Matrix Matrix:: checkCast() const
{
    unsigned int r = getNbRows();
    Matrix result(*this);

    for (unsigned int i = 0; i < r; i++)
    {
        result[i] = checkCast(tab[i]);
    }

    return result;
}


Matrix Matrix :: subMatrix(const unsigned int & a, const unsigned int & b) const
{
    unsigned int i, j;
    unsigned int ii = 0, jj = 0;
    unsigned int r = rows;
    unsigned int c = cols;

    Matrix sub(r-1,c-1);

    for(i = 0; i < r; i++)
    {
        jj = 0;
        if(i != a)
        {
            for (j = 0; j < c; j++)
            {
                if (j != b)
                {
                    sub[ii][jj] = tab[i][j];
                    jj++;
                }
            }
            ii++;
        }
    }
    return sub;
}


Matrix Matrix::matrixCol(const unsigned int & j) const {
    unsigned int i;
    Matrix vect(rows,1);

    for (i = 0; i < rows; i++) {
        vect[i][0] = tab[i][j];
    }

    return vect;
}


Matrix Matrix::matrixRow(const unsigned int & i) const {
    unsigned int j;
    Matrix vect(1,cols);

    for (j = 0; j < cols; j++) {
        vect[i][0] = tab[i][j];
    }

    return vect;
}


std::complex<double> Matrix::colNorm() const {
    unsigned int i;
    std::complex<double> z (0.0,0.0);
    for (i = 0; i < cols; i++) {
        z += tab[0][i];
    }
    return sqrt(z);
}


std::complex<double> Matrix::rowNorm() const {
    unsigned int i;
    std::complex<double> z (0.0,0.0);
    for (i = 0; i < rows ; i++) {
        z += tab[i][0];
    }
    return sqrt(z);
}


VectorX Matrix:: normalizeVectorX (const VectorX & v) const
{
    VectorX res;
    unsigned int i;
    double norm = 0;

    for (i = 0; i < rows; i++)
    {
        norm += ( (v[i].real() * v[i].real()) + (v[i].imag() * v[i].imag()) );
    }

    for (i = 0; i < rows; i++)
    {
        res.push_back(v[i] / sqrt(norm));
    }

    return res;
}



Eigen::MatrixXcd Matrix:: class2Eigen () const
{
    unsigned int i, j, r, c;
    r = getNbRows();
    c = getNbCols();
    Eigen:: MatrixXcd m(r,c);

    for(i = 0 ; i < r ; i++)
    {
        for(j = 0 ; j < c ; j++)
        {
            m(i,j) = tab[i][j] ;
        }
    }

    return m;
}


const Matrix Matrix:: eigen2Class(const Eigen::MatrixXcd & m) const
{
    unsigned int i, j, r, c ;
    r = static_cast<unsigned int>(m.rows());
    c = static_cast<unsigned int>(m.cols());
    Matrix a(r,c);

    for(i = 0 ; i < r ; i++)
    {
        for(j = 0 ; j < c ; j++)
        {
            a.tab[i][j] = m(i,j) ;
        }
    }

    return a;
}




/*************** ACCESSORS / MUTATORS / BASIC FUNCTIONS ***************/


unsigned int Matrix:: getNbRows() const
{
    return rows;
}


unsigned int Matrix:: getNbCols() const
{
    return cols;
}


void Matrix:: setNbRows(unsigned int row)
{
    this->rows = row;
    tab = (vector<vector<complex<double>>>(rows,vector<complex<double>> (cols,0)));
}


void Matrix:: setNbCols(unsigned int col)
{
    this->cols = col;
    tab = (vector<vector<complex<double>>>(rows,vector<complex<double>> (cols,0)));
}


complex<double>& Matrix:: getVal (const unsigned int indice)
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice " << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    return tab[indice/rows][indice%rows];
}


complex<double> Matrix:: getVal (const unsigned int indice) const
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice " << indice <<" n'existe pas dans cette matrice" << endl;
        return complex_null;
    }

    return tab[indice/rows][indice%rows];
}


vector<complex<double>>&  Matrix:: operator [] (const unsigned int indice)
{
    if ( indice >= rows)
    {
        cerr << "L'indice " << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }
    return tab[indice];
}


const std::vector<complex<double>>& Matrix:: operator [] (const unsigned int indice) const
{
    if ( indice >= rows)
    {
        cerr << "L'indice " << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }
    return tab[indice];
}


ostream& operator << (ostream& flux, const Matrix & m)
{
    for (auto i : m.tab)
    {
        for (auto j : i)
        {
            flux << j << "  ";
        }
        flux << endl;
    }
    flux << endl;
    return flux;
}


Matrix Matrix:: operator << (const string& values)
{
    unsigned int i,j;
    string c;
    vector<string> table (explode(values));

    if (table.size() != rows*cols) {
        cerr <<"Le nombre des valeurs rentrées ne correspond pas à la taille de la matrice" << endl;
        return matrix_null;
    }

    else
    {  for (i = 0; i < this->rows; i++)
        {
            for ( j = 0; j < this->cols; j++)
            {
                c = table[i*cols+j];
                tab[i][j] = atof(c.c_str());
            }
        }
     }
    return *this;
}


istream& operator >> (istream& flux, Matrix & m)
{
    unsigned int i,j,rows,cols;
    double value;
    flux >> rows >> cols;    //Entering rows and columns numbers
    m.setNbRows(rows);
    m.setNbCols(cols);

    for ( i = 0; i < rows; ++i )
    {
        for ( j = 0; j < cols; ++j )
        {
            flux >> value;
            m.tab[i][j] = value;      // Entering des coefficients
        }
    }

    return flux;
}


void Matrix:: setMatrixKB ()
{
    cout << "Saisir nblignes : ";
    cin >> rows;
    cout << "Saisir nbColonnes : ";
    cin >> cols;

    tab.resize(rows, vector<complex<double>>(cols));

    int re;
    int im;

    for(unsigned int i = 1; i <= rows; ++i)
    {
        for(unsigned int j = 1; j <= cols; ++j)
        {
            re = 0;
            im = 0;
            cout << endl << "Saisir la partie réelle du coeff " << "(" << i << " , " << j << ")" << ": ";
            cin >> re;
            cout << endl << "Saisir la partie imaginaire du coeff " << "(" << i << " , " << j << ")" << ": ";
            cin >> im;
            tab[i-1][j-1] = complex<double>(re,im);
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


const Matrix Matrix:: operator + (const Matrix & m) const
{
    if ( (rows!=m.rows) || (cols!=m.cols) )
    {
        cerr << "Addition impossible!" << endl;
        return matrix_null;
    }

    unsigned int i,j;
    Matrix copy(*this);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            copy[i][j] = copy[i][j] + m[i][j];
        }
    }
    return copy;
}


const Matrix Matrix:: operator - (const Matrix & m) const
{
    if ((rows!=m.rows) || (cols!=m.cols))
    {
        cerr << "Soustraction impossible!" << endl;
        return matrix_null;
    }

    unsigned int i,j;
    Matrix copy(*this);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            copy[i][j] = copy[i][j] - m[i][j];
        }
    }
    return copy;
}


const Matrix Matrix:: operator * (const Matrix & m) const
{
    if (cols != m.rows)
    {
        cerr << "Multiplication impossible!" << endl <<
                "A * B -> Le nombre de ligne de A doit  nombre de colonne de B!" << endl;
        return matrix_null;
    }

    unsigned int i,j,k;
    complex<double> sum;
    Matrix res(rows, m.cols, Matrix::Z);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < m.cols; j++)
        {
            sum = 0;
            for (k = 0; k < cols; k++)
            {
                sum += tab[i][k] * (m[k][j]);
            }
            res[i][j] = sum;
        }
    }
    return res;
}


const Matrix Matrix:: operator * (const std::complex<double> & lambda) const
{
    unsigned int i,j;
    Matrix res(*this);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            res[i][j] *= lambda;
        }
    }
    return res;
}


const Matrix operator * (const std::complex<double> & lambda, const Matrix & m)    // friend operator
{
    return m * lambda;
}


const Matrix Matrix:: operator / (const Matrix & m) const
{
    if (!m.isSQMatrix())
    {
        cerr << "Division est impossible, la matrice diviseure n'est pas une matrice carrée !" << endl;
        return matrix_null;
    }
    if (m.determinant() == 0.0)
    {
        cerr << "Division impossible, la matrice diviseure n'est pas inversible !" << endl;
        return matrix_null;
    }
    Matrix result ((*this) * m.inverse());
    return result ;
}


const Matrix Matrix:: operator ^ (const int & p) const
{

    if ( !isSQMatrix() )
    {
        cerr << "Erreur, la matrice n'est pas carrée ! " << endl;
        return matrix_null;
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

    if ( p < -1 )
    {
        temp = temp.inverse();
        temp2 = temp2.inverse();
    }

    for (int i = 1; i < abs(p); ++i )
    {
        temp = (temp * temp2);
    }
    return temp;
}


bool Matrix:: operator == (const Matrix & m ) const
{
    unsigned int i,j ;

    if ( (m.cols == cols) && (m.rows == rows) )
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < cols; j++)
            {
                if ( (abs(tab[i][j].real() - m.tab[i][j].real()) > EPSILON)
                    || (abs(tab[i][j].imag() - m.tab[i][j].imag()) > EPSILON)) //!\\ MODIFICATION A DISCUTER
                {
                    return false;
                }
            }
        }
        return true;
    }

    return false;
}


bool Matrix::operator != (const Matrix & m) const
{
    return !((*this) == m);
}


bool Matrix:: isSQMatrix() const
{
    return rows == cols;
}


complex<double> Matrix:: trace() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul de la trace impossible, la matrice n'est pas carrée" << endl;
        return complex_null;
    }

    complex<double> s(0.0,0.0);
    for ( unsigned int i = 0; i < rows; i++)
    {
        s += tab[i][i];
    }
    return s;
}


complex<double> Matrix:: determinant() const
{
    if (!isSQMatrix())
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        return complex_null;
    }

    Eigen::MatrixXcd m = class2Eigen();
    return m.determinant();
}


Matrix Matrix::coMatrix() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul de la comatrice impossible, la matrice n'est pas carrée" << endl;
        return matrix_null;
    }

    unsigned int i, j;
    Matrix com(rows,cols);
    Matrix sub(rows - 1, cols - 1);

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            sub = subMatrix(i,j);
            com[i][j] = pow(-1,i + j) * sub.determinant();
        }
    }
    return com;
}


Matrix Matrix:: transposeMatrix() const
{
    unsigned int i, j;
    Matrix copy(cols,rows);

    for (i = 0; i < copy.rows; i++)
    {
        for (j = 0; j < copy.cols; j++)
        {
            copy[i][j] = tab[j][i];
        }
    }
    return copy;
}


Matrix Matrix:: conjugateTranspose() const
{
    unsigned int i, j;
    Matrix copy(cols,rows);

    for (i = 0; i < copy.rows; i++)
    {
        for (j = 0; j < copy.cols; j++)
        {
            copy[i][j] = std::conj(tab[j][i]);
        }
    }
    return copy;
}


bool Matrix::isSymetric() const {
    return (*this == transposeMatrix());
}


bool Matrix::isSelfAdjoint() const {
    return (*this == conjugateTranspose());
}


Matrix Matrix:: inverse() const
{
    if (!isSQMatrix())
    {
        cerr << "Calcul de l'inverse impossible, la matrice n'est pas carrée" << endl;
        return matrix_null;
    }

    if(determinant() == 0.0)
    {
        cerr << "Calcul de l'inverse impossible, la matrice n'est pas inversible" << endl;
        return matrix_null;
    }

    Eigen::MatrixXcd m = class2Eigen(), inverse;

    return eigen2Class(m.inverse());
}


const Matrix Matrix:: gaussReduction()const
{
    Gauss g;
    Matrix res(*this);

    int col;
    int r = static_cast<int>(res.getNbRows()) ;
    int c = static_cast<int>(res.getNbCols()) ;


    int nonzero_row_id, next_row_id = 0;
    vector<Gauss> pivot_gauss;

    for (col = 0; col < c; col++)
    {
        nonzero_row_id = g.isNonZeroColumn(res, col, r, next_row_id);
        if (nonzero_row_id >= 0)
        {
            if (nonzero_row_id != next_row_id)
            {
                g.rowExchange(res.tab.begin() + next_row_id, res.tab.begin() + nonzero_row_id);
                nonzero_row_id = next_row_id;
            }
            pivot_gauss.push_back(Gauss(nonzero_row_id, col));
            for (int row = next_row_id; row < r; row++)
            {
                if (res[static_cast<unsigned int>(row)][static_cast<unsigned int>(col)] == 0.0)
                    continue;
                if (row == nonzero_row_id)
                    continue;
                g.rowReplace(res.tab.begin() + row,
                            res.tab.begin() + nonzero_row_id,
                            - res.tab[static_cast<unsigned int>(row)]
                                     [static_cast<unsigned int>(col)]
                            / res.tab[static_cast<unsigned int>(nonzero_row_id)]
                                     [static_cast<unsigned int>(col)]);
            }
            next_row_id++;
        }
        else
        {
            continue;
        }

    }

    for (vector<Gauss>::iterator pos = pivot_gauss.end() - 1;
         pos >= pivot_gauss.begin(); pos--)
    {
        if (pos->getVal(res).real() != 1.0)
        {
            res.tab[pos->getRow()] = res.normalizeVectorX(res.tab[pos->getRow()]);
        }
        for (int row = 0; row < r; row++)
        {
            if (res.tab[static_cast<unsigned int>(row)]
                        [static_cast<unsigned int>(pos->getCol())].real() != 0.0
                    && res.tab[static_cast<unsigned int>(row)]
                                [static_cast<unsigned int>(pos->getCol())].imag() != 0.0
                    && row != pos->getRow())
            {
                g.rowReplace(res.tab.begin() + row, res.tab.begin() + pos->getRow(),
                            -res.tab[static_cast<unsigned int>(row)][static_cast<unsigned int>(pos->getCol())]
                        / res.tab[static_cast<unsigned int>(pos->getRow())][static_cast<unsigned int>(pos->getCol())]);
            }
        }

    }

    return res;
}


unsigned int Matrix:: rank()const
{
    unsigned int i, j, r, c, rg = 0;
    bool non_zero = false;
    r = getNbRows();
    c = getNbCols();
    Matrix reduction(*this);
    reduction = reduction.gaussReduction();

    Matrix id (r,I);
    if (id == *this)
      return r;

    for (i = 0; i < r; i++)
    {
        non_zero = false;
        for (j = 0; j < c; j++)
        {
            if (reduction[i][j]!=0.0)
            {
                non_zero = true;    // rank is the number of non zero lines after gaussReduction
            }
        }
        if (non_zero)
        {
            rg++;
        }
    }

    return rg;
}


const pair<unsigned int, unsigned int> Matrix:: dimensionsStudy()const
{
    unsigned int dim_E = getNbCols();   // number of cols = dimension of start set of linear application
    unsigned int dim_im = rank();
    unsigned int dim_ker = dim_E - dim_im;   // using rank theorem

    return make_pair(dim_im,dim_ker);
}




// *********   ADVANCED MATRIX STUDY FUNCTIONS   *********


const VectorX Matrix:: eigenValues() const
{
    unsigned long int i, n;
    vector<complex<double>> result;
    Eigen::MatrixXcd a = class2Eigen();
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> m(a,false);
    n = static_cast<unsigned long int>(m.eigenvalues().size());

    for (i = 0; i < n; i++)
    {
        result.push_back(m.eigenvalues()(i));
    }

    return result;
}


const Polynomial Matrix:: characteristicPolynomial()const
{
    unsigned int i;
    VectorX vect_res;
    Polynomial result;
    Polynomial temp(1);

    vector<complex<double>> eigen_values;
    eigen_values = eigenValues();

    vect_res.push_back(eigen_values[0]);
    vect_res.push_back(-1);

    //result.tab[0] = eigen_values[0];
    //result.tab[1] = -1;

    result = Polynomial(1,vect_res);

    for(i = 1; i < eigen_values.size(); i++)
    {
        vect_res[0] = eigen_values[i];
        vect_res[1] = -1;
        temp = Polynomial(1,vect_res);
        result = result * temp;
    }

    return result;
}


const vector<Polynomial> Matrix:: splitCharacteristicPolynomial()const
{
    unsigned int i;
    VectorX temp_vect;
    std::vector<Polynomial> v;
    vector<complex<double>> eigen_values (eigenValues());

    temp_vect.push_back(eigen_values[0]);
    temp_vect.push_back(-1);
    v.push_back(Polynomial(1,temp_vect));

    for(i = 1; i < eigen_values.size(); i++)
    {
        temp_vect[0] = eigen_values[i];
        temp_vect[1] = -1;
        v.push_back(Polynomial(1,temp_vect));
    }

    return v;
}


const Matrix Matrix:: eigenVectors()const
{
    unsigned int i, j;
    Matrix res(getNbRows(),getNbCols());
    vector<VectorX> tab;
    Eigen:: MatrixXcd m = class2Eigen();
    Eigen:: ComplexEigenSolver<Eigen::MatrixXcd> ces(m);

    for (i = 0; i < getNbRows(); i++)
    {
        for (j = 0; j < getNbCols(); j++)
        {
            res[i][j] = ces.eigenvectors()(i,j);
        }
    }

    return res;

}


const vector<pair<complex<double>,VectorX>> Matrix:: allEigen()const
{
    unsigned int i;
    unsigned long int n;
    Matrix e_vector;
    VectorX e_value;
    vector<pair<complex<double>,VectorX>> result;

    e_value = eigenValues();
    e_vector = eigenVectors();

    n = e_value.size();

    for (i = 0; i < n; i++)
    {
        result.push_back(make_pair(e_value[i],e_vector[i])) ;

    }
    return result;
}


bool Matrix:: isDiagonalisableC()const
{
    if (!isSQMatrix())
        return false;

    Matrix diag(*this);
    Matrix p1(rows,cols,Matrix::Z);
    Matrix p2(rows,cols,Matrix::Z);

    allMatrix(p1,diag,p2);
    if (p2 == matrix_null) {
        return false;
    }

    return (p1.determinant() != std::complex<double>(0.0,0.0));

}


bool Matrix::isDiagonalisableR() const
{
    if (!isDiagonalisableC())
        return false;

    VectorX vect (eigenValues());
    for (unsigned int i = 0; i < vect.size(); i++) {
        if (vect[i].imag() != 0.0)
            return false;
    }
    return true;
}


bool Matrix::isPositiveDefinite() const {
    if (!isSQMatrix())
        return false;
    VectorX eigen_values(eigenValues());
    for (unsigned int i = 0; i < eigen_values.size(); i++) {
        if (eigen_values[i].real() < 0.0
            || eigen_values[i].imag() < 0.0)
            return false;
    }
    return true;
}


const Matrix Matrix:: diagonalise()const
{
    Matrix res(getNbRows(),getNbCols());
    VectorX v = eigenValues();
    Eigen:: MatrixXcd a,b;

    for (unsigned int i = 0; i < getNbRows(); i++)
    {
        res[i][i] = v[i];
    }

    return res;

}


const Matrix Matrix::transferMatrix()const
{
    if (!isSQMatrix())
        return matrix_null;

    return eigenVectors();

}


void Matrix:: allMatrix (Matrix & transferC2B, Matrix & diagonal,
                         Matrix & transferB2C) const
{
   transferC2B = transferMatrix();
   diagonal = diagonalise();
   if (transferC2B.determinant() == 0.0)
   {
       transferB2C = matrix_null;
   }
   else
   {
       transferB2C = (transferC2B.inverse());
   }

}


Matrix Matrix::normalizeMatrix() const {
    unsigned int i, j;
    Matrix res(*this);
    std::complex<double> norm;

    for (j = 0; j < cols; j++) {
        norm = std::complex<double> (0.0,0.0);
        for (i = 0; i < rows; i++) {
            norm += (res[i][j] * res[i][j]);
        }
        norm = sqrt(norm);
        if (norm != std::complex<double>(0.0,0.0)) {
            for (i = 0; i < rows; i++) {
                res[i][j] /= norm;
            }
        }

    }
    return res;
}


std::pair<Matrix,Matrix> Matrix::LUDecomposition() const {

    if (!isSQMatrix()) {
        std::cerr << "La décomposition LU ne s'effectue pour que pour des matrices carrées"
                    << std::endl;
        return std::pair<Matrix,Matrix>(matrix_null,matrix_null);
    }
    if (!isPositiveDefinite()) {
        std::cerr << "La décomposition LU ne s'effectue que pour des matrices définies positives"
                    << std::endl;
        return std::pair<Matrix,Matrix>(matrix_null,matrix_null);
    }

    unsigned int i, j, k, n = rows;
    Matrix l(n,n,Matrix::I);
    Matrix u(n,n,Matrix::Z);
    Matrix t(*this);

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n ; j++) {
            l[j][i] = t[j][i] / t[i][i];
        }
        for (j = i; j < n; j++) {
            u[i][j] = t[i][j];
        }
        for (j = i + 1; j < n; j++) {
            for (k = i + 1; k < n; k++) {
                t[j][k] = t[j][k] - l[j][i] * u[i][k];
            }
        }
    }
    u[n - 1][n - 1] = t[n - 1][n - 1];

    return std::pair<Matrix,Matrix>(l,u);
}


Matrix Matrix::solveAx_LU(const Matrix & b) const {

    if (!isSQMatrix()) {
        std::cerr << "La matrice n'est pas carrée..." << std::endl
                    << "Décomposition LU impossible" << std::endl;
        return matrix_null;
    }
    if (!isPositiveDefinite()) {
        std::cerr << "La matrice n'est pas  définie positive..." << std::endl
                    << "Décomposition LU impossible" << std::endl;
        return matrix_null;
    }

    unsigned int i, j, n = rows;
    Matrix l = LUDecomposition().first;
    Matrix u = LUDecomposition().second;
    Matrix x(n,1,Matrix::Z);
    Matrix y(n,1,Matrix::Z);

    y[0][0] = b[0][0];

    for (i = 1; i < n; i++) {
        y[i][0] = b[i][0];
        for (j = 0; j < i; j++) {
            y[i][0] -= (l[i][j] * y[j][0]);
        }
    }

    x[n - 1][0] = y[n - 1][0] / u[n - 1][n - 1];

    for(i = n - 2; i < n; i--) {
        x[i][0] = y[i][0];
        for(j = i + 1; j < n; j++) {
            x[i][0] -= (u[i][j] * x[j][0]);
        }
        if (u[i][i] == 0.0)
            x[i][0] = 0.0;
        else {
            x[i][0] /= u[i][i];
        }
    }

    return x;

}


Matrix Matrix::gramSchmidt() const {

    Matrix a(*this);
    Matrix q(rows,cols,Matrix::Z);

    Matrix temp_matrix (1,rows,Matrix::Z);
    unsigned int i, j, k;
    std::complex<double> coef;
    VectorX temp_vect;

    for(i = 0; i < rows; i++) {
        q[i][0] = a[i][0];
    }

    q = q.normalizeMatrix();

    for (i = 1; i < cols; i++) {
        coef = std::complex<double>(0.0, 0.0);
        temp_matrix = matrixCol(i);
        for (j = 0; j < i; j++) {
            coef = (q.matrixCol(j).transposeMatrix() * a.matrixCol(i))[0][0];
            coef /= (q.matrixCol(j).transposeMatrix() * q.matrixCol(j))[0][0];
            temp_matrix = temp_matrix - (q.matrixCol(j) * coef);
        }
        temp_matrix = temp_matrix.normalizeMatrix();

        for(k = 0; k < rows; k++) {
            q[k][i] = temp_matrix[k][0];
        }
    }

    return q;
}


std::pair<Matrix,Matrix> Matrix::QR_GramSchmidt() const {

    if (cols > rows) {
        std::cerr << "Nombre de lignes inférieur au nombre de colonnes..."
                    << std::endl << "Décomposition QR impossible" << std::endl;
        return std::pair<Matrix,Matrix>(matrix_null,matrix_null);
    }

    Matrix a(*this);
    Matrix q(rows,cols,Matrix::Z);
    Matrix r(cols,cols,Matrix::Z);

    Matrix temp_matrix (1,rows,Matrix::Z);
    unsigned int i, j, k;
    std::complex<double> coef;
    VectorX temp_vect;

    for(i = 0; i < rows; i++) {
        q[i][0] = a[i][0];
    }
    q = q.normalizeMatrix();
    r[0][0] = (a.matrixCol(0).transposeMatrix() * q.matrixCol(0))[0][0];

    for (i = 1; i < cols; i++) {
        coef = std::complex<double>(0.0, 0.0);
        temp_matrix = matrixCol(i);
        for (j = 0; j < i; j++) {
            coef = (q.matrixCol(j).transposeMatrix() * a.matrixCol(i))[0][0];
            r[j][i] = coef;
            coef /= (q.matrixCol(j).transposeMatrix() * q.matrixCol(j))[0][0];
            temp_matrix = temp_matrix - (q.matrixCol(j) * coef);
        }
        temp_matrix = temp_matrix.normalizeMatrix();

        for(k = 0; k < rows; k++) {
            q[k][i] = temp_matrix[k][0];
        }

        r[i][i] = (a.matrixCol(i).transposeMatrix() * q.matrixCol(i))[0][0];
    }

    return (std::pair<Matrix,Matrix> (q,r));
}


std::pair<Matrix,Matrix> Matrix::QR_Householder() const {

    if (cols > rows) {
        std::cerr << "Nombre de lignes inférieur au nombre de colonnes..."
                    << std::endl << "Décomposition QR impossible" << std::endl;
        return std::pair<Matrix,Matrix>(matrix_null,matrix_null);
    }

    unsigned int m = rows;
    unsigned int n = cols;
    Matrix h(m,m,Matrix::I);
    Matrix a(*this);
    VectorX v(m);
    unsigned int i, j, k;
    std::complex<double> alpha (0.0,0.0);
    std::complex<double> beta (0.0,0.0);
    std::complex<double> c (0.0,0.0);

    for (k = 0; k < n - 1; k++) {
        alpha = std::complex<double> (0.0,0.0);
        beta = std::complex<double> (0.0,0.0);

        for (i = k; i < m; i++) {
            alpha = alpha + (a[i][k] * a[i][k]);
        }
        alpha = sqrt(alpha);

        beta = alpha * (alpha - a[k][k]);
        v[k] = a[k][k] - alpha;
        for (i = k + 1; i < m; i++) {    // vecteur v
            v[i] = a[i][k];
        }

        for (j = k; j < n; j++) {      // A^k+1
            c = std::complex<double> (0.0,0.0);
            for (i = k; i < m; i++) {
                c += (v[i] * a[i][j] / beta);
            }
            for (i = k; i < m; i++) {
                a[i][j] -= (c * v[i]);
            }
        }

        for (j = 0; j < m; j++) {    // H = Hk ... H1
            c = std::complex<double> (0.0,0.0);
            for (i = k; i < m; i++) {
                c += (v[i] * h[i][j] / beta);
            }
            for (i = k; i < m; i++) {
                h[i][j] -= (c * v[i]);
            }
        }

    }

    for (i = 0; i < a.getNbCols(); i++) {
        for (j = 0; j < i; j++) {
            a[i][j] = 0.0;
        }
    }
    for (i = a.getNbCols() - 1; i < a.getNbRows(); i++) {
        for (j = 0; j < a.getNbCols() - 1; j++) {
            a[i][j] = 0.0;
        }
    }

    return std::pair<Matrix,Matrix> (h.transposeMatrix(),a);

}


Matrix Matrix::solveAx(const Matrix & b) const {

    if (!isSQMatrix()) {
        std::cerr << "Matrice non carrée..."
                    << std::endl << "Résolution impossible" << std::endl;
        return matrix_null;
    }
    if (rows != b.getNbRows() || b.getNbCols() != 1) {
        std::cerr << "Le vecteur b n'a pas la bonne dimension..."
                << std::endl << "Résolution impossible" << std::endl;
    }

    std::pair<Matrix,Matrix> qr (QR_Householder());
    Matrix q (qr.first.transposeMatrix() * b);
    Matrix r (qr.second);
    Matrix x (cols,1);
    unsigned int i, j;

    x[cols - 1][0] = q[cols - 1][0] / r[cols - 1][cols - 1];

    for (i = cols - 2; i < cols; i--) {
        x[i][0] = q[i][0];
        for(j = i + 1; j < cols; j++) {
            x[i][0] -= (r[i][j] * x[j][0]);
        }
        if (r[i][i] == 0.0)
            x[i][0] = 0.0;
        else {
            x[i][0] /= r[i][i];
        }
    }

    return x;
}


std::pair<Matrix,Matrix> Matrix::cholesky() const {

    if (!isSQMatrix()) {
        std::cerr << "Matrice non carrée" << std::endl
                << "Décomposition de Cholesky impossible" << std::endl;
        return std::pair<Matrix,Matrix> (matrix_null,matrix_null);
    }
    if (!isSymetric()){
        std::cerr << "Matrice non symétrique" << std::endl
                << "Décomposition de Cholesky impossible" << std::endl;
        return std::pair<Matrix,Matrix> (matrix_null,matrix_null);
    }
    if (!isPositiveDefinite()) {
        std::cerr << "Matrice non définie positive" << std::endl
                << "Décomposition de Cholesky impossible" << std::endl;
        return std::pair<Matrix,Matrix> (matrix_null,matrix_null);
    }

    Matrix d (rows,rows,Matrix::Z);
    Matrix l (rows,rows,Matrix::Z);
    unsigned int i, j, k;
    std::complex<double> temp;

    l[0][0] = sqrt(tab[0][0]);

    for (j = 1; j < rows; j++) {
        l[j][0] = tab[0][j] / l[0][0];
    }

    for (i = 1; i < rows; i++) {
        temp = std::complex<double> (0.0,0.0);
        for (k = 0; k < i; k++) {
            temp += l[i][k] * l[i][k];
        }
        l[i][i] = sqrt(tab[i][i] - temp);

        for (j = i + 1; j < rows; j++) {
            temp = std::complex<double> (0.0,0.0);
            for (k = 0; k < i; k++) {
                temp += l[i][k] * l[j][k];
            }
            l[j][i] = (tab[i][j] - temp) / l[i][i];
        }
    }

    return std::pair<Matrix,Matrix> (l,l.conjugateTranspose());

}



void Matrix:: regressionTest() const
{

    cout << endl << endl << "****** DEBUT DU TEST DE REGRESSION DE MATRIX******" << endl << endl << endl;

    complex<double> tra, det ;

    Matrix a(5, 5, {-19,-4,-12,17,4,19,-14,-5,-3,18,-4,-1,-13,0,19,16,5,-25,-22,-23,-9,-9,22,-9,21});
    Matrix b(5, 5, {-13,-24,13,-23,-5,5,12,-24,1,-18,21,-2,-21,-5,-4,-15,13,-11,14,8,12,5,8,-24,-2});
    Matrix c(4, 5, {6,2,0,0,-14,21,-6,21,-16,19,-25,8,-24,-1,-12,15,-6,3,-17,21});
    Matrix d(4, 5, {7,7,14,-13,-12,-7,-10,4,-2,-9,-7,-17,-13,-5,-6,5,19,-15,-3,-21});
    Matrix e(5, 4, {24,-7,15,5,10,-24,-2,-3,-9,-19,5,-9,-5,-22,20,18,-21,18,22,-24});
    Matrix f(5, 5, {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25});
    Matrix g(3, 3, {1,2,3,4,5,6,7,8,0});
    Matrix h(3, 3, {1,2,3,4,5,6,7,8,9});

    Matrix r1(5, 5, {-32,-28,1,-6,-1,24,-2,-29,-2,0,17,-3,-34,-5,15,1,18,-36,-8,-15,3,-4,30,-33,19});
    Matrix r2(4, 5, {13,9,14,-13,-26,14,-16,25,-18,10,-32,-9,-37,-6,-18,20,13,-12,-20,0});
    Matrix r3(5, 5, {-6,20,-25,40,9,14,-26,19,-4,36,-25,1,8,5,23,31,-8,-14,-36,-31,-21,-14,14,15,23});
    Matrix r4(4, 4, {458,-342,-222,360,-64,292,530,-810,-47,245,-795,337,-83,734,374,-744});
    Matrix r5(3, 3, {-16,8,-1,14,-7,2,-1,2,-1});
    Matrix r6(5, 5, {-16687473,-2859275,4429957,38295027,6405675,
                     11243373,2777717,844201,-31171603,-3135973,
                     -12584028,-3513568,10329116,6874376,20116276,
                     24146480,10255020,-32022704,-24798036,-33093968,
                     -8375425,-5884917,24096783,-17068165,33210649});
    Matrix r7(3, 3, {1,0,0,0,1,0,0,0,1});
    Matrix r8(3, 3, {1,0,-1,0,1,2,0,0,0});

    Matrix x(3, 3);
    Matrix x1(3, 3);
    Matrix x2(3, 3);
    Matrix x3(3, 3);
    Matrix y(4, 4);
    Matrix z(5, 5);
    Matrix z1(5, 5);
    Matrix z2(5, 5);
    Matrix z3(5, 5);


    cout << "! Addition de 2 matrices carrées: 5*5 + 5*5" << endl;
    {
        z = a + b;
        z = z.checkCast();
        if(z == r1)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
    }

    cout << "! Addition de 2 matrices non carrées: 4*5 + 4*5" << endl;
    {
        z = c + d;
        z = z.checkCast();
        if (z == r2)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Soustraction de matrices non carrées: 4*5 - 4*5" << endl;
    {
        z = a - b;
        z = z.checkCast();
        if(z == r3)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Multiplication de 2 matrices: 4*5 * 5*4" << endl;
    {
        y = c * e;
        y = y.checkCast();
        if (y == r4)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Calcul de trace" << endl;
    {
        tra = a.trace();
        if(tra + (complex<double>(47.0,0.0)) == 0.0)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Calcul de déterminant" << endl;
    {
        det = f.determinant();
        if (abs(det.real()) < EPSILON && abs(det.imag()) < EPSILON)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl;
        cout << endl;
    }

    cout << "! Calcul d'inverse et test de l'opérateur scale*Matrix" << endl;
    {
        x = (g^-1)*9;
        x = x.checkCast();
        if (x == r5)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Calcul de puissance" << endl;
    {
        z = a^5;
        z = z.checkCast();
        if (r6 == z)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Calcul de G * G^-1" << endl;
    {
        x = g*(g^-1);
        x = x.checkCast();
        if (x == r7)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl ;
        cout << endl ;
    }

    cout << "! Test de allMatrix" << endl;
    {
        g.allMatrix(x1,x2,x3);
        x = x1 * x2 * x3 ;
        x = x.checkCast();
        if (x == g)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }

        cout << "- Test avec une seconde matrice..." << endl; ;

        a.allMatrix(z1,z2,z3);
        z = z1 * z2 * z3;
        if (z.checkCast() == a)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }
        cout << endl << endl  ;
    }




    cout << endl << endl << "******* TEST REUSSI ******" << endl << endl
           <<  "****** FIN DU TEST DE REGRESSION DE MATRIX ******" << endl << endl ;

}
