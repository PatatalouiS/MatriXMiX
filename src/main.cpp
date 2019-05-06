
#include <QApplication>
#include "MainWindow.h"
#include "LibraryWindow.h"
#include "MatrixLibrary.h"
#include <stdlib.h>
using namespace std;

int main (int argc, char* argv[])
{

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();


   /* MatrixLibrary lib;
    Matrix a(2,2,{1,2,3,4});
    lib.addMatrix("A",a);
    if(lib.isCalculableExpression("((A+A))") == "calculable")
    cout<< lib.calculateExpression("((A+A))")<<endl ;*/

   /* vector<string> res;
    lib.polish("((A+A))",res);

    for (unsigned int i=0;i<res.size();i++)
    {
         cout<< res[i] << endl;
    }*/


}
