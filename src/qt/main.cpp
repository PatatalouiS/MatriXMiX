#include <QApplication>
#include "../qt/MainWindow.h"
#include "../qt/LibraryWindow.h"
#include "../maths/MatrixLibrary.h"
#include <stdlib.h>
using namespace std;

int main (int argc, char* argv[])

{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();

}
