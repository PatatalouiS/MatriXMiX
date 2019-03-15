
#include "MatrixLibrary.h"
#include <iostream>

using namespace std;



MatrixLibrary:: MatrixLibrary () : tab (vector<Matrix>())
{
}


MatrixLibrary:: ~MatrixLibrary()
{
}


unsigned int MatrixLibrary:: size () const
{
    return tab.size();
}


bool MatrixLibrary:: empty () const
{
    return size() == 0;
}


bool MatrixLibrary:: exist (const Matrix& m) const
{
    return false; // TEMPORAIRE
}


void MatrixLibrary:: print () const
{
    if (tab.size() == 0)
    {
        cout << "Aucune Matrice n'est rentrée !" << endl;
    }
    else
    {
        for(const auto& Mat: tab)
        {
            cout << "Matrice " << Mat.getName() << " : " << endl << Mat << endl;
        }
        cout << endl;
    }
}


void MatrixLibrary:: addMatrix ( const Matrix& m )
{
    if (exist(m))
    {
        cerr << "Erreur, la matrice" << m.getName() << " existe déjà !" << endl;
        exit(EXIT_FAILURE);
    }
    tab.push_back(m);
}

