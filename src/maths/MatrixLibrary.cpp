
#include "MatrixLibrary.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;



MatrixLibrary:: MatrixLibrary () : tab (map<string, pair<Matrix,complex<double>>>())
{
}


MatrixLibrary::  MatrixLibrary (const MatrixLibrary & lib)
{
    for (auto it = lib.tab.begin(); it != lib.tab.end(); it++ )
    {
        addMatrix(it->first,it->second.first);
    }
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
    return (size() == 0);
}


void MatrixLibrary:: clear ()
{
    tab.clear();
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
        cout << endl << endl << Mat.second.first << endl;;
    }
    cout << endl;
}


bool MatrixLibrary:: isName(const string & chain) const
{
    unsigned long int i = 1, s = chain.length();

    if ( !( ((chain[0] >= 'A') && (chain[0] <= 'Z'))
            || ((chain[0] >= 'a') && (chain[0] <= 'z')) ) )
        return false;

    while (i<s)
    {
        if ( ((chain[i] >= 'A') && (chain[i] <= 'Z'))
             || ((chain[i] >= 'a') && (chain[i] <= 'z'))
             || ((chain[i] >= '0') && (chain[i] <= '9')))
            i++;
        else return false;
    }

    return true;
}



void MatrixLibrary:: addMatrix (const string& name, const Matrix & m)
{
    if (isName(name))
        tab.insert({name, pair<Matrix,complex<double>> (m,m.determinant())});
    else cout<<"Nom de matrice non autorisé, veuillez choisir un autre..."<<endl;
}


const Matrix* MatrixLibrary:: find_matrix (const string& name) const
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &((tab.at(name)).first);
}


Matrix* MatrixLibrary:: find_matrix (const string& name)
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &((tab.at(name)).first);
}


const complex<double>* MatrixLibrary:: find_determinant (const string& name) const
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &((tab.at(name)).second);
}


complex<double>* MatrixLibrary:: find_determinant (const string& name)
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &((tab.at(name)).second);
}



void MatrixLibrary:: erase (const string & name)
{
    tab.erase(name);
    if(exist(name))
    {
        cout << "Suppression non effectuée" << endl;
    }
}


const map<string, pair<Matrix,complex<double>>>& MatrixLibrary:: data () const
{
    return tab;
}




void MatrixLibrary:: saveFile (const string & filename) const
{
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du fichier "
                "\nVeuillez vérifier le chemin du fichier" << endl;
        exit(EXIT_FAILURE);
    }

    file << "Matrix" << endl;

    for (auto it = tab.begin(); it != tab.end(); it++ )
    {
       string matrixname = it->first;
       Matrix m(*find_matrix(matrixname));

       file << endl << matrixname << endl;
       file << m.getNbRows() << " " << m.getNbCols() << endl;

       for (unsigned int i = 0; i < m.getNbRows(); i++)
       {
           for (unsigned int j = 0; j < m.getNbCols(); j++)
           {

               file << m[i][j] << " ";
           }
           file << endl;
       }
       cout << "La sauvegarde de la matrice " << matrixname << " est réussie" << endl << endl;
    }

    file.close();
}


void MatrixLibrary:: readFile (const string & filename)
{
    string matrixname;
    unsigned int r,c;
    ifstream file (filename.c_str());

    clear();

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
    }

    string testfile;
    file >> testfile ;

    if( testfile == "Matrix")
    {
        while(!file.eof())
        {
            file >> matrixname;
            file >> r >> c;

            Matrix m(r,c);

            for (unsigned int i = 0; i < r; i++)
            {
                for (unsigned int j = 0; j < c; j++)
                {
                    file >> m[i][j];
                }

            }
            addMatrix(matrixname,m);
        }

        file.close();

    }
    else
    {
        cout << "Erreur, ce fichier ne contient pas des matrices !" << endl ;

    }
}
