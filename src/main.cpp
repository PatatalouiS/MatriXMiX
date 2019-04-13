
#include <QApplication>
#include <iostream>
#include <QDir>
#include <QDebug>
#include "MainWindow.h"
#include "LibraryWindow.h"
#include <Dense>


using namespace std;


extern const string APP_PATH = QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();

int main (int argc, char* argv[])
{
    MatrixLibrary lib;
    vector<string> resultat;

    string expression1("((objet-1)+x*tmp/8)/25-12");

    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{0,0,0,1});
    Matrix res;

    lib.addMatrix("identite",a);
    lib.addMatrix("matriceb",b);


    res = lib.expressionCalcul("identite-matriceb");

    cout << res;


    return 0;

}


