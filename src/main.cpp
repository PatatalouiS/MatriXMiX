
#include <QApplication>
#include "MainWindow.h"
//#include "MatrixLibrary.h"

int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();

//        Matrix e (10,10, {1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,
//                  1,1,1,1,1,1,1,1,1,1,});

//        e.diagonalise();





//    return 0;
}

