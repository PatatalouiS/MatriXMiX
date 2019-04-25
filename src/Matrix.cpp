
#include <iostream>
#include <complex>
#include <fstream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include <stack>
#include <utility>
#include <Dense>
#include "Matrix.h"
#include "Gauss.h"


using namespace std;

const double EPSILON = 0.0001;
const string PATH = "../../data/sauvegarde.txt";

const vector<double> Matrix:: vector_noEigen = vector<double>();
const vector<pair<double,VectorX>> Matrix:: vector_pair_noEigen = vector<pair<double,VectorX>>();
const Matrix Matrix:: matrix_noEigen = Matrix();
const double Matrix:: double_notExist = double();


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
            srand(static_cast<unsigned>(time(nullptr)));

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
    this->rows=row;
    tab=(vector<vector<double>>(rows,vector<double> (cols,0)));
}


void Matrix:: setNbCols(unsigned int col)
{
     this->cols=col;
    tab=(vector<vector<double>>(rows,vector<double> (cols,0)));
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
        return double_notExist;
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


ostream& operator << (ostream& flux, const Matrix & m)
{
    for (auto i : m.tab)
    {
        for (auto j : i)
        {
            if(static_cast<int>(j*1000000) == 0)
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


vector<string> Matrix:: decoupe (const string & expression)
{
    unsigned int i;
    unsigned  long taille =expression.length();
    vector<string> tab;
    string c, temp;
    temp="";

    for (i=0; i<taille; i++)
    {
        c=expression[i];

        if(c == ",")
        {
            if (temp.length()!=0) tab.push_back(temp);
            temp="";
        }
        else if (!c.empty())
        {
            temp+=c;
        }

    }
    if(temp != "")
    tab.push_back(temp);

    return tab;
}


Matrix Matrix:: operator << (const string& values)
{
    string c;
    vector<string> table;
    table=decoupe(values);
    unsigned int i,j;

    if (table.size() != rows*cols)
    {
        cout<<"Le nombre des valeurs rentrées ne correspond pas à la taille de la matrice"<<endl;
    }

    else
    {  for ( i = 0; i < this->rows; i++ )
        {
            for ( j = 0; j < this->cols; j++ )
            {
                c=table[i*cols+j];
                tab[i][j]=atof(c.c_str());
            }
        }
     }
    return *this;
}


istream& operator >> (istream& flux, Matrix & m)
{
    unsigned int i,j,rows,cols;
    cout<<"Entrez le nombre de lignes puis de colonnes"<<endl;
    flux>>rows>>cols;
    double value;
    m.setNbRows(rows);
    m.setNbCols(cols);

    cout<<"Entrez les valeurs de la matrice"<<endl;
    for ( i = 0; i < rows; ++i )
    {
        for ( j = 0; j < cols; ++j )
        {
            flux >> value;
            m.tab[i][j]=value;
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


const Matrix Matrix:: operator+ (const Matrix & m) const
{
    if ( (rows!=m.rows) || (cols!=m.cols) )
    {
        cout << "Addition impossible!" << endl;
        return matrix_noEigen;
    }

    Matrix copy(*this);

    for (unsigned int i=0; i< rows; i++)
    {
        for (unsigned int j=0; j< cols; j++)
        {
            copy[i][j]=copy[i][j]+m[i][j];
        }
    }
    return copy;
}


const Matrix Matrix:: operator- (const Matrix & m) const
{
    if ((rows!=m.rows) || (cols!=m.cols))
    {
        cout << "Soustraction impossible!" << endl;
        return matrix_noEigen;
    }

    Matrix copy(*this);

    for (unsigned int i=0; i<m.rows; i++)
    {
        for (unsigned int j=0; j<m.cols; j++)
        {
            copy[i][j]=copy[i][j]-m[i][j];
        }
    }
    return copy;
}


const Matrix Matrix:: operator * (const Matrix & m) const
{
    if (cols != m.rows)
    {
        cout << "Multiplication impossible!" << endl << "A * B->Le nombre de ligne de A = nombre de colonne de B!" << endl;
        return matrix_noEigen;
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
    Matrix copy(*this);

    for (unsigned int i=0; i < rows; i++)
    {
        for (unsigned int j=0; j < cols; j++)
        {
            copy[i][j]=lambda*copy[i][j];
        }
    }
    return copy;
}


const Matrix operator * (const double & lambda, const Matrix & m)
{
    return m*lambda;
}


const Matrix Matrix:: operator / (const Matrix & m) const
{
    if ( !m.isSQMatrix() )
    {
        cerr << "La division est impossible, le diviseur n'est pas une matrice carrée !" << endl;
        return matrix_noEigen;
    }
    if (m.determinant() == 0.0)
    {
        cerr << "division impossible, la metrice diviseur n'est pas inversible !" << endl;
        exit(EXIT_FAILURE);
    }
    Matrix result( (*this) * m.inverse());
    return result.checkCast();
}


const Matrix Matrix:: operator ^ (const int & p) const
{
    if ( p < -1 )
    {
        cerr << "Erreur, la puissance demandée est invalide ! " << endl;
        return matrix_noEigen;
    }

    if ( !isSQMatrix() )
    {
        cerr << "Erreur, la matrice n'est pas carrée ! " << endl;
        return matrix_noEigen;
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

    for (int i=1; i<p; ++i )
    {
        temp = (temp * temp2);
    }
    return temp.checkCast();
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
                if (tab[i][j] - m.tab[i][j] != 0.0 )
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


Matrix Matrix:: checkCast() const
{
    Matrix result(*this);
    unsigned int i, j, r, c;
    r = getNbRows();
    c = getNbCols();
    int l;

    for (i =0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            for (l = -150 ; l < 150; l++)
            {
                if ( abs(tab[i][j]-l) < EPSILON )
                {
                    result[i][j] = l;
                    continue ;
                }
                else
                    result[i][j] = tab[i][j];
            }
        }
    }
    return result;
}


bool Matrix:: isSQMatrix() const
{
    return rows==cols;
}


double Matrix:: traceMatrix() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul de la trace impossible, la matrice n'est pas carrée" << endl;
        return double_notExist;
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
    if ( !isSQMatrix() )
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        return double_notExist;
    }

    unsigned int i,j,r,c;
    r = getNbRows();
    c = getNbCols();

    for (i=0; i<r; i++)
    {
        for (j=0; j<c; j++)
        {
            if ( (i!=j) && tab[i]==tab[j])
            {
                return 0.0;
            }
        }
    }


    return determinant(rows);
}


Matrix Matrix::coMatrix() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul de la comatrice impossible, la matrice n'est pas carrée" << endl;
        return matrix_noEigen;
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
    return com.checkCast();
}


Matrix Matrix:: transposeMatrix() const
{
    Matrix copy(*this);

    for (unsigned int i=0; i<copy.rows; i++)
    {
        for (unsigned int j=0; j<copy.cols; j++)
        {
            copy[i][j] = tab[j][i];
        }
    }
    return copy.checkCast();
}


Matrix Matrix:: inverse() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        return matrix_noEigen;
    }

    if (determinant() == 0.0)
    {
        cerr << "Le déterminant est nul, la matrice n'est donc pas inversible!" << endl;
        return matrix_noEigen;
    }

    Matrix temp(rows,cols), inverse(rows,cols);
    temp=(*this).coMatrix();
    temp=temp.transposeMatrix();
    inverse=temp*(1/determinant());

    return inverse.checkCast();
}


unsigned int Matrix:: rank()const
{
    unsigned int i, j, r, c, rg = 0;
    bool non_zero = false;
    r = getNbRows();
    c = getNbCols();
    Matrix copy(*this);
    copy = copy.gaussReduction();

    for (i = 0; i < r; i++)
    {
        non_zero = false;
        for (j = 0; j < c; j++)
        {
            if (copy[i][j]!=0.0)
            {
                non_zero = true;
            }
        }
        if (non_zero)
        {
            rg++;
        }
    }

    return rg;
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
    unsigned int i,j,x,subi=0,subj=0;

    Matrix submatrix (dim,dim);
    double det = 0;

    if ( dim == 1 )
    {
        return tab[0][0];
    }

    if (dim == 2)
    {
        return ((tab[0][0] * tab[1][1]) - (tab[1][0] * tab[0][1]));
    }

    for (x=0; x<dim; x++)
    {
        subi = 0;
        for (i=1; i<dim; i++)
        {
            subj = 0;
            for (j=0; j<dim; j++)
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


Eigen::MatrixXd Matrix:: class2Eigen () const
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


const Matrix Matrix:: eigen2Class(const Eigen::MatrixXd & m) const
{
    unsigned int i,j,r,c ;
    r = static_cast<unsigned int>(m.rows());
    c = static_cast<unsigned int>(m.cols());
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






// *********   FONCTIONS D'ETUDE DE MATRICES    *********


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
        nonzero_row_id = g.is_nonzero_column(res, col, r, next_row_id);
        if (nonzero_row_id >= 0)
        {
            if (nonzero_row_id != next_row_id)
            {
                g.row_exchange(res.tab.begin() + next_row_id, res.tab.begin() + nonzero_row_id);
                nonzero_row_id = next_row_id;
            }
            pivot_gauss.push_back(Gauss(nonzero_row_id, col));
            for (int row = next_row_id; row < r; row++)
            {
                if (res[row][col] == 0.0)
                    continue;
                if (row == nonzero_row_id)
                    continue;
                g.row_replace(res.tab.begin() + row,
                            res.tab.begin() + nonzero_row_id,
                            -res.tab[row][col] / res.tab[nonzero_row_id][col]);
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

        if (pos->getVal(res) != 1.0)
        {
            g.row_scale(res.tab.begin() + pos->row, 1 / res.tab[pos->row][pos->col]);
        }

        for (int row = 0; row < r; row++)
        {
            if (res.tab[row][pos->col] != 0.0 && row != pos->row)
            {
                g.row_replace(res.tab.begin() + row, res.tab.begin() + pos->row,
                            -res.tab[row][pos->col] / res.tab[pos->row][pos->col]);
            }
        }
    }

    return res;
}


const pair<unsigned int, unsigned int> Matrix:: dimensionsStudy()const
{
    unsigned int dim_E = getNbRows();
    unsigned int dim_im = rank();
    unsigned int dim_ker = dim_E - dim_im;

    return make_pair(dim_im,dim_ker);
}


const vector<double> Matrix:: eigenValues() const
{
    unsigned int i,n;
    vector<double> result;
    Eigen::MatrixXd a;

    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> m(a);
    n = static_cast<unsigned int>(m.eigenvalues().size());

    for (i=0; i<n; i++)
    {
        if (m.eigenvalues()(i).imag() != 0.0)
        {
            return Matrix::vector_noEigen;
        }

        if(abs(m.eigenvalues()(i).real()) < EPSILON)
            result.push_back(0);
        else
            result.push_back(m.eigenvalues()(i).real());
    }

    return result;
}


const Polynomial Matrix:: characteristicPolynomial()const
{
    unsigned int i,r;
    r = getNbRows();
    Polynomial result(r);
    Polynomial temp(1);



    vector<double> eigen_values;
    eigen_values = eigenValues();
    if (eigen_values == vector_noEigen)
        return Polynomial:: polynomial_noEigen;

    result.tab[0] = eigen_values[0];
    result.tab[1] = -1;
    for(i = 2; i < r+1; i++)
    {
        result.tab[i] = 0;
    }

    for(i = 1; i < r; i++)
    {
        temp.tab[0] = eigen_values[i];
        temp.tab[1] = -1;
        result = result*temp;
    }

    return result;
}


const vector<Polynomial> Matrix:: splitCharacteristicPolynomial()const
{
    vector<Polynomial> result;
    Polynomial temp(1);
    unsigned int i,r,c;
    r = getNbRows();
    c = getNbCols();

    vector<double> eigen_values;
    eigen_values = eigenValues();

    for(i = 0; i < r; i++)
    {
        temp.tab[0] = eigen_values[i];
        temp.tab[1] = -1;
        result.push_back(temp);
    }

    return result;
}


const vector<VectorX> Matrix:: eigenVectors()const
{
    unsigned int i, j, n=getNbRows();
    vector<VectorX> tab;
    VectorX temp;

    Matrix a(n,n);
    a=transferMatrix();

    for(i=0; i<n; i++)
    {
        temp.clear();

        for(j=0; j<n; j++)
        {
            temp.push_back(a[i][j]);
        }

    tab.push_back(temp);

    }

    return tab;

}


const vector<pair<double,VectorX>> Matrix:: allEigen()const
{
    unsigned int i;
    unsigned long int n;
    vector<VectorX> e_vector;
    vector<double> e_value;
    vector<double> null_vect = vector<double>();
    pair<double,VectorX> temp_pair;
    vector<pair<double,VectorX>> result;

    e_value = eigenValues();
    e_vector = eigenVectors();
    if (e_value == vector_noEigen)
        return vector_pair_noEigen;

    n = e_value.size();

    for(i=0; i<n; i++)
    {
        temp_pair = make_pair(e_value[i],e_vector[i]);
        result.push_back(temp_pair) ;

    }
    return result;
}


bool Matrix:: isDiagonalisable()const
{
    if (!isSQMatrix())
        return false;

    Matrix copy(*this);
    Matrix P1(*this);
    Matrix P2(*this);

    allMatrix(P1,copy,P2);

    if (P1==P2)
    {
        return false;
    }

    unsigned int i, j, r, c;
    r = copy.getNbRows();
    c = copy.getNbCols();

    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            if (i!=j && copy[i][j]!=0.0)
                return false;
        }
    }

    return true;
}


const Matrix Matrix:: diagonalise()const
{

    Matrix m;
    Eigen:: MatrixXd a,b;
    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> res(a);
    b = res.pseudoEigenvalueMatrix();
    m = eigen2Class(b);

    return m.checkCast();

}


const Matrix Matrix::transferMatrix()const
{
    unsigned int i, j, n=getNbRows();
    Matrix result(n,n);
    Eigen::MatrixXd a;

    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> m(a);

    result = eigen2Class(m.pseudoEigenvectors());

    for(i=0; i<n; i++)
    {

        for(j=0; j<n; j++)
        {
            if (abs(result[i][j]) < EPSILON)
                result[i][j]=0;
        }

    }

    return result.checkCast();

}


void Matrix:: allMatrix (Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C) const
{
   transferC2B = transferMatrix();
   diagonal = diagonalise();
   if (transferC2B.determinant()==0.0)
       transferB2C = matrix_noEigen;
   else
       transferB2C = (transferC2B^-1);
}


void Matrix::testRegression() const
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
        if(tra + 47 == 0.0)
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
        if(det == 0.0)
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
        if(det == 8366164.0)
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




/*
 début
pour i= 1 :n
L(i,i) = 1
    pour j=max(1,i−b) :i−1
        L(i,j) =A(i,j)
        pourk=max(1,i−b,j−b) :j−1
            L(i,j) =L(i,j)−L(i,k)∗D(k,k)∗L(j,k)
        L(i,j) =L(i,j)/D(j,j)
    D(i,i) =A(i,i)
    pourj=max(1,i−b) :i−1
        D(i,i) =D(i,i)−L(i,j)2∗D(j,j)
fin
*/
