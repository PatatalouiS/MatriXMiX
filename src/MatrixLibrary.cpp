
#include "MatrixLibrary.h"
#include <iostream>


using namespace std;


MatrixLibrary:: MatrixLibrary () : tab (map<string, Matrix>())
{
}


MatrixLibrary:: ~MatrixLibrary()
{
}


unsigned long int MatrixLibrary:: size () const
{
    return tab.size();
}


bool MatrixLibrary:: isEmpty () const
{
    return size() == 0;
}


bool MatrixLibrary:: exist (const string& name) const
{
    return (tab.count(name) != 0);
}


void MatrixLibrary:: print () const
{
    for(const auto& Mat: tab)
    { 
        cout << "Matrice " << Mat.first << " : ";
        cout << endl << endl << Mat.second << endl;;
    }
    cout << endl;
}


void MatrixLibrary:: addMatrix (const string& name, const Matrix& m)
{
    tab.insert({name, m});
}


const Matrix* MatrixLibrary:: find (const string& name) const
{
    if (tab.count(name) == 0)
    {
        return NULL;
    }
    return &tab.at(name);
}


void MatrixLibrary:: erase (const string & name)
{
    if(tab.erase(name)!=1)
    {
        cout << "Suppression non effectuée" << endl;
    }
}


const std::map<std::string, Matrix>& MatrixLibrary:: data () const
{
    return tab;
}


bool MatrixLibrary:: isAuthorisedName(const string & chaine)
{
    unsigned int i=0;
    long int s=chaine.length();

    while (i<s)
    {
        if ( ((chaine[i]>'A') && (chaine[i]<'Z'))
            || ((chaine[i]>'a') && (chaine[i]<'z'))
            || ((chaine[i]>'0') && (chaine[i]<'9')) )
            i++;
        else return false;
    }

    return true;
}


bool MatrixLibrary:: isName(const string & chaine)
{
    unsigned int i=0;
    long int s=chaine.length();

    while (i<s)
    {
        if ( ((chaine[i]>'A') && (chaine[i]<'Z'))
             || ((chaine[i]>'a') && (chaine[i]<'z')) )
            i++;
        else return false;
    }

    return true;
}


bool MatrixLibrary:: isFloat(const string & chaine)
{
    long int i=0, nbcoma=0;
    long int s=chaine.length();

    while (i<s)
    {
        if (chaine[i]=='.')
            nbcoma++;
        else if (! ((chaine[i]>='0') && (chaine[i]<='9')) )
            return false ;

        if (nbcoma > 1)
            return false;

        i++;
    }

    return true;
}


