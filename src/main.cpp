
#include <QApplication>
#include <QDir>
#include "MainWindow.h"
#include "LibraryWindow.h"

#if defined(Q_OS_MACX)

bool a = QDir::setCurrent("../../../data");
const QString C_PATH = QDir::currentPath();

#endif



using namespace std;


int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    //MainWindow* win = new MainWindow;
    LibraryWindow* win = new LibraryWindow(NULL);
    win->show();
    return app.exec();
}


