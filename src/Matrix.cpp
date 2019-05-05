
#include <iostream>
#include <complex>
#include <cstring>
#include <cmath>
#include <utility>
#include <Dense>
#include "Matrix.h"
#include "Gauss.h"


using namespace std;

const double EPSILON = 0.0001;


const vector<double> Matrix:: vector_noEigen = vector<double>();
const vector<pair<double,VectorX>> Matrix:: vector_pair_noEigen = vector<pair<double,VectorX>>();
const Matrix Matrix:: matrix_noEigen = Matrix();
const Matrix Matrix:: matrix_null = Matrix();
const double Matrix:: double_notExist = double();


// ********* CONSTRUCTORS / DESTRUCTORS *********



Matrix:: Matrix () : tab ( vector<vector<double>> ())
{
    rows = 0;
    cols = 0;
}


Matrix:: Matrix (const unsigned int rows, const unsigned int cols, const double value) :
        tab (vector<vector<double>>(rows,vector<double> (cols, value)))
{
    this->rows = rows;
    this->cols = cols;
}


Matrix:: Matrix (const unsigned int rows, const unsigned int cols, const enum initMatrix& type) :
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






// ******** STATIC FUNCTION *********


Matrix Matrix:: ID (const unsigned int size)
{
    return Matrix(size, size, Matrix::I);
}





// ******* ACCESSORS / MUTATORS & BASIC FUNCTIONS ********


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


double& Matrix:: getVal (const unsigned int indice)
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }

    return tab[indice/rows][indice%rows];
}


double Matrix:: getVal (const unsigned int indice) const
{
    if ( indice >= (rows * cols))
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        return double_notExist;
    }

    return tab[indice/rows][indice%rows];
}


vector<double>&  Matrix:: operator [] (const unsigned int indice)
{
    if ( indice >= rows)
    {
        cerr << "L'indice" << indice <<" n'existe pas dans cette matrice" << endl;
        exit ( EXIT_FAILURE );
    }
    return tab[indice];
}


const std::vector<double>& Matrix:: operator [] (const unsigned int indice) const
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
            flux << j << "  ";
        }
        flux << endl;
    }
    return flux;
}


Matrix Matrix:: operator << (const string& values)
{
    unsigned int i,j;
    string c;
    vector<string> table;
    table = explode(values);

    if (table.size() != rows*cols)
    {
        cerr <<"Le nombre des valeurs rentrées ne correspond pas à la taille de la matrice" << endl;
        return matrix_noEigen;
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


const Matrix Matrix:: operator + (const Matrix & m) const
{
    if ( (rows!=m.rows) || (cols!=m.cols) )
    {
        cerr << "Addition impossible!" << endl;
        return matrix_noEigen;
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
        return matrix_noEigen;
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
        return matrix_noEigen;
    }

    unsigned int i,j,k;
    double sum;
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


const Matrix Matrix:: operator * (const double & lambda) const
{
    unsigned int i,j;
    Matrix copy(*this);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            copy[i][j] = lambda * copy[i][j];
        }
    }
    return copy;
}


const Matrix operator * (const double & lambda, const Matrix & m)    // friend operator
{
    return m * lambda;
}


const Matrix Matrix:: operator / (const Matrix & m) const
{
    if ( !m.isSQMatrix() )
    {
        cerr << "Division est impossible, la matrice diviseure n'est pas une matrice carrée !" << endl;
        return matrix_null;
    }
    if (m.isNulDeterminant())
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


bool Matrix:: isSQMatrix() const
{
    return rows == cols;
}


double Matrix:: traceMatrix() const
{
    if ( !isSQMatrix() )
    {
        cerr << "Calcul de la trace impossible, la matrice n'est pas carrée" << endl;
        return double_notExist;
    }

    double s = 0;
    for ( unsigned int i = 0; i < rows; i++)
    {
        s += tab[i][i];
    }
    return s;
}


double Matrix:: determinant() const
{
    if (!isSQMatrix())
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        return double_notExist;
    }
    if (isNulDeterminant())
        return 0.0;

    return determinant(rows);   // call to the private recursive function
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
    Matrix copy(*this);

    for (i = 0; i < copy.rows; i++)
    {
        for (j = 0; j < copy.cols; j++)
        {
            copy[i][j] = tab[j][i];
        }
    }
    return copy;
}


Matrix Matrix:: inverse() const
{
    if (!isSQMatrix())
    {
        cerr << "Calcul du déterminant impossible, la matrice n'est pas carrée" << endl;
        return matrix_null;
    }

    if (isNulDeterminant())
    {
        cerr << "Le déterminant est nul, la matrice n'est donc pas inversible!" << endl;
        return matrix_null;
    }

    Matrix temp(rows,cols), inverse(rows,cols);
    temp = (*this).coMatrix();
    temp = temp.transposeMatrix();
    inverse = temp * (1 / determinant());

    return inverse;
}


unsigned int Matrix:: rank()const
{
    unsigned int i, j, r, c, rg = 0;
    bool non_zero = false;
    r = getNbRows();
    c = getNbCols();
    Matrix reduction(*this);
    reduction = reduction.gaussReduction();

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





// ********   PRIVATE FUNCTIONS   ***********

Matrix Matrix:: checkCast() const
{
    unsigned int i, j, r, c;
    r = getNbRows();
    c = getNbCols();
    int l;
    Matrix result(*this);

    for (i =0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            for (l = -150 ; l < 150; l++)
            {
                if ( abs(tab[i][j] - l) < EPSILON )
                {
                    result[i][j] = l;
                }
            }
        }
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


double Matrix:: determinant(const unsigned int & dim) const
{
    unsigned int i, j, x, subi = 0, subj = 0;

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

    for (x = 0; x < dim; x++)
    {
        subi = 0;
        for (i = 1; i < dim; i++)
        {
            subj = 0;
            for (j = 0; j < dim; j++)
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


bool Matrix:: isNulDeterminant() const
{
    return (! (rows == rank()));
}


Eigen::MatrixXd Matrix:: class2Eigen () const
{
    unsigned int i, j, r, c;
    r = getNbRows();
    c = getNbCols();
    Eigen:: MatrixXd m(r,c);

    for(i = 0 ; i < r ; i++)
    {
        for(j = 0 ; j < c ; j++)
        {
            m(i,j) = tab[i][j] ;
        }
    }

    return m;
}


const Matrix Matrix:: eigen2Class(const Eigen::MatrixXd & m) const
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






// *********   ADVANCED MATRIX STUDY FUNCTIONS   *********


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
                            -res.tab[static_cast<unsigned int>(row)][static_cast<unsigned int>(col)] /
                        res.tab[static_cast<unsigned int>(nonzero_row_id)][static_cast<unsigned int>(col)]);
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
            g.rowScale(res.tab.begin() + pos->row, 1
                       / res.tab[static_cast<unsigned int>(pos->row)][static_cast<unsigned int>(pos->col)]);
        }

        for (int row = 0; row < r; row++)
        {
            if (res.tab[static_cast<unsigned int>(row)][static_cast<unsigned int>(pos->col)] != 0.0 && row != pos->row)
            {
                g.rowReplace(res.tab.begin() + row, res.tab.begin() + pos->row,
                            -res.tab[static_cast<unsigned int>(row)][static_cast<unsigned int>(pos->col)]
                        / res.tab[static_cast<unsigned int>(pos->row)][static_cast<unsigned int>(pos->col)]);
            }
        }
    }

    return res;
}


const pair<unsigned int, unsigned int> Matrix:: dimensionsStudy()const
{
    unsigned int dim_E = getNbCols();   // number of cols = dimension of start set of linear application
    unsigned int dim_im = rank();
    unsigned int dim_ker = dim_E - dim_im;   // using rank theorem

    return make_pair(dim_im,dim_ker);
}


const vector<double> Matrix:: eigenValues() const
{
    unsigned int i, n;
    vector<double> result;
    Eigen::MatrixXd a;

    // convertion to eigen3 MatrixXd and using its solver
    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> m(a);
    n = static_cast<unsigned int>(m.eigenvalues().size());

    for (i = 0; i < n; i++)
    {
        if (m.eigenvalues()(i).imag() != 0.0) // no study of complex matrix
        {
            return Matrix::vector_noEigen;
        }

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
        return Polynomial:: polynomial_noEigen;  // no study of complex matrix

    // matrix characteristic polynomial is eigen values product
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
        result = result * temp;
    }

    return result;
}


const vector<Polynomial> Matrix:: splitCharacteristicPolynomial()const
{
    vector<Polynomial> result;
    Polynomial temp(1);
    unsigned int i,r;
    r = getNbRows();

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
    unsigned int i, j, n = getNbRows();
    vector<VectorX> tab;
    VectorX temp;

    Matrix a(n,n);
    a = transferMatrix();

    for(i = 0; i<n; i++)
    {
        temp.clear();

        for(j = 0; j<n; j++)
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
    {
        return vector_pair_noEigen;

    }

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
    Matrix p1(*this);
    Matrix p2(*this);

    allMatrix(p1,copy,p2);
    if (p2 == matrix_noEigen)
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
    return m;

}


const Matrix Matrix::transferMatrix()const
{
    if (!isSQMatrix())
        return matrix_noEigen;

    unsigned int n = getNbRows();
    Matrix result(n,n);
    Eigen::MatrixXd a;

    a = class2Eigen();
    Eigen::EigenSolver<Eigen::MatrixXd> m(a);

    result = eigen2Class(m.pseudoEigenvectors());

    return result;

}


void Matrix:: allMatrix (Matrix & transferC2B, Matrix & diagonal, Matrix & transferB2C) const
{
   transferC2B = transferMatrix();
   diagonal = diagonalise();
   if (transferC2B.isNulDeterminant())
   {
       transferB2C = matrix_noEigen;
   }
   else
   {
       transferB2C = (transferC2B^-1);
   }

}


void Matrix:: regressionTest() const
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
        tra = a.traceMatrix();
        if(tra + 47 == 0.0)
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
        if (det == 0.0)
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

    cout << "! Echelonnage d'une matrice avec la méthode de Gauss" << endl;
    {
        if (g.gaussReduction() == r7)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }

        cout << "- Test avec une seconde matrice..." << endl ;

        if (h.gaussReduction() == r8)
            cout << "Résultat correct! Poursuite..." << endl;
        else
        {
            cout << "Erreur détectée! \nEchec du test..." << endl;
            return ;
        }

        cout << endl << endl  ;
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
           <<  "****** FIN DU TEST DE REGRESSION ******" << endl << endl ;

}


