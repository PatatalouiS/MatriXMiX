
#include <QApplication>
#include "MainWindow.h"
#include "LibraryWindow.h"
#include "MatriXMiXTXT.h"
#include "MatrixLibrary.h"
#include "Fraction.h"
#include <stdlib.h>
using namespace std;

/*int main (int argc, char* argv[])
{

    Matrix a(10,10,{1,0,0,0,0,0,0,0,0,0,
                  0,1,0,0,0,0,0,0,0,0,
                  0,0,1,0,0,0,0,0,0,0,
                  0,0,0,1,0,0,0,0,0,0,
                  0,0,0,0,1,0,0,0,0,0,
                  0,0,0,0,0,1,0,0,0,0,
                  0,0,0,0,0,0,1,0,0,0,
                  0,0,0,0,0,0,0,1,0,0,
                  0,0,0,0,0,0,0,0,1,0,
                  0,0,0,0,0,0,0,0,0,1 });

    Matrix b(3,3,{1,2,3,4,5,6,7,8,0});
    Matrix p(3,3,{0.5,0.25,0.2,0.25,0.5,0.2,0.2,0.5,0.25});


    Matrix d(10,10,{2.9104602,-0.99999999,99999999,0.55555,0,888,0.524,-0.33333,0.39715,0.461654,
             0.99999999,-9,0.99999999,0.55555,0,888,0.524,-0.33333,-0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,-0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,-0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,-0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,-0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,0.33333,0.39715,0.461654,
             0.9104602,9,99999999,0.55555,0,888,0.524,0.33333,0.39715,0.461654,
             0.9104602,9,999999,0.55555,0,888,0.524,0.33333,0.39715,0.461654});
    QColor c(0,0,0,0);
    QApplication app(argc, argv);

    app.setQuitOnLastWindowClosed(false);
    ShowMatrixWidget * fenetre = new ShowMatrixWidget;
    fenetre->computeImgMatrix(d,20,c);
    fenetre->show();

    return app.exec();



    MatrixLibrary lib;
    vector<string> resultat;
    lib.cleanSaves();
    string expression("A+2+B");
    resultat = lib.decoupe(expression);


    //cout << lib.isCalculableExpression(expression) << endl;


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





    //lib.addMatrix("I+B",res);
    //lib.saveMatrix("I+B");

    //cout << lib.readMatrix("I+B") << endl << endl;

}*/


int main (int argc, char* argv[])
{
    //Matrix a; a.testRegression();
    MatrixLibrary lib; lib.testRegression();
    //QApplication app(argc, argv);
    //MainWindow mainWindow;
    //mainWindow.show();
    //return app.exec();
}


