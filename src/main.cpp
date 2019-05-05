
#include <QApplication>
#include "MainWindow.h"
#include "LibraryWindow.h"
#include "MatriXMiXTXT.h"
#include "MatrixLibrary.h"
#include "Fraction.h"
#include <stdlib.h>
using namespace std;

int main ()
{
    Polynomial p3(2,{6,5,1});
    Polynomial p4(2,{2,3,1});
    Polynomial res;

   /* res = p3 - p4;
    cout<<res<<" "<<res.degree;*/

   p3.testRegression();



    return 0;
}


/*int main (int argc, char* argv[])
{
    //Matrix a; a.testRegression();
    //QApplication app(argc, argv);
    //MainWindow mainWindow;
    //mainWindow.show();
    //return app.exec();
}*/


