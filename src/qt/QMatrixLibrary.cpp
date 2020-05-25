
#include "QMatrixLibrary.hpp"
#include <fstream>
#include <cassert>
#include <mpParser.h>
#include <QDebug>

using namespace std;

namespace {

    QString complexToExpr(const Value& v) {
        const double& real = v.real();
        const double& imag = v.imag();

        if((real == 0.f ) && (imag == 0.f)) {
            return "0";
        }

        if(imag == 0.f) {
            return QString::number(real);
        }

        QString convert;

        if(real != 0.f) {
             convert.append(QString::number(real));
        }

        if(imag > 0.f) {
            if(real != 0.f) {
                convert.append(" + ");
            }
            if(imag == 1.f) {
                convert.append("i");
            }
            else {
                convert.append(QString::number(imag))
                        .append("*i");
            }
        }
        else if(imag < 0.f) {
            if(imag == -1.f) {
                convert.append("-i");
            }
            else {
                convert.append(" - ")
                        .append(QString::number(abs(imag)))
                        .append("*i");
            }
        }
        return convert;
    }

}

mup::ParserX QMatrixLibrary::parser = mup::ParserX();


QMatrixLibrary:: QMatrixLibrary () : tab(QMap<QString, UserMatrix>())
{}


QMatrixLibrary::  QMatrixLibrary (const QMatrixLibrary & lib) {
    for(const auto& [ name, userMtx ] : lib) {
        tab.insert(name, userMtx);
    }
}


unsigned long int QMatrixLibrary:: size () const {
    return tab.size();
}


bool QMatrixLibrary:: isEmpty () const {
    return size() == 0;
}


void QMatrixLibrary:: clear () {
    tab.clear();
}


bool QMatrixLibrary:: exist (const QString& name) const {
    //return (tab.count(name) != 0);
    return tab.contains(name);
}


bool QMatrixLibrary:: isName(const QString & chain) const {
    unsigned int i = 1, s = chain.length();

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


const Matrix& QMatrixLibrary:: addMatrix (const QString& name, const  UserInputs& entries) {
    if(isName(name)) {

        VectorX values;

        for(const QString& entry : entries) {
            parser.SetExpr(entry.toStdString());
            values.push_back(parser.Eval().GetComplex());
        }

        Matrix newMatrix(entries.getRows(), entries.getCols(), values);

        auto inserted = tab.insert( name, {  newMatrix,
                              newMatrix.determinant(),
                              entries                   });

        return inserted.value().matrix;
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
        return Matrix::matrix_null;
    }
}


void QMatrixLibrary:: addMatrix (const QString& name, const Matrix& m) {
    if(isName(name)) {

        UserInputs defaults(m.getNbRows(), m.getNbCols());

        for(unsigned int i = 0; i < m.getNbRows() * m.getNbCols(); ++i) {
            defaults.put(complexToExpr(m.getVal(i)));
        }

        tab.insert( name, { m,
                            m.determinant(),
                            defaults });
    }
    else {
        cout << "Nom de matrice non autorisé, "
             << "veuillez choisir un autre..."<< endl;
    }
}


const Matrix* QMatrixLibrary:: find_matrix (const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name].matrix
        : nullptr;
}


Matrix* QMatrixLibrary:: find_matrix (const QString& name) {
    return const_cast<Matrix*>(static_cast<const QMatrixLibrary&>(*this).find_matrix(name));
}


const Value* QMatrixLibrary:: find_determinant (const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name].determinant
        : nullptr;
}


Value* QMatrixLibrary:: find_determinant (const QString& name) {
    return const_cast<Value*>(static_cast<const QMatrixLibrary&>(*this).find_determinant(name));
}


const UserInputs* QMatrixLibrary::find_inputs(const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name].entries
        : nullptr;
}

UserInputs* QMatrixLibrary::find_inputs(const QString& name) {
    return const_cast<UserInputs*>(static_cast<const QMatrixLibrary&>(*this).find_inputs(name));
}

const UserMatrix* QMatrixLibrary::find_all(const QString& name) const {
    return exist(name)
        ? &const_cast<QMatrixLibrary&>(*this).tab[name]
        : nullptr;
}

UserMatrix* QMatrixLibrary::find_all(const QString& name) {
    return const_cast<UserMatrix*>(static_cast< const QMatrixLibrary&>(*this).find_all(name));
}



void QMatrixLibrary:: erase (const QString & name) {
    tab.remove(name);
    if(exist(name)) {
        cout << "Suppression non effectuée" << endl;
    }
}


const QMap<QString, UserMatrix>& QMatrixLibrary:: data () const {
    return tab;
}


QMap<QString, UserMatrix>::const_key_value_iterator QMatrixLibrary::begin() const {
    return tab.keyValueBegin();
}

QMap<QString, UserMatrix>::const_key_value_iterator QMatrixLibrary::end() const {
    return tab.keyValueEnd();
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
