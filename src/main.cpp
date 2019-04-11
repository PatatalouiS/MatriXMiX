
#include <QApplication>
#include <iostream>
<<<<<<< HEAD
#include <QDir>
#include <QDebug>
#include "MainWindow.h"
#include "LibraryWindow.h"





using namespace std;

extern const string APP_PATH = QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();

int main (int argc, char* argv[])
{
    QApplication app(argc, argv);

    QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();

    //MainWindow* win = new MainWindow;
    LibraryWindow* win = new LibraryWindow(nullptr);
    win->show();
    return app.exec();
=======
#include "MatriXMiXTXT.h"
#include "VectorX.h"
#include "Polynomial.h"
#include "Matrix.h"

using namespace std;


int main (void)
{

    Matrix a(3,3,{1,1,1,1,1,1,1,1,1});

    cout << a << endl;

    a.allEigen();

    if (a.isDiagonalisable())
        cout << "Diagonalisable" << endl;
    else
        cout << "Pas diagonalisable" << endl;

    return 0;

>>>>>>> origin/calcul_matriciel_tarik
}


