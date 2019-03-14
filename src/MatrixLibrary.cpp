
#include "MatrixLibrary.h"
#include <iostream>

using namespace std;



MatrixLibrary:: MatrixLibrary () : library (vector<Matrix>())
{
}


MatrixLibrary:: ~MatrixLibrary()
{
}


void MatrixLibrary:: addMatrix ( const Matrix& m )
{
    if (exist(m))
    {
        cerr << "Erreur, ce nom de Matrice existe déja ! " << endl;
        exit (EXIT_FAILURE);
    }
    library.push_back(m);
}


bool MatrixLibrary:: exist (const Matrix& m)
{
}
