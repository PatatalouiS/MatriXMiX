
#include "QMatrixLibrary.hpp"
#include <stack>
#include <iostream>
#include <fstream>
#include <cassert>
#include <mpParser.h>

using namespace std;

mup::ParserX QMatrixLibrary::parser = mup::ParserX();


QMatrixLibrary:: QMatrixLibrary () : tab(map<string, UserMatrix>())
{}


QMatrixLibrary::  QMatrixLibrary (const QMatrixLibrary & lib) {
    for(const auto& [ name, qMatrix ] : lib.data()) {
        tab.insert({ name, qMatrix });
    }
}


unsigned long int QMatrixLibrary:: size () const {
    return tab.size();
}


bool QMatrixLibrary:: isEmpty () const {
    return (size() == 0);
}


void QMatrixLibrary:: clear () {
    tab.clear();
}


bool QMatrixLibrary:: exist (const string& name) const {
    return (tab.count(name) != 0);
}


void QMatrixLibrary:: print () const {
    for(const auto& [ name, qMatrix ] : tab) {
        cout << "Matrice " << name << " : "
            << endl << endl << qMatrix.matrix << endl;
    }
    cout << endl;
}


bool QMatrixLibrary:: isName(const string & chain) const {
    unsigned long int i = 1, s = chain.length();

    if ( !( ((chain[0] >= 'A') && (chain[0] <= 'Z'))
            || ((chain[0] >= 'a') && (chain[0] <= 'z')) ) )
        return false;

    while (i<s) {
        if ( ((chain[i] >= 'A') && (chain[i] <= 'Z'))
             || ((chain[i] >= 'a') && (chain[i] <= 'z'))
             || ((chain[i] >= '0') && (chain[i] <= '9')))
            i++;
        else return false;
    }
    return true;
}


void QMatrixLibrary:: addMatrix (const string& name, const UserInputs& entries) {
    if(isName(name)) {

        VectorX values;

        for(const string& entry : entries) {
            parser.SetExpr(entry);
            values.push_back(parser.Eval().GetComplex());
        }

        Matrix newMatrix(entries.getRows(), entries.getCols(), values);

        tab.insert({ name, {  newMatrix,
                              newMatrix.determinant(),
                              entries                   }});
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
    }
}


void QMatrixLibrary:: addMatrix (const string& name, const Matrix& m) {
    if(isName(name)) {

        UserInputs defaults(m.getNbRows(), m.getNbCols());

        for(unsigned int i = 0; i < m.getNbRows() * m.getNbCols(); ++i) {
            //complex to string
        }

        tab.insert({ name, { m,
                            m.determinant(),
                            defaults }});
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
    }
}


const Matrix* QMatrixLibrary:: find_matrix (const string& name) const {
    if(tab.count(name) == 0) {
        return nullptr;
    }
    return &(tab.at(name).matrix);
}


Matrix* QMatrixLibrary:: find_matrix (const string& name) {
    return const_cast<Matrix*>(static_cast<const QMatrixLibrary&>(*this).find_matrix(name));
}


const Value* QMatrixLibrary:: find_determinant (const string& name) const {
    if(tab.count(name) == 0) {
        return nullptr;
    }
    return &(tab.at(name).determinant);
}


Value* QMatrixLibrary:: find_determinant (const string& name) {
    return const_cast<Value*>(static_cast<const QMatrixLibrary&>(*this).find_determinant(name));
}



void QMatrixLibrary:: erase (const string & name) {
    tab.erase(name);
    if(exist(name)) {
        cout << "Suppression non effectuée" << endl;
    }
}


const std::map<std::string, UserMatrix>& QMatrixLibrary:: data () const {
    return tab;
}

// to recode later, we must implement expr support
void QMatrixLibrary:: saveFile (const string & filename) const
{
//    ofstream file (filename.c_str());

//    if(!file.is_open())
//    {
//        cout << "Erreur lors de la lecture du fichier "
//                "\nVeuillez vérifier le chemin du fichier" << endl;
//        exit(EXIT_FAILURE);
//    }

//    file << "Matrix" << endl;

//    for (auto it = tab.begin(); it != tab.end(); it++ )
//    {
//       string matrixname = it->first;
//       Matrix m(*find_matrix(matrixname));

//       file << endl << matrixname << endl;
//       file << m.getNbRows() << " " << m.getNbCols() << endl;

//       for (unsigned int i = 0; i < m.getNbRows(); i++)
//       {
//           for (unsigned int j = 0; j < m.getNbCols(); j++)
//           {

//               file << m[i][j] << " ";
//           }
//           file << endl;
//       }
//       cout << "La sauvegarde de la matrice " << matrixname << " est réussie" << endl << endl;
//    }

//    file.close();
}

// To recode later, we must implement expr support
void QMatrixLibrary:: readFile (const string & filename)
{
//    string matrixname;
//    unsigned int r,c;
//    ifstream file (filename.c_str());

//    clear();

//    if(!file.is_open())
//    {
//        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
//    }

//    string testfile;
//    file >> testfile ;

//    if( testfile == "Matrix")
//    {
//        while(!file.eof())
//        {
//            file >> matrixname;
//            file >> r >> c;

//            Matrix m(r,c);

//            for (unsigned int i = 0; i < r; i++)
//            {
//                for (unsigned int j = 0; j < c; j++)
//                {
//                    file >> m[i][j];
//                }

//            }
//            addMatrix(matrixname,m);
//        }

//        file.close();

//    }
//    else
//    {
//        cout << "Erreur, ce fichier ne contient pas des matrices !" << endl ;

//    }
}
