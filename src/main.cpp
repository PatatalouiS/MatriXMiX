
#include <QApplication>
#include "MainWindow.h"
#include <iostream>
//#include <QDir>
//#include <QDebug>
//#include "MainWindow.h"
//#include "LibraryWindow.h"
#include "Matrix.h"
#include "MatriXMiXTXT.h"
#include "MatrixLibrary.h"
#include "Fraction.h"


int main (int argc, char* argv[])
{
  Fraction f;
  double d1 = 5.5;
  double d2 = -9.66666666666;

  cout << 1 - d2 - floor(d2) << endl;
  f = f.double2Fraction(d1);
  cout << f << endl;
  f = f.double2Fraction(d2);
  cout << f << endl;


  QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainWindow* win = new MainWindow;
    win->show();
    return app.exec();










   /* MatrixLibrary lib;
    vector<string> resultat;
    lib.cleanSaves();
    string expression("A+2+B");
    resultat = lib.decoupe(expression);*/


    //cout << lib.isCalculableExpression(expression) << endl;

    /*
    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{5,0,0,1});
    Matrix res;

    lib.addMatrix("identite",a);
    lib.addMatrix("matrice",b);
    lib.saveMatrix("identite");
    lib.saveMatrix("matrice");


    // resultat = lib.decoupe("matrice^-1");

    lib.polonaise("matrice*2+(identite^-1)",resultat);

    for(unsigned int i = 0 ; i < resultat.size() ; i++)
    {
        cout << resultat[i]<<endl;
    }




   res = lib.expressionCalcul("identite*2+matrice^-1");
   // res=a^-1;
   cout << res << endl;

*/



    //lib.addMatrix("I+B",res);
    //lib.saveMatrix("I+B");

    //cout << lib.readMatrix("I+B") << endl << endl;


}


