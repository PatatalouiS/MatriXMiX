
//#include <QApplication>
#include <iostream>
//#include <QDir>
//#include <QDebug>
//#include "MainWindow.h"
//#include "LibraryWindow.h"
#include "Matrix.h"
#include "MatriXMiXTXT.h"
#include "MatrixLibrary.h"

using namespace std;


//extern const string APP_PATH = QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();

int main (int argc, char* argv[])
{

    MatrixLibrary lib;
    lib.cleanSaves();

    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{0,0,0,1});

    Matrix res(2,2);
    res << "7,7,3,45";
    cout << res <<endl;

    lib.addMatrix("identite",a);
    lib.addMatrix("matrice",b);
    //lib.saveMatrix("identite");
    //lib.saveMatrix("matrice");

    res = lib.expressionCalcul("identite+3+matrice");
    cout << res << endl;


    return 0;
}


