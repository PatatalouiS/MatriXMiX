
#include "MatrixLibrary.h"
#include <iostream>

using namespace std;



MatrixLibrary:: MatrixLibrary () : tab (map<string, Matrix>())
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
    return (tab.count(m.getName()) != 0);
}


void MatrixLibrary:: print () const
{
    for(const auto& Mat: tab)
    {
        cout << "Matrice " << Mat.second.getName() << " : ";
        cout << endl << endl << Mat.second << endl;;
    }
    cout << endl;
}



void MatrixLibrary:: addMatrix ( const Matrix& m )
{
    tab.insert({m.getName(), m});
}


const Matrix* MatrixLibrary:: search (const std::string& name) const
{
    Matrix();
    
    if (tab.count(name) == 0)
    {
        return NULL;
    }
    return &tab.at(name);
}
