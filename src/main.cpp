
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
    vector<string> resultat;
    lib.cleanSaves();
    string expression1("((objet-1)+x*tmp/8)/25-12");

    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{0,0,0,1});
    Matrix res;

    lib.addMatrix("identite",a);
    lib.addMatrix("matrice",b);
    lib.saveMatrix("identite");
    lib.saveMatrix("matrice");



   /* lib.polonaise("1+5*indentite",resultat);

    for(unsigned int i = 0 ; i < resultat.size() ; i++)
    {
        cout << resultat[i]<<endl;
    }*/




   res = lib.expressionCalcul("identite+3+matrice");
   // res=a^-1;
   cout << res << endl;

    return 0;

}


