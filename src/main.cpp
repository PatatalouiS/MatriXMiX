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

}
