
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

    /*bool r;
    r=lib.priorite_sup_egal("-","+");
    if (r){
        cout<<"true";
    }else cout<<"false";*/


    lib.addMatrix("identite",a);
    lib.addMatrix("matriceb",b);
    /*const Matrix* resu; r=lib.priorite_sup_egal("-","+");
    if (r==1){
        cout<<true;
    }else cout<<false;

    resu=lib.find("identite");
    cout<<*resu;
    lib.print();*/

    //cout << "cout avant appel à polonaise " << endl  ;



    //lib.polonaise("variable=((objet-1)+x*tmp/8)/25-1",resultat);

    res=lib.expressionCalcul("identite*matriceb");

    cout<<res;

    /*for (int i=0; i<resultat.size(); i++)
    {
        cout<<resultat[i]<<" ";
    }*/

    return 0;

}


