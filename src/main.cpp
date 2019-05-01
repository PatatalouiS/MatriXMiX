
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
 /* Fraction f;
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
    win->showMinimized();
    return app.exec();*/

    MatrixLibrary lib;
    Matrix a (2,2,{1,0,0,1});
    Matrix b (2,2,{5,0,0,1});
    Matrix res;

    lib.addMatrix("identite",a);
    lib.addMatrix("matrice",b);

    //lib.saveFile("../data/sauvegarde.txt");
    lib.readFile("../data/sauvegarde.txt");
    lib.print();



    return 0;

}


